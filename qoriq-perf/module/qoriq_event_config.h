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
#ifndef QORIQ_EVENT_CONFIG_H
#define QORIQ_EVENT_CONFIG_H

#include <linux/perf_event.h>
#include "epu_counters.h"
#include "epu_events.h"
#include "ddr_events.h"
#include "npc_events.h"
#include "corenet_events.h"
#include "dpaa_events.h"
#include "ddr_cmplx_events.h"
#include "qoriq_counters.h"

#define QORIQ_NUM_EVENT_CONFIGURATIONS 32 /* QORIQ_EPU_NUM_COUNTERS */

/* indicates the method used for the CNDC/DPAA event selection */
enum EVENT_SELECTION_TYPE {
        EVENT_SELECTION_REFERENCE,
        EVENT_SELECTION_GENERAL
};


/* contains the specific configuration choices
 * to configure the counting of an event.
 */
struct qoriq_event_config {

	/* non 0 indicates if this configuration is being used */
	struct perf_event *perf_event;

	/* epu counter in use for this configuration */
	const struct epu_counter *epu_counter;
	
	/* epu counter index in use for this configuration */
	struct qoriq_counter_indx counter_ind;

	//	int counter_index;

	/* overflow epu counter in use for this configuration */
	//const struct epu_counter *of_epu_counter;

	/* overflow epu counter index in use for this configuration */
//	int of_counter_index;
	
	/*  EPU */
	struct {
		/* the desired event */
		const struct epu_event *event;
	} epu;
	/* DDR */
	struct {
		/* the desired event */
		const struct ddr_event *event;
		int device_index;
	} ddr;
	/* NPC */
	struct {
		/* the desired event */
		const struct npc_event *event;
	} npc;
	/* CNDC */
	struct {
		/* the desired event */
		const struct corenet_event *event;
		/* indicates the method used for the CNDC event */
		enum EVENT_SELECTION_TYPE event_selection_type;
		/* the reference index or the byte selection index */
		int index;
	} corenet;
	/* DPAA */
	struct {
		/* the desired event */
		const struct dpaa_event *event;
		/* indicates the method used for the DPAA event */
		enum EVENT_SELECTION_TYPE event_selection_type;
		/* the reference index or the group selection index */
		int index;
	} dpaa;
	/* DDR_CMPLX */
	struct {
		/* the desired event */
		const struct ddr_cmplx_event *event;
	} ddr_cmplx;
};

/* Public interface */
void qoriq_event_config_init(struct qoriq_event_config qoriq_event_config[]);
struct qoriq_event_config *qoriq_event_config_for_event(struct qoriq_event_config qoriq_event_config[],
		struct perf_event *perf_event, long unsigned int *index);
struct qoriq_event_config *qoriq_event_config_allocate(struct qoriq_event_config qoriq_event_config[],
		struct perf_event *perf_event, long unsigned int *index);
void qoriq_event_config_deallocate(struct qoriq_event_config qoriq_event_config[],
		long unsigned int index);
void qoriq_event_config_deallocate_event(struct qoriq_event_config qoriq_event_config[],
		struct perf_event *perf_event);
struct qoriq_event_config *qoriq_event_config_at_index(struct qoriq_event_config qoriq_event_config[],
		long unsigned int index);

#endif /*QORIQ_EVENT_CONFIG_H */
