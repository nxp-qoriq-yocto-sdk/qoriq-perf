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
#ifndef CORENET_EVENTS_H
#define CORENET_EVENTS_H

#include "dcsr_corenet_v1.h"

/*
 * CoreNet Performance Monitor General "counter-mux" Events
 *
 * Provides a mapping from the Corenet PM events
 * to the EPU events and counters.
 *
 * byte_sel_mux_val selects the specific Corenet PM event group
 *
 */

struct corenet_event {
	u32		code;	/* qoriq raw event code */
	u32		byte_select_mux_value;
	u32		epu_event_code[CNDC_NO_GENERAL_EVENTS];
};

/* Public interface */

/* Return a pointer to the corenet_pm_event associated with the event_code.
 * Returns 0 if not found.
 */
const struct corenet_event *corenet_event_from_code(u32 event_code);

#endif /*CORENET_EVENTS_H */
