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


#include <linux/kernel.h>
#include <linux/perf_event.h>
#include <asm/io.h>
#include "qoriq_hitgen_config.h"
#include "dcsr_nxc_v1.h"
#include "qoriq_cntrs.h"
#include "qoriq_raw_events.h"
#include "qoriq_perf.h"
#include "qoriq_counters.h"

extern struct dbg_devices dbg_dev;

static struct qoriq_hitgens_state {

	unsigned long hitgens_in_use;
} qoriq_hitgens;

static struct qoriq_hitgen_config hitgen_configs[NXC_NO_OF_HITGENS];

void init_hitgen_configs()
{
	int i;
	
	for (i=0; i < NXC_NO_OF_HITGENS; i++) {
		hitgen_configs[i].perf_event = NULL;
		hitgen_configs[i].epu_counter = NULL;
	}
}
/* atomic update of the counters in use */
static inline void set_hitgen_in_use(int ctr)
{
	set_bit(NXC_NO_OF_HITGENS-1-ctr, &qoriq_hitgens.hitgens_in_use);
}

/* atomic update of the counters in use */
static inline void clr_hitgen_in_use(int ctr)
{
	clear_bit(NXC_NO_OF_HITGENS-1-ctr, &qoriq_hitgens.hitgens_in_use);
}

/* atomic update of the counters in use */
static inline void set_hg_sig_in_use(struct qoriq_hitgen_config *in_hg,
										int sig)
{
	set_bit(NXC_HG_NO_OF_MASK_UNITS-1-sig, &in_hg->hg_sigs_in_use);
}

/* atomic update of the counters in use */
static inline void clr_hg_sig_in_use(struct qoriq_hitgen_config *in_hg,
										int sig)
{
	clear_bit(NXC_HG_NO_OF_MASK_UNITS-1-sig, &in_hg->hg_sigs_in_use);
}

static inline unsigned int get_sig_in_use(struct qoriq_hitgen_config *in_hg,
												int sig)
{
	return test_bit(NXC_HG_NO_OF_MASK_UNITS-1-sig, &in_hg->hg_sigs_in_use);
}

static struct qoriq_hitgen_config* get_epu_counter_for_hg(
												struct perf_event *in_event,
												int hg_ind)
{
	int j;
//	int ind;
//	int of_ind;
	struct qoriq_counter_indx ind;
	int epuRet;
	struct qoriq_hitgen_config *hg_info = NULL;
	const struct epu_counter *tmp_epu_ctr = NULL;

	for (j = 0; j < NXC_HG_NO_OF_MASK_UNITS; j++) {
		
		/* skip HG's already being used */
		if (get_sig_in_use(&hitgen_configs[hg_ind],j)) 
			continue;

		tmp_epu_ctr = epu_counter_from_code(j+hg_ind*NXC_HG_NO_OF_MASK_UNITS + 
											EPU_EVENT_BASE_NXC + 0x10);

		epuRet = qoriq_get_available_counter(tmp_epu_ctr, &ind);

		if (epuRet == 0) {

			hitgen_configs[hg_ind].epu_ctr_ind = ind;
		//	hitgen_configs[hg_ind].epu_of_ctr_ind = of_ind;
			hitgen_configs[hg_ind].epu_counter = tmp_epu_ctr;
			hitgen_configs[hg_ind].perf_event = in_event;
			hg_info = &hitgen_configs[hg_ind];			
			set_hg_sig_in_use(&hitgen_configs[hg_ind], j);

			break;
		}
	}		
	
	return hg_info;
}

/* Return NULL if no hitgen/epu counter combo is available 
 * Function assumes given perf_event has not already been configured.
 */
const struct qoriq_hitgen_config* qoriq_hitgen_get_hitgen_epu_cntr(
						struct perf_event* in_event)      
{
	int i;
	u32 in_DDR_ind;
	const struct ddr_cmplx_event *in_ddr_cmplx_ev = NULL;
	const struct ddr_cmplx_event *tmp_ddr_cmplx_ev = NULL;
	struct qoriq_hitgen_config *hg_info = NULL;

	in_ddr_cmplx_ev = ddr_cmplx_event_from_code(in_event->hw.config);

	in_DDR_ind = in_ddr_cmplx_ev->ddr_ind;
	
	/* First, see if there is already a hitgen configured to use the src we 
	 * need for this event */
	for (i = 0; i < NXC_NO_OF_HITGENS; i++) {
		
		if (hitgen_configs[i].perf_event != NULL) {
			tmp_ddr_cmplx_ev = ddr_cmplx_event_from_code(
									hitgen_configs[i].perf_event->hw.config);
			if (tmp_ddr_cmplx_ev == NULL)
				continue;
			
			if (tmp_ddr_cmplx_ev->ddr_ind == in_DDR_ind){
				/* The HG associated with tmp_ddr_cmplx_ev is configed for
				 * the same source as in_event */

				hg_info = get_epu_counter_for_hg(in_event, i);

				if (hg_info != NULL)
					goto exit;
			}
		}
	}

	for (i = 0; i < NXC_NO_OF_HITGENS; i++) {	
		if (hitgen_configs[i].perf_event != NULL)
			continue;

		hg_info = get_epu_counter_for_hg(in_event, i);

		if (hg_info != NULL)
			goto exit;		
	}

	return NULL;

exit: 

	return hg_info;
}

void qoriq_hitgen_deallocate_hitgens(struct perf_event* in_event)
{
	int i;
	
	for (i = 0; i < NXC_NO_OF_HITGENS; i++) {
		if (hitgen_configs[i].perf_event == in_event) {
			// hitgen_configs[i].epu_ctr_ind = -1;
			qoriq_cntrs_init_cntr(&hitgen_configs[i].epu_ctr_ind);
			hitgen_configs[i].epu_counter = NULL;
			hitgen_configs[i].perf_event = NULL;
			hitgen_configs[i].hg_sigs_in_use = 0;
		}
	}
}
#define NXC_HGMCFG_CMPB_MSK_HIT_SHIFT 3

void ddr_cmplx_configure(const struct qoriq_hitgen_config *hitgen, 
								struct qoriq_event_config *ev_cfg)
{
	unsigned int hg_ind;
	unsigned int hg_sig;
	u32 eventID;
	u8 srcID;
	u8 srcIDMask;
	u32 hgmcfg0_val = 0;
	u32 hgmcfgn_val = 0;
	u32 hgmecrn_val = 0;
	u32 cmpbvalmask_m = 0;

	hg_ind = (hitgen->epu_counter->code - EPU_EVENT_BASE_NXC - 0x10)/
													NXC_HG_NO_OF_MASK_UNITS;
	hg_sig = (hitgen->epu_counter->code - EPU_EVENT_BASE_NXC - 0x10) %
													NXC_HG_NO_OF_MASK_UNITS;
	
	 /* Below, index 1 corresponds to DDR 2; index 0 corresponds to DDR1 */
	if (ev_cfg->ddr_cmplx.event->ddr_ind == 1)
		hgmcfg0_val |= 0x1 << NXC_HGMCFG0_SRC_SEL_SHIFT;
	/* else NOP hgmcfg0_val |= 0x0 << NXC_HGMCFG0_SRC_SEL_SHIFT;  */

	switch (ev_cfg->ddr_cmplx.event->miss_hit_modify) {
		case DDRC_MISS:
			hgmcfgn_val |= (0x3 <<  NXC_HGMCFG_ECCMPMSK_SHIFT);
			hgmecrn_val |= (0x2 << NXC_HGMECR_INV_SHIFT);
			break;
	
		case DDRC_HIT:
			hgmcfgn_val |= (0x3 <<  NXC_HGMCFG_ECCMPMSK_SHIFT);
			/* NOP hgmecrn_val |= (0x0 << NXC_HGMECR_INV_SHIFT); */
			break;
	
		case DDRC_MODIFY:
			hgmcfgn_val |= (0x81 <<  NXC_HGMCFG_ECCMPMSK_SHIFT);
			/* NOP hgmecrn_val |= (0x0 << NXC_HGMECR_INV_SHIFT); */
			break;
	}
	
	eventID = hitgen->perf_event->hw.config;
	
	/* Handle Source filtering, if necessary */
	if (eventID & DDR_CMPLX_SRC_FILTER_BIT) {
		hgmcfg0_val |= 0x01 << NXC_HGMCFG0_CMPR_B_SHIFT;
		
		srcID = (eventID & DDR_CMPLX_SRC_ID_MASK) 
								>> DDR_CMPLX_SRC_ID_SHIFT;
		
		srcIDMask = (eventID & DDR_CMPLX_SRC_ID_MSK_MASK)
								>> DDR_CMPLX_SRC_ID_MSK_SHIFT;

		cmpbvalmask_m |= srcID << NXC_CMPBVALMSKM_VAL_SHIFT;
		cmpbvalmask_m |= srcIDMask << NXC_CMPBVALMSKM_MSK_SHIFT;

		out_be32(NXC_REG_PTR(hit_gen[hg_ind].cmpbvalmsk), cmpbvalmask_m);
		
		hgmcfgn_val |= 0x1 << NXC_HGMCFG_CMPB_MSK_HIT_SHIFT;
	}
	
   	/* Disable NXC */
    out_be32(NXC_REG_PTR(nxccr0),0x0);
    
	/* write HGmCFG0*/
	out_be32(NXC_REG_PTR(hit_gen[hg_ind].hgcfg0), hgmcfg0_val);
				
	/* write HGmCFGn Mask*/
	out_be32(NXC_REG_PTR(hit_gen[hg_ind].hgmsk_cfg[hg_sig]),
			hgmcfgn_val);
	
	/* write HGmCFGn EC config */
	out_be32(NXC_REG_PTR(hit_gen[hg_ind].hgecr[hg_sig]),
							hgmecrn_val);

	/* Enable NXC */
	out_be32(NXC_REG_PTR(nxccr0),0x1);

}
