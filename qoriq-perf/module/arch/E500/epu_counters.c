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

#include "epu_counters.h"

/* Table of all EPU counter mux events */
const struct epu_counter epu_counter[] = {
		{
			.code = PLATFORM_CYCLES,
			.cnt_mask = 0xffffffff,
			.cnt_mux = 0,
		},
		{
			.code = CN_RefEv1,
			.cnt_mask = 0xffff0000,
			.cnt_mux = 0,
		},
		{
			.code = CN_RefEv2,
			.cnt_mask = 0x0000ffff,
			.cnt_mux = 0,
		},
		{
			.code = CN_RefEv3,
			.cnt_mask = 0xffff0000,
			.cnt_mux = 1,
		},
		{
			.code = CN_RefEv4,
			.cnt_mask = 0x0000ffff,
			.cnt_mux = 1,
		},
		{
			.code = CDAC1_hit0,
			.cnt_mask = 0xffff0000,
			.cnt_mux = 2,
		},
		{
			.code = CDAC1_hit1,
			.cnt_mask = 0x0000f000,
			.cnt_mux = 4,
		},
		{
			.code = CDAC1_hit2,
			.cnt_mask = 0x00000f00,
			.cnt_mux = 4,
		},

		{
			.code = CDAC2_hit0,
			.cnt_mask = 0xffff0000,
			.cnt_mux = 3,
		},
		{
			.code = CDAC2_hit1,
			.cnt_mask = 0x0000f000,
			.cnt_mux = 5,
		},
		{
			.code = CDAC2_hit2,
			.cnt_mask = 0x00000f00,
			.cnt_mux = 5,
		},
		{
			.code = CDAC3_hit0,
			.cnt_mask = 0x0000ffff,
			.cnt_mux = 2,
		},
		{
			.code = CDAC3_hit1,
			.cnt_mask = 0xf0000000,
			.cnt_mux = 4,
		},
		{
			.code = CDAC3_hit2,
			.cnt_mask = 0x0f000000,
			.cnt_mux = 4,
		},
		{
			.code = CDAC4_hit0,
			.cnt_mask = 0x0000ffff,
			.cnt_mux = 3,
		},
		{
			.code = CDAC4_hit1,
			.cnt_mask = 0xf0000000,
			.cnt_mux = 5,
		},
		{
			.code = CDAC4_hit2,
			.cnt_mask = 0x0f000000,
			.cnt_mux = 5,
		},
		{
			.code = C_0,
			.cnt_mask = 0xc0000000,
			.cnt_mux = 6,
		},
		{
			.code = C_2,
			.cnt_mask = 0x30000000,
			.cnt_mux = 6,
		},
		{
			.code = C_4,
			.cnt_mask = 0x0c000000,
			.cnt_mux = 6,
		},
		{
			.code = C_6,
			.cnt_mask = 0x03000000,
			.cnt_mux = 6,
		},
		{
			.code = C_8,
			.cnt_mask = 0x00c00000,
			.cnt_mux = 6,
		},
		{
			.code = C_10,
			.cnt_mask = 0x00300000,
			.cnt_mux = 6,
		},
		{
			.code = C_12,
			.cnt_mask = 0x000c0000,
			.cnt_mux = 6,
		},
		{
			.code = C_14,
			.cnt_mask = 0x00030000,
			.cnt_mux = 6,
		},
		{
			.code = C_16,
			.cnt_mask = 0x0000c000,
			.cnt_mux = 6,
		},
		{
			.code = C_18,
			.cnt_mask = 0x00003000,
			.cnt_mux = 6,
		},
		{
			.code = C_20,
			.cnt_mask = 0x00000c00,
			.cnt_mux = 6,
		},
		{
			.code = C_22,
			.cnt_mask = 0x00000300,
			.cnt_mux = 6,
		},
		{
			.code = C_24,
			.cnt_mask = 0x000000c0,
			.cnt_mux = 6,
		},
		{
			.code = C_26,
			.cnt_mask = 0x00000030,
			.cnt_mux = 6,
		},
		{
			.code = C_28,
			.cnt_mask = 0x0000000c,
			.cnt_mux = 6,
		},
		{
			.code = C_30,
			.cnt_mask = 0x00000003,
			.cnt_mux = 6,
		},
		{
			.code = C_1,
			.cnt_mask = 0x60000000,
			.cnt_mux = 7,
		},
		{
			.code = C_3,
			.cnt_mask = 0x18000000,
			.cnt_mux = 7,
		},
		{
			.code = C_5,
			.cnt_mask = 0x06000000,
			.cnt_mux = 7,
		},
		{
			.code = C_7,
			.cnt_mask = 0x01800000,
			.cnt_mux = 7,
		},
		{
			.code = C_9,
			.cnt_mask = 0x00600000,
			.cnt_mux = 7,
		},
		{
			.code = C_11,
			.cnt_mask = 0x00180000,
			.cnt_mux = 7,
		},
		{
			.code = C_13,
			.cnt_mask = 0x00060000,
			.cnt_mux = 7,
		},
		{
			.code = C_15,
			.cnt_mask = 0x00018000,
			.cnt_mux = 7,
		},
		{
			.code = C_17,
			.cnt_mask = 0x00006000,
			.cnt_mux = 7,
		},
		{
			.code = C_19,
			.cnt_mask = 0x00006000,
			.cnt_mux = 7,
		},
		{
			.code = C_21,
			.cnt_mask = 0x00000600,
			.cnt_mux = 7,
		},
		{
			.code = C_23,
			.cnt_mask = 0x00000180,
			.cnt_mux = 7,
		},
		{
			.code = C_25,
			.cnt_mask = 0x00000060,
			.cnt_mux = 7,
		},
		{
			.code = C_27,
			.cnt_mask = 0x00000018,
			.cnt_mux = 7,
		},
		{
			.code = C_29,
			.cnt_mask = 0x00000006,
			.cnt_mux = 7,
		},
		{
			.code = C_31,
			.cnt_mask = 0x80000001,
			.cnt_mux = 7,
		},
		{
			.code = DP_RefEv0,
			.cnt_mask = 0xffff0000,
			.cnt_mux = 8,
		},
		{
			.code = DP_RefEv1,
			.cnt_mask = 0x0000ffff,
			.cnt_mux = 8,
		},
		{
			.code = DP_RefEv2,
			.cnt_mask = 0xffff0000,
			.cnt_mux = 9,
		},
		{
			.code = DP_RefEv3,
			.cnt_mask = 0x0000ffff,
			.cnt_mux = 9,
		},
		{
			.code = DP_Ev0_DPQOC0,
			.cnt_mask = 0xffff0000,
			.cnt_mux = 10,
		},
		{
			.code = DP_Ev1_DPQOC1,
			.cnt_mask = 0x0000ffff,
			.cnt_mux = 10,
		},
		{
			.code = DP_Ev2_DPQOC2,
			.cnt_mask = 0xffff0000,
			.cnt_mux = 11,
		},
		{
			.code = DP_Ev3_DPQOC3,
			.cnt_mask = 0x0000ffff,
			.cnt_mux = 11,
		},
		{
			.code = DP_Ev4_DPFOC0,
			.cnt_mask = 0xffff0000,
			.cnt_mux = 12,
		},
		{
			.code = DP_Ev5_DPFOC1,
			.cnt_mask = 0x0000ffff,
			.cnt_mux = 12,
		},
		{
			.code = DP_Ev6_DPFOC2,
			.cnt_mask = 0xf0000000,
			.cnt_mux = 13,
		},
		{
			.code = DP_Ev7_DPFOC3,
			.cnt_mask = 0x0f000000,
			.cnt_mux = 13,
		},
		{
			.code = D_0,
			.cnt_mask = 0xc0000000,
			.cnt_mux = 14,
		},
		{
			.code = D_2,
			.cnt_mask = 0x30000000,
			.cnt_mux = 14,
		},
		{
			.code = D_4,
			.cnt_mask = 0x0c000000,
			.cnt_mux = 14,
		},
		{
			.code = D_6,
			.cnt_mask = 0x03000000,
			.cnt_mux = 14,
		},
		{
			.code = D_8,
			.cnt_mask = 0x00c00000,
			.cnt_mux = 14,
		},
		{
			.code = D_10,
			.cnt_mask = 0x00300000,
			.cnt_mux = 14,
		},
		{
			.code = D_12,
			.cnt_mask = 0x000c0000,
			.cnt_mux = 14,
		},
		{
			.code = D_14,
			.cnt_mask = 0x00030000,
			.cnt_mux = 14,
		},
		{
			.code = D_16,
			.cnt_mask = 0x0000c000,
			.cnt_mux = 14,
		},
		{
			.code = D_18,
			.cnt_mask = 0x00003000,
			.cnt_mux = 14,
		},
		{
			.code = D_20,
			.cnt_mask = 0x00000c00,
			.cnt_mux = 14,
		},
		{
			.code = D_22,
			.cnt_mask = 0x00000300,
			.cnt_mux = 14,
		},
		{
			.code = D_24,
			.cnt_mask = 0x000000c0,
			.cnt_mux = 14,
		},
		{
			.code = D_26,
			.cnt_mask = 0x00000030,
			.cnt_mux = 14,
		},
		{
			.code = D_28,
			.cnt_mask = 0x0000000c,
			.cnt_mux = 14,
		},
		{
			.code = D_30,
			.cnt_mask = 0x00000003,
			.cnt_mux = 14,
		},
		{
			.code = D_1,
			.cnt_mask = 0x60000000,
			.cnt_mux = 15,
		},
		{
			.code = D_3,
			.cnt_mask = 0x18000000,
			.cnt_mux = 15,
		},
		{
			.code = D_5,
			.cnt_mask = 0x06000000,
			.cnt_mux = 15,
		},
		{
			.code = D_7,
			.cnt_mask = 0x01800000,
			.cnt_mux = 15,
		},
		{
			.code = D_9,
			.cnt_mask = 0x00600000,
			.cnt_mux = 15,
		},
		{
			.code = D_11,
			.cnt_mask = 0x00180000,
			.cnt_mux = 15,
		},
		{
			.code = D_13,
			.cnt_mask = 0x00060000,
			.cnt_mux = 15,
		},
		{
			.code = D_15,
			.cnt_mask = 0x00018000,
			.cnt_mux = 15,
		},
		{
			.code = D_17,
			.cnt_mask = 0x00006000,
			.cnt_mux = 15,
		},
		{
			.code = D_19,
			.cnt_mask = 0x00006000,
			.cnt_mux = 15,
		},
		{
			.code = D_21,
			.cnt_mask = 0x00000600,
			.cnt_mux = 15,
		},
		{
			.code = D_23,
			.cnt_mask = 0x00000180,
			.cnt_mux = 15,
		},
		{
			.code = D_25,
			.cnt_mask = 0x00000060,
			.cnt_mux = 15,
		},
		{
			.code = D_27,
			.cnt_mask = 0x00000018,
			.cnt_mux = 15,
		},
		{
			.code = D_29,
			.cnt_mask = 0x00000006,
			.cnt_mux = 15,
		},
		{
			.code = D_31,
			.cnt_mask = 0x80000001,
			.cnt_mux = 15,
		},
		{
			.code = D_32,
			.cnt_mask = 0xc0000000,
			.cnt_mux = 16,
		},
		{
			.code = D_34,
			.cnt_mask = 0x30000000,
			.cnt_mux = 16,
		},
		{
			.code = D_36,
			.cnt_mask = 0x0c000000,
			.cnt_mux = 16,
		},
		{
			.code = D_38,
			.cnt_mask = 0x03000000,
			.cnt_mux = 16,
		},
		{
			.code = D_40,
			.cnt_mask = 0x00c00000,
			.cnt_mux = 16,
		},
		{
			.code = D_42,
			.cnt_mask = 0x00300000,
			.cnt_mux = 16,
		},
		{
			.code = D_44,
			.cnt_mask = 0x000c0000,
			.cnt_mux = 16,
		},
		{
			.code = D_46,
			.cnt_mask = 0x00030000,
			.cnt_mux = 16,
		},
		{
			.code = D_48,
			.cnt_mask = 0x0000c000,
			.cnt_mux = 16,
		},
		{
			.code = D_50,
			.cnt_mask = 0x00003000,
			.cnt_mux = 16,
		},
		{
			.code = D_52,
			.cnt_mask = 0x00000c00,
			.cnt_mux = 16,
		},
		{
			.code = D_54,
			.cnt_mask = 0x00000300,
			.cnt_mux = 16,
		},
		{
			.code = D_56,
			.cnt_mask = 0x000000c0,
			.cnt_mux = 16,
		},
		{
			.code = D_58,
			.cnt_mask = 0x00000030,
			.cnt_mux = 16,
		},
		{
			.code = D_60,
			.cnt_mask = 0x0000000c,
			.cnt_mux = 16,
		},
		{
			.code = D_62,
			.cnt_mask = 0x00000003,
			.cnt_mux = 16,
		},
		{
			.code = D_33,
			.cnt_mask = 0x60000000,
			.cnt_mux = 17,
		},
		{
			.code = D_35,
			.cnt_mask = 0x18000000,
			.cnt_mux = 17,
		},
		{
			.code = D_37,
			.cnt_mask = 0x06000000,
			.cnt_mux = 17,
		},
		{
			.code = D_39,
			.cnt_mask = 0x01800000,
			.cnt_mux = 17,
		},
		{
			.code = D_41,
			.cnt_mask = 0x00600000,
			.cnt_mux = 17,
		},
		{
			.code = D_43,
			.cnt_mask = 0x00180000,
			.cnt_mux = 17,
		},
		{
			.code = D_45,
			.cnt_mask = 0x00060000,
			.cnt_mux = 17,
		},
		{
			.code = D_47,
			.cnt_mask = 0x00018000,
			.cnt_mux = 17,
		},
		{
			.code = D_49,
			.cnt_mask = 0x00006000,
			.cnt_mux = 17,
		},
		{
			.code = D_51,
			.cnt_mask = 0x00006000,
			.cnt_mux = 17,
		},
		{
			.code = D_53,
			.cnt_mask = 0x00000600,
			.cnt_mux = 17,
		},
		{
			.code = D_55,
			.cnt_mask = 0x00000180,
			.cnt_mux = 17,
		},
		{
			.code = D_57,
			.cnt_mask = 0x00000060,
			.cnt_mux = 17,
		},
		{
			.code = D_59,
			.cnt_mask = 0x00000018,
			.cnt_mux = 17,
		},
		{
			.code = D_61,
			.cnt_mask = 0x00000006,
			.cnt_mux = 17,
		},
		{
			.code = D_63,
			.cnt_mask = 0x80000001,
			.cnt_mux = 17,
		},
		{
			.code = OCeaN_RefEv0,
			.cnt_mask = 0xffff0000,
			.cnt_mux = 18,
		},
		{
			.code = OCeaN_RefEv1,
			.cnt_mask = 0x0000ffff,
			.cnt_mux = 18,
		},
		{
			.code = OCeaN_RefEv2,
			.cnt_mask = 0xffff0000,
			.cnt_mux = 19,
		},
		{
			.code = OCeaN_RefEv3,
			.cnt_mask = 0x0000ffff,
			.cnt_mux = 19,
		},
		{
			.code = NDAC1_hit1,
			.cnt_mask = 0xf0000000,
			.cnt_mux = 20,
		},
		{
			.code = NDAC1_hit2,
			.cnt_mask = 0x0f000000,
			.cnt_mux = 20,
		},
		{
			.code = NDAC1_hit3,
			.cnt_mask = 0x00f00000,
			.cnt_mux = 20,
		},
		{
			.code = NDAC1_hit4,
			.cnt_mask = 0x000f0000,
			.cnt_mux = 20,
		},
		{
			.code = NDAC1_hit5,
			.cnt_mask = 0x0000f000,
			.cnt_mux = 20,
		},
		{
			.code = NDAC2_hit1,
			.cnt_mask = 0x000000f,
			.cnt_mux = 21,
		},
		{
			.code = NDAC2_hit2,
			.cnt_mask = 0x00000f0,
			.cnt_mux = 21,
		},
		{
			.code = NDAC2_hit3,
			.cnt_mask = 0x00000f00,
			.cnt_mux = 21,
		},
		{
			.code = NDAC2_hit4,
			.cnt_mask = 0x0000f000,
			.cnt_mux = 21,
		},
		{
			.code = NDAC2_hit5,
			.cnt_mask = 0x000f0000,
			.cnt_mux = 21,
		},
		{
			.code = NDAC3_hit1,
			.cnt_mask = 0xf0000000,
			.cnt_mux = 22,
		},
		{
			.code = NDAC3_hit2,
			.cnt_mask = 0x0f000000,
			.cnt_mux = 22,
		},
		{
			.code = NDAC3_hit3,
			.cnt_mask = 0x00f00000,
			.cnt_mux = 22,
		},
		{
			.code = NDAC3_hit4,
			.cnt_mask = 0x000f0000,
			.cnt_mux = 22,
		},
		{
			.code = NDAC3_hit5,
			.cnt_mask = 0x0000f000,
			.cnt_mux = 22,
		},
		{
			.code = NDB1_hit1,
			.cnt_mask = 0x00000f00,
			.cnt_mux = 20,
		},
		{
			.code = NDB1_hit2,
			.cnt_mask = 0x000000f0,
			.cnt_mux = 20,
		},
		{
			.code = NDB1_hit3,
			.cnt_mask = 0x0000000f,
			.cnt_mux = 20,
		},
		{
			.code = NDB2_hit1,
			.cnt_mask = 0x00f00000,
			.cnt_mux = 21,
		},
		{
			.code = NDB2_hit2,
			.cnt_mask = 0x0f000000,
			.cnt_mux = 21,
		},
		{
			.code = NDB2_hit3,
			.cnt_mask = 0xf0000000,
			.cnt_mux = 21,
		},
		{
			.code = NDB3_hit1,
			.cnt_mask = 0x00000f00,
			.cnt_mux = 22,
		},
		{
			.code = NDB3_hit2,
			.cnt_mask = 0x000000f0,
			.cnt_mux = 22,
		},
		{
			.code = NDB3_hit3,
			.cnt_mask = 0x0000000f,
			.cnt_mux = 22,
		},
		{
			.code = N_0,
			.cnt_mask = 0xc0000000,
			.cnt_mux = 24,
		},
		{
			.code = N_2,
			.cnt_mask = 0x30000000,
			.cnt_mux = 24,
		},
		{
			.code = N_4,
			.cnt_mask = 0x0c000000,
			.cnt_mux = 24,
		},
		{
			.code = N_6,
			.cnt_mask = 0x03000000,
			.cnt_mux = 24,
		},
		{
			.code = N_8,
			.cnt_mask = 0x00c00000,
			.cnt_mux = 24,
		},
		{
			.code = N_10,
			.cnt_mask = 0x00300000,
			.cnt_mux = 24,
		},
		{
			.code = N_12,
			.cnt_mask = 0x000c0000,
			.cnt_mux = 24,
		},
		{
			.code = N_14,
			.cnt_mask = 0x00030000,
			.cnt_mux = 24,
		},
		{
			.code = N_16,
			.cnt_mask = 0x0000c000,
			.cnt_mux = 24,
		},
		{
			.code = N_18,
			.cnt_mask = 0x00003000,
			.cnt_mux = 24,
		},
		{
			.code = N_20,
			.cnt_mask = 0x00000c00,
			.cnt_mux = 24,
		},
		{
			.code = N_22,
			.cnt_mask = 0x00000300,
			.cnt_mux = 24,
		},
		{
			.code = N_24,
			.cnt_mask = 0x000000c0,
			.cnt_mux = 24,
		},
		{
			.code = N_26,
			.cnt_mask = 0x00000030,
			.cnt_mux = 24,
		},
		{
			.code = N_28,
			.cnt_mask = 0x0000000c,
			.cnt_mux = 24,
		},
		{
			.code = N_30,
			.cnt_mask = 0x00000003,
			.cnt_mux = 24,
		},
		{
			.code = N_1,
			.cnt_mask = 0x60000000,
			.cnt_mux = 25,
		},
		{
			.code = N_3,
			.cnt_mask = 0x18000000,
			.cnt_mux = 25,
		},
		{
			.code = N_5,
			.cnt_mask = 0x06000000,
			.cnt_mux = 25,
		},
		{
			.code = N_7,
			.cnt_mask = 0x01800000,
			.cnt_mux = 25,
		},
		{
			.code = N_9,
			.cnt_mask = 0x00600000,
			.cnt_mux = 25,
		},
		{
			.code = N_11,
			.cnt_mask = 0x00180000,
			.cnt_mux = 25,
		},
		{
			.code = N_13,
			.cnt_mask = 0x00060000,
			.cnt_mux = 25,
		},
		{
			.code = N_15,
			.cnt_mask = 0x00018000,
			.cnt_mux = 25,
		},
		{
			.code = N_17,
			.cnt_mask = 0x00006000,
			.cnt_mux = 25,
		},
		{
			.code = N_19,
			.cnt_mask = 0x00006000,
			.cnt_mux = 25,
		},
		{
			.code = N_21,
			.cnt_mask = 0x00000600,
			.cnt_mux = 25,
		},
		{
			.code = N_23,
			.cnt_mask = 0x00000180,
			.cnt_mux = 25,
		},
		{
			.code = N_25,
			.cnt_mask = 0x00000060,
			.cnt_mux = 25,
		},
		{
			.code = N_27,
			.cnt_mask = 0x00000018,
			.cnt_mux = 25,
		},
		{
			.code = N_29,
			.cnt_mask = 0x00000006,
			.cnt_mux = 25,
		},
		{
			.code = N_31,
			.cnt_mask = 0x80000001,
			.cnt_mux = 25,
		},
		
		
		{
			.code = CTR_0,
			.cnt_mask = 0x0000000f,
			.cnt_mux = 34,
		},
		{
			.code = CTR_1,
			.cnt_mask = 0x0000000f,
			.cnt_mux = 35,
		},
		{
			.code = CTR_2,
			.cnt_mask = 0x0000000f,
			.cnt_mux = 36,
		},
		{
			.code = CTR_3,
			.cnt_mask = 0x0000000f,
			.cnt_mux = 37,
		},
		{
			.code = CTR_4,
			.cnt_mask = 0x000000f0,
			.cnt_mux = 34,
		},
		{
			.code = CTR_5,
			.cnt_mask = 0x000000f0,
			.cnt_mux = 35,
		},
		{
			.code = CTR_6,
			.cnt_mask = 0x000000f0,
			.cnt_mux = 36,
		},
		{
			.code = CTR_7,
			.cnt_mask = 0x000000f0,
			.cnt_mux = 37,
		},
		{
			.code = CTR_8,
			.cnt_mask = 0x00000f00,
			.cnt_mux = 34,
		},
		{
			.code = CTR_9,
			.cnt_mask = 0x00000f00,
			.cnt_mux = 35,
		},
		{
			.code = CTR_10,
			.cnt_mask = 0x00000f00,
			.cnt_mux = 36,
		},
		{
			.code = CTR_11,
			.cnt_mask = 0x00000f00,
			.cnt_mux = 37,
		},
		{
			.code = CTR_12,
			.cnt_mask = 0x0000f000,
			.cnt_mux = 34,
		},
		{
			.code = CTR_13,
			.cnt_mask = 0x0000f000,
			.cnt_mux = 35,
		},
		{
			.code = CTR_14,
			.cnt_mask = 0x0000f000,
			.cnt_mux = 36,
		},
		{
			.code = CTR_15,
			.cnt_mask = 0x0000f000,
			.cnt_mux = 37,
		},
		{
			.code = CTR_16,
			.cnt_mask = 0x000f0000,
			.cnt_mux = 34,
		},
		{
			.code = CTR_17,
			.cnt_mask = 0x000f0000,
			.cnt_mux = 35,
		},
		{
			.code = CTR_18,
			.cnt_mask = 0x000f0000,
			.cnt_mux = 36,
		},
		{
			.code = CTR_19,
			.cnt_mask = 0x000f0000,
			.cnt_mux = 37,
		},
		{
			.code = CTR_20,
			.cnt_mask = 0x00f00000,
			.cnt_mux = 34,
		},
		{
			.code = CTR_21,
			.cnt_mask = 0x00f00000,
			.cnt_mux = 35,
		},
		{
			.code = CTR_22,
			.cnt_mask = 0x00f00000,
			.cnt_mux = 36,
		},
		{
			.code = CTR_23,
			.cnt_mask = 0x00f00000,
			.cnt_mux = 37,
		},
		{
			.code = CTR_24,
			.cnt_mask = 0x0f000000,
			.cnt_mux = 34,
		},
		{
			.code = CTR_25,
			.cnt_mask = 0x0f000000,
			.cnt_mux = 35,
		},
		{
			.code = CTR_26,
			.cnt_mask = 0x0f000000,
			.cnt_mux = 36,
		},
		{
			.code = CTR_27,
			.cnt_mask = 0x0f000000,
			.cnt_mux = 37,
		},
		{
			.code = CTR_28,
			.cnt_mask = 0xf0000000,
			.cnt_mux = 34,
		},
		{
			.code = CTR_29,
			.cnt_mask = 0xf0000000,
			.cnt_mux = 35,
		},
		{
			.code = CTR_30,
			.cnt_mask = 0xf0000000,
			.cnt_mux = 36,
		},
		{
			.code = CTR_31,
			.cnt_mask = 0xf0000000,
			.cnt_mux = 37,
		},		
		{
			.code = DDR1_0,
			.cnt_mask = 0xc0000000,
			.cnt_mux = 57,
		},
		{
			.code = DDR1_1,
			.cnt_mask = 0x30000000,
			.cnt_mux = 57,
		},
		{
			.code = DDR1_2,
			.cnt_mask = 0x0c000000,
			.cnt_mux = 57,
		},
		{
			.code = DDR1_3,
			.cnt_mask = 0x03000000,
			.cnt_mux = 57,
		},
		{
			.code = DDR1_4,
			.cnt_mask = 0x00c00000,
			.cnt_mux = 57,
		},
		{
			.code = DDR2_0,
			.cnt_mask = 0x00300000,
			.cnt_mux = 57,
		},
		{
			.code = DDR2_1,
			.cnt_mask = 0x000c0000,
			.cnt_mux = 57,
		},
		{
			.code = DDR2_2,
			.cnt_mask = 0x00030000,
			.cnt_mux = 57,
		},
		{
			.code = DDR2_3,
			.cnt_mask = 0x0000c000,
			.cnt_mux = 57,
		},
		{
			.code = DDR2_4,
			.cnt_mask = 0x00003000,
			.cnt_mux = 57,
		},
		{
			.code = NPC_QWRITE,
			.cnt_mask = 0x00000300,
			.cnt_mux = 60,
		},
		{
			.code = NPC_TGT_REGION_FULL,
			.cnt_mask = 0x000000c0,
			.cnt_mux = 60,
		},
		{
			.code = NPC_TRBFR_FULL,
			.cnt_mask = 0x00000030,
			.cnt_mux = 60,
		},
		{
			.code = NPC_EV_OUT,
			.cnt_mask = 0x0000000c,
			.cnt_mux = 60,
		},
		{
			.code = NPC_MMA_DONE,
			.cnt_mask = 0x00000003,
			.cnt_mux = 60,
		},
};

/* epu_counter public functions */

const struct epu_counter *epu_counter_from_code( u32 event_code )
{
	const struct epu_counter *ec = epu_counter;
	static const int NUM_ELEMENTS = sizeof(epu_counter)/sizeof(epu_counter[0]);
	int i;
	for (i = 0; i<NUM_ELEMENTS; i++) {
		if (ec->code == event_code)
			return ec;
		ec++;
	}
	return 0;
}
