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
#ifndef EPU_COUNTERS_H
#define EPU_COUNTERS_H

#include <linux/types.h>

/*
 * epu_counter contains the information to
 * program the EPU counters.
 *
 * Identified by a unique event code.
 * EPU configuration information:
 * cnt_mask - eligible counters for event
 * cnt_mux - value to select event as input
 */
struct epu_counter {
	u32		code;		/* epu counter mux event code */
	/* mask of counters for this event.
	 * counter number position match EPCTRISR */
	u32		cnt_mask;
	u32		cnt_mux;
};

/* Base code numbers for the counter code */
enum EPU_EVENT_BASE {
	EPU_EVENT_BASE_START = 0x100,
	EPU_EVENT_BASE_EPU = EPU_EVENT_BASE_START,
	EPU_EVENT_BASE_CORENET = 0x200,
	EPU_EVENT_BASE_DATAPATH = 0x300,
	EPU_EVENT_BASE_NXC = 0x400,
	EPU_EVENT_BASE_SCU = 0x500,
	EPU_EVENT_BASE_CNT = 0x600,
	EPU_EVENT_BASE_CORE = 0x700,
	EPU_EVENT_BASE_MPIC = 0x800,
	EPU_EVENT_BASE_RCPM = 0x900,
	EPU_EVENT_BASE_ELBC = 0xa00,
	EPU_EVENT_BASE_DDR = 0xb00,
	EPU_EVENT_BASE_NPC = 0xc00,
	EPU_EVENT_BASE_END = 0xdff,
};

enum EPU_COUNTER_EVENTS {
	PLATFORM_CYCLES = EPU_EVENT_BASE_EPU + 0x0,

	CN_RefEv1 = EPU_EVENT_BASE_CORENET + 0x0,
	CN_RefEv2,
	CN_RefEv3,
	CN_RefEv4,

	CDAC1_hit0 = EPU_EVENT_BASE_CORENET + 0x10,
	CDAC1_hit1,
	CDAC1_hit2,
	CDAC2_hit0,
	CDAC2_hit1,
	CDAC2_hit2,
	CDAC3_hit0,
	CDAC3_hit1,
	CDAC3_hit2,
	CDAC4_hit0,
	CDAC4_hit1,
	CDAC4_hit2,

	C_0 = EPU_EVENT_BASE_CORENET + 0x20,
	C_1,
	C_2,
	C_3,
	C_4,
	C_5,
	C_6,
	C_7,
	C_8,
	C_9,
	C_10,
	C_11,
	C_12,
	C_13,
	C_14,
	C_15,
	C_16,
	C_17,
	C_18,
	C_19,
	C_20,
	C_21,
	C_22,
	C_23,
	C_24,
	C_25,
	C_26,
	C_27,
	C_28,
	C_29,
	C_30,
	C_31,

	DP_RefEv0 = EPU_EVENT_BASE_DATAPATH + 0x0,
	DP_RefEv1,
	DP_RefEv2,
	DP_RefEv3,

	DP_Ev0_DPQOC0 = EPU_EVENT_BASE_DATAPATH + 0x10,
	DP_Ev1_DPQOC1,
	DP_Ev2_DPQOC2,
	DP_Ev3_DPQOC3,
	DP_Ev4_DPFOC0,
	DP_Ev5_DPFOC1,
	DP_Ev6_DPFOC2,
	DP_Ev7_DPFOC3,

	D_0 = EPU_EVENT_BASE_DATAPATH + 0x20,
	D_1,
	D_2,
	D_3,
	D_4,
	D_5,
	D_6,
	D_7,
	D_8,
	D_9,
	D_10,
	D_11,
	D_12,
	D_13,
	D_14,
	D_15,
	D_16,
	D_17,
	D_18,
	D_19,
	D_20,
	D_21,
	D_22,
	D_23,
	D_24,
	D_25,
	D_26,
	D_27,
	D_28,
	D_29,
	D_30,
	D_31,
	D_32,
	D_33,
	D_34,
	D_35,
	D_36,
	D_37,
	D_38,
	D_39,
	D_40,
	D_41,
	D_42,
	D_43,
	D_44,
	D_45,
	D_46,
	D_47,
	D_48,
	D_49,
	D_50,
	D_51,
	D_52,
	D_53,
	D_54,
	D_55,
	D_56,
	D_57,
	D_58,
	D_59,
	D_60,
	D_61,
	D_62,
	D_63,

	OCeaN_RefEv0 = EPU_EVENT_BASE_NXC + 0x0,
	OCeaN_RefEv1,
	OCeaN_RefEv2,
	OCeaN_RefEv3,

	NDAC1_hit1 = EPU_EVENT_BASE_NXC + 0x10,
	NDAC1_hit2,
	NDAC1_hit3,
	NDAC1_hit4,
	NDAC1_hit5,

	NDAC2_hit1,
	NDAC2_hit2,
	NDAC2_hit3,
	NDAC2_hit4,
	NDAC2_hit5,

	NDAC3_hit1,
	NDAC3_hit2,
	NDAC3_hit3,
	NDAC3_hit4,
	NDAC3_hit5,

	NDB1_hit1 = EPU_EVENT_BASE_NXC + 0x20,
	NDB1_hit2,
	NDB1_hit3,

	NDB2_hit1,
	NDB2_hit2,
	NDB2_hit3,

	NDB3_hit1,
	NDB3_hit2,
	NDB3_hit3,

	N_0 = EPU_EVENT_BASE_NXC + 0x10,
	N_1,
	N_2,
	N_3,
	N_4,
	N_5,
	N_6,
	N_7,
	N_8,
	N_9,
	N_10,
	N_11,
	N_12,
	N_13,
	N_14,
	N_15,
	N_16,
	N_17,
	N_18,
	N_19,
	N_20,
	N_21,
	N_22,
	N_23,
	N_24,
	N_25,
	N_26,
	N_27,
	N_28,
	N_29,
	N_30,
	N_31,

	CTR_0 = EPU_EVENT_BASE_CNT + 0x0,
	CTR_1,
	CTR_2,
	CTR_3,
	CTR_4,
	CTR_5,
	CTR_6,
	CTR_7,
	CTR_8,
	CTR_9,
	CTR_10,
	CTR_11,
	CTR_12,
	CTR_13,
	CTR_14,
	CTR_15,
	CTR_16,
	CTR_17,
	CTR_18,
	CTR_19,
	CTR_20,
	CTR_21,
	CTR_22,
	CTR_23,
	CTR_24,
	CTR_25,
	CTR_26,
	CTR_27,
	CTR_28,
	CTR_29,
	CTR_30,
	CTR_31,
	
	DDR1_0 = EPU_EVENT_BASE_DDR + 0x0,
	DDR1_1,
	DDR1_2,
	DDR1_3,
	DDR1_4,
	DDR1_5,

	DDR2_0 = EPU_EVENT_BASE_DDR + 0x10,
	DDR2_1,
	DDR2_2,
	DDR2_3,
	DDR2_4,
	DDR2_5,

	DDR3_0 = EPU_EVENT_BASE_DDR + 0x20,
	DDR3_1,
	DDR3_2,
	DDR3_3,
	DDR3_4,
	DDR3_5,

	DDR4_0 = EPU_EVENT_BASE_DDR + 0x30,
	DDR4_1,
	DDR4_2,
	DDR4_3,
	DDR4_4,
	DDR4_5,

	/* the following is a work-around for an B4860 R2
	 * only issue
	 */
	DDR1_R2 = EPU_EVENT_BASE_DDR + 0x40,
	DDR2_R2 = EPU_EVENT_BASE_DDR,
	
	NPC_QWRITE = EPU_EVENT_BASE_NPC + 0x0,
	NPC_TGT_REGION_FULL,
	NPC_TRBFR_FULL,
	NPC_EV_OUT,
	NPC_MMA_DONE,
};

/* Public interface
 */

/* Return a pointer to the epu_counter associated with the event_code.
 * Returns 0 if not found.
 */
const struct epu_counter *epu_counter_from_code(u32 event_code);

#endif /* EPU_COUNTERS_H */
