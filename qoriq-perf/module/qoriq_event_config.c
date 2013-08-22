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

extern NOINLINE void qoriq_initialize_cnt_ind(struct qoriq_counter_indx *ind);

/* Initialize entry */
static NOINLINE void init_entry(struct qoriq_event_config *ev_cfg)
{
	ev_cfg->perf_event = 0;
	ev_cfg->epu_counter = 0;
	ev_cfg->epu.event = 0;
	ev_cfg->ddr.event = 0;
	ev_cfg->npc.event = 0;
	ev_cfg->corenet.event = 0;
	ev_cfg->ddr_cmplx.event = 0;
	
	qoriq_initialize_cnt_ind(&ev_cfg->counter_ind);
}


/* qoriq_event_config public methods */

NOINLINE void qoriq_event_config_init(struct qoriq_event_config qoriq_event_config[])
{
	int i;
	for (i = 0; i < QORIQ_NUM_EVENT_CONFIGURATIONS; i++ ) {
		init_entry(&qoriq_event_config[i]);
	}
}

NOINLINE struct qoriq_event_config *qoriq_event_config_for_event(struct qoriq_event_config qoriq_event_config[],
		struct perf_event *perf_event, long unsigned int *index)
{
	int i;
	struct qoriq_event_config *ret = 0;

	if (perf_event == 0 )
		return ret;

	for (i = 0; i < QORIQ_NUM_EVENT_CONFIGURATIONS; i++ ) {
		if (qoriq_event_config[i].perf_event == perf_event) {
			ret = &qoriq_event_config[i];
			*index = i;
			break;
		}
	}

	return ret;
}

NOINLINE struct qoriq_event_config *qoriq_event_config_allocate(struct qoriq_event_config qoriq_event_config[],
		struct perf_event *perf_event, long unsigned int *index)
{
	int i;
	struct qoriq_event_config *ret = 0;

	if (perf_event == 0 )
		return ret;

	/* look for a empty entry and allocate */
	for (i = 0; i < QORIQ_NUM_EVENT_CONFIGURATIONS; i++ ) {
		if (qoriq_event_config[i].perf_event == 0) {
			qoriq_event_config[i].perf_event = perf_event;
			ret = &qoriq_event_config[i];
			*index = i;
			break;
		}
	}

	return ret;
}

NOINLINE void qoriq_event_config_deallocate(struct qoriq_event_config qoriq_event_config[],
		long unsigned int index)
{
	if (index >=  0 || index < QORIQ_NUM_EVENT_CONFIGURATIONS) {
		init_entry(&qoriq_event_config[index]);
	}
}

NOINLINE void qoriq_event_config_deallocate_event(struct qoriq_event_config qoriq_event_config[],
		struct perf_event *perf_event)
{
	int i;
	/* should only be one but check all */
	for (i = 0; i < QORIQ_NUM_EVENT_CONFIGURATIONS; i++ ) {
		if (qoriq_event_config[i].perf_event == perf_event) {
			init_entry(&qoriq_event_config[i]);
		}
	}
}

NOINLINE struct qoriq_event_config *qoriq_event_config_at_index(struct qoriq_event_config qoriq_event_config[],
		long unsigned int index)
{
	struct qoriq_event_config *ret = 0;
	if (index >=  0 || index < QORIQ_NUM_EVENT_CONFIGURATIONS) {
		ret = &qoriq_event_config[index];
	}
	return ret;
}


