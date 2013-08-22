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
#ifndef QORIQ_COUNTERS_H
#define QORIQ_COUNTERS_H

#include <linux/perf_event.h>
#include "qoriq_cntrs.h"


struct qoriq_counter_indx {
	int base;
#if defined(QORIQ_CHAINED_COUNTERS)
	int overflow;
#endif
	
};

extern NOINLINE void qoriq_cntrs_state_init(void);

extern NOINLINE int qoriq_v_counter_inc(int ctr);
extern NOINLINE u64 qoriq_v_counter_read(u32 ctr);
extern NOINLINE int qoriq_get_available_counter(const struct epu_counter *cnt, 
										struct qoriq_counter_indx *cnt_index);
extern NOINLINE void qoriq_v_counter_write(u32 ctr, u64 val);

extern NOINLINE void qoriq_init_epu_counter(int epu_ctr_index);
extern NOINLINE void qoriq_set_counter_in_use(struct qoriq_counter_indx *ctr);
extern NOINLINE void qoriq_clear_counter_in_use(int base_ind);
extern NOINLINE int qoriq_get_perf_event_ind(int ctr);
extern NOINLINE void qoriq_cntrs_init_cntr(struct qoriq_counter_indx *cnt_index);

#endif /*QORIQ_EVENT_CONFIG_H */
