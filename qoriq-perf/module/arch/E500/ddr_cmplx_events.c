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

#include "ddr_cmplx_events.h"
#include "qoriq_raw_events.h"
#include "epu_counters.h"

/* Table of DDR event mappings */
const struct ddr_cmplx_event ddr_cmplx_event[] = {
		{
			.code = QE_DDR1_PAGE_HIT,
			.ddr_ind = 0,
			.miss_hit_modify = 1,
		},
		{
			.code = QE_DDR1_PAGE_MISS,
			.ddr_ind = 0,
			.miss_hit_modify = 0,
		},
		{
			.code = QE_DDR2_PAGE_HIT,
			.ddr_ind = 1,
			.miss_hit_modify = 1,
		},
		{
			.code = QE_DDR2_PAGE_MISS,
			.ddr_ind = 1,
			.miss_hit_modify = 0,
		},
};

/* Return a pointer to the ddr_event associated with the event_code.
 * Returns 0 if not found.
 */

const struct ddr_cmplx_event *ddr_cmplx_event_from_code( u32 event_code )
{
	const struct ddr_cmplx_event *ev = ddr_cmplx_event;
	static const int NUM_ELEMENTS = sizeof(ddr_cmplx_event)/sizeof(ddr_cmplx_event[0]);
	int i;
	u32 in_evt_code;
	
	in_evt_code = event_code & (QORIQ_EVENT_GROUP_MASK | QORIQ_EVENT_ID_MASK);
	
	for (i = 0; i<NUM_ELEMENTS; i++) {
		if (ev->code == in_evt_code)
			return ev;
		ev++;
	}
	return 0;
}
