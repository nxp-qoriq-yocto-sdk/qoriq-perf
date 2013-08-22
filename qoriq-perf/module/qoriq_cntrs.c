/*
 * Copyright (C) 2010, 2011, 2012 Freescale Semiconductor, Inc.
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

#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/of_platform.h>
#include <asm/irq_regs.h>

#include "qoriq_cntrs.h"
#include "qoriq_event_config.h"
#include "qoriq_perf.h"
#include "qoriq_raw_events.h"
#include "corenet_events.h"
#include "dpaa_events.h"
#include "ddr_events.h"
#include "npc_events.h"
#include "epu_events.h"
#include "epu_counters.h"
#include "ddr_cmplx_events.h"
#include "qoriq_hitgen_config.h"
#include "qoriq_counters.h"

/* maintains information on each sub-device managed by the driver */
extern struct dbg_devices dbg_dev;

extern void record_and_restart(struct perf_event *event, u64 val );
extern NOINLINE void qoriq_ddr_enable_events(u32 ddr_cntlr_ind, int enable);
extern void qoriq_epu_configure_counter(struct qoriq_event_config *ev_cfg);

/*  Qoriq Counters State */
static struct qoriq_events_state {
	struct qoriq_event_config ev_conf[QORIQ_NUM_EVENT_CONFIGURATIONS];
	/* Used to protect event config array */
	spinlock_t ev_lock;
	/* virtualized counters */
	/* event associated with counter */
	struct perf_event *perf_event[QORIQ_EPU_NUM_COUNTERS];
	/* keep track of DPAA resources in use */
	u8 pmg_sel_ref[DPAA_NUM_GENERAL_EV];
	u8 refev_sel[DPAA_NUM_REF_EV];
} qoriq_events;

/*
 * Initialize all the Qoriq counter state information.
 * Called only once at module load.
 */
static NOINLINE void qoriq_event_state_init(void)
{
	int i;
			
	spin_lock_init(&qoriq_events.ev_lock);

	qoriq_cntrs_state_init();
	
	qoriq_event_config_init(qoriq_events.ev_conf);
	
	for (i = 0; i < QORIQ_EPU_NUM_COUNTERS; ++i) {		
		qoriq_init_epu_counter(i);
		qoriq_events.perf_event[i] = NULL;
	}

	for (i = 0; i < DPAA_NUM_GENERAL_EV; ++i)
		qoriq_events.pmg_sel_ref[i] = 0;
	for (i = 0; i < DPAA_NUM_REF_EV; ++i)
		qoriq_events.refev_sel[i] = 0;
	
}

/*
 * pass in event->hw.config, return corresponding counter index of event if it
 * is already configured. If it is not already configured, return -1.
 */
NOINLINE int qoriq_perf_event_from_id(u64 in_evt_id)
{
	int i;
	struct perf_event *tmp_event = NULL;
	
	for (i = 0; i < QORIQ_EPU_NUM_COUNTERS; i++) {
		tmp_event = qoriq_events.perf_event[i];
		
		if (tmp_event && tmp_event->hw.config == in_evt_id) {
			return i;
		}
	}
	
	return -1;
}


static NOINLINE int dpaa_general_select_counter(struct perf_event *event,
		struct qoriq_event_config *ev_cfg)
{
	int ret = 1;
	int i;
	int found = 0;
	const struct epu_counter *epu_counter;
	struct qoriq_counter_indx counter_index;
	u32 val;
	u32 pmg_sel[DPAA_NUM_GENERAL_EV];

	ev_cfg->dpaa.event = dpaa_event_from_code(event->hw.config);
	if (!ev_cfg->dpaa.event)
		goto exit;

	val = in_be32(DPAA_REG_PTR(dppescr));
	pmg_sel[0] = (val & DPAA_DPPESCR_PMG0_SEL_MASK) >>
												DPAA_DPPESCR_PMG0_SEL_SHIFT;
	pmg_sel[1] = (val & DPAA_DPPESCR_PMG1_SEL_MASK) >>
												DPAA_DPPESCR_PMG1_SEL_SHIFT;

	/* look for an already set compatible PMGn_SEL */
	for (i = 0; i < DPAA_NUM_GENERAL_EV; i++) {
		if (qoriq_events.pmg_sel_ref[i] > 0 && pmg_sel[i] == ev_cfg->dpaa.event->word) {
			/* check if EPU counter available for the epu_event_code
			 * [pmgn index] */
			epu_counter = epu_counter_from_code(
										ev_cfg->dpaa.event->epu_event_code[i]);
			ret = qoriq_get_available_counter(epu_counter, &counter_index);
			if (!ret) {
				found = 1;
				break;
			}
		}
	}

	/* look for an unused PMGn_SEL */
	if (!found) {		
		for (i = 0; i < DPAA_NUM_GENERAL_EV; i++) {
			if (qoriq_events.pmg_sel_ref[i] == 0) {
				/* check if EPU counter available for the epu_event_code
				 * 	[Bn index] */
				epu_counter = epu_counter_from_code(
										ev_cfg->dpaa.event->epu_event_code[i]);
				ret = qoriq_get_available_counter(epu_counter, &counter_index);
				if (!ret) {
					found = 1;
					break;
				}
			}
		}
	}

	if (found) {
		ev_cfg->counter_ind = counter_index;
//		ev_cfg->counter_index = counter_index;
//		ev_cfg->of_counter_index = of_cnt_index;
		ev_cfg->epu_counter = epu_counter;
		ev_cfg->dpaa.event_selection_type = EVENT_SELECTION_GENERAL;
		ev_cfg->dpaa.index = i;
		ret = 0;
		
	}
exit:
	return ret;
}

static NOINLINE int dpaa_reference_select_counter(struct perf_event *event,
		struct qoriq_event_config *ev_cfg)
{
	int ret = 1;
	int i;
	int found = 0;
	const struct epu_counter *epu_counter = 0;
	//int counter_index = 0;
	//int of_cnt_index;
	struct qoriq_counter_indx cnt_index;
	
	u32 val;
	u32 refev_sel[DPAA_NUM_REF_EV];

	
	ev_cfg->dpaa.event = dpaa_event_from_code(event->hw.config);
	if (!ev_cfg->dpaa.event)
		goto exit;
	
	val = in_be32(DPAA_REG_PTR(dprescr[0]));
	refev_sel[0] = (val & DPAA_DPRESCR1_REFEV0_SEL_MASK) >>
												DPAA_DPRESCR1_REFEV0_SEL_SHIFT;
	refev_sel[1] = (val & DPAA_DPRESCR1_REFEV1_SEL_MASK) >>
												DPAA_DPRESCR1_REFEV1_SEL_SHIFT;
	val = in_be32(DPAA_REG_PTR(dprescr[1]));
	refev_sel[2] = (val & DPAA_DPRESCR2_REFEV2_SEL_MASK) >>
												DPAA_DPRESCR2_REFEV2_SEL_SHIFT;
	refev_sel[3] = (val & DPAA_DPRESCR2_REFEV3_SEL_MASK) >>
												DPAA_DPRESCR2_REFEV3_SEL_SHIFT;

	for (i = 0; i < DPAA_NUM_REF_EV; i++) {
		if (!qoriq_events.refev_sel[i]) {
			/* check if EPU counter available for this reference event */
			epu_counter = epu_counter_from_code(DP_RefEv0 + i);
			ret = qoriq_get_available_counter(epu_counter, &cnt_index);
			if (!ret) {
				found = 1;
				break;
			}
		}
	}

	if (found) {
		ev_cfg->counter_ind = cnt_index;
	//	ev_cfg->counter_index = counter_index;
	//	ev_cfg->of_counter_index = of_cnt_index;
		ev_cfg->epu_counter = epu_counter;
		ev_cfg->dpaa.event_selection_type = EVENT_SELECTION_REFERENCE;
		ev_cfg->dpaa.index = i;
		ret = 0;		
	}
exit:
	return ret;
}

static NOINLINE int dpaa_select_counter(struct perf_event *event,
		struct qoriq_event_config *ev_cfg)
{
	int ret;

	ret = dpaa_general_select_counter(event, ev_cfg);
	if (ret) {
		/* try for a reference counter */
		ret = dpaa_reference_select_counter(event, ev_cfg);
	}

	return ret;
}

static int dpaa_configure_counter(const struct qoriq_event_config *ev_cfg)
{
	int ret = -1;
	u32 val;
	u32 code;
	u32 ind = 0;
	
	switch (ev_cfg->dpaa.event_selection_type) {
	case EVENT_SELECTION_REFERENCE:
	{

		ind = ev_cfg->dpaa.index;

		code = ev_cfg->dpaa.event->code - QORIQ_EVENT_BASE_DATAPATH;
		
		if (ind >=0 && ind < 2) {
			val = in_be32(DPAA_REG_PTR(dprescr[0]));
		}
		else if (ind >= 2 && ind < 4) {
			val = in_be32(DPAA_REG_PTR(dprescr[1]));
		}
		else {
			printk(KERN_ERR 
			 "qoriq-cntrs: DPAA Reference (REFEVn_SEL) index out of range.\n");
			goto exit;
		}

		switch (ev_cfg->dpaa.index) {
		case 0:
			qoriq_events.refev_sel[0] = 1;
			val &= ~DPAA_DPRESCR1_REFEV0_SEL_MASK;
			val |= (code << DPAA_DPRESCR1_REFEV0_SEL_SHIFT);
			out_be32(DPAA_REG_PTR(dprescr[0]), val);
			break;
		case 1:
			qoriq_events.refev_sel[1] = 1;
			val &= ~DPAA_DPRESCR1_REFEV1_SEL_MASK;
			val |= (code << DPAA_DPRESCR1_REFEV1_SEL_SHIFT);
			out_be32(DPAA_REG_PTR(dprescr[0]), val);
			break;
		case 2:
			qoriq_events.refev_sel[2] = 1;
			val &= ~DPAA_DPRESCR2_REFEV2_SEL_MASK;
			val |= (code << DPAA_DPRESCR2_REFEV2_SEL_SHIFT);
			out_be32(DPAA_REG_PTR(dprescr[1]), val);
			break;
		case 3:
			qoriq_events.refev_sel[3] = 1;
			val &= ~DPAA_DPRESCR2_REFEV3_SEL_MASK;
			val |= (code << DPAA_DPRESCR2_REFEV3_SEL_SHIFT);
			out_be32(DPAA_REG_PTR(dprescr[1]), val);
			break;
		default:
			printk(KERN_ERR 
			 "qoriq-cntrs: DPAA Reference (REFEVn_SEL) index out of range.\n");
			goto exit;
		}
	}
	break;
	
	case EVENT_SELECTION_GENERAL:
	{
		val = in_be32(DPAA_REG_PTR(dppescr));

		switch (ev_cfg->dpaa.index) {
		case 0:
			qoriq_events.pmg_sel_ref[0]++;
			val &= ~DPAA_DPPESCR_PMG0_SEL_MASK;
			val |= (ev_cfg->dpaa.event->word << DPAA_DPPESCR_PMG0_SEL_SHIFT)
												& DPAA_DPPESCR_PMG0_SEL_MASK;
			break;
		case 1:
			qoriq_events.pmg_sel_ref[1]++;
			val &= ~DPAA_DPPESCR_PMG1_SEL_MASK;
			val |= (ev_cfg->dpaa.event->word << DPAA_DPPESCR_PMG1_SEL_SHIFT)
								& DPAA_DPPESCR_PMG1_SEL_MASK;
			break;
		default:
			printk(KERN_ERR 
				"qoriq-cntrs: DPAA General (PMGn_SEL) index out of range.\n");
			goto exit;
			break;
		}
		
		out_be32(DPAA_REG_PTR(dppescr), val);

		break;
	}
	default:
		printk(KERN_ERR "qoriq-cntrs: Unknown DPAA Event Selection type.\n");
		goto exit;
		break;
	}

	ret = 0;
exit:
	return ret;
}

static NOINLINE void dpaa_deconfigure_counter(
									const struct qoriq_event_config *ev_cfg)
{
	switch (ev_cfg->dpaa.event_selection_type) {
	case EVENT_SELECTION_REFERENCE:
		qoriq_events.refev_sel[ev_cfg->dpaa.index] = 0;
		break;
	case EVENT_SELECTION_GENERAL:
		qoriq_events.pmg_sel_ref[ev_cfg->dpaa.index]--;
		break;
	default:
		break;
	}
}

static NOINLINE int corenet_general_select_counter(struct perf_event *event,
		struct qoriq_event_config *ev_cfg)
{
	int ret = 1;
	int i;
	int found = 0;
	const struct epu_counter *epu_counter;
//	int counter_index;
//	int of_cnt_index;
	struct qoriq_counter_indx cnt_index;
	u32 byte_sel;
	u8 bn_sel[CNDC_NO_GENERAL_EVENTS];

	ev_cfg->corenet.event = corenet_event_from_code(event->hw.config);
	if (!ev_cfg->corenet.event)
		goto exit;

	byte_sel = in_be32(CNDC1_REG_PTR(cpmsr1));
	bn_sel[0] = (byte_sel & CNDC_CPMSR1_B0_SEL_MASK) >> 
													CNDC_CPMSR1_B0_SEL_SHIFT;
	bn_sel[1] = (byte_sel & CNDC_CPMSR1_B1_SEL_MASK) >>
													CNDC_CPMSR1_B1_SEL_SHIFT;
	bn_sel[2] = (byte_sel & CNDC_CPMSR1_B2_SEL_MASK) >>
													CNDC_CPMSR1_B2_SEL_SHIFT;
	bn_sel[3] = (byte_sel & CNDC_CPMSR1_B3_SEL_MASK) >>
													CNDC_CPMSR1_B3_SEL_SHIFT;

	/* look for an already set compatible Bn_SEL */
	for (i = 0; i < CNDC_NO_GENERAL_EVENTS; i++) {
		if (bn_sel[i] == ev_cfg->corenet.event->byte_select_mux_value) {
			/* check if EPU counter available for the epu_event_code 
			 * [Bn index] */
			epu_counter = epu_counter_from_code(
								ev_cfg->corenet.event->epu_event_code[i]);
			ret = qoriq_get_available_counter(epu_counter, &cnt_index);
			if (!ret) {
				found = 1;
				break;
			}
		}
	}

	/* look for an unused Bn_SEL */
	if (!found) {
		for (i = 0; i < CNDC_NO_GENERAL_EVENTS; i++) {
			if (bn_sel[i] == 0) {
				/* check if EPU counter available for the epu_event_code 
				 * [Bn index] */
				epu_counter =
						epu_counter_from_code(
								ev_cfg->corenet.event->epu_event_code[i]);
				
				ret = qoriq_get_available_counter(epu_counter, &cnt_index);
				if (!ret) {
					found = 1;
					break;
				}
			}
		}
	}

	if (found) {
		ev_cfg->counter_ind = cnt_index;
		//ev_cfg->epu_counter = epu_counter;
		//ev_cfg->of_counter_index = of_cnt_index;
		ev_cfg->epu_counter = epu_counter;
		ev_cfg->corenet.event_selection_type = EVENT_SELECTION_GENERAL;
		ev_cfg->corenet.index = i;
		ret = 0;
	}

exit:
	return ret;
}

static NOINLINE int corenet_reference_select_counter(struct perf_event *event,
		struct qoriq_event_config *ev_cfg)
{
	int ret = 1;
	int i;
	int found = 0;
	const struct epu_counter *epu_counter = 0;
	//int counter_index = 0;
	//int of_cnt_index;
	struct qoriq_counter_indx cnt_index;
	u32 val;

	ev_cfg->corenet.event = corenet_event_from_code(event->hw.config);
	if (!ev_cfg->corenet.event)
		goto exit;

	/* look for an already set REFSEL */
	for (i = 0; i < CNDC_NO_REF_EVENTS; i++) {
		val = in_be32(CNDC1_REG_PTR(cprescr[i]));
		if (val == ev_cfg->corenet.event->code - QORIQ_EVENT_BASE_CORENET) {
			/* check if EPU counter available for this reference event */
			epu_counter = epu_counter_from_code(CN_RefEv1 + i);
			ret = qoriq_get_available_counter(epu_counter, &cnt_index);
			if (!ret) {
				found = 1;
				break;
			}
		}
	}

	/* look for an unused REFSEL register */
	if (!found) {
		for (i = 0; i < CNDC_NO_REF_EVENTS; i++) {
			val = in_be32(CNDC1_REG_PTR(cprescr[i]));
			if (val == 0) {
				/* check if EPU counter available for this reference event */
				epu_counter = epu_counter_from_code(CN_RefEv1 + i);
				ret = qoriq_get_available_counter(epu_counter, &cnt_index);
				if (!ret) {
					found = 1;
					break;
				}
			}
		}
	}

	if (found) {
		//ev_cfg->counter_index = counter_index;
		//ev_cfg->of_counter_index = of_cnt_index;
		ev_cfg->counter_ind = cnt_index;
		ev_cfg->epu_counter = epu_counter;
		ev_cfg->corenet.event_selection_type = EVENT_SELECTION_REFERENCE;
		ev_cfg->corenet.index = i;
		ret = 0;
	}

exit:
	return ret;
}

static NOINLINE int corenet_select_counter(struct perf_event *event,
		struct qoriq_event_config *ev_cfg)
{
	int ret;
	/* try for a reference counter first */
	ret = corenet_reference_select_counter(event, ev_cfg);
	if (ret) {
		/* try for a general counter */
		ret = corenet_general_select_counter(event, ev_cfg);
	}

	return ret;
}

static NOINLINE int corenet_configure_counter(
									const struct qoriq_event_config *ev_cfg)
{
	int ret = -1;
	u32 val;

	switch (ev_cfg->corenet.event_selection_type) {
	case EVENT_SELECTION_REFERENCE:
		if (ev_cfg->corenet.index < 0 ||
				ev_cfg->corenet.index >= CNDC_NO_REF_EVENTS) {
			printk(KERN_ERR
			"qoriq-cntrs: Corenet Reference (CPRESCRn) index out of range.\n");
			goto exit;
		}
		val = ev_cfg->corenet.event->code - QORIQ_EVENT_BASE_CORENET;
		out_be32(CNDC1_REG_PTR(cprescr[ev_cfg->corenet.index]), val);
		break;
	case EVENT_SELECTION_GENERAL:
	{
		switch (ev_cfg->corenet.index) {
		case 0:
			val = in_be32(CNDC1_REG_PTR(cpmsr1)) & ~CNDC_CPMSR1_B0_SEL_MASK;
			val |= (ev_cfg->corenet.event->byte_select_mux_value <<
											CNDC_CPMSR1_B0_SEL_SHIFT)
												& CNDC_CPMSR1_B0_SEL_MASK;
			out_be32(CNDC1_REG_PTR(cpmsr1), val);
			break;
		case 1:
			val = in_be32(CNDC1_REG_PTR(cpmsr1)) & ~CNDC_CPMSR1_B1_SEL_MASK;
			val |= (ev_cfg->corenet.event->byte_select_mux_value <<
											CNDC_CPMSR1_B1_SEL_SHIFT)
												& CNDC_CPMSR1_B1_SEL_MASK;
			out_be32(CNDC1_REG_PTR(cpmsr1), val);
			break;
		case 2:
			val = in_be32(CNDC1_REG_PTR(cpmsr1)) & ~CNDC_CPMSR1_B2_SEL_MASK;
			val |= (ev_cfg->corenet.event->byte_select_mux_value <<
											CNDC_CPMSR1_B2_SEL_SHIFT)
												& CNDC_CPMSR1_B2_SEL_MASK;
			out_be32(CNDC1_REG_PTR(cpmsr1), val);
			break;
		case 3:
			val = in_be32(CNDC1_REG_PTR(cpmsr1)) & ~CNDC_CPMSR1_B3_SEL_MASK;
			val |= (ev_cfg->corenet.event->byte_select_mux_value <<
											CNDC_CPMSR1_B3_SEL_SHIFT)
													& CNDC_CPMSR1_B3_SEL_MASK;
			out_be32(CNDC1_REG_PTR(cpmsr1), val);
			break;
		default:
			printk(KERN_ERR
				"qoriq-cntrs: Corenet General (Bn_SEL) index out of range.\n");
			goto exit;
			break;
		}
		break;
	}
	default:
		printk(KERN_ERR
				"qoriq-cntrs: Unknown Corenet Event Selection type.\n");
		goto exit;
		break;
	}

	ret = 0;
exit:
	return ret;
}

static NOINLINE void corenet_deconfigure_counter(
									const struct qoriq_event_config *ev_cfg)
{
	switch (ev_cfg->corenet.event_selection_type) {
	case EVENT_SELECTION_REFERENCE:
		if (ev_cfg->corenet.index >= 0 &&
				ev_cfg->corenet.index < CNDC_NO_REF_EVENTS) {
			out_be32(CNDC1_REG_PTR(cprescr[ev_cfg->corenet.index]), 0);
		}
		break;
	case EVENT_SELECTION_GENERAL:
	{
		u32 val;

		switch (ev_cfg->corenet.index) {
		case 0:
			val = in_be32(CNDC1_REG_PTR(cpmsr1)) & ~CNDC_CPMSR1_B0_SEL_MASK;
			out_be32(CNDC1_REG_PTR(cpmsr1), val);
			break;
		case 1:
			val = in_be32(CNDC1_REG_PTR(cpmsr1)) & ~CNDC_CPMSR1_B1_SEL_MASK;
			out_be32(CNDC1_REG_PTR(cpmsr1), val);
			break;
		case 2:
			val = in_be32(CNDC1_REG_PTR(cpmsr1)) & ~CNDC_CPMSR1_B2_SEL_MASK;
			out_be32(CNDC1_REG_PTR(cpmsr1), val);
			break;
		case 3:
			val = in_be32(CNDC1_REG_PTR(cpmsr1)) & ~CNDC_CPMSR1_B3_SEL_MASK;
			out_be32(CNDC1_REG_PTR(cpmsr1), val);
			break;
		default:
			break;
		}
		break;
	}
	default:
		break;
	}
}


static NOINLINE void dpaa_enable_events(int enable)
{
	/* DDR - PMOVR | TPEN  */
	static const u32 enable_val = 0xfc00f000;
	//static const u32 enable_val = 0xfc000000;
	static const u32 disable_val =0x0;

    if (enable)
    	out_be32(DPAA_REG_PTR(dpepgcr), enable_val);
    else
    	out_be32(DPAA_REG_PTR(dpepgcr), disable_val);

}


/* Starts the selected EPU counter */
static NOINLINE void epu_counter_start(int ctr)
{
	static const u32 start = 0x80000000;
	u32 val = in_be32(EPU_REG_PTR(epccr[ctr]));
	out_be32(EPU_REG_PTR(epccr[ctr]), val | start);
}

/* Disables the selected EPU counter */
static NOINLINE void epu_counter_stop(int ctr)
{
	/* !EN  */
	static const u32 stop = 0x80000000;
	u32 val = in_be32(EPU_REG_PTR(epccr[ctr])) & ~stop;

	out_be32(EPU_REG_PTR(epccr[ctr]), val);
}

/*
 *  Functions called from the generic PMU
 */

void qoriq_cntrs_start(struct perf_event *event)
{
	if (event->hw.idx < 0)
		return;

	epu_counter_start(event->hw.idx);
}

NOINLINE void qoriq_cntrs_stop(struct perf_event *event)
{
	if (event->hw.idx < 0)
		return;

	epu_counter_stop(event->hw.idx);
}

NOINLINE void qoriq_cntrs_global_enable(void)
{
	/* GCE Global Counter enable */
	out_be32(EPU_REG_PTR(epgcr), 0x80000000);
}

NOINLINE void qoriq_cntrs_global_disable(void)
{
	/* GCE Global Counter disable */
	out_be32(EPU_REG_PTR(epgcr), 0x00000000);
}

/*
 * return 0 is resources are available to configure the provided event.
 * return 1 if there are not enough resources.
 */
static NOINLINE int check_available_resources(struct perf_event *event)
{
	int ret = 1;
	int tmp;
	struct qoriq_event_config *ev_cfg = NULL;
	const struct qoriq_hitgen_config *hitgen = NULL;

	ev_cfg = qoriq_event_config_allocate(qoriq_events.ev_conf, event,
												&event->hw.config_base);

	if (!ev_cfg) 
		goto exit;

	/* chase all the info we need for configuration */
	switch (event->hw.event_base) {
	case QORIQ_EVENT_BASE_EPU:
		ev_cfg->epu.event = epu_event_from_code(event->hw.config);
		if (!ev_cfg->epu.event)
			goto exit;

		ev_cfg->epu_counter =
				epu_counter_from_code(ev_cfg->epu.event->epu_event_code);
		
		if (!ev_cfg->epu_counter)
			goto exit;

		tmp = qoriq_get_available_counter(ev_cfg->epu_counter, 
											&ev_cfg->counter_ind);
		if (tmp) {
			DBG_PRINT(KERN_INFO,"FAILED to acquire counters.");
			goto exit;
		}
		break;
		
	case QORIQ_EVENT_BASE_CORENET:
		tmp = corenet_select_counter(event, ev_cfg);

		if (tmp)
			goto exit;
				
		break;
		
	case QORIQ_EVENT_BASE_DATAPATH:
		ret = dpaa_select_counter(event, ev_cfg);
		if (ret)
			goto exit;

		break;
	case QORIQ_EVENT_BASE_NXC:
	case QORIQ_EVENT_BASE_SCU:
	case QORIQ_EVENT_BASE_CORE:
	case QORIQ_EVENT_BASE_MPIC:
	case QORIQ_EVENT_BASE_RCPM:
	case QORIQ_EVENT_BASE_ELBC:
		goto exit;
		break;
	case QORIQ_EVENT_BASE_DDR:
		ev_cfg->ddr.event = ddr_event_from_code(event->hw.config);
		if (!ev_cfg->ddr.event)
			goto exit;

		ev_cfg->epu_counter = 
				epu_counter_from_code(ev_cfg->ddr.event->epu_event_code);
		if (!ev_cfg->epu_counter)
			goto exit;

		tmp = qoriq_get_available_counter(ev_cfg->epu_counter,
											&ev_cfg->counter_ind);
		if (tmp)
			goto exit;

		break;

	case QORIQ_EVENT_BASE_DDR_COMPLEX:
			
		ev_cfg->ddr_cmplx.event = 
				ddr_cmplx_event_from_code(event->hw.config);
		
		if (!ev_cfg->ddr_cmplx.event)
			goto exit;
		
		hitgen = qoriq_hitgen_get_hitgen_epu_cntr(event);
		
		if (hitgen == NULL)
			goto exit;
		
		if (!hitgen->epu_counter)
			goto exit;

		 qoriq_hitgen_deallocate_hitgens(event);

		break;
		
	case QORIQ_EVENT_BASE_NPC:
		
		ev_cfg->npc.event = npc_event_from_code(event->hw.config);
		if (!ev_cfg->npc.event)
			goto exit;

		ev_cfg->epu_counter =
				epu_counter_from_code(ev_cfg->npc.event->epu_event_code);
		if (!ev_cfg->epu_counter)
			goto exit;

		tmp = qoriq_get_available_counter(ev_cfg->epu_counter, 
											&ev_cfg->counter_ind);
		if (tmp)
			goto exit;
				
		break;
		
	default:
		goto exit;
		break;
	}

	ret = 0;

exit:

	if (ret != 0)
		printk(KERN_ERR "\nOut of resources: Unable to allocate counter for event r%llx\n",
				event->hw.config);
	
	qoriq_event_config_deallocate_event(qoriq_events.ev_conf, event);

	spin_unlock(&qoriq_events.ev_lock);

	return ret;

}
/*
 * This function is called whenever the perf_event comes into "scope".
 * Since the physical counter may have been used for other purposes, all
 * configuration needed to setup the counter needs to be performed
 * on each qoriq_cntrs_add call.
 */
NOINLINE int qoriq_cntrs_add(struct perf_event *event)
{
	int ret = -EAGAIN;
	int new_config;
	struct qoriq_event_config *ev_cfg=NULL;
	const struct qoriq_hitgen_config *hitgen = NULL;
	
	new_config = 0;

	if (event == NULL)
		goto exit;
	
	spin_lock(&qoriq_events.ev_lock);
	

	/* 
	 * If there is already a configuration for this event type, don't 
	 * configure it again. 
	 */
	if (qoriq_perf_event_from_id(event->hw.config) >= 0) {

		ret = 0x10000000;
		goto exit;
	}

	/* retrieve or allocate the event_config for this event */
	ev_cfg = qoriq_event_config_for_event(qoriq_events.ev_conf, event,
													&event->hw.config_base);

	if (!ev_cfg) {

		ev_cfg = qoriq_event_config_allocate(qoriq_events.ev_conf, event,
													&event->hw.config_base);

		new_config = 1;
		if (!ev_cfg) {
			goto exit;
		}
	}

	/* chase all the info we need for configuration */
	switch (event->hw.event_base) {
	case QORIQ_EVENT_BASE_EPU:
		if (new_config) {
			ev_cfg->epu.event = epu_event_from_code(event->hw.config);
			if (!ev_cfg->epu.event)
				goto exit;

			ev_cfg->epu_counter =
					epu_counter_from_code(ev_cfg->epu.event->epu_event_code);
			
			if (!ev_cfg->epu_counter)
				goto exit;

			ret = qoriq_get_available_counter(ev_cfg->epu_counter, 
												&ev_cfg->counter_ind);
			if (ret) {
				DBG_PRINT(KERN_INFO,"FAILED to acquire counters.");
				goto exit;
			}
		}

		/* will be null for invalid events provided by user */
		/* ev_cfg->epu_counter will be NULL if we ran out of counters */
		if (ev_cfg->epu.event == NULL || ev_cfg->epu_counter == NULL)
			goto exit; 

		/* setup the epu counter */
		qoriq_epu_configure_counter(ev_cfg);
		qoriq_set_counter_in_use(&ev_cfg->counter_ind);
		event->hw.idx = ev_cfg->counter_ind.base;
		qoriq_events.perf_event[ev_cfg->counter_ind.base] = event;
		break;
	case QORIQ_EVENT_BASE_CORENET:
		if (new_config) {
			ret = corenet_select_counter(event, ev_cfg);
			if (ret)
				goto exit;
		}
		
		/* will be null for invalid events provided by user */
		/* ev_cfg->epu_counter will be NULL if we ran out of counters */
		if (!ev_cfg->corenet.event || ev_cfg->epu_counter == NULL) 
			goto exit;

		/* setup for corenet */
		ret = corenet_configure_counter(ev_cfg);
		if (ret)
			goto exit;
		/* setup the epu counter */
		qoriq_epu_configure_counter(ev_cfg);
		qoriq_set_counter_in_use(&ev_cfg->counter_ind);
		event->hw.idx = ev_cfg->counter_ind.base;
		qoriq_events.perf_event[ev_cfg->counter_ind.base] = event;
		
		break;
	case QORIQ_EVENT_BASE_DATAPATH:
		if (new_config) {
			dpaa_enable_events(1);
			ret = dpaa_select_counter(event, ev_cfg);
			if (ret)
				goto exit;

			/* setup for DPAA */
			ret = dpaa_configure_counter(ev_cfg);
			if (ret)
				goto exit;		
		}

		/* will be null for invalid events provided by user */
		/* ev_cfg->epu_counter will be NULL if we ran out of counters */
		if (!ev_cfg->dpaa.event || ev_cfg->epu_counter == NULL)
			goto exit;


		
		/* setup the epu counter */
		qoriq_epu_configure_counter(ev_cfg);
		qoriq_set_counter_in_use(&ev_cfg->counter_ind);
		event->hw.idx = ev_cfg->counter_ind.base;
		qoriq_events.perf_event[ev_cfg->counter_ind.base] = event;
		
		break;
	case QORIQ_EVENT_BASE_NXC:
	case QORIQ_EVENT_BASE_SCU:
	case QORIQ_EVENT_BASE_CORE:
	case QORIQ_EVENT_BASE_MPIC:
	case QORIQ_EVENT_BASE_RCPM:
	case QORIQ_EVENT_BASE_ELBC:
		goto exit;
		break;
	case QORIQ_EVENT_BASE_DDR:

		if (new_config) {
			ev_cfg->ddr.event = ddr_event_from_code(event->hw.config);
			if (!ev_cfg->ddr.event)
				goto exit;

			ev_cfg->epu_counter = 
					epu_counter_from_code(ev_cfg->ddr.event->epu_event_code);
			if (!ev_cfg->epu_counter)
				goto exit;

			ret = qoriq_get_available_counter(ev_cfg->epu_counter,
												&ev_cfg->counter_ind);

			if (ret)
				goto exit;
		}

		/* will be null for invalid events provided by user */
		/* ev_cfg->epu_counter will be NULL if we ran out of counters */
		if (!ev_cfg->ddr.event || ev_cfg->epu_counter == NULL)
			goto exit;		
		
		/* setup the ddr */
		qoriq_ddr_enable_events(ev_cfg->ddr.event->dev_index, 1);

		/* setup the epu counter */
		qoriq_epu_configure_counter(ev_cfg);

		qoriq_set_counter_in_use(&ev_cfg->counter_ind);
		event->hw.idx = ev_cfg->counter_ind.base;
		qoriq_events.perf_event[ev_cfg->counter_ind.base] = event;
			
		break;
	case QORIQ_EVENT_BASE_DDR_COMPLEX:
		if (new_config) {
			
			ev_cfg->ddr_cmplx.event = 
					ddr_cmplx_event_from_code(event->hw.config);
			
			/* ASSERT(ev_cfg->ddr_cmplx.event) */
			if (!ev_cfg->ddr_cmplx.event)
				goto exit;
			
			hitgen = qoriq_hitgen_get_hitgen_epu_cntr(event);
			
			if (hitgen == NULL)
				goto exit;
			
			/* Update ev_cfg counter info with hitgen info
			 * (needed for qoriq_epu_configure_counter() */
			
			//ev_cfg->of_counter_index = hitgen->epu_of_ctr_ind;
			//ev_cfg->counter_ind = hitgen->epu_ctr_ind;
			ev_cfg->counter_ind = hitgen->epu_ctr_ind;
			
			ev_cfg->epu_counter = hitgen->epu_counter;
			
			if (!ev_cfg->epu_counter)
				goto exit;

			
			/* Disable DDR Performance Monitor Resources for this DDR 
			 * controller */
			qoriq_ddr_enable_events(ev_cfg->ddr_cmplx.event->ddr_ind, 0);

			/* "Configure one of the NXC's 3 available HitGen units" */
			ddr_cmplx_configure(hitgen, ev_cfg);
			
		}

		/* will be null for invalid events provided by user */
		/* ev_cfg->epu_counter will be NULL if we ran out of counters */
		if (!ev_cfg->ddr_cmplx.event || ev_cfg->epu_counter == NULL)
			goto exit;
		
		/* "Basic Enabling of EPU Counters" */
		qoriq_epu_configure_counter(ev_cfg);

		/* "Enable DDR Performance Monitor Resources" for this DDR controller */
		qoriq_ddr_enable_events(ev_cfg->ddr_cmplx.event->ddr_ind, 1);

		qoriq_set_counter_in_use(&ev_cfg->counter_ind);
		event->hw.idx = hitgen->epu_ctr_ind.base;
		qoriq_events.perf_event[hitgen->epu_ctr_ind.base] = event;		
		
		break;
	case QORIQ_EVENT_BASE_NPC:
		if (new_config) {
			ev_cfg->npc.event = npc_event_from_code(event->hw.config);
			if (!ev_cfg->npc.event)
				goto exit;

			ev_cfg->epu_counter =
					epu_counter_from_code(ev_cfg->npc.event->epu_event_code);
			if (!ev_cfg->epu_counter)
				goto exit;

			ret = qoriq_get_available_counter(ev_cfg->epu_counter, 
												&ev_cfg->counter_ind);
			if (ret)
				goto exit;
			
		}
		
		/* will be null for invalid events provided by user */
		/* ev_cfg->epu_counter will be NULL if we ran out of counters */
		if (!ev_cfg->npc.event || ev_cfg->epu_counter == NULL)
			goto exit;

		/* no setup for the npc */
		/* setup the epu counter */
		qoriq_epu_configure_counter(ev_cfg);
		qoriq_set_counter_in_use(&ev_cfg->counter_ind);
		event->hw.idx = ev_cfg->counter_ind.base;
		qoriq_events.perf_event[ev_cfg->counter_ind.base] = event;
		break;
	default:
		goto exit;
		break;
	}

	ret = 0;

exit:
	spin_unlock(&qoriq_events.ev_lock);

	return ret;
}

/*
 * This function is called whenever the perf_event goes out of "scope".
 * Since the physical counter may be used for other purposes, the
 * counter is stopped and its value is read and stored. Its optional
 * whether the counter is reset or not.
 */
NOINLINE void qoriq_cntrs_del(struct perf_event *event)
{
	struct qoriq_event_config *ev_cfg;
	long unsigned int index;
	
	
	if (event->hw.idx < 0)
		return;

	/* stop the counter */
	epu_counter_stop(event->hw.idx);

	spin_lock(&qoriq_events.ev_lock);

	/* remove any device configuration */
	ev_cfg = qoriq_event_config_for_event(qoriq_events.ev_conf, event, &index);
	if (ev_cfg) {
		switch (event->hw.event_base) {
		case QORIQ_EVENT_BASE_EPU:
			break;
		case QORIQ_EVENT_BASE_CORENET:
			corenet_deconfigure_counter(ev_cfg);
			break;
		case QORIQ_EVENT_BASE_DATAPATH:
			dpaa_deconfigure_counter(ev_cfg);
			break;
		case QORIQ_EVENT_BASE_NXC:
		case QORIQ_EVENT_BASE_SCU:
		case QORIQ_EVENT_BASE_CORE:
		case QORIQ_EVENT_BASE_MPIC:
		case QORIQ_EVENT_BASE_RCPM:
		case QORIQ_EVENT_BASE_ELBC:
			break;
		case QORIQ_EVENT_BASE_DDR:
			break;
		case QORIQ_EVENT_BASE_DDR_COMPLEX:
			/* deconfigure counter--anything to be done here? */
			
			 qoriq_hitgen_deallocate_hitgens(event);
			break;
		case QORIQ_EVENT_BASE_NPC:
			break;
		default:
			break;
		}
	}

	/* spin_lock(&qoriq_events.ev_lock); */

	/* release the counter configuration */
	
	/* following needs to happen before qoriq_events.perf_event[event->hw.idx]
	 * set to NULL
	 */
	qoriq_event_config_deallocate_event(qoriq_events.ev_conf, event);
	qoriq_events.perf_event[event->hw.idx] = NULL;
	qoriq_clear_counter_in_use(event->hw.idx);
	
	event->hw.idx = -1;

	spin_unlock(&qoriq_events.ev_lock);
}

/*
 * The pmu_read() acquires the count from the hw counter and
 * adjusts the pef_event counters with the values.
 */
NOINLINE u64 qoriq_cntrs_read(struct perf_event *event)
{
	u64 val = 0;
	
	if (event->hw.idx >= 0)
		val = qoriq_v_counter_read(event->hw.idx);

	return val;
}

NOINLINE void qoriq_cntrs_write(struct perf_event *event, u64 val)
{
	if (event->hw.idx < 0)
		return;

	qoriq_v_counter_write(event->hw.idx, val);
}

/*
 * The qoriq_cntrs_event_init function is called whenever a new
 * event measurement is required.
 *
 * This implementation does not support groups (yet) or special operations.
 *
 * The event.hw structure is used to store useful configuration data since this
 * same event structure will be presented to other PMU calls.
 *
 * This driver uses the fields as follows:
 *
 * hw.config Copy of the perf event raw event number
 * hw.event_base The qoriq device originating the event (from 
 * enum QORIQ_EVENT_BASE) hw.config_base. An index to the qoriq_event_config
 * array entry.hw.idx. The index to the selected EPU counter valid between
 * *_add() and *_del() calls. Set to -1 otherwise.
 *
 * struct hw_perf_event {
 *	u64		config;
 *	u64		last_tag;
 *	unsigned long	config_base;
 *	unsigned long	event_base;
 *	int		idx;
 *	int		last_cpu;
 *	unsigned int	extra_reg;
 *	u64		extra_config;
 *	int		extra_alloc;
 *	...
 * };
 *
 */
NOINLINE int qoriq_cntrs_event_init(struct perf_event *event)
{

#if 0   /* ignore this test for now - PAPI will set some of these */

	/* These event exclusions not available */
	if (event->attr.exclude_user || event->attr.exclude_kernel ||
			event->attr.exclude_idle)
		return -ENOTSUPP;
#endif
	/*
	 * Validate perf_event request and save off the event
	 * and some possible configuration limitations in the
	 * event.hw structure.
	 * The actual epu_counter is not yet identified.
	 */

	event->hw.config = event->attr.config;
	event->hw.event_base = event->attr.config & QORIQ_EVENT_GROUP_MASK;
	event->hw.idx = -1;

	
	/* If the event has already been configured, don't bother to check whether
	 * resources are available for it. It this case, it is a pseudo-event, and
	 * no resources will be used on it anyway. Additionally if we return 
	 * non-zero for the pseudo-event, the actual event will do any
	 * counting.
	 */
	if (qoriq_perf_event_from_id(event->hw.config) < 0) {
		if (check_available_resources(event)) {
			return -EINVAL;
		}
	}
	
	/*
	 * If this is in a group, check if it can go on with all the
	 * other hardware events in the group.  We assume the event
	 * hasn't been linked into its leader's sibling list at this point.
	 */
	if (event->group_leader != event)
		return -EINVAL;

	return 0;
}

/*
 * EPU counter interrupt (perfmon) handler
 */
static NOINLINE irqreturn_t qoriq_perfmon_interrupt(int irq, void *ptr)
{
	unsigned long flags;
	struct perf_event *event;
	u64 val;
	u32 ctrisr;
	int ctr = QORIQ_EPU_NUM_COUNTERS - 1;
	
	ctrisr = in_be32(EPU_REG_PTR(epctrisr));
	if (!ctrisr)
		return IRQ_NONE;

	local_irq_save(flags);
	/* clear all the interrupt bits (w1c) */
	out_be32(EPU_REG_PTR(epctrisr), ctrisr);

	/* Shift through all the pending interrupts */
	while (ctrisr) {
		if (ctrisr & 1) {
			
			/* Note that overflowed counters should be
			 * the high order chained counters, not the base
			 * counters.
			 */
			if (qoriq_v_counter_inc(ctr)) {
				/* counter has overflowed */
				event = 
				 qoriq_events.perf_event[qoriq_get_perf_event_ind(ctr)];
				if (event) {
					val = qoriq_cntrs_read(event);
					record_and_restart(event, val);
				} else {
					/* Disable the counter since
					 * no event associated with it */
					epu_counter_stop(ctr);
				}
			}
		}
		ctr--;
		ctrisr >>= 1;
	}

	local_irq_restore(flags);

	return IRQ_HANDLED;
}

/* interrupt information used by the EPU perfmon interrupt */
struct intr {
	int num;
	const char *name;
	irqreturn_t (*handler)(int irq, void *ptr);
};

struct intr intr = {
		.name = "epu-perfmon",
		.handler = &qoriq_perfmon_interrupt,
};

/*
 * Searches the device tree for the interrupt information
 * for the EPU and binds the interrupt handler function to
 * the interrupt.
 */
static NOINLINE int qoriq_epu_bind_irq(struct device_node *epu_node)
{
	int ret = 0;

	
	/* clear all the interrupt bits (w1c) */
	out_be32(EPU_REG_PTR(epctrisr), 0xffffffff);

	intr.num = of_irq_to_resource(epu_node, 0, NULL);
	if (intr.num != NO_IRQ) {
		ret = request_irq(intr.num, intr.handler,
				IRQF_SHARED, intr.name, epu_node);
		if (ret) {
			printk(KERN_ERR
				"request_irq() of irq_num: %d failed.\n",
				intr.num);
			return -ENODEV;
		}
	}

	return ret;
}

static NOINLINE int qoriq_epu_unbind_irq(struct device_node *epu_node)
{
	int ret = 0;

	/* clear all the interrupt bits (w1c) */
	out_be32(EPU_REG_PTR(epctrisr), 0xffffffff);

	/* clean out the pending work queue */
	flush_scheduled_work();

	/* free the irq number */
	if (intr.num != NO_IRQ)
		free_irq(intr.num, epu_node);

	return ret;
}

/* QORIQ Counter Driver Initialization Functions */

NOINLINE int qoriq_cntrs_init()
{
	int ret;
	qoriq_event_state_init();
	ret = qoriq_epu_bind_irq(dbg_dev.epu.np);
	
	init_hitgen_configs();
	
	return ret;
}

NOINLINE void qoriq_cntrs_remove()
{
	qoriq_epu_unbind_irq(dbg_dev.epu.np);
}
