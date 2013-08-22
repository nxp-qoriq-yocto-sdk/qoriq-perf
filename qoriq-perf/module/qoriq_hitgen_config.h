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
#ifndef QORIQ_HITGEN_CONFIG_H
#define QORIQ_HITGEN_CONFIG_H

#include <linux/kernel.h>
#include <linux/perf_event.h>
#include "epu_counters.h"
#include "dcsr_nxc_v1.h"
#include "qoriq_event_config.h"

enum HITGEN_CNTR {
	HG_INVAL = -1,
	HG1 = 1,
	HG2,
	HG3,
};


/* contains the specific configuration choices
 * to configure a hit generator
 */
struct qoriq_hitgen_config  {
	/* non 0 indicates if this configuration is being used */
	struct perf_event *perf_event;

	const struct epu_counter *epu_counter;
//	int epu_ctr_ind;
//	int epu_of_ctr_ind;
	struct qoriq_counter_indx epu_ctr_ind;
	unsigned long hg_sigs_in_use;
};

/* Public interface */
void init_hitgen_configs(void);

const struct qoriq_hitgen_config* qoriq_hitgen_get_hitgen_epu_cntr(
												struct perf_event* in_event);   

void qoriq_hitgen_deallocate_hitgens(struct perf_event* in_event);

void ddr_cmplx_configure(const struct qoriq_hitgen_config *hitgen, 
									struct qoriq_event_config *ev_cfg);

#endif /*QORIQ_HITGEN_CONFIG_H */
