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

#include "corenet_events.h"
#include "qoriq_raw_events.h"
#include "epu_counters.h"

/* Table of Corenet event mappings */
const struct corenet_event corenet_event[] = {
		{
			.code = QE_CNDC_PE_CPC0_WRITE_MISS,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_0,
			.epu_event_code = { C_0, C_8, C_16, C_24 },
		},
		{
			.code = QE_CNDC_PE_CPC0_WRITE_HIT,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_0,
			.epu_event_code = { C_1, C_9, C_17, C_25 },
		},
		{
			.code = QE_CNDC_PE_CPC0_WRITE_ALLOC,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_0,
			.epu_event_code = { C_2, C_10, C_18, C_26 },
		},
		{
			.code = QE_CNDC_PE_CPC0_STASH_ALLOC,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_0,
			.epu_event_code = { C_4, C_12, C_20, C_28 },
		},
		{
			.code = QE_CNDC_PE_CPC0_READ_MISS,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_0,
			.epu_event_code = { C_5, C_13, C_21, C_29 },
		},
		{
			.code = QE_CNDC_PE_CPC0_READ_HIT,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_0,
			.epu_event_code = { C_6, C_14, C_22, C_30 },
		},
		{
			.code = QE_CNDC_PE_CPC0_READ_ALLOC,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_0,
			.epu_event_code = { C_7, C_15, C_23, C_31 },
		},
		{
			.code = QE_CNDC_PE_CPC0_OTHER_MISS,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_1,
			.epu_event_code = { C_0, C_8, C_16, C_24 },
		},
		{
			.code = QE_CNDC_PE_CPC0_OTHER_HIT,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_1,
			.epu_event_code = { C_1, C_9, C_17, C_25 },
		},
		{
			.code = QE_CNDC_PE_CPC0_DECORATED,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_1,
			.epu_event_code = { C_2, C_10, C_18, C_26 },
		},
		{
			.code = QE_CNDC_PE_CPC0_CASTOUT,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_1,
			.epu_event_code = { C_3, C_11, C_19, C_27 },
		},
		{
			.code = QE_CNDC_PE_CPC0_MARKED_WRITE_MISS,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_2,
			.epu_event_code = { C_0, C_8, C_16, C_24 },
		},
		{
			.code = QE_CNDC_PE_CPC0_MARKED_WRITE_HIT,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_2,
			.epu_event_code = { C_1, C_9, C_17, C_25 },
		},
		{
			.code = QE_CNDC_PE_CPC0_MARKED_WRITE_ALLOC,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_2,
			.epu_event_code = { C_2, C_10, C_18, C_26 },
		},
		{
			.code = QE_CNDC_PE_CPC0_MARKED_STASH_ALLOC,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_2,
			.epu_event_code = { C_4, C_12, C_20, C_28 },
		},
		{
			.code = QE_CNDC_PE_CPC0_MARKED_READ_MISS,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_2,
			.epu_event_code = { C_5, C_13, C_21, C_29 },
		},
		{
			.code = QE_CNDC_PE_CPC0_MARKED_READ_HIT,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_2,
			.epu_event_code = { C_6, C_14, C_22, C_30 },
		},
		{
			.code = QE_CNDC_PE_CPC0_MARKED_READ_ALLOC,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_2,
			.epu_event_code = { C_7, C_15, C_23, C_31 },
		},
		{
			.code = QE_CNDC_PE_CPC0_MARKED_OTHER_MISS,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_3,
			.epu_event_code = { C_0, C_8, C_16, C_24 },
		},
		{
			.code = QE_CNDC_PE_CPC0_MARKED_OTHER_HIT,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_3,
			.epu_event_code = { C_1, C_9, C_17, C_25 },
		},
		{
			.code = QE_CNDC_PE_CPC0_MARKED_DECORATED,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_3,
			.epu_event_code = { C_2, C_10, C_18, C_26 },
		},
		{
			.code = QE_CNDC_PE_CPC0_MARKED_CASTOUT,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_3,
			.epu_event_code = { C_3, C_11, C_19, C_27 },
		},
		{
			.code = QE_CNDC_PE_CPC0_DATA_WRITE,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_4,
			.epu_event_code = { C_0, C_8, C_16, C_24 },
		},
		{
			.code = QE_CNDC_PE_CPC0_DATA_RMW,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_4,
			.epu_event_code = { C_1, C_9, C_17, C_25 },
		},
		{
			.code = QE_CNDC_PE_CPC0_DATA_READ,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_4,
			.epu_event_code = { C_2, C_10, C_18, C_26 },
		},
		{
			.code = QE_CNDC_PE_CPC0_DATA_ACCESS,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_4,
			.epu_event_code = { C_3, C_11, C_19, C_27 },
		},
		{
			.code = QE_CNDC_PE_CPC0_MARKED_DATA_WRITE,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_4,
			.epu_event_code = { C_4, C_12, C_20, C_28 },
		},
		{
			.code = QE_CNDC_PE_CPC0_MARKED_DATA_RMW,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_4,
			.epu_event_code = { C_5, C_13, C_21, C_29 },
		},
		{
			.code = QE_CNDC_PE_CPC0_MARKED_DATA_READ,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_4,
			.epu_event_code = { C_6, C_14, C_22, C_30 },
		},
		{
			.code = QE_CNDC_PE_CPC0_MARKED_DATA_ACCESS,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_0_BYTE_4,
			.epu_event_code = { C_7, C_15, C_23, C_31 },
		},
		{
			.code = QE_CNDC_PE_CPC1_WRITE_MISS,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_0,
			.epu_event_code = { C_0, C_8, C_16, C_24 },
		},
		{
			.code = QE_CNDC_PE_CPC1_WRITE_HIT,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_0,
			.epu_event_code = { C_1, C_9, C_17, C_25 },
		},
		{
			.code = QE_CNDC_PE_CPC1_WRITE_ALLOC,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_0,
			.epu_event_code = { C_2, C_10, C_18, C_26 },
		},
		{
			.code = QE_CNDC_PE_CPC1_STASH_ALLOC,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_0,
			.epu_event_code = { C_4, C_12, C_20, C_28 },
		},
		{
			.code = QE_CNDC_PE_CPC1_READ_MISS,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_0,
			.epu_event_code = { C_5, C_13, C_21, C_29 },
		},
		{
			.code = QE_CNDC_PE_CPC1_READ_HIT,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_0,
			.epu_event_code = { C_6, C_14, C_22, C_30 },
		},
		{
			.code = QE_CNDC_PE_CPC1_READ_ALLOC,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_0,
			.epu_event_code = { C_7, C_15, C_23, C_31 },
		},
		{
			.code = QE_CNDC_PE_CPC1_OTHER_MISS,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_1,
			.epu_event_code = { C_0, C_8, C_16, C_24 },
		},
		{
			.code = QE_CNDC_PE_CPC1_OTHER_HIT,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_1,
			.epu_event_code = { C_1, C_9, C_17, C_25 },
		},
		{
			.code = QE_CNDC_PE_CPC1_DECORATED,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_1,
			.epu_event_code = { C_2, C_10, C_18, C_26 },
		},
		{
			.code = QE_CNDC_PE_CPC1_CASTOUT,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_1,
			.epu_event_code = { C_3, C_11, C_19, C_27 },
		},
		{
			.code = QE_CNDC_PE_CPC1_MARKED_WRITE_MISS,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_2,
			.epu_event_code = { C_0, C_8, C_16, C_24 },
		},
		{
			.code = QE_CNDC_PE_CPC1_MARKED_WRITE_HIT,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_2,
			.epu_event_code = { C_1, C_9, C_17, C_25 },
		},
		{
			.code = QE_CNDC_PE_CPC1_MARKED_WRITE_ALLOC,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_2,
			.epu_event_code = { C_2, C_10, C_18, C_26 },
		},
		{
			.code = QE_CNDC_PE_CPC1_MARKED_STASH_ALLOC,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_2,
			.epu_event_code = { C_4, C_12, C_20, C_28 },
		},
		{
			.code = QE_CNDC_PE_CPC1_MARKED_READ_MISS,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_2,
			.epu_event_code = { C_5, C_13, C_21, C_29 },
		},
		{
			.code = QE_CNDC_PE_CPC1_MARKED_READ_HIT,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_2,
			.epu_event_code = { C_6, C_14, C_22, C_30 },
		},
		{
			.code = QE_CNDC_PE_CPC1_MARKED_READ_ALLOC,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_2,
			.epu_event_code = { C_7, C_15, C_23, C_31 },
		},
		{
			.code = QE_CNDC_PE_CPC1_MARKED_OTHER_MISS,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_3,
			.epu_event_code = { C_0, C_8, C_16, C_24 },
		},
		{
			.code = QE_CNDC_PE_CPC1_MARKED_OTHER_HIT,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_3,
			.epu_event_code = { C_1, C_9, C_17, C_25 },
		},
		{
			.code = QE_CNDC_PE_CPC1_MARKED_DECORATED,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_3,
			.epu_event_code = { C_2, C_10, C_18, C_26 },
		},
		{
			.code = QE_CNDC_PE_CPC1_MARKED_CASTOUT,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_3,
			.epu_event_code = { C_3, C_11, C_19, C_27 },
		},
		{
			.code = QE_CNDC_PE_CPC1_DATA_WRITE,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_4,
			.epu_event_code = { C_0, C_8, C_16, C_24 },
		},
		{
			.code = QE_CNDC_PE_CPC1_DATA_RMW,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_4,
			.epu_event_code = { C_1, C_9, C_17, C_25 },
		},
		{
			.code = QE_CNDC_PE_CPC1_DATA_READ,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_4,
			.epu_event_code = { C_2, C_10, C_18, C_26 },
		},
		{
			.code = QE_CNDC_PE_CPC1_DATA_ACCESS,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_4,
			.epu_event_code = { C_3, C_11, C_19, C_27 },
		},
		{
			.code = QE_CNDC_PE_CPC1_MARKED_DATA_WRITE,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_4,
			.epu_event_code = { C_4, C_12, C_20, C_28 },
		},
		{
			.code = QE_CNDC_PE_CPC1_MARKED_DATA_RMW,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_4,
			.epu_event_code = { C_5, C_13, C_21, C_29 },
		},
		{
			.code = QE_CNDC_PE_CPC1_MARKED_DATA_READ,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_4,
			.epu_event_code = { C_6, C_14, C_22, C_30 },
		},
		{
			.code = QE_CNDC_PE_CPC1_MARKED_DATA_ACCESS,
			.byte_select_mux_value = CNDC_CPMSR1_PLATFORM_1_BYTE_4,
			.epu_event_code = { C_7, C_15, C_23, C_31 },
		},
};

/* Return a pointer to the corenet_pm_event associated with the event_code.
 * Returns 0 if not found.
 */
const struct corenet_event *corenet_event_from_code( u32 event_code )
{
	const struct corenet_event *ev = corenet_event;
	static const int NUM_ELEMENTS = sizeof(corenet_event)/sizeof(corenet_event[0]);
	int i;
	for (i = 0; i<NUM_ELEMENTS; i++) {
		if (ev->code == event_code)
			return ev;
		ev++;
	}
	return 0;
}
