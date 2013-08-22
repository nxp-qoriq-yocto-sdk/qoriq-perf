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

#include <linux/io.h>
#include "dpaa_events.h"
#include "qoriq_raw_events.h"
#include "epu_counters.h"

/* Table of DPAA event mappings */
const struct dpaa_event dpaa_event[] = {
		{
				.code = QE_DPAA_PE_QM_DCP0_DEQ_EXCEEDS_THRESHOLD_A, /* 0 */
				.word = 0,
				.epu_event_code = { D_0, D_32 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_DEQ_EXCEEDS_THRESHOLD_B, /* 1 */
				.word = 0,
				.epu_event_code = { D_1, D_33 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_DEQ_EXCEEDS_THRESHOLD_C, /* 2 */
				.word = 0,
				.epu_event_code = { D_2, D_34 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_DEQ_EXCEEDS_THRESHOLD_D, /* 3 */
				.word = 0,
				.epu_event_code = { D_3, D_35 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_DEQ_EXCEEDS_THRESHOLD_A, /* 4 */
				.word = 0,
				.epu_event_code = { D_4, D_36 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_DEQ_EXCEEDS_THRESHOLD_B, /* 5 */
				.word = 0,
				.epu_event_code = { D_5, D_37 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_DEQ_EXCEEDS_THRESHOLD_C, /* 6 */
				.word = 0,
				.epu_event_code = { D_6, D_38 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_DEQ_EXCEEDS_THRESHOLD_D, /* 7 */
				.word = 0,
				.epu_event_code = { D_7, D_39 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_DEQ_EXCEEDS_THRESHOLD_A, /* 8 */
				.word = 0,
				.epu_event_code = { D_8, D_40 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_DEQ_EXCEEDS_THRESHOLD_B, /* 9 */
				.word = 0,
				.epu_event_code = { D_9, D_41 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_DEQ_EXCEEDS_THRESHOLD_C, /* 10 */
				.word = 0,
				.epu_event_code = { D_10, D_42 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_DEQ_EXCEEDS_THRESHOLD_D, /* 11 */
				.word = 0,
				.epu_event_code = { D_11, D_43 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_DEQ_EXCEEDS_THRESHOLD_A, /* 12 */
				.word = 0,
				.epu_event_code = { D_12, D_44 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_DEQ_EXCEEDS_THRESHOLD_B, /* 13 */
				.word = 0,
				.epu_event_code = { D_13, D_45 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_DEQ_EXCEEDS_THRESHOLD_C, /* 14 */
				.word = 0,
				.epu_event_code = { D_14, D_46 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_DEQ_EXCEEDS_THRESHOLD_D, /* 15 */
				.word = 0,
				.epu_event_code = { D_15, D_47 },
		},
		{
				.code = QE_DPAA_PE_QM_PFDR_PREFETCH_DENIED, /* 47 */
				.word = 1,
				.epu_event_code = { D_15, D_47 },
		},
		{
				.code = QE_DPAA_PE_QM_USED_PFDR_NO_PREFETCH_READ, /* 48 */
				.word = 1,
				.epu_event_code = { D_16, D_48 },
		},
		{
				.code = QE_DPAA_PE_QM_SFDR_ALLOCATION_SUCCEED, /* 49 */
				.word = 1,
				.epu_event_code = { D_17, D_49 },
		},
		{
				.code = QE_DPAA_PE_QM_SFDR_ALLOCATION_FAILED, /* 50 */
				.word = 1,
				.epu_event_code = { D_18, D_50 },
		},
		{
				.code = QE_DPAA_PE_QM_PARTIALLY_FULL_PFDR_WRITE, /* 51 */
				.word = 1,
				.epu_event_code = { D_19, D_51 },
		},
		{
				.code = QE_DPAA_PE_QM_FQ_TRULY_SCHEDULED_DCPx, /* 52 */
				.word = 1,
				.epu_event_code = { D_20, D_52 },
		},
		{
				.code = QE_DPAA_PE_QM_FQ_TRULY_SCHEDULED_SPx, /* 53 */
				.word = 1,
				.epu_event_code = { D_21, D_53 },
		},
		{
				.code = QE_DPAA_PE_QM_FQ_TRULY_SCHEDULED_RESCH, /* 54 */
				.word = 1,
				.epu_event_code = { D_22, D_54 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_ENQ_CMD_RECEIVED, /* 55 */
				.word = 1,
				.epu_event_code = { D_23, D_55 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_ENQ_CMD_RECEIVED, /* 56 */
				.word = 1,
				.epu_event_code = { D_24, D_56 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_ENQ_CMD_RECEIVED, /* 57 */
				.word = 1,
				.epu_event_code = { D_25, D_57 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_ENQ_CMD_RECEIVED, /* 58 */
				.word = 1,
				.epu_event_code = { D_26, D_58 },
		},
		{
				.code = QE_DPAA_PE_QM_SP0_ENQ_CMD_RECEIVED, /* 59 */
				.word = 1,
				.epu_event_code = { D_27, D_59 },
		},
		{
				.code = QE_DPAA_PE_QM_SP1_ENQ_CMD_RECEIVED, /* 60 */
				.word = 1,
				.epu_event_code = { D_28, D_60 },
		},
		{
				.code = QE_DPAA_PE_QM_SP2_ENQ_CMD_RECEIVED, /* 61 */
				.word = 1,
				.epu_event_code = { D_29, D_61 },
		},
		{
				.code = QE_DPAA_PE_QM_SP3_ENQ_CMD_RECEIVED, /* 62 */
				.word = 1,
				.epu_event_code = { D_30, D_62 },
		},
		{
				.code = QE_DPAA_PE_QM_SP4_ENQ_CMD_RECEIVED, /* 63 */
				.word = 1,
				.epu_event_code = { D_31, D_63 },
		},
		{
				.code = QE_DPAA_PE_QM_SP5_ENQ_CMD_RECEIVED, /* 64 */
				.word = 2,
				.epu_event_code = { D_0, D_32 },
		},
		{
				.code = QE_DPAA_PE_QM_SP6_ENQ_CMD_RECEIVED, /* 65 */
				.word = 2,
				.epu_event_code = { D_1, D_33 },
		},
		{
				.code = QE_DPAA_PE_QM_SP7_ENQ_CMD_RECEIVED, /* 66 */
				.word = 2,
				.epu_event_code = { D_2, D_34 },
		},
		{
				.code = QE_DPAA_PE_QM_SP8_ENQ_CMD_RECEIVED, /* 67 */
				.word = 2,
				.epu_event_code = { D_3, D_35 },
		},
		{
				.code = QE_DPAA_PE_QM_SP9_ENQ_CMD_RECEIVED, /* 68 */
				.word = 2,
				.epu_event_code = { D_4, D_36 },
		},
		{
				.code = QE_DPAA_PE_QM_SP0_ENQ_CMD_PULLED_EQCR_FULL, /* 69 */
				.word = 2,
				.epu_event_code = { D_5, D_37 },
		},
		{
				.code = QE_DPAA_PE_QM_SP1_ENQ_CMD_PULLED_EQCR_FULL, /* 70 */
				.word = 2,
				.epu_event_code = { D_6, D_38 },
		},
		{
				.code = QE_DPAA_PE_QM_SP2_ENQ_CMD_PULLED_EQCR_FULL, /* 71 */
				.word = 2,
				.epu_event_code = { D_7, D_39 },
		},
		{
				.code = QE_DPAA_PE_QM_SP3_ENQ_CMD_PULLED_EQCR_FULL, /* 72 */
				.word = 2,
				.epu_event_code = { D_8, D_40 },
		},
		{
				.code = QE_DPAA_PE_QM_SP4_ENQ_CMD_PULLED_EQCR_FULL, /* 73 */
				.word = 2,
				.epu_event_code = { D_9, D_41 },
		},
		{
				.code = QE_DPAA_PE_QM_SP5_ENQ_CMD_PULLED_EQCR_FULL, /* 74 */
				.word = 2,
				.epu_event_code = { D_10, D_42 },
		},
		{
				.code = QE_DPAA_PE_QM_SP6_ENQ_CMD_PULLED_EQCR_FULL, /* 75 */
				.word = 2,
				.epu_event_code = { D_11, D_43 },
		},
		{
				.code = QE_DPAA_PE_QM_SP7_ENQ_CMD_PULLED_EQCR_FULL, /* 76 */
				.word = 2,
				.epu_event_code = { D_12, D_44 },
		},
		{
				.code = QE_DPAA_PE_QM_SP8_ENQ_CMD_PULLED_EQCR_FULL, /* 77 */
				.word = 2,
				.epu_event_code = { D_13, D_45 },
		},
		{
				.code = QE_DPAA_PE_QM_SP9_ENQ_CMD_PULLED_EQCR_FULL, /* 78 */
				.word = 2,
				.epu_event_code = { D_14, D_46 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_ENQ_CMD_FIFO_FULL, /* 79 */
				.word = 2,
				.epu_event_code = { D_15, D_47 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_ENQ_CMD_FIFO_FULL, /* 80 */
				.word = 2,
				.epu_event_code = { D_16, D_48 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_ENQ_CMD_FIFO_FULL, /* 81 */
				.word = 2,
				.epu_event_code = { D_17, D_49 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_ENQ_CMD_FIFO_FULL, /* 82 */
				.word = 2,
				.epu_event_code = { D_18, D_50 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_EQCR_CR_DISPATCH_FIFO_FULL, /* 83 */
				.word = 2,
				.epu_event_code = { D_19, D_51 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_DEQ_CMD_FIFO_FULL, /* 84 */
				.word = 2,
				.epu_event_code = { D_20, D_52 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_DEQ_CMD_FIFO_FULL, /* 85 */
				.word = 2,
				.epu_event_code = { D_21, D_53 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_DEQ_CMD_FIFO_FULL, /* 86 */
				.word = 2,
				.epu_event_code = { D_22, D_54 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_DEQ_CMD_FIFO_FULL, /* 87 */
				.word = 2,
				.epu_event_code = { D_23, D_55 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_DEQ_RSP_FIFO_FULL, /* 88 */
				.word = 2,
				.epu_event_code = { D_24, D_56 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_DEQ_RSP_FIFO_FULL, /* 89 */
				.word = 2,
				.epu_event_code = { D_25, D_57 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_DEQ_RSP_FIFO_FULL, /* 90 */
				.word = 2,
				.epu_event_code = { D_26, D_58 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_DEQ_RSP_FIFO_FULL, /* 91 */
				.word = 2,
				.epu_event_code = { D_27, D_59 },
		},
		{
				.code = QE_DPAA_PE_QM_SP0_DEQ_CMD_READY_DQRR_FULL, /* 92 */
				.word = 2,
				.epu_event_code = { D_28, D_60 },
		},
		{
				.code = QE_DPAA_PE_QM_SP1_DEQ_CMD_READY_DQRR_FULL, /* 93 */
				.word = 2,
				.epu_event_code = { D_29, D_61 },
		},
		{
				.code = QE_DPAA_PE_QM_SP2_DEQ_CMD_READY_DQRR_FULL, /* 94 */
				.word = 2,
				.epu_event_code = { D_30, D_62 },
		},
		{
				.code = QE_DPAA_PE_QM_SP3_DEQ_CMD_READY_DQRR_FULL, /* 95 */
				.word = 2,
				.epu_event_code = { D_31, D_63 },
		},
		{
				.code = QE_DPAA_PE_QM_SP4_DEQ_CMD_READY_DQRR_FULL, /* 96 */
				.word = 3,
				.epu_event_code = { D_0, D_32 },
		},
		{
				.code = QE_DPAA_PE_QM_SP5_DEQ_CMD_READY_DQRR_FULL, /* 97 */
				.word = 3,
				.epu_event_code = { D_1, D_33 },
		},
		{
				.code = QE_DPAA_PE_QM_SP6_DEQ_CMD_READY_DQRR_FULL, /* 98 */
				.word = 3,
				.epu_event_code = { D_2, D_34 },
		},
		{
				.code = QE_DPAA_PE_QM_SP7_DEQ_CMD_READY_DQRR_FULL, /* 99 */
				.word = 3,
				.epu_event_code = { D_3, D_35 },
		},
		{
				.code = QE_DPAA_PE_QM_SP8_DEQ_CMD_READY_DQRR_FULL, /* 100 */
				.word = 3,
				.epu_event_code = { D_4, D_36 },
		},
		{
				.code = QE_DPAA_PE_QM_SP9_DEQ_CMD_READY_DQRR_FULL, /* 101 */
				.word = 3,
				.epu_event_code = { D_5, D_37 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_ENQ_SEQ_DISPATCHED, /* 102 */
				.word = 3,
				.epu_event_code = { D_6, D_38 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_ENQ_SEQ_DISPATCHED, /* 103 */
				.word = 3,
				.epu_event_code = { D_7, D_39 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_ENQ_SEQ_DISPATCHED, /* 104 */
				.word = 3,
				.epu_event_code = { D_8, D_40 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_ENQ_SEQ_DISPATCHED, /* 105 */
				.word = 3,
				.epu_event_code = { D_9, D_41 },
		},
		{
				.code = QE_DPAA_PE_QMAN_SPx_ENQ_SEQ_DISPATCHED, /* 106 */
				.word = 3,
				.epu_event_code = { D_10, D_42 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_ENQ_SEQ_DISPATCH_FIFO_FULL, /* 107 */
				.word = 3,
				.epu_event_code = { D_11, D_43 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_ENQ_SEQ_DISPATCH_FIFO_FULL, /* 108 */
				.word = 3,
				.epu_event_code = { D_12, D_44 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_ENQ_SEQ_DISPATCH_FIFO_FULL, /* 109 */
				.word = 3,
				.epu_event_code = { D_13, D_45 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_ENQ_SEQ_DISPATCH_FIFO_FULL, /* 110 */
				.word = 3,
				.epu_event_code = { D_14, D_46 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_ENQ_SEQ_DISPATCH_FIFO_FULL, /* 111 */
				.word = 3,
				.epu_event_code = { D_15, D_47 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_DEQ_SEQ_DELIVERS_1, /* 112 */
				.word = 3,
				.epu_event_code = { D_16, D_48 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_DEQ_SEQ_DELIVERS_1, /* 113 */
				.word = 3,
				.epu_event_code = { D_17, D_49 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_DEQ_SEQ_DELIVERS_1, /* 114 */
				.word = 3,
				.epu_event_code = { D_18, D_50 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_DEQ_SEQ_DELIVERS_1, /* 115 */
				.word = 3,
				.epu_event_code = { D_19, D_51 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_DEQ_SEQ_DELIVERS_1, /* 116 */
				.word = 3,
				.epu_event_code = { D_20, D_52 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_DEQ_SEQ_DELIVERS_2, /* 117 */
				.word = 3,
				.epu_event_code = { D_21, D_53 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_DEQ_SEQ_DELIVERS_2, /* 118 */
				.word = 3,
				.epu_event_code = { D_22, D_54 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_DEQ_SEQ_DELIVERS_2, /* 119 */
				.word = 3,
				.epu_event_code = { D_23, D_55 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_DEQ_SEQ_DELIVERS_2, /* 120 */
				.word = 3,
				.epu_event_code = { D_24, D_56 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_DEQ_SEQ_DELIVERS_2, /* 121 */
				.word = 3,
				.epu_event_code = { D_25, D_57 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_DEQ_SEQ_DELIVERS_3, /* 122 */
				.word = 3,
				.epu_event_code = { D_26, D_58 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_DEQ_SEQ_DELIVERS_3, /* 123 */
				.word = 3,
				.epu_event_code = { D_27, D_59 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_DEQ_SEQ_DELIVERS_3, /* 124 */
				.word = 3,
				.epu_event_code = { D_28, D_60 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_DEQ_SEQ_DELIVERS_3, /* 125 */
				.word = 3,
				.epu_event_code = { D_29, D_61 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_DEQ_SEQ_DELIVERS_3, /* 126 */
				.word = 3,
				.epu_event_code = { D_30, D_62 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_DEQ_CMD_DISPATCH_FIFO_FULL, /* 127 */
				.word = 3,
				.epu_event_code = { D_31, D_63 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_DEQ_CMD_DISPATCH_FIFO_FULL, /* 128 */
				.word = 4,
				.epu_event_code = { D_0, D_32 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_DEQ_CMD_DISPATCH_FIFO_FULL, /* 129 */
				.word = 4,
				.epu_event_code = { D_1, D_33 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_DEQ_CMD_DISPATCH_FIFO_FULL, /* 130 */
				.word = 4,
				.epu_event_code = { D_2, D_34 },
		},
		{
				.code = QE_DPAA_PE_QM_FRAME_IN_ORL, /* 131 */
				.word = 4,
				.epu_event_code = { D_3, D_35 },
		},
		{
				.code = QE_DPAA_PE_QM_FRAME_IN_ORL_ORP_ADVANCE, /* 132 */
				.word = 4,
				.epu_event_code = { D_4, D_36 },
		},
		{
				.code = QE_DPAA_PE_QM_REJECTED_LATE_FRAME, /* 133 */
				.word = 4,
				.epu_event_code = { D_5, D_37 },
		},
		{
				.code = QE_DPAA_PE_QM_ACCEPCTED_LATE_FRAME, /* 134 */
				.word = 4,
				.epu_event_code = { D_6, D_38 },
		},
		{
				.code = QE_DPAA_PE_QM_REJECTED_EARLY_FRAME, /* 135 */
				.word = 4,
				.epu_event_code = { D_7, D_39 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_FRAME_ENQ_REJECTED, /* 140 */
				.word = 4,
				.epu_event_code = { D_12, D_44 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_FRAME_ENQ_REJECTED, /* 141 */
				.word = 4,
				.epu_event_code = { D_13, D_45 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_FRAME_ENQ_REJECTED, /* 142 */
				.word = 4,
				.epu_event_code = { D_14, D_46 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_FRAME_ENQ_REJECTED, /* 143 */
				.word = 4,
				.epu_event_code = { D_15, D_47 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_FRAME_ENQ_REJECTED, /* 144 */
				.word = 4,
				.epu_event_code = { D_16, D_48 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_FRAME_ENQ_WRED_REJECTED, /* 145 */
				.word = 4,
				.epu_event_code = { D_17, D_49 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_FRAME_ENQ_WRED_REJECTED, /* 146 */
				.word = 4,
				.epu_event_code = { D_18, D_50 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_FRAME_ENQ_WRED_REJECTED, /* 147 */
				.word = 4,
				.epu_event_code = { D_19, D_51 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_FRAME_ENQ_WRED_REJECTED, /* 148 */
				.word = 4,
				.epu_event_code = { D_20, D_52 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_FRAME_ENQ_WRED_REJECTED, /* 149 */
				.word = 4,
				.epu_event_code = { D_21, D_53 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_FRAME_ENQ_TD_CONG_REJECTED, /* 150 */
				.word = 4,
				.epu_event_code = { D_22, D_54 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_FRAME_ENQ_TD_CONG_REJECTED, /* 151 */
				.word = 4,
				.epu_event_code = { D_23, D_55 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_FRAME_ENQ_TD_CONG_REJECTED, /* 152 */
				.word = 4,
				.epu_event_code = { D_24, D_56 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_FRAME_ENQ_TD_CONG_REJECTED, /* 153 */
				.word = 4,
				.epu_event_code = { D_25, D_57 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_FRAME_ENQ_TD_CONG_REJECTED, /* 154 */
				.word = 4,
				.epu_event_code = { D_26, D_58 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_FRAME_ENQ_TD_FQ_REJECTED, /* 155 */
				.word = 4,
				.epu_event_code = { D_27, D_59 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_FRAME_ENQ_TD_FQ_REJECTED, /* 156 */
				.word = 4,
				.epu_event_code = { D_28, D_60 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_FRAME_ENQ_TD_FQ_REJECTED, /* 157 */
				.word = 4,
				.epu_event_code = { D_29, D_61 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_FRAME_ENQ_TD_FQ_REJECTED, /* 158 */
				.word = 4,
				.epu_event_code = { D_30, D_62 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_FRAME_ENQ_TD_FQ_REJECTED, /* 159 */
				.word = 4,
				.epu_event_code = { D_31, D_63 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_ENQ_MARK_01, /* 160 */
				.word = 5,
				.epu_event_code = { D_0, D_32 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_ENQ_MARK_10, /* 161 */
				.word = 5,
				.epu_event_code = { D_1, D_33 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_ENQ_MARK_11, /* 162 */
				.word = 5,
				.epu_event_code = { D_2, D_34 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_FRAME_ENQ_MARK_01, /* 163 */
				.word = 5,
				.epu_event_code = { D_3, D_35 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_FRAME_ENQ_MARK_10, /* 164 */
				.word = 5,
				.epu_event_code = { D_4, D_36 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_FRAME_ENQ_MARK_11, /* 165 */
				.word = 5,
				.epu_event_code = { D_5, D_37 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_DEQ_MARK_01, /* 166 */
				.word = 5,
				.epu_event_code = { D_6, D_38 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_DEQ_MARK_10, /* 167 */
				.word = 5,
				.epu_event_code = { D_7, D_39 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_DEQ_MARK_11, /* 168 */
				.word = 5,
				.epu_event_code = { D_8, D_40 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_FRAME_DEQ_MARK_01, /* 169 */
				.word = 5,
				.epu_event_code = { D_9, D_41 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_FRAME_DEQ_MARK_10, /* 170 */
				.word = 5,
				.epu_event_code = { D_10, D_42 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_FRAME_DEQ_MARK_11, /* 171 */
				.word = 5,
				.epu_event_code = { D_11, D_43 },
		},
		{
				.code = QE_DPAA_PE_QM_ORL_FRAME_ENQ_MARK_01, /* 172 */
				.word = 5,
				.epu_event_code = { D_12, D_44 },
		},
		{
				.code = QE_DPAA_PE_QM_ORL_FRAME_ENQ_MARK_10, /* 173 */
				.word = 5,
				.epu_event_code = { D_13, D_45 },
		},
		{
				.code = QE_DPAA_PE_QM_ORL_FRAME_ENQ_MARK_11, /* 174 */
				.word = 5,
				.epu_event_code = { D_14, D_46 },
		},
		{
				.code = QE_DPAA_PE_BM_FBPR_WRITE_FREELIST_MONITOR_0, /* 192 */
				.word = 6,
				.epu_event_code = { D_0, D_32 },
		},
		{
				.code = QE_DPAA_PE_BM_FBPR_READ_FREELIST_MONITOR_0, /* 193 */
				.word = 6,
				.epu_event_code = { D_1, D_33 },
		},
		{
				.code = QE_DPAA_PE_BM_FBPR_WRITE_FREELIST_MONITOR_1, /* 194 */
				.word = 6,
				.epu_event_code = { D_2, D_34 },
		},
		{
				.code = QE_DPAA_PE_BM_FBPR_READ_FREELIST_MONITOR_1, /* 195 */
				.word = 6,
				.epu_event_code = { D_3, D_35 },
		},
		{
				.code = QE_DPAA_PE_BM_FBPR_WRITE_FREELIST_MONITOR_2, /* 196 */
				.word = 6,
				.epu_event_code = { D_4, D_36 },
		},
		{
				.code = QE_DPAA_PE_BM_FBPR_READ_FREELIST_MONITOR_2, /* 197 */
				.word = 6,
				.epu_event_code = { D_5, D_37 },
		},
		{
				.code = QE_DPAA_PE_BM_FBPR_WRITE_FREELIST_MONITOR_3, /* 198 */
				.word = 6,
				.epu_event_code = { D_6, D_38 },
		},
		{
				.code = QE_DPAA_PE_BM_FBPR_READ_FREELIST_MONITOR_3, /* 199 */
				.word = 6,
				.epu_event_code = { D_7, D_39 },
		},
		{
				.code = QE_DPAA_PE_BM_FBPR_WRITE_FREELIST_MONITOR_4, /* 200 */
				.word = 6,
				.epu_event_code = { D_8, D_40 },
		},
		{
				.code = QE_DPAA_PE_BM_FBPR_READ_FREELIST_MONITOR_4, /* 201 */
				.word = 6,
				.epu_event_code = { D_9, D_41 },
		},
		{
				.code = QE_DPAA_PE_BM_FBPR_WRITE_FREELIST_MONITOR_5, /* 202 */
				.word = 6,
				.epu_event_code = { D_10, D_42 },
		},
		{
				.code = QE_DPAA_PE_BM_FBPR_READ_FREELIST_MONITOR_5, /* 203 */
				.word = 6,
				.epu_event_code = { D_11, D_43 },
		},
		{
				.code = QE_DPAA_PE_BM_FBPR_WRITE_FREELIST_MONITOR_6, /* 204 */
				.word = 6,
				.epu_event_code = { D_12, D_44 },
		},
		{
				.code = QE_DPAA_PE_BM_FBPR_READ_FREELIST_MONITOR_6, /* 205 */
				.word = 6,
				.epu_event_code = { D_13, D_45 },
		},
		{
				.code = QE_DPAA_PE_BM_FBPR_WRITE_FREELIST_MONITOR_7, /* 206 */
				.word = 6,
				.epu_event_code = { D_14, D_46 },
		},
		{
				.code = QE_DPAA_PE_BM_FBPR_READ_FREELIST_MONITOR_7, /* 207 */
				.word = 6,
				.epu_event_code = { D_15, D_47 },
		},
		{
				.code = QE_DPAA_PE_BM_RELEASE_BUF_EXCEEDS_CMD_MONITOR_0, /* 208 */
				.word = 6,
				.epu_event_code = { D_16, D_48 },
		},
		{
				.code = QE_DPAA_PE_BM_ACQUIRE_BUF_EXCEEDS_CMD_MONITOR_0, /* 209 */
				.word = 6,
				.epu_event_code = { D_17, D_49 },
		},
		{
				.code = QE_DPAA_PE_BM_RELEASE_BUF_EXCEEDS_CMD_MONITOR_1, /* 210 */
				.word = 6,
				.epu_event_code = { D_18, D_50 },
		},
		{
				.code = QE_DPAA_PE_BM_ACQUIRE_BUF_EXCEEDS_CMD_MONITOR_1, /* 211 */
				.word = 6,
				.epu_event_code = { D_19, D_51 },
		},
		{
				.code = QE_DPAA_PE_BM_RELEASE_BUF_EXCEEDS_CMD_MONITOR_2, /* 212 */
				.word = 6,
				.epu_event_code = { D_20, D_52 },
		},
		{
				.code = QE_DPAA_PE_BM_ACQUIRE_BUF_EXCEEDS_CMD_MONITOR_2, /* 213 */
				.word = 6,
				.epu_event_code = { D_21, D_53 },
		},
		{
				.code = QE_DPAA_PE_BM_RELEASE_BUF_EXCEEDS_CMD_MONITOR_3, /* 214 */
				.word = 6,
				.epu_event_code = { D_22, D_54 },
		},
		{
				.code = QE_DPAA_PE_BM_ACQUIRE_BUF_EXCEEDS_CMD_MONITOR_3, /* 215 */
				.word = 6,
				.epu_event_code = { D_23, D_55 },
		},
		{
				.code = QE_DPAA_PE_BM_RELEASE_BUF_EXCEEDS_CMD_MONITOR_4, /* 216 */
				.word = 6,
				.epu_event_code = { D_24, D_56 },
		},
		{
				.code = QE_DPAA_PE_BM_ACQUIRE_BUF_EXCEEDS_CMD_MONITOR_4, /* 217 */
				.word = 6,
				.epu_event_code = { D_25, D_57 },
		},
		{
				.code = QE_DPAA_PE_BM_RELEASE_BUF_EXCEEDS_CMD_MONITOR_5, /* 218 */
				.word = 6,
				.epu_event_code = { D_26, D_58 },
		},
		{
				.code = QE_DPAA_PE_BM_ACQUIRE_BUF_EXCEEDS_CMD_MONITOR_5, /* 219 */
				.word = 6,
				.epu_event_code = { D_27, D_59 },
		},
		{
				.code = QE_DPAA_PE_BM_RELEASE_BUF_EXCEEDS_CMD_MONITOR_6, /* 220 */
				.word = 6,
				.epu_event_code = { D_28, D_60 },
		},
		{
				.code = QE_DPAA_PE_BM_ACQUIRE_BUF_EXCEEDS_CMD_MONITOR_6, /* 221 */
				.word = 6,
				.epu_event_code = { D_29, D_61 },
		},
		{
				.code = QE_DPAA_PE_BM_RELEASE_BUF_EXCEEDS_CMD_MONITOR_7, /* 222 */
				.word = 6,
				.epu_event_code = { D_30, D_62 },
		},
		{
				.code = QE_DPAA_PE_BM_ACQUIRE_BUF_EXCEEDS_CMD_MONITOR_7, /* 223 */
				.word = 6,
				.epu_event_code = { D_31, D_63 },
		},
		{
				.code = QE_DPAA_PE_QM_PAMU_PPAACT_CACHE_MISS, /* 234 */
				.word = 7,
				.epu_event_code = { D_10, D_42 },
		},
		{
				.code = QE_DPAA_PE_QM_PAMU_PPAACT_CACHE_HIT, /* 235 */
				.word = 7,
				.epu_event_code = { D_11, D_43 },
		},
		{
				.code = QE_DPAA_PE_QM_PAMU_SPAACT_CACHE_MISS, /* 236 */
				.word = 7,
				.epu_event_code = { D_12, D_44 },
		},
		{
				.code = QE_DPAA_PE_QM_PAMU_SPAACT_CACHE_HIT, /* 237 */
				.word = 7,
				.epu_event_code = { D_13, D_45 },
		},
		{
				.code = QE_DPAA_PE_QM_PAMU_OMT_CACHE_MISS, /* 238 */
				.word = 7,
				.epu_event_code = { D_14, D_46 },
		},
		{
				.code = QE_DPAA_PE_QM_PAMU_OMT_CACHE_HIT, /* 239 */
				.word = 7,
				.epu_event_code = { D_15, D_47 },
		},
		{
				.code = QE_DPAA_PE_QM_PAMU_PPAACT_SNOOP_HIT, /* 240 */
				.word = 7,
				.epu_event_code = { D_16, D_48 },
		},
		{
				.code = QE_DPAA_PE_QM_PAMU_SPAACT_SNOOP_HIT, /* 241 */
				.word = 7,
				.epu_event_code = { D_17, D_49 },
		},
		{
				.code = QE_DPAA_PE_QM_PAMU_OMT_SNOOP_HIT, /* 242 */
				.word = 7,
				.epu_event_code = { D_18, D_50 },
		},
		{
				.code = QE_DPAA_PE_QM_PAMU_NO_ADDR_TRANS, /* 247 */
				.word = 7,
				.epu_event_code = { D_23, D_55 },
		},
		{
				.code = QE_DPAA_PE_QM_PAMU_WINDOW_ADDR_TRANS, /* 248 */
				.word = 7,
				.epu_event_code = { D_24, D_56 },
		},
		{
				.code = QE_DPAA_PE_QM_PAMU_NO_TRANS, /* 249 */
				.word = 7,
				.epu_event_code = { D_25, D_57 },
		},
		{
				.code = QE_DPAA_PE_QM_PAMU_IMMEDIATE_TRANS, /* 250 */
				.word = 7,
				.epu_event_code = { D_26, D_58 },
		},
		{
				.code = QE_DPAA_PE_QM_PAMU_INDEX_TRANS, /* 251 */
				.word = 7,
				.epu_event_code = { D_27, D_59 },
		},
		{
				.code = QE_DPAA_PE_PME_MIA_BUSY, /* 264 */
				.word = 8,
				.epu_event_code = { D_8, D_40 },
		},
		{
				.code = QE_DPAA_PE_PME_PMFA_BUSY1, /* 265 */
				.word = 8,
				.epu_event_code = { D_9, D_41 },
		},
		{
				.code = QE_DPAA_PE_PME_PMFA_BUSY2, /* 266 */
				.word = 8,
				.epu_event_code = { D_10, D_42 },
		},
		{
				.code = QE_DPAA_PE_PME_PMFA_BUSY3, /* 267 */
				.word = 8,
				.epu_event_code = { D_11, D_43 },
		},
		{
				.code = QE_DPAA_PE_PME_READ_SYSTEM_BUS, /* 268 */
				.word = 8,
				.epu_event_code = { D_12, D_44 },
		},
		{
				.code = QE_DPAA_PE_PME_WRITE_SYSTEM_BUS, /* 269 */
				.word = 8,
				.epu_event_code = { D_13, D_45 },
		},
		{
				.code = QE_DPAA_PE_PME_HITS_PMFA_CONTEXT_CACHE, /* 270 */
				.word = 8,
				.epu_event_code = { D_14, D_46 },
		},
		{
				.code = QE_DPAA_PE_PME_HITS_PMFA_RESIDUE_CACHE, /* 271 */
				.word = 8,
				.epu_event_code = { D_15, D_47 },
		},
		{
				.code = QE_DPAA_PE_PME_KES_BUSY1, /* 272 */
				.word = 8,
				.epu_event_code = { D_16, D_48 },
		},
		{
				.code = QE_DPAA_PE_PME_KES_BUSY2, /* 273 */
				.word = 8,
				.epu_event_code = { D_17, D_49 },
		},
		{
				.code = QE_DPAA_PE_PME_HITS_DXE_PATTERN_DESCRIPTION, /* 276 */
				.word = 8,
				.epu_event_code = { D_20, D_52 },
		},
		{
				.code = QE_DPAA_PE_PME_SRE_PREFETCH_SEQ_BUSY1, /* 277 */
				.word = 8,
				.epu_event_code = { D_21, D_53 },
		},
		{
				.code = QE_DPAA_PE_PME_SRE_PREFETCH_SEQ_BUSY2, /* 278 */
				.word = 8,
				.epu_event_code = { D_22, D_54 },
		},
		{
				.code = QE_DPAA_PE_PME_SRE_PREFETCH_SEQ_BUSY3, /* 279 */
				.word = 8,
				.epu_event_code = { D_23, D_55 },
		},
		{
				.code = QE_DPAA_PE_PME_SRE_EXECUTE_SEQ_BUSY1, /* 280 */
				.word = 8,
				.epu_event_code = { D_24, D_56 },
		},
		{
				.code = QE_DPAA_PE_PME_SRE_EXECUTE_SEQ_BUSY2, /* 281 */
				.word = 8,
				.epu_event_code = { D_25, D_57 },
		},
		{
				.code = QE_DPAA_PE_PME_SRE_EXECUTE_SEQ_BUSY3, /* 282 */
				.word = 8,
				.epu_event_code = { D_26, D_58 },
		},
		{
				.code = QE_DPAA_PE_PME_DXE_PREFETCH_SEQ_BUSY1, /* 283 */
				.word = 8,
				.epu_event_code = { D_27, D_59 },
		},
		{
				.code = QE_DPAA_PE_PME_DXE_PREFETCH_SEQ_BUSY2, /* 284 */
				.word = 8,
				.epu_event_code = { D_28, D_60 },
		},
		{
				.code = QE_DPAA_PE_PME_DXE_PREFETCH_SEQ_BUSY3, /* 285 */
				.word = 8,
				.epu_event_code = { D_29, D_61 },
		},
		{
				.code = QE_DPAA_PE_PME_DXE_EXECUTE_SEQ_BUSY1, /* 286 */
				.word = 8,
				.epu_event_code = { D_30, D_62 },
		},
		{
				.code = QE_DPAA_PE_PME_DXE_EXECUTE_SEQ_BUSY2, /* 287 */
				.word = 8,
				.epu_event_code = { D_31, D_63 },
		},
		{
				.code = QE_DPAA_PE_SEC4_DEQ_MARK_01, /* 288 */
				.word = 9,
				.epu_event_code = { D_0, D_32 },
		},
		{
				.code = QE_DPAA_PE_SEC4_DEQ_MARK_10, /* 289 */
				.word = 9,
				.epu_event_code = { D_1, D_33 },
		},
		{
				.code = QE_DPAA_PE_SEC4_DEQ_MARK_11, /* 290 */
				.word = 9,
				.epu_event_code = { D_2, D_34 },
		},
		{
				.code = QE_DPAA_PE_SEC4_ENQ_MARK_01, /* 291 */
				.word = 9,
				.epu_event_code = { D_3, D_35 },
		},
		{
				.code = QE_DPAA_PE_SEC4_ENQ_MARK_10, /* 292 */
				.word = 9,
				.epu_event_code = { D_4, D_36 },
		},
		{
				.code = QE_DPAA_PE_SEC4_ENQ_MARK_11, /* 293 */
				.word = 9,
				.epu_event_code = { D_5, D_37 },
		},
		{
				.code = QE_DPAA_PE_SEC4_JOB_INSERT_FROM_QUEUE_INTERFACE, /* 294 */
				.word = 9,
				.epu_event_code = { D_6, D_38 },
		},
		{
				.code = QE_DPAA_PE_SEC4_JOB_INSERT_FROM_RTIC, /* 295 */
				.word = 9,
				.epu_event_code = { D_7, D_39 },
		},
		{
				.code = QE_DPAA_PE_SEC4_JOB_INSERT_FROM_JOB_QUEUE0, /* 296 */
				.word = 9,
				.epu_event_code = { D_8, D_40 },
		},
		{
				.code = QE_DPAA_PE_SEC4_JOB_INSERT_FROM_JOB_QUEUE1 , /* 297 */
				.word = 9,
				.epu_event_code = { D_9, D_41 },
		},
		{
				.code = QE_DPAA_PE_SEC4_JOB_INSERT_FROM_JOB_QUEUE2, /* 298 */
				.word = 9,
				.epu_event_code = { D_10, D_42 },
		},
		{
				.code = QE_DPAA_PE_SEC4_JOB_INSERT_FROM_JOB_QUEUE3, /* 299 */
				.word = 9,
				.epu_event_code = { D_11, D_43 },
		},
		{
				.code = QE_DPAA_PE_SEC4_JOB_TO_DECO0, /* 300 */
				.word = 9,
				.epu_event_code = { D_12, D_44 },
		},
		{
				// AWAITS and IDLE's should be swapped due to Si bug
			//	.code = QE_DPAA_PE_SEC4_DECO0_IDLE, /* 301 */
				.code = QE_DPAA_PE_SEC4_DECO0_AWAITS_DMA, /* 302 */
				.word = 9,
				.epu_event_code = { D_13, D_45 },
		},
		{
				// AWAITS and IDLE's should be swapped due to Si bug
			//	.code = QE_DPAA_PE_SEC4_DECO0_AWAITS_DMA, /* 302 */
				.code = QE_DPAA_PE_SEC4_DECO0_IDLE, /* 301 */
				.word = 9,
				.epu_event_code = { D_14, D_46 },
		},
		{
				.code = QE_DPAA_PE_SEC4_CMD_IN_DECO0, /* 303 */
				.word = 9,
				.epu_event_code = { D_15, D_47 },
		},
		{
				.code = QE_DPAA_PE_SEC4_JOB_TO_DECO1, /* 304 */
				.word = 9,
				.epu_event_code = { D_16, D_48 },
		},
		{
				// AWAITS and IDLE's should be swapped due to Si bug
			//	.code = QE_DPAA_PE_SEC4_DECO1_IDLE, /* 305 */
				.code = QE_DPAA_PE_SEC4_DECO1_AWAITS_DMA, /* 306 */
				.word = 9,
				.epu_event_code = { D_17, D_49 },
		},
		{
				// AWAITS and IDLE's should be swapped due to Si bug
				//	.code = QE_DPAA_PE_SEC4_DECO1_AWAITS_DMA, /* 306 */
				.code = QE_DPAA_PE_SEC4_DECO1_IDLE, /* 305 */
				.word = 9,
				.epu_event_code = { D_18, D_50 },
		},
		{
				.code = QE_DPAA_PE_SEC4_CMD_IN_DECO1, /* 307 */
				.word = 9,
				.epu_event_code = { D_19, D_51 },
		},
		{
				.code = QE_DPAA_PE_SEC4_JOB_TO_DECO2, /* 308 */
				.word = 9,
				.epu_event_code = { D_20, D_52 },
		},
		{
				// AWAITS and IDLE's should be swapped due to Si bug
				// .code = QE_DPAA_PE_SEC4_DECO2_IDLE, /* 309 */
				.code = QE_DPAA_PE_SEC4_DECO2_AWAITS_DMA, /* 310 */
				.word = 9,
				.epu_event_code = { D_21, D_53 },
		},
		{
				// AWAITS and IDLE's should be swapped due to Si bug
				//.code = QE_DPAA_PE_SEC4_DECO2_AWAITS_DMA, /* 310 */
				.code = QE_DPAA_PE_SEC4_DECO2_IDLE, /* 309 */
				.word = 9,
				.epu_event_code = { D_22, D_54 },
		},
		{
				.code = QE_DPAA_PE_SEC4_CMD_IN_DECO2, /* 311 */
				.word = 9,
				.epu_event_code = { D_23, D_55 },
		},
		{
				.code = QE_DPAA_PE_SEC4_JOB_TO_DECO3, /* 312 */
				.word = 9,
				.epu_event_code = { D_24, D_56 },
		},
		{
				// AWAITS and IDLE's should be swapped due to Si bug
				// .code = QE_DPAA_PE_SEC4_DECO3_IDLE, /* 313 */
				.code = QE_DPAA_PE_SEC4_DECO3_AWAITS_DMA, /* 314 */
				.word = 9,
				.epu_event_code = { D_25, D_57 },
		},
		{
				// AWAITS and IDLE's should be swapped due to Si bug
				// .code = QE_DPAA_PE_SEC4_DECO3_AWAITS_DMA, /* 314 */
				.code = QE_DPAA_PE_SEC4_DECO3_IDLE, /* 313 */
				.word = 9,
				.epu_event_code = { D_26, D_58 },
		},
		{
				.code = QE_DPAA_PE_SEC4_CMD_IN_DECO3, /* 315 */
				.word = 9,
				.epu_event_code = { D_27, D_59 },
		},
		{
				.code = QE_DPAA_PE_SEC4_JOB_TO_DECO4, /* 316 */
				.word = 9,
				.epu_event_code = { D_28, D_60 },
		},
		{
				// AWAITS and IDLE's should be swapped due to Si bug
				//.code = QE_DPAA_PE_SEC4_DECO4_IDLE, /* 317 */
				.code = QE_DPAA_PE_SEC4_DECO4_AWAITS_DMA, /* 318 */
				.word = 9,
				.epu_event_code = { D_29, D_61 },
		},
		{
				// AWAITS and IDLE's should be swapped due to Si bug
				//.code = QE_DPAA_PE_SEC4_DECO4_AWAITS_DMA, /* 318 */
				.code = QE_DPAA_PE_SEC4_DECO4_IDLE, /* 317 */
				.word = 9,
				.epu_event_code = { D_30, D_62 },
		},
		{
				.code = QE_DPAA_PE_SEC4_CMD_IN_DECO4, /* 319 */
				.word = 9,
				.epu_event_code = { D_31, D_63 },
		},
		{
				.code = QE_DPAA_PE_SEC4_PAMU_PPAACT_CACHE_MISS, /* 330 */
				.word = 10,
				.epu_event_code = { D_10, D_42 },
		},
		{
				.code = QE_DPAA_PE_SEC4_PAMU_PPAACT_CACHE_HIT, /* 331 */
				.word = 10,
				.epu_event_code = { D_11, D_43 },
		},
		{
				.code = QE_DPAA_PE_SEC4_PAMU_SPAACT_CACHE_MISS, /* 332 */
				.word = 10,
				.epu_event_code = { D_12, D_44 },
		},
		{
				.code = QE_DPAA_PE_SEC4_PAMU_SPAACT_CACHE_HIT, /* 333 */
				.word = 10,
				.epu_event_code = { D_13, D_45 },
		},
		{
				.code = QE_DPAA_PE_SEC4_PAMU_OMT_CACHE_MISS, /* 334 */
				.word = 10,
				.epu_event_code = { D_14, D_46 },
		},
		{
				.code = QE_DPAA_PE_SEC4_PAMU_OMT_CACHE_HIT, /* 335 */
				.word = 10,
				.epu_event_code = { D_15, D_47 },
		},
		{
				.code = QE_DPAA_PE_SEC4_PAMU_PPAACT_SNOOP_HIT, /* 336 */
				.word = 10,
				.epu_event_code = { D_16, D_48 },
		},
		{
				.code = QE_DPAA_PE_SEC4_PAMU_SPAACT_SNOOP_HIT, /* 337 */
				.word = 10,
				.epu_event_code = { D_17, D_49 },
		},
		{
				.code = QE_DPAA_PE_SEC4_PAMU_OMT_SNOOP_HIT, /* 338 */
				.word = 10,
				.epu_event_code = { D_18, D_50 },
		},
		{
				.code = QE_DPAA_PE_SEC4_PAMU_NO_ADDR_TRANS, /* 343 */
				.word = 10,
				.epu_event_code = { D_23, D_55 },
		},
		{
				.code = QE_DPAA_PE_SEC4_PAMU_WINDOW_ADDR_TRANS, /* 344 */
				.word = 10,
				.epu_event_code = { D_24, D_56 },
		},
		{
				.code = QE_DPAA_PE_SEC4_PAMU_NO_TRANS, /* 345 */
				.word = 10,
				.epu_event_code = { D_25, D_57 },
		},
		{
				.code = QE_DPAA_PE_SEC4_PAMU_IMMEDIATE_TRANS, /* 346 */
				.word = 10,
				.epu_event_code = { D_26, D_58 },
		},
		{
				.code = QE_DPAA_PE_SEC4_PAMU_INDEX_TRANS, /* 347 */
				.word = 10,
				.epu_event_code = { D_27, D_59 },
		},
		{
				.code = QE_DPAA_PE_FM1_GMAC_USED_RX_FIFO_GE, /* 352 */
				.word = 11,
				.epu_event_code = { D_0, D_32 },
		},
		{
				.code = QE_DPAA_PE_FM1_DTSEC0_USED_RX_FIFO_GE, /* 353 */
				.word = 11,
				.epu_event_code = { D_1, D_33 },
		},
		{
				.code = QE_DPAA_PE_FM1_DTSEC1_USED_RX_FIFO_GE, /* 354 */
				.word = 11,
				.epu_event_code = { D_2, D_34 },
		},
		{
				.code = QE_DPAA_PE_FM1_DTSEC2_USED_RX_FIFO_GE, /* 355 */
				.word = 11,
				.epu_event_code = { D_3, D_35 },
		},
		{
				.code = QE_DPAA_PE_FM1_DTSEC3_USED_RX_FIFO_GE, /* 356 */
				.word = 11,
				.epu_event_code = { D_4, D_36 },
		},
		{
				.code = QE_DPAA_PE_FM1_PAUSE_FOR_GMAC, /* 357 */
				.word = 11,
				.epu_event_code = { D_5, D_37 },
		},
		{
				.code = QE_DPAA_PE_FM1_PAUSE_FOR_DTSEC0, /* 358 */
				.word = 11,
				.epu_event_code = { D_6, D_38 },
		},
		{
				.code = QE_DPAA_PE_FM1_PAUSE_FOR_DTSEC1, /* 359 */
				.word = 11,
				.epu_event_code = { D_7, D_39 },
		},
		{
				.code = QE_DPAA_PE_FM1_PAUSE_FOR_DTSEC2, /* 360 */
				.word = 11,
				.epu_event_code = { D_8, D_40 },
		},
		{
				.code = QE_DPAA_PE_FM1_PAUSE_FOR_DTSEC3, /* 361 */
				.word = 11,
				.epu_event_code = { D_9, D_41 },
		},
		{
				.code = QE_DPAA_PE_FM1_BMI_TRAP_MARK_01, /* 362 */
				.word = 11,
				.epu_event_code = { D_10, D_42 },
		},
		{
				.code = QE_DPAA_PE_FM1_BMI_TRAP_MARK_10, /* 363 */
				.word = 11,
				.epu_event_code = { D_11, D_43 },
		},
		{
				.code = QE_DPAA_PE_FM1_BMI_TRAP_MARK_11, /* 364 */
				.word = 11,
				.epu_event_code = { D_12, D_44 },
		},
		{
				.code = QE_DPAA_PE_FM1_DEFAULT_QUEUE_USED, /* 365 */
				.word = 11,
				.epu_event_code = { D_13, D_45 },
		},
		{
				.code = QE_DPAA_PE_FM1_KEYGEN_TRAP_MARK_01, /* 366 */
				.word = 11,
				.epu_event_code = { D_14, D_46 },
		},
		{
				.code = QE_DPAA_PE_FM1_KEYGEN_TRAP_MARK_10, /* 367 */
				.word = 11,
				.epu_event_code = { D_15, D_47 },
		},
		{
				.code = QE_DPAA_PE_FM1_KEYGEN_TRAP_MARK_11, /* 368 */
				.word = 11,
				.epu_event_code = { D_16, D_48 },
		},
		{
				.code = QE_DPAA_PE_FM1_PARSER_TRAP_MARK_01, /* 369 */
				.word = 11,
				.epu_event_code = { D_17, D_49 },
		},
		{
				.code = QE_DPAA_PE_FM1_PARSER_TRAP_MARK_10, /* 370 */
				.word = 11,
				.epu_event_code = { D_18, D_50 },
		},
		{
				.code = QE_DPAA_PE_FM1_PARSER_TRAP_MARK_11, /* 371 */
				.word = 11,
				.epu_event_code = { D_19, D_51 },
		},
		{
				.code = QE_DPAA_PE_FM1_CHANGED_TO_RED, /* 372 */
				.word = 11,
				.epu_event_code = { D_20, D_52 },
		},
		{
				.code = QE_DPAA_PE_FM1_CHANGED_TO_YELLOW, /* 373 */
				.word = 11,
				.epu_event_code = { D_21, D_53 },
		},
		{
				.code = QE_DPAA_PE_FM1_POLICER_TRAP_MARK_01, /* 374 */
				.word = 11,
				.epu_event_code = { D_22, D_54 },
		},
		{
				.code = QE_DPAA_PE_FM1_POLICER_TRAP_MARK_10, /* 375 */
				.word = 11,
				.epu_event_code = { D_23, D_55 },
		},
		{
				.code = QE_DPAA_PE_FM1_POLICER_TRAP_MARK_11, /* 376 */
				.word = 11,
				.epu_event_code = { D_24, D_56 },
		},
		{
				.code = QE_DPAA_PE_FM1_CLASSIFIER1_TRAP_MARK_01, /* 377 */
				.word = 11,
				.epu_event_code = { D_25, D_57 },
		},
		{
				.code = QE_DPAA_PE_FM1_CLASSIFIER1_TRAP_MARK_10, /* 378 */
				.word = 11,
				.epu_event_code = { D_26, D_58 },
		},
		{
				.code = QE_DPAA_PE_FM1_CLASSIFIER1_TRAP_MARK_11, /* 379 */
				.word = 11,
				.epu_event_code = { D_27, D_59 },
		},
		{
				.code = QE_DPAA_PE_FM1_CLASSIFIER2_TRAP_MARK_01, /* 380 */
				.word = 11,
				.epu_event_code = { D_28, D_60 },
		},
		{
				.code = QE_DPAA_PE_FM1_CLASSIFIER2_TRAP_MARK_10, /* 381 */
				.word = 11,
				.epu_event_code = { D_29, D_61 },
		},
		{
				.code = QE_DPAA_PE_FM1_CLASSIFIER2_TRAP_MARK_11, /* 382 */
				.word = 11,
				.epu_event_code = { D_30, D_62 },
		},
		{
				.code = QE_DPAA_PE_FM1_DMA_CMD_QUEUE_EMERGENCY, /* 384 */
				.word = 12,
				.epu_event_code = { D_0, D_32 },
		},
		{
				.code = QE_DPAA_PE_FM1_DMA_READ_BUF_EMERGENCY, /* 385 */
				.word = 12,
				.epu_event_code = { D_1, D_33 },
		},
		{
				.code = QE_DPAA_PE_FM1_DMA_WRITE_BUF_EMERGENCY, /* 386 */
				.word = 12,
				.epu_event_code = { D_2, D_34 },
		},
		{
				.code = QE_DPAA_PE_FM1_DMA_FPM_WAIT_EMERGENCY, /* 387 */
				.word = 12,
				.epu_event_code = { D_3, D_35 },
		},
		{
				.code = QE_DPAA_PE_FM1_DMA_FPM_SOS_EMERGENCY, /* 388 */
				.word = 12,
				.epu_event_code = { D_4, D_36 },
		},
		{
				.code = QE_DPAA_PE_FM1_QMI_TRAP_MARK_01, /* 389 */
				.word = 12,
				.epu_event_code = { D_5, D_37 },
		},
		{
				.code = QE_DPAA_PE_FM1_QMI_TRAP_MARK_10, /* 390 */
				.word = 12,
				.epu_event_code = { D_6, D_38 },
		},
		{
				.code = QE_DPAA_PE_FM1_QMI_TRAP_MARK_11, /* 391 */
				.word = 12,
				.epu_event_code = { D_7, D_39 },
		},
		{
				.code = QE_DPAA_PE_SEC4_DEQ_MARK_01_DUP, /* 401 */
				.word = 12,
				.epu_event_code = { D_17, D_49 },
		},
		{
				.code = QE_DPAA_PE_SEC4_DEQ_MARK_10_DUP, /* 402 */
				.word = 12,
				.epu_event_code = { D_18, D_50 },
		},
		{
				.code = QE_DPAA_PE_SEC4_DEQ_MARK_11_DUP, /* 403 */
				.word = 12,
				.epu_event_code = { D_19, D_51 },
		},
		{
				.code = QE_DPAA_PE_SEC4_ENQ_MARK_01_DUP, /* 404 */
				.word = 12,
				.epu_event_code = { D_20, D_52 },
		},
		{
				.code = QE_DPAA_PE_SEC4_ENQ_MARK_10_DUP, /* 405 */
				.word = 12,
				.epu_event_code = { D_21, D_53 },
		},
		{
				.code = QE_DPAA_PE_SEC4_ENQ_MARK_11_DUP, /* 406 */
				.word = 12,
				.epu_event_code = { D_22, D_54 },
		},
		{
				.code = QE_DPAA_PE_FM2_DMA_CMD_QUEUE_EMERGENCY, /* 407 */
				.word = 12,
				.epu_event_code = { D_23, D_55 },
		},
		{
				.code = QE_DPAA_PE_FM2_DMA_READ_BUF_EMERGENCY, /* 408 */
				.word = 12,
				.epu_event_code = { D_24, D_56 },
		},
		{
				.code = QE_DPAA_PE_FM2_DMA_WRITE_BUF_EMERGENCY, /* 409 */
				.word = 12,
				.epu_event_code = { D_25, D_57 },
		},
		{
				.code = QE_DPAA_PE_FM2_DMA_FPM_WAIT_EMERGENCY, /* 410 */
				.word = 12,
				.epu_event_code = { D_26, D_58 },
		},
		{
				.code = QE_DPAA_PE_FM2_DMA_FPM_SOS_EMERGENCY, /* 411 */
				.word = 12,
				.epu_event_code = { D_27, D_59 },
		},
		{
				.code = QE_DPAA_PE_FM2_QMI_TRAP_MARK_01, /* 412 */
				.word = 12,
				.epu_event_code = { D_28, D_60 },
		},
		{
				.code = QE_DPAA_PE_FM2_QMI_TRAP_MARK_10, /* 413 */
				.word = 12,
				.epu_event_code = { D_29, D_61 },
		},
		{
				.code = QE_DPAA_PE_FM2_QMI_TRAP_MARK_11, /* 414 */
				.word = 12,
				.epu_event_code = { D_30, D_62 },
		},
		{
				.code = QE_DPAA_PE_FM1_PAMU_PPAACT_CACHE_MISS, /* 426 */
				.word = 13,
				.epu_event_code = { D_10, D_42 },
		},
		{
				.code = QE_DPAA_PE_FM1_PAMU_PPAACT_CACHE_HIT, /* 427 */
				.word = 13,
				.epu_event_code = { D_11, D_43 },
		},
		{
				.code = QE_DPAA_PE_FM1_PAMU_SPAACT_CACHE_MISS, /* 428 */
				.word = 13,
				.epu_event_code = { D_12, D_44 },
		},
		{
				.code = QE_DPAA_PE_FM1_PAMU_SPAACT_CACHE_HIT, /* 429 */
				.word = 13,
				.epu_event_code = { D_13, D_45 },
		},
		{
				.code = QE_DPAA_PE_FM1_PAMU_OMT_CACHE_MISS, /* 430 */
				.word = 13,
				.epu_event_code = { D_14, D_46 },
		},
		{
				.code = QE_DPAA_PE_FM1_PAMU_OMT_CACHE_HIT, /* 431 */
				.word = 13,
				.epu_event_code = { D_15, D_47 },
		},
		{
				.code = QE_DPAA_PE_FM1_PAMU_PPAACT_SNOOP_HIT, /* 432 */
				.word = 13,
				.epu_event_code = { D_16, D_48 },
		},
		{
				.code = QE_DPAA_PE_FM1_PAMU_SPAACT_SNOOP_HIT, /* 433 */
				.word = 13,
				.epu_event_code = { D_17, D_49 },
		},
		{
				.code = QE_DPAA_PE_FM1_PAMU_OMT_SNOOP_HIT, /* 434 */
				.word = 13,
				.epu_event_code = { D_18, D_50 },
		},
		{
				.code = QE_DPAA_PE_FM1_PAMU_NO_ADDR_TRANS, /* 439 */
				.word = 13,
				.epu_event_code = { D_23, D_55 },
		},
		{
				.code = QE_DPAA_PE_FM1_PAMU_WINDOW_ADDR_TRANS, /* 440 */
				.word = 13,
				.epu_event_code = { D_24, D_56 },
		},
		{
				.code = QE_DPAA_PE_FM1_PAMU_NO_TRANS, /* 441 */
				.word = 13,
				.epu_event_code = { D_25, D_57 },
		},
		{
				.code = QE_DPAA_PE_FM1_PAMU_IMMEDIATE_TRANS, /* 442 */
				.word = 13,
				.epu_event_code = { D_26, D_58 },
		},
		{
				.code = QE_DPAA_PE_FM1_PAMU_INDEX_TRANS, /* 443 */
				.word = 13,
				.epu_event_code = { D_27, D_59 },
		},
		{
				.code = QE_DPAA_PE_FM2_GMAC_USED_RX_FIFO_GE, /* 448 */
				.word = 14,
				.epu_event_code = { D_0, D_32 },
		},
		{
				.code = QE_DPAA_PE_FM2_DTSEC0_USED_RX_FIFO_GE, /* 449 */
				.word = 14,
				.epu_event_code = { D_1, D_33 },
		},
		{
				.code = QE_DPAA_PE_FM2_DTSEC1_USED_RX_FIFO_GE, /* 450 */
				.word = 14,
				.epu_event_code = { D_2, D_34 },
		},
		{
				.code = QE_DPAA_PE_FM2_DTSEC2_USED_RX_FIFO_GE, /* 451 */
				.word = 14,
				.epu_event_code = { D_3, D_35 },
		},
		{
				.code = QE_DPAA_PE_FM2_DTSEC3_USED_RX_FIFO_GE, /* 452 */
				.word = 14,
				.epu_event_code = { D_4, D_36 },
		},
		{
				.code = QE_DPAA_PE_FM2_PAUSE_FOR_GMAC, /* 453 */
				.word = 14,
				.epu_event_code = { D_5, D_37 },
		},
		{
				.code = QE_DPAA_PE_FM2_PAUSE_FOR_DTSEC0, /* 454 */
				.word = 14,
				.epu_event_code = { D_6, D_38 },
		},
		{
				.code = QE_DPAA_PE_FM2_PAUSE_FOR_DTSEC1, /* 455 */
				.word = 14,
				.epu_event_code = { D_7, D_39 },
		},
		{
				.code = QE_DPAA_PE_FM2_PAUSE_FOR_DTSEC2, /* 456 */
				.word = 14,
				.epu_event_code = { D_8, D_40 },
		},
		{
				.code = QE_DPAA_PE_FM2_PAUSE_FOR_DTSEC3, /* 457 */
				.word = 14,
				.epu_event_code = { D_9, D_41 },
		},
		{
				.code = QE_DPAA_PE_FM2_BMI_TRAP_MARK_01, /* 458 */
				.word = 14,
				.epu_event_code = { D_10, D_42 },
		},
		{
				.code = QE_DPAA_PE_FM2_BMI_TRAP_MARK_10, /* 459 */
				.word = 14,
				.epu_event_code = { D_11, D_43 },
		},
		{
				.code = QE_DPAA_PE_FM2_BMI_TRAP_MARK_11, /* 460 */
				.word = 14,
				.epu_event_code = { D_12, D_44 },
		},
		{
				.code = QE_DPAA_PE_FM2_DEFAULT_QUEUE_USED, /* 461 */
				.word = 14,
				.epu_event_code = { D_13, D_45 },
		},
		{
				.code = QE_DPAA_PE_FM2_KEYGEN_TRAP_MARK_01, /* 462 */
				.word = 14,
				.epu_event_code = { D_14, D_46 },
		},
		{
				.code = QE_DPAA_PE_FM2_KEYGEN_TRAP_MARK_10, /* 463 */
				.word = 14,
				.epu_event_code = { D_15, D_47 },
		},
		{
				.code = QE_DPAA_PE_FM2_KEYGEN_TRAP_MARK_11, /* 464 */
				.word = 14,
				.epu_event_code = { D_16, D_48 },
		},
		{
				.code = QE_DPAA_PE_FM2_PARSER_TRAP_MARK_01, /* 465 */
				.word = 14,
				.epu_event_code = { D_17, D_49 },
		},
		{
				.code = QE_DPAA_PE_FM2_PARSER_TRAP_MARK_10, /* 466 */
				.word = 14,
				.epu_event_code = { D_18, D_50 },
		},
		{
				.code = QE_DPAA_PE_FM2_PARSER_TRAP_MARK_11, /* 467 */
				.word = 14,
				.epu_event_code = { D_19, D_51 },
		},
		{
				.code = QE_DPAA_PE_FM2_CHANGED_TO_RED, /* 468 */
				.word = 14,
				.epu_event_code = { D_20, D_52 },
		},
		{
				.code = QE_DPAA_PE_FM2_CHANGED_TO_YELLOW, /* 469 */
				.word = 14,
				.epu_event_code = { D_21, D_53 },
		},
		{
				.code = QE_DPAA_PE_FM2_POLICER_TRAP_MARK_01, /* 470 */
				.word = 14,
				.epu_event_code = { D_22, D_54 },
		},
		{
				.code = QE_DPAA_PE_FM2_POLICER_TRAP_MARK_10, /* 471 */
				.word = 14,
				.epu_event_code = { D_23, D_55 },
		},
		{
				.code = QE_DPAA_PE_FM2_POLICER_TRAP_MARK_11, /* 472 */
				.word = 14,
				.epu_event_code = { D_24, D_56 },
		},
		{
				.code = QE_DPAA_PE_FM2_CLASSIFIER1_TRAP_MARK_01, /* 473 */
				.word = 14,
				.epu_event_code = { D_25, D_57 },
		},
		{
				.code = QE_DPAA_PE_FM2_CLASSIFIER1_TRAP_MARK_10, /* 474 */
				.word = 14,
				.epu_event_code = { D_26, D_58 },
		},
		{
				.code = QE_DPAA_PE_FM2_CLASSIFIER1_TRAP_MARK_11, /* 475 */
				.word = 14,
				.epu_event_code = { D_27, D_59 },
		},
		{
				.code = QE_DPAA_PE_FM2_CLASSIFIER2_TRAP_MARK_01, /* 476 */
				.word = 14,
				.epu_event_code = { D_28, D_60 },
		},
		{
				.code = QE_DPAA_PE_FM2_CLASSIFIER2_TRAP_MARK_10, /* 477 */
				.word = 14,
				.epu_event_code = { D_29, D_61 },
		},
		{
				.code = QE_DPAA_PE_FM2_CLASSIFIER2_TRAP_MARK_11, /* 478 */
				.word = 14,
				.epu_event_code = { D_30, D_62 },
		},
		{
				.code = QE_DPAA_PE_PME_READ_SYSTEM_BUS_DUP, /* 488 */
				.word = 15,
				.epu_event_code = { D_8, D_40 },
		},
		{
				.code = QE_DPAA_PE_PME_WRITE_SYSTEM_BUS_DUP, /* 489 */
				.word = 15,
				.epu_event_code = { D_9, D_41 },
		},
		{
				.code = QE_DPAA_PE_FM2_PAMU_PPAACT_CACHE_MISS, /* 522 */
				.word = 16,
				.epu_event_code = { D_10, D_42 },
		},
		{
				.code = QE_DPAA_PE_FM2_PAMU_PPAACT_CACHE_HIT, /* 523 */
				.word = 16,
				.epu_event_code = { D_11, D_43 },
		},
		{
				.code = QE_DPAA_PE_FM2_PAMU_SPAACT_CACHE_MISS, /* 524 */
				.word = 16,
				.epu_event_code = { D_12, D_44 },
		},
		{
				.code = QE_DPAA_PE_FM2_PAMU_SPAACT_CACHE_HIT, /* 525 */
				.word = 16,
				.epu_event_code = { D_13, D_45 },
		},
		{
				.code = QE_DPAA_PE_FM2_PAMU_OMT_CACHE_MISS, /* 526 */
				.word = 16,
				.epu_event_code = { D_14, D_46 },
		},
		{
				.code = QE_DPAA_PE_FM2_PAMU_OMT_CACHE_HIT, /* 527 */
				.word = 16,
				.epu_event_code = { D_15, D_47 },
		},
		{
				.code = QE_DPAA_PE_FM2_PAMU_PPAACT_SNOOP_HIT, /* 528 */
				.word = 16,
				.epu_event_code = { D_16, D_48 },
		},
		{
				.code = QE_DPAA_PE_FM2_PAMU_SPAACT_SNOOP_HIT, /* 529 */
				.word = 16,
				.epu_event_code = { D_17, D_49 },
		},
		{
				.code = QE_DPAA_PE_FM2_PAMU_OMT_SNOOP_HIT, /* 530 */
				.word = 16,
				.epu_event_code = { D_18, D_50 },
		},
		{
				.code = QE_DPAA_PE_FM2_PAMU_NO_ADDR_TRANS, /* 535 */
				.word = 16,
				.epu_event_code = { D_23, D_55 },
		},
		{
				.code = QE_DPAA_PE_FM2_PAMU_WINDOW_ADDR_TRANS, /* 536 */
				.word = 16,
				.epu_event_code = { D_24, D_56 },
		},
		{
				.code = QE_DPAA_PE_FM2_PAMU_NO_TRANS, /* 537 */
				.word = 16,
				.epu_event_code = { D_25, D_57 },
		},
		{
				.code = QE_DPAA_PE_FM2_PAMU_IMMEDIATE_TRANS, /* 538 */
				.word = 16,
				.epu_event_code = { D_26, D_58 },
		},
		{
				.code = QE_DPAA_PE_FM2_PAMU_INDEX_TRANS, /* 539 */
				.word = 16,
				.epu_event_code = { D_27, D_59 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_DEQ_EXCEEDS_THRESHOLD_A_DUP, /* 544 */
				.word = 17,
				.epu_event_code = { D_0, D_32 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_DEQ_EXCEEDS_THRESHOLD_B_DUP, /* 545 */
				.word = 17,
				.epu_event_code = { D_1, D_33 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_DEQ_EXCEEDS_THRESHOLD_C_DUP, /* 546 */
				.word = 17,
				.epu_event_code = { D_2, D_34 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_DEQ_EXCEEDS_THRESHOLD_D_DUP, /* 547 */
				.word = 17,
				.epu_event_code = { D_3, D_35 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_ENQ_CMD_RECEIVED_DUP, /* 552 */
				.word = 17,
				.epu_event_code = { D_8, D_40 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_ENQ_CMD_FIFO_FULL_DUP, /* 553 */
				.word = 17,
				.epu_event_code = { D_9, D_41 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_DEQ_CMD_FIFO_FULL_DUP, /* 554 */
				.word = 17,
				.epu_event_code = { D_10, D_42 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_DEQ_RSP_FIFO_FULL_DUP, /* 555 */
				.word = 17,
				.epu_event_code = { D_11, D_43 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_ENQ_SEQ_DISPATCH_DUP, /* 556 */
				.word = 17,
				.epu_event_code = { D_12, D_44 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_ENQ_SEQ_DISPATCH_FIFO_FULL_DUP, /* 557 */
				.word = 17,
				.epu_event_code = { D_13, D_45 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_DEQ_SEQ_DELIVERS_1_DUP, /* 558 */
				.word = 17,
				.epu_event_code = { D_14, D_46 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_DEQ_SEQ_DELIVERS_2_DUP, /* 559 */
				.word = 17,
				.epu_event_code = { D_15, D_47 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_DEQ_SEQ_DELIVERS_3_DUP, /* 560 */
				.word = 17,
				.epu_event_code = { D_16, D_48 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_DEQ_CMD_DISPATCH_FIFO_FULL_DUP, /* 561 */
				.word = 17,
				.epu_event_code = { D_17, D_49 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_FRAME_ENQ_REJECTED_DUP, /* 562 */
				.word = 17,
				.epu_event_code = { D_18, D_50 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_FRAME_ENQ_WRED_REJECTED_DUP, /* 563 */
				.word = 17,
				.epu_event_code = { D_19, D_51 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_FRAME_ENQ_TD_CONG_REJECTED_DUP, /* 564 */
				.word = 17,
				.epu_event_code = { D_20, D_52 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP0_FRAME_ENQ_TD_FQ_REJECTED_DUP, /* 565 */
				.word = 17,
				.epu_event_code = { D_21, D_53 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_ENQ_MARK_01_DUP, /* 566 */
				.word = 17,
				.epu_event_code = { D_22, D_54 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_ENQ_MARK_10_DUP, /* 567 */
				.word = 17,
				.epu_event_code = { D_23, D_55 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_ENQ_MARK_11_DUP, /* 568 */
				.word = 17,
				.epu_event_code = { D_24, D_56 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_DEQ_MARK_01_DUP, /* 569 */
				.word = 17,
				.epu_event_code = { D_25, D_57 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_DEQ_MARK_10_DUP, /* 570 */
				.word = 17,
				.epu_event_code = { D_26, D_58 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_DEQ_MARK_11_DUP, /* 571 */
				.word = 17,
				.epu_event_code = { D_27, D_59 },
		},
		{
				.code = QE_DPAA_PE_QM_ORL_FRAME_ENQ_MARK_01_DUP, /* 572 */
				.word = 17,
				.epu_event_code = { D_28, D_60 },
		},
		{
				.code = QE_DPAA_PE_QM_ORL_FRAME_ENQ_MARK_10_DUP, /* 573 */
				.word = 17,
				.epu_event_code = { D_29, D_61 },
		},
		{
				.code = QE_DPAA_PE_QM_ORL_FRAME_ENQ_MARK_11_DUP, /* 574 */
				.word = 17,
				.epu_event_code = { D_30, D_62 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_DEQ_EXCEEDS_THRESHOLD_A_DUP, /* 576 */
				.word = 18,
				.epu_event_code = { D_0, D_32 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_DEQ_EXCEEDS_THRESHOLD_B_DUP, /* 577 */
				.word = 18,
				.epu_event_code = { D_1, D_33 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_DEQ_EXCEEDS_THRESHOLD_C_DUP, /* 578 */
				.word = 18,
				.epu_event_code = { D_2, D_34 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_DEQ_EXCEEDS_THRESHOLD_D_DUP, /* 579 */
				.word = 18,
				.epu_event_code = { D_3, D_35 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_ENQ_CMD_RECEIVED_DUP, /* 584 */
				.word = 18,
				.epu_event_code = { D_8, D_40 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_ENQ_CMD_FIFO_FULL_DUP, /* 585 */
				.word = 18,
				.epu_event_code = { D_9, D_41 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_DEQ_CMD_FIFO_FULL_DUP, /* 586 */
				.word = 18,
				.epu_event_code = { D_10, D_42 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_DEQ_RSP_FIFO_FULL_DUP, /* 587 */
				.word = 18,
				.epu_event_code = { D_11, D_43 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_ENQ_SEQ_DISPATCH_DUP, /* 588 */
				.word = 18,
				.epu_event_code = { D_12, D_44 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_ENQ_SEQ_DISPATCH_FIFO_FULL_DUP, /* 589 */
				.word = 18,
				.epu_event_code = { D_13, D_45 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_DEQ_SEQ_DELIVERS_1_DUP, /* 590 */
				.word = 18,
				.epu_event_code = { D_14, D_46 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_DEQ_SEQ_DELIVERS_2_DUP, /* 591 */
				.word = 18,
				.epu_event_code = { D_15, D_47 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_DEQ_SEQ_DELIVERS_3_DUP, /* 592 */
				.word = 18,
				.epu_event_code = { D_16, D_48 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_DEQ_CMD_DISPATCH_FIFO_FULL_DUP, /* 593 */
				.word = 18,
				.epu_event_code = { D_17, D_49 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_FRAME_ENQ_REJECTED_DUP, /* 594 */
				.word = 18,
				.epu_event_code = { D_18, D_50 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_FRAME_ENQ_WRED_REJECTED_DUP, /* 595 */
				.word = 18,
				.epu_event_code = { D_19, D_51 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_FRAME_ENQ_TD_CONG_REJECTED_DUP, /* 596 */
				.word = 18,
				.epu_event_code = { D_20, D_52 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP1_FRAME_ENQ_TD_FQ_REJECTED_DUP, /* 597 */
				.word = 18,
				.epu_event_code = { D_21, D_53 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_ENQ_MARK_01_DUP2, /* 598 */
				.word = 18,
				.epu_event_code = { D_22, D_54 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_ENQ_MARK_10_DUP2, /* 599 */
				.word = 18,
				.epu_event_code = { D_23, D_55 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_ENQ_MARK_11_DUP2, /* 600 */
				.word = 18,
				.epu_event_code = { D_24, D_56 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_DEQ_MARK_01_DUP2, /* 601 */
				.word = 18,
				.epu_event_code = { D_25, D_57 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_DEQ_MARK_10_DUP2, /* 602 */
				.word = 18,
				.epu_event_code = { D_26, D_58 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_DEQ_MARK_11_DUP2, /* 603 */
				.word = 18,
				.epu_event_code = { D_27, D_59 },
		},
		{
				.code = QE_DPAA_PE_QM_ORL_FRAME_ENQ_MARK_01_DUP2, /* 604 */
				.word = 18,
				.epu_event_code = { D_28, D_60 },
		},
		{
				.code = QE_DPAA_PE_QM_ORL_FRAME_ENQ_MARK_10_DUP2, /* 605 */
				.word = 18,
				.epu_event_code = { D_29, D_61 },
		},
		{
				.code = QE_DPAA_PE_QM_ORL_FRAME_ENQ_MARK_11_DUP2, /* 606 */
				.word = 18,
				.epu_event_code = { D_30, D_62 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_DEQ_EXCEEDS_THRESHOLD_A_DUP, /* 608 */
				.word = 19,
				.epu_event_code = { D_0, D_32 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_DEQ_EXCEEDS_THRESHOLD_B_DUP, /* 609 */
				.word = 19,
				.epu_event_code = { D_1, D_33 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_DEQ_EXCEEDS_THRESHOLD_C_DUP, /* 610 */
				.word = 19,
				.epu_event_code = { D_2, D_34 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_DEQ_EXCEEDS_THRESHOLD_D_DUP, /* 611 */
				.word = 19,
				.epu_event_code = { D_3, D_35 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_ENQ_CMD_RECEIVED_DUP, /* 616 */
				.word = 19,
				.epu_event_code = { D_8, D_40 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_ENQ_CMD_FIFO_FULL_DUP, /* 617 */
				.word = 19,
				.epu_event_code = { D_9, D_41 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_DEQ_CMD_FIFO_FULL_DUP, /* 618 */
				.word = 19,
				.epu_event_code = { D_10, D_42 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_DEQ_RSP_FIFO_FULL_DUP, /* 619 */
				.word = 19,
				.epu_event_code = { D_11, D_43 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_ENQ_SEQ_DISPATCH_DUP, /* 620 */
				.word = 19,
				.epu_event_code = { D_12, D_44 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_ENQ_SEQ_DISPATCH_FIFO_FULL_DUP, /* 621 */
				.word = 19,
				.epu_event_code = { D_13, D_45 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_DEQ_SEQ_DELIVERS_1_DUP, /* 622 */
				.word = 19,
				.epu_event_code = { D_14, D_46 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_DEQ_SEQ_DELIVERS_2_DUP, /* 623 */
				.word = 19,
				.epu_event_code = { D_15, D_47 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_DEQ_SEQ_DELIVERS_3_DUP, /* 624 */
				.word = 19,
				.epu_event_code = { D_16, D_48 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_DEQ_CMD_DISPATCH_FIFO_FULL_DUP, /* 625 */
				.word = 19,
				.epu_event_code = { D_17, D_49 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_FRAME_ENQ_REJECTED_DUP, /* 626 */
				.word = 19,
				.epu_event_code = { D_18, D_50 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_FRAME_ENQ_WRED_REJECTED_DUP, /* 627 */
				.word = 19,
				.epu_event_code = { D_19, D_51 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_FRAME_ENQ_TD_CONG_REJECTED_DUP, /* 628 */
				.word = 19,
				.epu_event_code = { D_20, D_52 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP2_FRAME_ENQ_TD_FQ_REJECTED_DUP, /* 629 */
				.word = 19,
				.epu_event_code = { D_21, D_53 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_ENQ_MARK_01_DUP3, /* 630 */
				.word = 19,
				.epu_event_code = { D_22, D_54 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_ENQ_MARK_10_DUP3, /* 631 */
				.word = 19,
				.epu_event_code = { D_23, D_55 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_ENQ_MARK_11_DUP3, /* 632 */
				.word = 19,
				.epu_event_code = { D_24, D_56 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_DEQ_MARK_01_DUP3, /* 633 */
				.word = 19,
				.epu_event_code = { D_25, D_57 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_DEQ_MARK_10_DUP3, /* 634 */
				.word = 19,
				.epu_event_code = { D_26, D_58 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_DEQ_MARK_11_DUP3, /* 635 */
				.word = 19,
				.epu_event_code = { D_27, D_59 },
		},
		{
				.code = QE_DPAA_PE_QM_ORL_FRAME_ENQ_MARK_01_DUP3, /* 636 */
				.word = 19,
				.epu_event_code = { D_28, D_60 },
		},
		{
				.code = QE_DPAA_PE_QM_ORL_FRAME_ENQ_MARK_10_DUP3, /* 637 */
				.word = 19,
				.epu_event_code = { D_29, D_61 },
		},
		{
				.code = QE_DPAA_PE_QM_ORL_FRAME_ENQ_MARK_11_DUP3, /* 638 */
				.word = 19,
				.epu_event_code = { D_30, D_62 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_DEQ_EXCEEDS_THRESHOLD_A_DUP, /* 640 */
				.word = 20,
				.epu_event_code = { D_0, D_32 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_DEQ_EXCEEDS_THRESHOLD_B_DUP, /* 641 */
				.word = 20,
				.epu_event_code = { D_1, D_33 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_DEQ_EXCEEDS_THRESHOLD_C_DUP, /* 642 */
				.word = 20,
				.epu_event_code = { D_2, D_34 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_DEQ_EXCEEDS_THRESHOLD_D_DUP, /* 643 */
				.word = 20,
				.epu_event_code = { D_3, D_35 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_ENQ_CMD_RECEIVED_DUP, /* 648 */
				.word = 20,
				.epu_event_code = { D_8, D_40 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_ENQ_CMD_FIFO_FULL_DUP, /* 649 */
				.word = 20,
				.epu_event_code = { D_9, D_41 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_DEQ_CMD_FIFO_FULL_DUP, /* 650 */
				.word = 20,
				.epu_event_code = { D_10, D_42 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_DEQ_RSP_FIFO_FULL_DUP, /* 651 */
				.word = 20,
				.epu_event_code = { D_11, D_43 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_ENQ_SEQ_DISPATCH_DUP, /* 652 */
				.word = 20,
				.epu_event_code = { D_12, D_44 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_ENQ_SEQ_DISPATCH_FIFO_FULL_DUP, /* 653 */
				.word = 20,
				.epu_event_code = { D_13, D_45 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_DEQ_SEQ_DELIVERS_1_DUP, /* 654 */
				.word = 20,
				.epu_event_code = { D_14, D_46 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_DEQ_SEQ_DELIVERS_2_DUP, /* 655 */
				.word = 20,
				.epu_event_code = { D_15, D_47 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_DEQ_SEQ_DELIVERS_3_DUP, /* 656 */
				.word = 20,
				.epu_event_code = { D_16, D_48 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_DEQ_CMD_DISPATCH_FIFO_FULL_DUP, /* 657 */
				.word = 20,
				.epu_event_code = { D_17, D_49 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_FRAME_ENQ_REJECTED_DUP, /* 658 */
				.word = 20,
				.epu_event_code = { D_18, D_50 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_FRAME_ENQ_WRED_REJECTED_DUP, /* 659 */
				.word = 20,
				.epu_event_code = { D_19, D_51 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_FRAME_ENQ_TD_CONG_REJECTED_DUP, /* 660 */
				.word = 20,
				.epu_event_code = { D_20, D_52 },
		},
		{
				.code = QE_DPAA_PE_QM_DCP3_FRAME_ENQ_TD_FQ_REJECTED_DUP, /* 661 */
				.word = 20,
				.epu_event_code = { D_21, D_53 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_ENQ_MARK_01_DUP4, /* 662 */
				.word = 20,
				.epu_event_code = { D_22, D_54 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_ENQ_MARK_10_DUP4, /* 663 */
				.word = 20,
				.epu_event_code = { D_23, D_55 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_ENQ_MARK_11_DUP4, /* 664 */
				.word = 20,
				.epu_event_code = { D_24, D_56 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_DEQ_MARK_01_DUP4, /* 665 */
				.word = 20,
				.epu_event_code = { D_25, D_57 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_DEQ_MARK_10_DUP4, /* 666 */
				.word = 20,
				.epu_event_code = { D_26, D_58 },
		},
		{
				.code = QE_DPAA_PE_QM_DCPx_FRAME_DEQ_MARK_11_DUP4, /* 667 */
				.word = 20,
				.epu_event_code = { D_27, D_59 },
		},
		{
				.code = QE_DPAA_PE_QM_ORL_FRAME_ENQ_MARK_01_DUP4, /* 668 */
				.word = 20,
				.epu_event_code = { D_28, D_60 },
		},
		{
				.code = QE_DPAA_PE_QM_ORL_FRAME_ENQ_MARK_10_DUP4, /* 669 */
				.word = 20,
				.epu_event_code = { D_29, D_61 },
		},
		{
				.code = QE_DPAA_PE_QM_ORL_FRAME_ENQ_MARK_11_DUP4, /* 670 */
				.word = 20,
				.epu_event_code = { D_30, D_62 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_EQCR_CR_DISPATCH_FIFO_FULL_DUP, /* 676 */
				.word = 21,
				.epu_event_code = { D_4, D_36 },
		},
		{
				.code = QE_DPAA_PE_QMAN_SPx_ENQ_SEQ_DISPATCHED_DUP, /* 677 */
				.word = 21,
				.epu_event_code = { D_5, D_37 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_ENQ_SEQ_DISPATCH_FIFO_FULL_DUP, /* 678 */
				.word = 21,
				.epu_event_code = { D_6, D_38 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_DEQ_SEQ_DELIVERS_1_DUP, /* 679 */
				.word = 21,
				.epu_event_code = { D_7, D_39 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_DEQ_SEQ_DELIVERS_2_DUP, /* 680 */
				.word = 21,
				.epu_event_code = { D_8, D_40 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_DEQ_SEQ_DELIVERS_3_DUP, /* 681 */
				.word = 21,
				.epu_event_code = { D_9, D_41 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_FRAME_ENQ_REJECTED_DUP, /* 682 */
				.word = 21,
				.epu_event_code = { D_10, D_42 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_FRAME_ENQ_WRED_REJECTED_DUP, /* 683 */
				.word = 21,
				.epu_event_code = { D_11, D_43 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_FRAME_ENQ_TD_CONG_REJECTED_DUP, /* 684 */
				.word = 21,
				.epu_event_code = { D_12, D_44 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_FRAME_ENQ_TD_FQ_REJECTED_DUP, /* 685 */
				.word = 21,
				.epu_event_code = { D_13, D_45 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_FRAME_ENQ_MARK_01_DUP, /* 686 */
				.word = 21,
				.epu_event_code = { D_14, D_46 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_FRAME_ENQ_MARK_10_DUP, /* 687 */
				.word = 21,
				.epu_event_code = { D_15, D_47 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_FRAME_ENQ_MARK_11_DUP, /* 688 */
				.word = 21,
				.epu_event_code = { D_16, D_48 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_FRAME_DEQ_MARK_01_DUP, /* 689 */
				.word = 21,
				.epu_event_code = { D_17, D_49 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_FRAME_DEQ_MARK_10_DUP, /* 690 */
				.word = 21,
				.epu_event_code = { D_18, D_50 },
		},
		{
				.code = QE_DPAA_PE_QM_SPx_FRAME_DEQ_MARK_11_DUP, /* 691 */
				.word = 21,
				.epu_event_code = { D_19, D_51 },
		},
		{
				.code = QE_DPAA_PE_QM_ORL_FRAME_ENQ_MARK_01_DUP5, /* 692 */
				.word = 21,
				.epu_event_code = { D_20, D_52 },
		},
		{
				.code = QE_DPAA_PE_QM_ORL_FRAME_ENQ_MARK_10_DUP5, /* 693 */
				.word = 21,
				.epu_event_code = { D_21, D_53 },
		},
		{
				.code = QE_DPAA_PE_QM_ORL_FRAME_ENQ_MARK_11_DUP5, /* 694 */
				.word = 21,
				.epu_event_code = { D_22, D_54 },
		},
		{
				.code = QE_DPAA_PE_QM_PFDR_PREFETCH_DENIED_DUP, /* 715 */
				.word = 22,
				.epu_event_code = { D_11, D_43 },
		},
		{
				.code = QE_DPAA_PE_QM_USED_PFDR_NO_PREFETCH_READ_DUP, /* 716 */
				.word = 22,
				.epu_event_code = { D_12, D_44 },
		},
		{
				.code = QE_DPAA_PE_QM_SFDR_ALLOCATION_SUCCEED_DUP, /* 717 */
				.word = 22,
				.epu_event_code = { D_13, D_45 },
		},
		{
				.code = QE_DPAA_PE_QM_SFDR_ALLOCATION_FAILED_DUP, /* 718 */
				.word = 22,
				.epu_event_code = { D_14, D_46 },
		},
		{
				.code = QE_DPAA_PE_QM_PARTIALLY_FULL_PFDR_WRITE_DUP, /* 719 */
				.word = 22,
				.epu_event_code = { D_15, D_47 },
		},
		{
				.code = QE_DPAA_PE_QM_FQ_TRULY_SCHEDULED_DCPx_DUP, /* 720 */
				.word = 22,
				.epu_event_code = { D_16, D_48 },
		},
		{
				.code = QE_DPAA_PE_QM_FQ_TRULY_SCHEDULED_SPx_DUP, /* 721 */
				.word = 22,
				.epu_event_code = { D_17, D_49 },
		},
		{
				.code = QE_DPAA_PE_QM_FQ_TRULY_SCHEDULED_RESCH_DUP, /* 722 */
				.word = 22,
				.epu_event_code = { D_18, D_50 },
		},
		{
				.code = QE_DPAA_PE_QM_FRAME_IN_ORL_DUP, /* 723 */
				.word = 22,
				.epu_event_code = { D_19, D_51 },
		},
		{
				.code = QE_DPAA_PE_QM_FRAME_IN_ORL_ORP_ADVANCE_DUP, /* 724 */
				.word = 22,
				.epu_event_code = { D_20, D_52 },
		},
		{
				.code = QE_DPAA_PE_QM_REJECTED_LATE_FRAME_DUP, /* 725 */
				.word = 22,
				.epu_event_code = { D_21, D_53 },
		},
		{
				.code = QE_DPAA_PE_QM_ACCEPCTED_LATE_FRAME_DUP, /* 726 */
				.word = 22,
				.epu_event_code = { D_22, D_54 },
		},
		{
				.code = QE_DPAA_PE_QM_REJECTED_EARLY_FRAME_DUP, /* 727 */
				.word = 22,
				.epu_event_code = { D_23, D_55 },
		},
		{
				.code = QE_DPAA_PE_QM_SP0_ENQ_CMD_RECEIVED_DUP, /* 736 */
				.word = 23,
				.epu_event_code = { D_0, D_32 },
		},
		{
				.code = QE_DPAA_PE_QM_SP1_ENQ_CMD_RECEIVED_DUP, /* 737 */
				.word = 23,
				.epu_event_code = { D_1, D_33 },
		},
		{
				.code = QE_DPAA_PE_QM_SP2_ENQ_CMD_RECEIVED_DUP, /* 738 */
				.word = 23,
				.epu_event_code = { D_2, D_34 },
		},
		{
				.code = QE_DPAA_PE_QM_SP3_ENQ_CMD_RECEIVED_DUP, /* 739 */
				.word = 23,
				.epu_event_code = { D_3, D_35 },
		},
		{
				.code = QE_DPAA_PE_QM_SP4_ENQ_CMD_RECEIVED_DUP, /* 740 */
				.word = 23,
				.epu_event_code = { D_4, D_36 },
		},
		{
				.code = QE_DPAA_PE_QM_SP5_ENQ_CMD_RECEIVED_DUP, /* 741 */
				.word = 23,
				.epu_event_code = { D_5, D_37 },
		},
		{
				.code = QE_DPAA_PE_QM_SP6_ENQ_CMD_RECEIVED_DUP, /* 742 */
				.word = 23,
				.epu_event_code = { D_6, D_38 },
		},
		{
				.code = QE_DPAA_PE_QM_SP7_ENQ_CMD_RECEIVED_DUP, /* 743 */
				.word = 23,
				.epu_event_code = { D_7, D_39 },
		},
		{
				.code = QE_DPAA_PE_QM_SP8_ENQ_CMD_RECEIVED_DUP, /* 744 */
				.word = 23,
				.epu_event_code = { D_8, D_40 },
		},
		{
				.code = QE_DPAA_PE_QM_SP9_ENQ_CMD_RECEIVED_DUP, /* 745 */
				.word = 23,
				.epu_event_code = { D_9, D_41 },
		},
		{
				.code = QE_DPAA_PE_QM_SP0_ENQ_CMD_PULLED_EQCR_FULL_DUP, /* 746 */
				.word = 23,
				.epu_event_code = { D_10, D_42 },
		},
		{
				.code = QE_DPAA_PE_QM_SP1_ENQ_CMD_PULLED_EQCR_FULL_DUP, /* 747 */
				.word = 23,
				.epu_event_code = { D_11, D_43 },
		},
		{
				.code = QE_DPAA_PE_QM_SP2_ENQ_CMD_PULLED_EQCR_FULL_DUP, /* 748 */
				.word = 23,
				.epu_event_code = { D_12, D_44 },
		},
		{
				.code = QE_DPAA_PE_QM_SP3_ENQ_CMD_PULLED_EQCR_FULL_DUP, /* 749 */
				.word = 23,
				.epu_event_code = { D_13, D_45 },
		},
		{
				.code = QE_DPAA_PE_QM_SP4_ENQ_CMD_PULLED_EQCR_FULL_DUP, /* 750 */
				.word = 23,
				.epu_event_code = { D_14, D_46 },
		},
		{
				.code = QE_DPAA_PE_QM_SP5_ENQ_CMD_PULLED_EQCR_FULL_DUP, /* 751 */
				.word = 23,
				.epu_event_code = { D_15, D_47 },
		},
		{
				.code = QE_DPAA_PE_QM_SP6_ENQ_CMD_PULLED_EQCR_FULL_DUP, /* 752 */
				.word = 23,
				.epu_event_code = { D_16, D_48 },
		},
		{
				.code = QE_DPAA_PE_QM_SP7_ENQ_CMD_PULLED_EQCR_FULL_DUP, /* 753 */
				.word = 23,
				.epu_event_code = { D_17, D_49 },
		},
		{
				.code = QE_DPAA_PE_QM_SP8_ENQ_CMD_PULLED_EQCR_FULL_DUP, /* 754 */
				.word = 23,
				.epu_event_code = { D_18, D_50 },
		},
		{
				.code = QE_DPAA_PE_QM_SP9_ENQ_CMD_PULLED_EQCR_FULL_DUP, /* 755 */
				.word = 23,
				.epu_event_code = { D_19, D_51 },
		},
		{
				.code = QE_DPAA_PE_QM_SP0_DEQ_CMD_READY_DQRR_FULL_DUP, /* 756 */
				.word = 23,
				.epu_event_code = { D_20, D_52 },
		},
		{
				.code = QE_DPAA_PE_QM_SP1_DEQ_CMD_READY_DQRR_FULL_DUP, /* 757 */
				.word = 23,
				.epu_event_code = { D_21, D_53 },
		},
		{
				.code = QE_DPAA_PE_QM_SP2_DEQ_CMD_READY_DQRR_FULL_DUP, /* 758 */
				.word = 23,
				.epu_event_code = { D_22, D_54 },
		},
		{
				.code = QE_DPAA_PE_QM_SP3_DEQ_CMD_READY_DQRR_FULL_DUP, /* 759 */
				.word = 23,
				.epu_event_code = { D_23, D_55 },
		},
		{
				.code = QE_DPAA_PE_QM_SP4_DEQ_CMD_READY_DQRR_FULL_DUP, /* 760 */
				.word = 23,
				.epu_event_code = { D_24, D_56 },
		},
		{
				.code = QE_DPAA_PE_QM_SP5_DEQ_CMD_READY_DQRR_FULL_DUP, /* 761 */
				.word = 23,
				.epu_event_code = { D_25, D_57 },
		},
		{
				.code = QE_DPAA_PE_QM_SP6_DEQ_CMD_READY_DQRR_FULL_DUP, /* 762 */
				.word = 23,
				.epu_event_code = { D_26, D_58 },
		},
		{
				.code = QE_DPAA_PE_QM_SP7_DEQ_CMD_READY_DQRR_FULL_DUP, /* 763 */
				.word = 23,
				.epu_event_code = { D_27, D_59 },
		},
		{
				.code = QE_DPAA_PE_QM_SP8_DEQ_CMD_READY_DQRR_FULL_DUP, /* 764 */
				.word = 23,
				.epu_event_code = { D_28, D_60 },
		},
		{
				.code = QE_DPAA_PE_QM_SP9_DEQ_CMD_READY_DQRR_FULL_DUP, /* 765 */
				.word = 23,
				.epu_event_code = { D_29, D_61 },
		},
};

/* Return a pointer to the dpaa_event associated with the event_code.
 * Returns 0 if not found.
 */
const struct dpaa_event *dpaa_event_from_code( u32 event_code )
{
	const struct dpaa_event *ev = dpaa_event;
	static const int NUM_ELEMENTS = sizeof(dpaa_event)/sizeof(dpaa_event[0]);
	int i;
	for (i = 0; i<NUM_ELEMENTS; i++) {
		if (ev->code == event_code)
			return ev;

		ev++;
	}
	
	printk(KERN_ERR "DPAA Event code r%x not found!", event_code);
	
	return 0;
}
