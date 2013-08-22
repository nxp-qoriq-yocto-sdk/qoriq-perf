/*
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * This software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "qoriq_event_config.h"
#include "qoriq_perf.h"
#include "qoriq_cntrs.h"
#include "qoriq_counters.h"
#include <linux/io.h>

/* maintains information on each sub-device managed by the driver */
extern struct dbg_devices dbg_dev;

static inline void clr_counter_in_use(int base_ind);
static NOINLINE int qoriq_get_counter(struct qoriq_counter_indx *cnt_indx,
								u32 potential_counters);
static NOINLINE int get_available_cntr_from_potential(int potential_counters);
static NOINLINE int qoriq_get_overflow_counter(u32 base);

/*  Qoriq Counters State */
static struct qoriq_cntrs_state {
	/* virtualized counters */
	u32 v_counter[QORIQ_EPU_NUM_COUNTERS];
	/* overflow counters map; maps a base counter to it's overflow cntr ind*/
	int cntr_2_off_cntr_map[QORIQ_EPU_NUM_COUNTERS];
	/* overflow counters map; maps a base counter to it's overflow cntr ind*/
	int off_cntr_2_cntr_map[QORIQ_EPU_NUM_COUNTERS];
	/* Used to protect v_counter array */
	spinlock_t vc_lock;
	/* keep track of counter usage */
	unsigned long counters_in_use;
	/* keep track of DPAA resources in use */
} qoriq_cntrs;


NOINLINE void qoriq_initialize_cnt_ind(struct qoriq_counter_indx *ind)
{
	ind->base = 0;
	ind->overflow = 0;
}

/* atomic update of the counters in use */
NOINLINE void qoriq_set_counter_in_use(struct qoriq_counter_indx *ctr)
{
	set_bit(QORIQ_EPU_NUM_COUNTERS - 1 - ctr->base, 
				&qoriq_cntrs.counters_in_use);
	set_bit(QORIQ_EPU_NUM_COUNTERS - 1 - ctr->overflow,
				&qoriq_cntrs.counters_in_use);
	
	qoriq_cntrs.cntr_2_off_cntr_map[ctr->base] = ctr->overflow;
	
	qoriq_cntrs.off_cntr_2_cntr_map[ctr->overflow] = ctr->base;
}

NOINLINE int qoriq_get_perf_event_ind(int ctr)
{
	/* for the non-overflow counter case, this would just
	 * return ctr */
	return qoriq_cntrs.off_cntr_2_cntr_map[ctr];
}

NOINLINE void qoriq_clear_counter_in_use(int base_ind)
{
	clr_counter_in_use(base_ind);
	qoriq_cntrs.v_counter[base_ind] = 0;
}

/* atomic update of the counters in use */
static inline void clr_counter_in_use(int base_ind)
{
	int overflow_ind = qoriq_cntrs.cntr_2_off_cntr_map[base_ind];
	
	clear_bit(QORIQ_EPU_NUM_COUNTERS - 1 - base_ind,
			&qoriq_cntrs.counters_in_use);
	clear_bit(QORIQ_EPU_NUM_COUNTERS - 1 - overflow_ind, 
			&qoriq_cntrs.counters_in_use);

	qoriq_cntrs.cntr_2_off_cntr_map[base_ind] = -1;
	qoriq_cntrs.off_cntr_2_cntr_map[overflow_ind] = -1;
}

/* Increment the virtual counter and handle roll over */
NOINLINE int qoriq_v_counter_inc(int ctr)
{
	int ret;

	spin_lock(&qoriq_cntrs.vc_lock);
	qoriq_cntrs.v_counter[ctr]++;
	ret = (qoriq_cntrs.v_counter[ctr] & QORIQ_EPU_V_COUNTER_OVFLOW_VALUE) ? 
											1 : 0;
	if (ret)
		qoriq_cntrs.v_counter[ctr] = 0;
	spin_unlock(&qoriq_cntrs.vc_lock);

	return ret;
}

/* Acquires the selected extended counter value */
NOINLINE u64 qoriq_v_counter_read(u32 ctr)
{
	u64 val;
	u32 count_base;
	u32 count_of;
	
	spin_lock(&qoriq_cntrs.vc_lock);

	count_base = in_be32(EPU_REG_PTR(epctr[ctr]));
	
	/*ASSERT qoriq_cntrs.cntr_2_off_cntr_map[ctr] != -1 */
	if (qoriq_cntrs.cntr_2_off_cntr_map[ctr] != -1)
		count_of =
			in_be32(EPU_REG_PTR(epctr[qoriq_cntrs.cntr_2_off_cntr_map[ctr]]));
	else {

		/* the following (commented out) can occur when we run out of counters
		 * for the event. So...apparently not unexpected.
		 */
/*		printk(KERN_ERR 
		"UNEXPECTED: Overflow counter for counter %d has not been configured",
			ctr);
*/		
		val = 0;
		goto exit;
	}
	
	val = 
	  (unsigned long long)
	  	  (qoriq_cntrs.v_counter[qoriq_cntrs.cntr_2_off_cntr_map[ctr]])
					<< QORIQ_EPU_COUNTER_NUM_BITS * QORIQ_EPU_NUM_CHAINED | 
						count_of << QORIQ_EPU_COUNTER_NUM_BITS |
						count_base;	
exit:
	spin_unlock(&qoriq_cntrs.vc_lock);

	return val;
}

/* Sets the selected extended counter with a value */
NOINLINE void qoriq_v_counter_write(u32 ctr, u64 val)
{
	spin_lock(&qoriq_cntrs.vc_lock);
	out_be32(EPU_REG_PTR(epctr[ctr]),
			val & QORIQ_EPU_COUNTER_MASK);

	/* ASSERT qoriq_cntrs.cntr_2_off_cntr_map != -1 */
	if (qoriq_cntrs.cntr_2_off_cntr_map[ctr] != -1)
		out_be32(EPU_REG_PTR(epctr[qoriq_cntrs.cntr_2_off_cntr_map[ctr]]),
			(val & QORIQ_EPU_COUNTER_OF_MASK) >> QORIQ_EPU_COUNTER_NUM_BITS);

	qoriq_cntrs.v_counter[ctr] = 
					val >> QORIQ_EPU_COUNTER_NUM_BITS*QORIQ_EPU_NUM_CHAINED;
	
	spin_unlock(&qoriq_cntrs.vc_lock);
}

/*
 * "Reset Counters to be Used" 
 */
NOINLINE void qoriq_init_epu_counter(int epu_ctr_index)
{	
printk(KERN_DEBUG "A epu_ctr_index=%x", epu_ctr_index);

	/* Reset counter's control register/disable individual counter */
	out_be32(EPU_REG_PTR(epccr[epu_ctr_index]), 0);
	
	/* Reset counter's value */
	qoriq_v_counter_write(epu_ctr_index,0);
	
	/* Reset counter's capture value */	
	out_be32(EPU_REG_PTR(epcapr[epu_ctr_index]), 0);
	
//	/* Repeat for overflow counter */
//
//	/* Reset counter's control register/disable individual counter */	
//	out_be32(
//		EPU_REG_PTR(epccr[qoriq_cntrs.cntr_2_off_cntr_map[epu_ctr_index]]), 0);
//
//	/* Reset counter's value */
//	qoriq_v_counter_write(qoriq_cntrs.cntr_2_off_cntr_map[epu_ctr_index],0);
//	
//	/* Reset counter's capture value */
//	out_be32(
//	 EPU_REG_PTR(epcapr[qoriq_cntrs.cntr_2_off_cntr_map[epu_ctr_index]]), 0);

}

/*
 * Search for the next available counter
 * Returns 0 in success
 */
NOINLINE int qoriq_get_available_counter(const struct epu_counter *cnt, 
										struct qoriq_counter_indx *in_cnt_index)
					//				int *cnt_index, int *of_cnt_index)	
{
	u32 potential_counters;
	u32 cnt_index;
	u32 of_cnt_index;
	
	/*
	 * Look for potential unused counters for this event type
	 * limited by epu_counter[event].cnt_mask
	 */
	potential_counters = 
				(qoriq_cntrs.counters_in_use & cnt->cnt_mask) ^ cnt->cnt_mask;

	if (!potential_counters)
		return -1;
	
/*	ret = qoriq_get_counter(cnt_index, potential_counters);
	
	
	if (ret < 0)
		return -1;
*/
				
	cnt_index = get_available_cntr_from_potential(potential_counters);

	if (cnt_index < 0)
		return -1;

	of_cnt_index = qoriq_get_overflow_counter(cnt_index);

	if (of_cnt_index < 0)
		return -1;

	in_cnt_index->base = cnt_index;
	in_cnt_index->overflow = of_cnt_index;

	return 0;
}

NOINLINE void qoriq_cntrs_init_cntr(struct qoriq_counter_indx *cnt_index)
{
	cnt_index->base = -1;
	cnt_index->overflow = -1;
}
/*
 * Initialize all the Qoriq counter state information.
 * Called only once at module load.
 */
NOINLINE void qoriq_cntrs_state_init(void)
{
	int i;		
	spin_lock_init(&qoriq_cntrs.vc_lock);

	for (i = 0; i < QORIQ_EPU_NUM_COUNTERS; ++i) {
		qoriq_cntrs.v_counter[i] = 0;
		qoriq_cntrs.cntr_2_off_cntr_map[i] = -1;
		qoriq_cntrs.off_cntr_2_cntr_map[i] = -1;
	}
	
	qoriq_cntrs.counters_in_use = 0;
}

/* Return available counter starting from the largest index. If none available
 * return < 0 */
static NOINLINE int get_available_cntr_from_potential(int potential_counters)
{
	int i = QORIQ_EPU_NUM_COUNTERS-1;
	int ret = -1;	
	
	while (potential_counters) {
		if (potential_counters & 1) {
			ret = i;
			break;
		}
		
		i--;
		potential_counters >>= 1;
	}

	return ret;
}

/*
 * Return overflow counter for given counter.
 * -1 for fail.
 */
static NOINLINE int qoriq_get_overflow_counter(u32 cnt_index)
{
	const struct epu_counter *ov_cnt=NULL;
	u32 cntrs_in_use;
	int of_cnt_index;
	u32 potential_counters;

	ov_cnt = epu_counter_from_code(EPU_EVENT_BASE_CNT + cnt_index);

	if (ov_cnt == NULL) {
		printk(KERN_ERR "Unable to allocate overflow performance counter");
		return -1;
	}
		
	/*
	 * Look for potential unused counters for this event type
	 * limited by epu_counter[event].cnt_mask
	 */
	
	/* consider the "base" counter as in use*/

	cntrs_in_use = qoriq_cntrs.counters_in_use | (1 << cnt_index);
	potential_counters = 
					(cntrs_in_use & ov_cnt->cnt_mask) ^ ov_cnt->cnt_mask;
	
	if (!potential_counters)
		return -1;

	/* Look for an available counter starting from the largest index. */
	of_cnt_index = get_available_cntr_from_potential(potential_counters); 

	return of_cnt_index;
}

/* Return 0 for success */
/*
static NOINLINE int qoriq_get_counter(struct qoriq_counter_indx *cnt_indx,
								u32 potential_counters)
{
	u32 base;
	u32 overflow;
	
	base = get_available_cntr_from_potential(potential_counters);

	if (base < 0) 
		return -1;
	
	overflow = qoriq_get_overflow_counter(base);

	if (overflow < 0)
		return -1;
	
	cnt_indx->base = base;
	
	cnt_indx->overflow = overflow;
	
	return 0;
}
*/

/*
 * Perform the configuration to enable this counter.
 * Return 0 on success
 */
void qoriq_epu_configure_counter(struct qoriq_event_config *ev_cfg)
{
	const struct epu_counter *ec=NULL;
	const struct epu_counter *ec_of=NULL;
	int epu_ctr_index;
	int epu_of_ctr_index;
	
	u32 val = 0;


	/* TODO: ASSERT the following are not NULL
	 */
	ec = ev_cfg->epu_counter;
	epu_ctr_index = ev_cfg->counter_ind.base;
	epu_of_ctr_index = ev_cfg->counter_ind.overflow;

	ec_of = epu_counter_from_code(EPU_EVENT_BASE_CNT + epu_ctr_index);

	if (ec == NULL) {
		printk(KERN_ERR "Unexpected NULL pointer when configuring EPU");
		return;
	}
	/* platform cycles are a special case */
	if (ec->code != PLATFORM_CYCLES) {
		/* EPU input mux ISEL = mux val */
		val = ec->cnt_mux << EPU_EPIMCR_ISEL_SHIFT;

		out_be32(EPU_REG_PTR(epimcr[epu_ctr_index]), val);

		val = (3 << EPU_EPCCR_CONTROL_ISEL_SHIFT); // |
			//	(1 << EPU_EPCCR_CONTROL_EDE_SHIFT); 
	}

	out_be32(EPU_REG_PTR(epccr[epu_ctr_index]), val);

	/**********************************/
	/* configure the overflow counter */
	/**********************************/

	val = ec_of->cnt_mux << EPU_EPIMCR_ISEL_SHIFT;
	out_be32(EPU_REG_PTR(epimcr[epu_of_ctr_index]), val);

	/* EPU counter ISEL = EN |use mux src | EDE = rising
	 * 							| AC = interrupt on overflow */
	val = 1 << EPU_EPCCR_CONTROL_EN_SHIFT |
			3 << EPU_EPCCR_CONTROL_ISEL_SHIFT |
			1 << EPU_EPCCR_CONTROL_EDE_SHIFT |
			1 << EPU_EPCCR_CONTROL_AC_SHIFT;	
		
	out_be32(EPU_REG_PTR(epccr[epu_of_ctr_index]), val);
}
