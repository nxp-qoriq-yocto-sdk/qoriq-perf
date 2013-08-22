/*
 * Copyright (C) 2010, 2011, 2012 Freescale Semiconductor, Inc.
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

#ifndef DCSR_DPAA_V1_H
#define DCSR_DPAA_V1_H

#include "common.h"

/* Number of QMAN Software Portals */
#define DPAA_NO_OF_QMAN_SP		10
/* Number of QMAN Direct Connect Portals */
#define DPAA_NO_OF_QMAN_DCP		4
/* Number of Queue Operation Event Registers */
#define DPAA_NO_OF_QOER			4
/* Number of Frame Operation Event Registers */
#define DPAA_NO_OF_FOER			8
/* Number of Event Generation Control Registers */
#define DPAA_NO_OF_EGCR			4
/* Number of Group Event Control Registers */
#define DPAA_NO_OF_GECR			4
/* Number of Group Configuration Registers */
#define DPAA_NO_OF_GCR			4
/* Number of Reference Event Selection Control Registers */
#define DPAA_NO_OF_DPRESCR		2

/* The Data Path Debug Register Memory Map */
struct dpaa {
	/* Data Path External Halt Control Register */
	u32 dpehcr;
	/* Data Path Resume Control Register */
	u32 dprcr;
	/* QMan Portal External Halt Control Register */
	u32 qpehcr;
	/* QMan Portal Resume Control Register */
	u32 qprcr;
	/* QMan Software Portal Halt Status Registers 0-9 */
	u32 qsphsr[DPAA_NO_OF_QMAN_SP];
	u32 reserved1[0x02];
	/* QMan Direct Connect Portal Halt Status Registers 0-3*/
	u32 qdcphsr[DPAA_NO_OF_QMAN_DCP];
	u32 reserved2[0x04];
	/* FMan 1 Halt Control Status Register */
	u32 fmhsr0;
	/* FMan 2 Halt Control Status Register */
	u32 fmhsr1;
	u32 reserved3[0x26];

	/* Data Path Queue Operation Event Registers 0 - 3 */
	u32 dpqoer[DPAA_NO_OF_QOER];
	u32 reserved4[0x04];
	/* Data Path Frame Operation Event Registers 0 - 7 */
	u32 dpfoer[DPAA_NO_OF_FOER];
	u32 reserved5[0x08];
	/* Data Path Event Generation Control Registers 0 - 3 */
	u32 dpegcr[DPAA_NO_OF_EGCR];
	u32 reserved6[0x04];
	/* Data Path Group Event Control Registers 0 - 3 */
	u32 dpgecr[DPAA_NO_OF_GECR];
	u32 reserved7[0x04];
	/* Data Path Group Configuration Registers 0 - 3 */
	u32 dpgcr[DPAA_NO_OF_GCR];
	u32 reserved8[0x04];
	/* Data Path Event Port General Control Register */
	u32 dpepgcr;
	/* Data Path Performance Event Selection Control Register */
	u32 dppescr;
	/* Data Path Reference Event Selection Control Register 1, 2 */
	u32 dprescr[DPAA_NO_OF_DPRESCR];
	u32 reserved9[0x0C];

	/* Data Path Trace Armed Register */
	u32 dptarm;
	/* Data Path Trace General Control Register */
	u32 dptgcr;
	/* Data Path Trace Filter Trigger Control Register 1 */
	u32 dptftcr1;
	/* Data Path Trace Filter Trigger Control Register 2 */
	u32 dptftcr2;
	/* Data Path Circuit Trace Static Control Register */
	u32 dpctscr;
	/* Data Path Circuit Trace Dynamic Control Register */
	u32 dpctdcr;
	u32 reserved10[0x02];
	/* Data Path Watchpoint Mask Control Register */
	u32 dpwmsk;
	u32 reserved11[0x377];
} PACKED;
CTASSERT(sizeof(struct dpaa) == 0x1000);

/*
 * The DPPESCR register is used for selecting the first 32-bit performance event group and the second 32-bit
 * performance event group from a total of 24 performance event groups.
 */
#define DPAA_DPPESCR_PMG1_SEL_MASK	0x000f8000
#define DPAA_DPPESCR_PMG1_SEL_SHIFT	0xf
#define DPAA_DPPESCR_PMG0_SEL_MASK	0xf8000000
#define DPAA_DPPESCR_PMG0_SEL_SHIFT	0x1b

/*
 * The DPRESCR1 register is used to select the Data Path Reference events 0–1
 * that will be fed into the EPU SCUs.
 */
#define DPAA_DPRESCR1_REFEV1_SEL_MASK	0x0000ffc0
#define DPAA_DPRESCR1_REFEV1_SEL_SHIFT	0x6
#define DPAA_DPRESCR1_REFEV0_SEL_MASK	0xffc00000
#define DPAA_DPRESCR1_REFEV0_SEL_SHIFT	0x16

/*
 * The DPRESCR2 register is used to select the Data Path Reference events 2–3
 * that will be fed into the EPU SCUs.
 */
#define DPAA_DPRESCR2_REFEV3_SEL_MASK	0x0000ffc0
#define DPAA_DPRESCR2_REFEV3_SEL_SHIFT	0x6
#define DPAA_DPRESCR2_REFEV2_SEL_MASK	0xffc00000
#define DPAA_DPRESCR2_REFEV2_SEL_SHIFT	0x16

/* The Data Path Debug Client Performance events */
enum DPDC_PERFEV {

	/******************************************************************
	 *      DPDC Performance Event Word 0 (events 0 - 31)             *
	 *             Queue Manager Performance Events                   *
	 ******************************************************************/

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP0 exceeds threshold A in DCP0. */
	DPDC_PE_QM_DCP0_DEQ_EXCEEDS_THRESHOLD_A		=	0,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP0 exceeds threshold B in DCP0. */
	DPDC_PE_QM_DCP0_DEQ_EXCEEDS_THRESHOLD_B		=	1,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP0 exceeds threshold C in DCP0. */
	DPDC_PE_QM_DCP0_DEQ_EXCEEDS_THRESHOLD_C		=	2,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP0 exceeds threshold D in DCP0. */
	DPDC_PE_QM_DCP0_DEQ_EXCEEDS_THRESHOLD_D		=	3,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP1 exceeds threshold A in DCP1. */
	DPDC_PE_QM_DCP1_DEQ_EXCEEDS_THRESHOLD_A		=	4,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP1 exceeds threshold B in DCP1. */
	DPDC_PE_QM_DCP1_DEQ_EXCEEDS_THRESHOLD_B		=	5,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP1 exceeds threshold C in DCP1. */
	DPDC_PE_QM_DCP1_DEQ_EXCEEDS_THRESHOLD_C		=	6,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP1 exceeds threshold D in DCP1. */
	DPDC_PE_QM_DCP1_DEQ_EXCEEDS_THRESHOLD_D		=	7,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP2 exceeds threshold A in DCP2. */
	DPDC_PE_QM_DCP2_DEQ_EXCEEDS_THRESHOLD_A		=	8,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP2 exceeds threshold B in DCP2. */
	DPDC_PE_QM_DCP2_DEQ_EXCEEDS_THRESHOLD_B		=	9,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP2 exceeds threshold C in DCP2. */
	DPDC_PE_QM_DCP2_DEQ_EXCEEDS_THRESHOLD_C		=	10,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP2 exceeds threshold D in DCP2. */
	DPDC_PE_QM_DCP2_DEQ_EXCEEDS_THRESHOLD_D		=	11,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP3 exceeds threshold A in DCP3. */
	DPDC_PE_QM_DCP3_DEQ_EXCEEDS_THRESHOLD_A		=	12,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP3 exceeds threshold B in DCP3. */
	DPDC_PE_QM_DCP3_DEQ_EXCEEDS_THRESHOLD_B		=	13,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP3 exceeds threshold C in DCP3. */
	DPDC_PE_QM_DCP3_DEQ_EXCEEDS_THRESHOLD_C		=	14,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP3 exceeds threshold D in DCP3. */
	DPDC_PE_QM_DCP3_DEQ_EXCEEDS_THRESHOLD_D		=	15,

	/*---------------- 16 - 31 entries are reserved. ---------------------*/

	/******************************************************************
	 *      DPDC Performance Event Word 1 (events 32 - 63)            *
	 *             Queue Manager Performance Events                   *
	 ******************************************************************/

	/*---------------- 32 - 46 entries are reserved. -------------------*/

	/* Pulses high for one cycle when a PFDR prefetch is attempted and denied
	 * due to lack of prefetch catch box resources.*/
	DPDC_PE_QM_PFDR_PREFETCH_DENIED			=	47,

	/* Pulses high for one cycle when a PFDR read is initiated for a PFDR
	 * which is in use in a FQ, and the read is not a prefetch. */
	DPDC_PE_QM_USED_PFDR_NO_PREFETCH_READ		=	48,

	/* Pulses high for one cycle every time an SFDR allocation succeeds. */
	DPDC_PE_QM_SFDR_ALLOCATION_SUCCEED		=	49,

	/* Pulses high for one cycle every time an SFDR allocation fails. */
	DPDC_PE_QM_SFDR_ALLOCATION_FAILED		=	50,

	/* Pulses high for one cycle every time a write of a partially full
	 * PFDR occurs. */
	DPDC_PE_QM_PARTIALLY_FULL_PFDR_WRITE		=	51,

	/* Pulses high for one cycle every time a FQ transitions to the Truly
	 * Scheduled state in a direct connect portal sequencer. */
	DPDC_PE_QM_FQ_TRULY_SCHEDULED_DCPx		=	52,

	/* Pulses high for one cycle every time a FQ transitions to the Truly
	 * Scheduled state in a software portal sequencer. */
	DPDC_PE_QM_FQ_TRULY_SCHEDULED_SPx		=	53,

	/* Pulses high for one cycle every time a FQ transitions to the
	 * Truly Scheduled state in a reschedule sequencer. */
	DPDC_PE_QM_FQ_TRULY_SCHEDULED_RESCH		=	54,

	/* Pulse high for one cycle for every enqueue command received in DCP0*/
	DPDC_PE_QM_DCP0_ENQ_CMD_RECEIVED		=	55,

	/* Pulse high for one cycle for every enqueue command received in DCP1*/
	DPDC_PE_QM_DCP1_ENQ_CMD_RECEIVED		=	56,

	/* Pulse high for one cycle for every enqueue command received in DCP2*/
	DPDC_PE_QM_DCP2_ENQ_CMD_RECEIVED		=	57,

	/* Pulse high for one cycle for every enqueue command received in DCP3*/
	DPDC_PE_QM_DCP3_ENQ_CMD_RECEIVED		=	58,

	/* Pulse high for one cycle for every enqueue command received in SP0*/
	DPDC_PE_QM_SP0_ENQ_CMD_RECEIVED			=	59,

	/* Pulse high for one cycle for every enqueue command received in SP1*/
	DPDC_PE_QM_SP1_ENQ_CMD_RECEIVED			=	60,

	/* Pulse high for one cycle for every enqueue command received in SP2*/
	DPDC_PE_QM_SP2_ENQ_CMD_RECEIVED			=	61,

	/* Pulse high for one cycle for every enqueue command received in SP3*/
	DPDC_PE_QM_SP3_ENQ_CMD_RECEIVED			=	62,

	/* Pulse high for one cycle for every enqueue command received in SP4*/
	DPDC_PE_QM_SP4_ENQ_CMD_RECEIVED			=	63,

	/******************************************************************
	 *      DPDC Performance Event Word 2 (events 64 - 95)            *
	 *             Queue Manager Performance Events                   *
	 ******************************************************************/

	/* Pulse high for one cycle for every enqueue command received in SP5*/
	DPDC_PE_QM_SP5_ENQ_CMD_RECEIVED			=	64,

	/* Pulse high for one cycle for every enqueue command received in SP6*/
	DPDC_PE_QM_SP6_ENQ_CMD_RECEIVED			=	65,

	/* Pulse high for one cycle for every enqueue command received in SP7*/
	DPDC_PE_QM_SP7_ENQ_CMD_RECEIVED			=	66,

	/* Pulse high for one cycle for every enqueue command received in SP8*/
	DPDC_PE_QM_SP8_ENQ_CMD_RECEIVED			=	67,

	/* Pulse high for one cycle for every enqueue command received in SP9*/
	DPDC_PE_QM_SP9_ENQ_CMD_RECEIVED			=	68,

	/* Pulses high for one cycle for every enqueue command pulled from the
	 * EQCR ring when that ring is full in SP0. */
	DPDC_PE_QM_SP0_ENQ_CMD_PULLED_EQCR_FULL		=	69,

	/* Pulses high for one cycle for every enqueue command pulled from the
	 * EQCR ring when that ring is full in SP1. */
	DPDC_PE_QM_SP1_ENQ_CMD_PULLED_EQCR_FULL		=	70,

	/* Pulses high for one cycle for every enqueue command pulled from the
	 * EQCR ring when that ring is full in SP2. */
	DPDC_PE_QM_SP2_ENQ_CMD_PULLED_EQCR_FULL		=	71,

	/* Pulses high for one cycle for every enqueue command pulled from the
	 * EQCR ring when that ring is full in SP3. */
	DPDC_PE_QM_SP3_ENQ_CMD_PULLED_EQCR_FULL		=	72,

	/* Pulses high for one cycle for every enqueue command pulled from the
	 * EQCR ring when that ring is full in SP4. */
	DPDC_PE_QM_SP4_ENQ_CMD_PULLED_EQCR_FULL		=	73,

	/* Pulses high for one cycle for every enqueue command pulled from the
	 * EQCR ring when that ring is full in SP5. */
	DPDC_PE_QM_SP5_ENQ_CMD_PULLED_EQCR_FULL		=	74,

	/* Pulses high for one cycle for every enqueue command pulled from the
	 * EQCR ring when that ring is full in SP6. */
	DPDC_PE_QM_SP6_ENQ_CMD_PULLED_EQCR_FULL		=	75,

	/* Pulses high for one cycle for every enqueue command pulled from the
	 * EQCR ring when that ring is full in SP7. */
	DPDC_PE_QM_SP7_ENQ_CMD_PULLED_EQCR_FULL		=	76,

	/* Pulses high for one cycle for every enqueue command pulled from the
	 * EQCR ring when that ring is full in SP8. */
	DPDC_PE_QM_SP8_ENQ_CMD_PULLED_EQCR_FULL		=	77,

	/* Pulses high for one cycle for every enqueue command pulled from the
	 * EQCR ring when that ring is full in SP9. */
	DPDC_PE_QM_SP9_ENQ_CMD_PULLED_EQCR_FULL		=	78,

	/* Asserted whenever the enqueue command FIFO in a direct connect
	 * portal is full in DCP0. */
	DPDC_PE_QM_DCP0_ENQ_CMD_FIFO_FULL		=	79,

	/* Asserted whenever the enqueue command FIFO in a direct connect
	 * portal is full in DCP1. */
	DPDC_PE_QM_DCP1_ENQ_CMD_FIFO_FULL		=	80,

	/* Asserted whenever the enqueue command FIFO in a direct connect
	 * portal is full in DCP2. */
	DPDC_PE_QM_DCP2_ENQ_CMD_FIFO_FULL		=	81,

	/* Asserted whenever the enqueue command FIFO in a direct connect
	 * portal is full in DCP3. */
	DPDC_PE_QM_DCP3_ENQ_CMD_FIFO_FULL		=	82,

	/* Asserted whenever the EQCR/CR command dispatch FIFO which services
	 * all software portals is full. */
	DPDC_PE_QM_SPx_EQCR_CR_DISPATCH_FIFO_FULL	=	83,

	/* Asserted whenever the dequeue command FIFO in DCP0 is full. */
	DPDC_PE_QM_DCP0_DEQ_CMD_FIFO_FULL		=	84,

	/* Asserted whenever the dequeue command FIFO in DCP1 is full. */
	DPDC_PE_QM_DCP1_DEQ_CMD_FIFO_FULL		=	85,

	/* Asserted whenever the dequeue command FIFO in DCP2 is full. */
	DPDC_PE_QM_DCP2_DEQ_CMD_FIFO_FULL		=	86,

	/* Asserted whenever the dequeue command FIFO in DCP3 is full. */
	DPDC_PE_QM_DCP3_DEQ_CMD_FIFO_FULL		=	87,

	/* Asserted whenever the dequeue response FIFO in DCP0 is full. */
	DPDC_PE_QM_DCP0_DEQ_RSP_FIFO_FULL		=	88,

	/* Asserted whenever the dequeue response FIFO in DCP1 is full. */
	DPDC_PE_QM_DCP1_DEQ_RSP_FIFO_FULL		=	89,

	/* Asserted whenever the dequeue response FIFO in DCP2 is full. */
	DPDC_PE_QM_DCP2_DEQ_RSP_FIFO_FULL		=	90,

	/* Asserted whenever the dequeue response FIFO in DCP3 is full. */
	DPDC_PE_QM_DCP3_DEQ_RSP_FIFO_FULL		=	91,

	/* Asserted whenever a dequeue command is valid and ready to be
	 * dispatched from a software portal 0, but cannot proceed due to
	 * lack of space in the DQRR ring. */
	DPDC_PE_QM_SP0_DEQ_CMD_READY_DQRR_FULL		=	92,

	/* Asserted whenever a dequeue command is valid and ready to be
	 * dispatched from a software portal 1, but cannot proceed due to
	 * lack of space in the DQRR ring. */
	DPDC_PE_QM_SP1_DEQ_CMD_READY_DQRR_FULL		=	93,

	/* Asserted whenever a dequeue command is valid and ready to be
	 * dispatched from a software portal 2, but cannot proceed due to
	 * lack of space in the DQRR ring. */
	DPDC_PE_QM_SP2_DEQ_CMD_READY_DQRR_FULL		=	94,

	/* Asserted whenever a dequeue command is valid and ready to be
	 * dispatched from a software portal 3, but cannot proceed due to
	 * lack of space in the DQRR ring. */
	DPDC_PE_QM_SP3_DEQ_CMD_READY_DQRR_FULL		=	95,

	/******************************************************************
	 *      DPDC Performance Event Word 3 (events 96 - 127)           *
	 *             Queue Manager Performance Events                   *
	 ******************************************************************/

	/* Asserted whenever a dequeue command is valid and ready to be
	 * dispatched from a software portal 4, but cannot proceed due to
	 * lack of space in the DQRR ring. */
	DPDC_PE_QM_SP4_DEQ_CMD_READY_DQRR_FULL		=	96,

	/* Asserted whenever a dequeue command is valid and ready to be
	 * dispatched from a software portal 5, but cannot proceed due to
	 * lack of space in the DQRR ring. */
	DPDC_PE_QM_SP5_DEQ_CMD_READY_DQRR_FULL		=	97,

	/* Asserted whenever a dequeue command is valid and ready to be
	 * dispatched from a software portal 6, but cannot proceed due to
	 * lack of space in the DQRR ring. */
	DPDC_PE_QM_SP6_DEQ_CMD_READY_DQRR_FULL		=	98,

	/* Asserted whenever a dequeue command is valid and ready to be
	 * dispatched from a software portal 7, but cannot proceed due to
	 * lack of space in the DQRR ring. */
	DPDC_PE_QM_SP7_DEQ_CMD_READY_DQRR_FULL		=	99,

	/* Asserted whenever a dequeue command is valid and ready to be
	 * dispatched from a software portal 8, but cannot proceed due to
	 * lack of space in the DQRR ring. */
	DPDC_PE_QM_SP8_DEQ_CMD_READY_DQRR_FULL		=	100,

	/* Asserted whenever a dequeue command is valid and ready to be
	 * dispatched from a software portal 9, but cannot proceed due to
	 * lack of space in the DQRR ring. */
	DPDC_PE_QM_SP9_DEQ_CMD_READY_DQRR_FULL		=	101,

	/* Pulses high for one cycle for every enqueue sequence that is
	 * dispatched for DCP0. This number may be lower than the number of
	 * enqueue commands received, because enqueue commands can be
	 * dispatched up to 3 at a time when they target the same FQ. */
	DPDC_PE_QM_DCP0_ENQ_SEQ_DISPATCHED		=	102,

	/* Pulses high for one cycle for every enqueue sequence that is
	 * dispatched for DCP1. */
	 DPDC_PE_QM_DCP1_ENQ_SEQ_DISPATCHED		=	103,

	/* Pulses high for one cycle for every enqueue sequence that is
	 * dispatched for DCP2. */
	 DPDC_PE_QM_DCP2_ENQ_SEQ_DISPATCHED		=	104,

	/* Pulses high for one cycle for every enqueue sequence that is
	 * dispatched for DCP3. */
	 DPDC_PE_QM_DCP3_ENQ_SEQ_DISPATCHED		=	105,

	/* Pulses high for one cycle for every enqueue sequence that is
	 * dispatched for any software portal (Monitored at the output of the
	 * EQCR/CR dispatch FIFO). */
	DPDC_PE_QMAN_SPx_ENQ_SEQ_DISPATCHED		=	106,

	/* Pulses high for one cycle for every enqueue sequence that is
	 * dispatched for DCP0 when the corresponding command FIFO is full. */
	DPDC_PE_QM_DCP0_ENQ_SEQ_DISPATCH_FIFO_FULL	=	107,

	/* Pulses high for one cycle for every enqueue sequence that is
	 * dispatched for DCP0 when the corresponding command FIFO is full. */
	DPDC_PE_QM_DCP1_ENQ_SEQ_DISPATCH_FIFO_FULL	=	108,

	/* Pulses high for one cycle for every enqueue sequence that is
	 * dispatched for DCP0 when the corresponding command FIFO is full. */
	DPDC_PE_QM_DCP2_ENQ_SEQ_DISPATCH_FIFO_FULL	=	109,

	/* Pulses high for one cycle for every enqueue sequence that is
	 * dispatched for DCP0 when the corresponding command FIFO is full. */
	DPDC_PE_QM_DCP3_ENQ_SEQ_DISPATCH_FIFO_FULL	=	110,

	/* Pulses high for one cycle for every enqueue sequence that is
	 * dispatched for any software portal when the corresponding command
	 * FIFO is full. */
	DPDC_PE_QM_SPx_ENQ_SEQ_DISPATCH_FIFO_FULL	=	111,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 1 or more frames for DCP0. */
	DPDC_PE_QM_DCP0_DEQ_SEQ_DELIVERS_1		=	112,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 1 or more frames for DCP1. */
	DPDC_PE_QM_DCP1_DEQ_SEQ_DELIVERS_1		=	113,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 1 or more frames for DCP2. */
	DPDC_PE_QM_DCP2_DEQ_SEQ_DELIVERS_1		=	114,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 1 or more frames for DCP3. */
	DPDC_PE_QM_DCP3_DEQ_SEQ_DELIVERS_1		=	115,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 1 or more frames for any software portal. */
	 DPDC_PE_QM_SPx_DEQ_SEQ_DELIVERS_1		=	116,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 2 or more frames for DCP0. */
	DPDC_PE_QM_DCP0_DEQ_SEQ_DELIVERS_2		=	117,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 2 or more frames for DCP1. */
	DPDC_PE_QM_DCP1_DEQ_SEQ_DELIVERS_2		=	118,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 2 or more frames for DCP2. */
	DPDC_PE_QM_DCP2_DEQ_SEQ_DELIVERS_2		=	119,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 2 or more frames for DCP3. */
	DPDC_PE_QM_DCP3_DEQ_SEQ_DELIVERS_2		=	120,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 2 or more frames for any software portal. */
	 DPDC_PE_QM_SPx_DEQ_SEQ_DELIVERS_2		=	121,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 3 frames for DCP0. */
	DPDC_PE_QM_DCP0_DEQ_SEQ_DELIVERS_3		=	122,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 3 frames for DCP1. */
	DPDC_PE_QM_DCP1_DEQ_SEQ_DELIVERS_3		=	123,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 3 frames for DCP2. */
	DPDC_PE_QM_DCP2_DEQ_SEQ_DELIVERS_3		=	124,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 3 frames for DCP3. */
	DPDC_PE_QM_DCP3_DEQ_SEQ_DELIVERS_3		=	125,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 3 frames for any software portal. */
	 DPDC_PE_QM_SPx_DEQ_SEQ_DELIVERS_3		=	126,

	/* Pulses high for one cycle for every dequeue command dispatched when
	 * the dequeue command FIFO in DCP0 is full. */
	DPDC_PE_QM_DCP0_DEQ_CMD_DISPATCH_FIFO_FULL	=	127,

	/******************************************************************
	 *      DPDC Performance Event Word 4 (events 128 - 159)          *
	 *             Queue Manager Performance Events                   *
	 ******************************************************************/

	/* Pulses high for one cycle for every dequeue command dispatched when
	 * the dequeue command FIFO in DCP1 is full. */
	DPDC_PE_QM_DCP1_DEQ_CMD_DISPATCH_FIFO_FULL	=	128,

	/* Pulses high for one cycle for every dequeue command dispatched when
	 * the dequeue command FIFO in DCP2 is full. */
	DPDC_PE_QM_DCP2_DEQ_CMD_DISPATCH_FIFO_FULL	=	129,

	/* Pulses high for one cycle for every dequeue command dispatched when
	 * the dequeue command FIFO in DCP3 is full. */
	DPDC_PE_QM_DCP3_DEQ_CMD_DISPATCH_FIFO_FULL	=	130,

	/* Pulses high for one cycle for every frame that is not next in
	 * sequence and is placed in an order restoration list (ORL). */
	DPDC_PE_QM_FRAME_IN_ORL				=	131,

	/* Pulses high for one cycle for every frame that is placed in an order
	 * restoration list and causes an auto advance of an ORP window. */
	DPDC_PE_QM_FRAME_IN_ORL_ORP_ADVANCE		=	132,

	/* Pulses high for one cycle for every frame that is rejected as a late
	 * arrival at an ORP. */
	DPDC_PE_QM_REJECTED_LATE_FRAME			=	133,

	/* Pulses high for one cycle for every frame that is accepted and falls
	 * in the acceptable late arrival window at an ORP. */
	DPDC_PE_QM_ACCEPCTED_LATE_FRAME			=	134,

	/* Pulses high for one cycle for every frame that is rejected as an
	 * early arrival at an ORP, for example, falls in the early arrival
	 * rejection window. */
	 DPDC_PE_QM_REJECTED_EARLY_FRAME		=	135,

	/*---------------- 136 - 139 entries are reserved. -------------------*/

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * in DCP0. */
	DPDC_PE_QM_DCP0_FRAME_ENQ_REJECTED		=	140,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * in DCP1. */
	DPDC_PE_QM_DCP1_FRAME_ENQ_REJECTED		=	141,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * in DCP2. */
	DPDC_PE_QM_DCP2_FRAME_ENQ_REJECTED		=	142,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * in DCP3. */
	DPDC_PE_QM_DCP3_FRAME_ENQ_REJECTED		=	143,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * in any software portal. */
	DPDC_PE_QM_SPx_FRAME_ENQ_REJECTED		=	144,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to WRED discard in DCP0. */
	DPDC_PE_QM_DCP0_FRAME_ENQ_WRED_REJECTED		=	145,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to WRED discard in DCP1. */
	DPDC_PE_QM_DCP1_FRAME_ENQ_WRED_REJECTED		=	146,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to WRED discard in DCP2. */
	DPDC_PE_QM_DCP2_FRAME_ENQ_WRED_REJECTED		=	147,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to WRED discard in DCP3. */
	DPDC_PE_QM_DCP3_FRAME_ENQ_WRED_REJECTED		=	148,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to WRED discard in any software portal. */
	DPDC_PE_QM_SPx_FRAME_ENQ_WRED_REJECTED		=	149,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to tail drop configured in the FQ's congestion group in DCP0. */
	DPDC_PE_QM_DCP0_FRAME_ENQ_TD_CONG_REJECTED	=	150,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to tail drop configured in the FQ's congestion group in DCP1. */
	DPDC_PE_QM_DCP1_FRAME_ENQ_TD_CONG_REJECTED	=	151,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to tail drop configured in the FQ's congestion group in DCP2. */
	DPDC_PE_QM_DCP2_FRAME_ENQ_TD_CONG_REJECTED	=	152,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to tail drop configured in the FQ's congestion group in DCP3. */
	DPDC_PE_QM_DCP3_FRAME_ENQ_TD_CONG_REJECTED	=	153,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to tail drop configured in the FQ's congestion group in any
	 * software portal. */
	DPDC_PE_QM_SPx_FRAME_ENQ_TD_CONG_REJECTED	=	154,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to tail drop configured in the FQ itself in DCP0. */
	DPDC_PE_QM_DCP0_FRAME_ENQ_TD_FQ_REJECTED	=	155,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to tail drop configured in the FQ itself in DCP1. */
	DPDC_PE_QM_DCP1_FRAME_ENQ_TD_FQ_REJECTED	=	156,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to tail drop configured in the FQ itself in DCP2. */
	DPDC_PE_QM_DCP2_FRAME_ENQ_TD_FQ_REJECTED	=	157,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to tail drop configured in the FQ itself in DCP3. */
	DPDC_PE_QM_DCP3_FRAME_ENQ_TD_FQ_REJECTED	=	158,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to tail drop configured in the FQ itself in any software portal*/
	DPDC_PE_QM_SPx_FRAME_ENQ_TD_FQ_REJECTED		=	159,

	/******************************************************************
	 *      DPDC Performance Event Word 5 (events 160 - 191)          *
	 *             Queue Manager Performance Events                   *
	 ******************************************************************/

	/* Pulses high for one cycle for every frame enqueue received from
	 * direct connect portal containing a marked frame in a direct connect
	 * portal with debug mark code point 01. */
	DPDC_PE_QM_DCPx_FRAME_ENQ_MARK_01		=	160,

	/* Pulses high for one cycle for every frame enqueue received from
	 * direct connect portal containing a marked frame in a direct connect
	 * portal with debug mark code point 10. */
	DPDC_PE_QM_DCPx_FRAME_ENQ_MARK_10		=	161,

	/* Pulses high for one cycle for every frame enqueue received from
	 * direct connect portal containing a marked frame in a direct connect
	 * portal with debug mark code point 11. */
	DPDC_PE_QM_DCPx_FRAME_ENQ_MARK_11		=	162,

	/* Pulses high for one cycle for every frame enqueue received from
	 * software portal containing a marked frame in a direct connect portal
	 * with debug mark code point 01. */
	DPDC_PE_QM_SPx_FRAME_ENQ_MARK_01		=	163,

	/* Pulses high for one cycle for every frame enqueue received from
	 * software portal containing a marked frame in a direct connect portal
	 * with debug mark code point 10. */
	DPDC_PE_QM_SPx_FRAME_ENQ_MARK_10		=	164,

	/* Pulses high for one cycle for every frame enqueue received from
	 * software portal containing a marked frame in a direct connect portal
	 * with debug mark code point 11. */
	DPDC_PE_QM_SPx_FRAME_ENQ_MARK_11		=	165,

	/* Pulses high for one cycle for every frame dequeue produced
	 * containing a marked frame in a direct connect portal with debug mark
	 * code point 01 */
	DPDC_PE_QM_DCPx_FRAME_DEQ_MARK_01		=	166,

	/* Pulses high for one cycle for every frame dequeue produced
	 * containing a marked frame in a direct connect portal with debug mark
	 * code point 01 */
	DPDC_PE_QM_DCPx_FRAME_DEQ_MARK_10		=	167,

	/* Pulses high for one cycle for every frame dequeue produced
	 * containing a marked frame in a direct connect portal with debug mark
	 * code point 11 */
	DPDC_PE_QM_DCPx_FRAME_DEQ_MARK_11		=	168,

	/* Pulses high for one cycle for every frame dequeue produced
	 * containing a marked frame in a software portal with debug mark code
	 * point 01. */
	DPDC_PE_QM_SPx_FRAME_DEQ_MARK_01		=	169,

	/* Pulses high for one cycle for every frame dequeue produced
	 * containing a marked frame in a software portal with debug mark code
	 * point 10. */
	DPDC_PE_QM_SPx_FRAME_DEQ_MARK_10		=	170,

	/* Pulses high for one cycle for every frame dequeue produced
	 * containing a marked frame in a software portal with debug mark code
	 * point 11. */
	DPDC_PE_QM_SPx_FRAME_DEQ_MARK_11		=	171,

	/* Pulses high for one cycle for every marked frame that is enqueued
	 * after leaving an ORP with debug mark code point 01. */
	DPDC_PE_QM_ORL_FRAME_ENQ_MARK_01		=	172,

	/* Pulses high for one cycle for every marked frame that is enqueued
	 * after leaving an ORP with debug mark code point 10. */
	DPDC_PE_QM_ORL_FRAME_ENQ_MARK_10		=	173,

	/* Pulses high for one cycle for every marked frame that is enqueued
	 * after leaving an ORP with debug mark code point 11. */
	DPDC_PE_QM_ORL_FRAME_ENQ_MARK_11		=	174,

	/*----------------- 175 - 191 entries are reserved -------------------*/

	/******************************************************************
	 *      DPDC Performance Event Word 6 (events 192 - 223)          *
	 *             Buffer Manager Performance Events                  *
	 ******************************************************************/


	/* Pulses high for one cycle every time a FBPR write succeeds for free
	 * list event monitor 0. */
	DPDC_PE_BM_FBPR_WRITE_FREELIST_MONITOR_0	=	192,

	/* Pulses high for one cycle every time a FBPR reads succeeds for free
	 * list event monitor 0. */
	DPDC_PE_BM_FBPR_READ_FREELIST_MONITOR_0		=	193,

	/* Pulses high for one cycle every time a FBPR write succeeds for free
	 * list event monitor 1. */
	DPDC_PE_BM_FBPR_WRITE_FREELIST_MONITOR_1	=	194,

	/* Pulses high for one cycle every time a FBPR reads succeeds for free
	 * list event monitor 1. */
	DPDC_PE_BM_FBPR_READ_FREELIST_MONITOR_1		=	195,

	/* Pulses high for one cycle every time a FBPR write succeeds for free
	 * list event monitor 2. */
	DPDC_PE_BM_FBPR_WRITE_FREELIST_MONITOR_2	=	196,

	/* Pulses high for one cycle every time a FBPR reads succeeds for free
	 * list event monitor 2. */
	DPDC_PE_BM_FBPR_READ_FREELIST_MONITOR_2		=	197,

	/* Pulses high for one cycle every time a FBPR write succeeds for free
	 * list event monitor 3. */
	DPDC_PE_BM_FBPR_WRITE_FREELIST_MONITOR_3	=	198,

	/* Pulses high for one cycle every time a FBPR reads succeeds for free
	 * list event monitor 3. */
	DPDC_PE_BM_FBPR_READ_FREELIST_MONITOR_3		=	199,

	/* Pulses high for one cycle every time a FBPR write succeeds for free
	 * list event monitor 4. */
	DPDC_PE_BM_FBPR_WRITE_FREELIST_MONITOR_4	=	200,

	/* Pulses high for one cycle every time a FBPR reads succeeds for free
	 * list event monitor 4. */
	DPDC_PE_BM_FBPR_READ_FREELIST_MONITOR_4		=	201,

	/* Pulses high for one cycle every time a FBPR write succeeds for free
	 * list event monitor 5. */
	DPDC_PE_BM_FBPR_WRITE_FREELIST_MONITOR_5	=	202,

	/* Pulses high for one cycle every time a FBPR reads succeeds for free
	 * list event monitor 5. */
	DPDC_PE_BM_FBPR_READ_FREELIST_MONITOR_5		=	203,

	/* Pulses high for one cycle every time a FBPR write succeeds for free
	 * list event monitor 6. */
	DPDC_PE_BM_FBPR_WRITE_FREELIST_MONITOR_6	=	204,

	/* Pulses high for one cycle every time a FBPR reads succeeds for free
	 * list event monitor 6. */
	DPDC_PE_BM_FBPR_READ_FREELIST_MONITOR_6		=	205,

	/* Pulses high for one cycle every time a FBPR write succeeds for free
	 * list event monitor 7. */
	DPDC_PE_BM_FBPR_WRITE_FREELIST_MONITOR_7	=	206,

	/* Pulses high for one cycle every time a FBPR reads succeeds for free
	 * list event monitor 7. */
	DPDC_PE_BM_FBPR_READ_FREELIST_MONITOR_7		=	207,

	/* Pulses high for one cycle every time a release buffer command
	 * threshold exceeded for command event monitor 0 */
	DPDC_PE_BM_RELEASE_BUF_EXCEEDS_CMD_MONITOR_0	=	208,

	/* Pulses high for one cycle every time an acquire buffer command
	 * threshold exceeded for command event monitor 0 */
	DPDC_PE_BM_ACQUIRE_BUF_EXCEEDS_CMD_MONITOR_0	=	209,

	/* Pulses high for one cycle every time a release buffer command
	 * threshold exceeded for command event monitor 1 */
	DPDC_PE_BM_RELEASE_BUF_EXCEEDS_CMD_MONITOR_1	=	210,

	/* Pulses high for one cycle every time an acquire buffer command
	 * threshold exceeded for command event monitor 1 */
	DPDC_PE_BM_ACQUIRE_BUF_EXCEEDS_CMD_MONITOR_1	=	211,

	/* Pulses high for one cycle every time a release buffer command
	 * threshold exceeded for command event monitor 2 */
	DPDC_PE_BM_RELEASE_BUF_EXCEEDS_CMD_MONITOR_2	=	212,

	/* Pulses high for one cycle every time an acquire buffer command
	 * threshold exceeded for command event monitor 2 */
	DPDC_PE_BM_ACQUIRE_BUF_EXCEEDS_CMD_MONITOR_2	=	213,

	/* Pulses high for one cycle every time a release buffer command
	 * threshold exceeded for command event monitor 3 */
	DPDC_PE_BM_RELEASE_BUF_EXCEEDS_CMD_MONITOR_3	=	214,

	/* Pulses high for one cycle every time an acquire buffer command
	 * threshold exceeded for command event monitor 3 */
	DPDC_PE_BM_ACQUIRE_BUF_EXCEEDS_CMD_MONITOR_3	=	215,

	/* Pulses high for one cycle every time a release buffer command
	 * threshold exceeded for command event monitor 4 */
	DPDC_PE_BM_RELEASE_BUF_EXCEEDS_CMD_MONITOR_4	=	216,

	/* Pulses high for one cycle every time an acquire buffer command
	 * threshold exceeded for command event monitor 4 */
	DPDC_PE_BM_ACQUIRE_BUF_EXCEEDS_CMD_MONITOR_4	=	217,

	/* Pulses high for one cycle every time a release buffer command
	 * threshold exceeded for command event monitor 5 */
	DPDC_PE_BM_RELEASE_BUF_EXCEEDS_CMD_MONITOR_5	=	218,

	/* Pulses high for one cycle every time an acquire buffer command
	 * threshold exceeded for command event monitor 5 */
	DPDC_PE_BM_ACQUIRE_BUF_EXCEEDS_CMD_MONITOR_5	=	219,

	/* Pulses high for one cycle every time a release buffer command
	 * threshold exceeded for command event monitor 6 */
	DPDC_PE_BM_RELEASE_BUF_EXCEEDS_CMD_MONITOR_6	=	220,

	/* Pulses high for one cycle every time an acquire buffer command
	 * threshold exceeded for command event monitor 6 */
	DPDC_PE_BM_ACQUIRE_BUF_EXCEEDS_CMD_MONITOR_6	=	221,

	/* Pulses high for one cycle every time a release buffer command
	 * threshold exceeded for command event monitor 7 */
	DPDC_PE_BM_RELEASE_BUF_EXCEEDS_CMD_MONITOR_7	=	222,

	/* Pulses high for one cycle every time an acquire buffer command
	 * threshold exceeded for command event monitor 7 */
	DPDC_PE_BM_ACQUIRE_BUF_EXCEEDS_CMD_MONITOR_7	=	223,

	/******************************************************************
	 *      DPDC Performance Event Word 7 (events 224 - 255)          *
	 *                  QM Performance Events                         *
	 ******************************************************************/

	/*---------------- 224 - 233 entries are reserved. -------------------*/

	/* PAMU PPAACT cache miss for the lookup request. */
	DPDC_PE_QM_PAMU_PPAACT_CACHE_MISS		=	234,

	/* PAMU PPAACT cache hit for the lookup request. */
	DPDC_PE_QM_PAMU_PPAACT_CACHE_HIT		=	235,

	/* PAMU SPAACT cache miss for the lookup request. */
	DPDC_PE_QM_PAMU_SPAACT_CACHE_MISS		=	236,

	/* PAMU SPAACT cache hit for the lookup request. */
	DPDC_PE_QM_PAMU_SPAACT_CACHE_HIT		=	237,

	/* PAMU OMT cache miss for the lookup request. */
	DPDC_PE_QM_PAMU_OMT_CACHE_MISS			=	238,

	/* PAMU OMT cache hit for the lookup request. */
	DPDC_PE_QM_PAMU_OMT_CACHE_HIT			=	239,

	/* Snoop invalidation hit in PAMU PPAACT cache */
	DPDC_PE_QM_PAMU_PPAACT_SNOOP_HIT		=	240,

	/* Snoop invalidation hit in PAMU SPAACT cache */
	DPDC_PE_QM_PAMU_SPAACT_SNOOP_HIT		=	241,

	/* Snoop invalidation hit in PAMU OMT cache */
	DPDC_PE_QM_PAMU_OMT_SNOOP_HIT			=	242,

	/*---------------- 243 - 246 entries are reserved. -------------------*/

	/* PAMU performs no address translation for the lookup request */
	DPDC_PE_QM_PAMU_NO_ADDR_TRANS			=	247,

	/* PAMU performs window address translation */
	DPDC_PE_QM_PAMU_WINDOW_ADDR_TRANS		=	248,

	/* PAMU performs no operation translation */
	DPDC_PE_QM_PAMU_NO_TRANS			=	249,

	/* PAMU performs immediate operation translation */
	DPDC_PE_QM_PAMU_IMMEDIATE_TRANS			=	250,

	/* PAMU performs index operation translation */
	DPDC_PE_QM_PAMU_INDEX_TRANS			=	251,

	/*---------------- 252 entry is reserved. ----------------------------*/

	/*------- 253 - 255 entries are reserved, tied to zero in DPDC -------*/

	/******************************************************************
	 *      DPDC Performance Event Word 8 (events 256 - 287)          *
	 *           Pattern Match Engine Performance Events              *
	 ******************************************************************/

	/*---------------- 256 - 263 entries are reserved. -------------------*/

	/* Number of cycles in which the Memory Interface Arbiter (MIA) is busy.
	 * Asserted if there are any outstanding read or write transactions
	 * remaining in MIA|x{2019}s internal queues. */
	DPDC_PE_PME_MIA_BUSY				=	264,

	/* Number of cycles in which the PMFA is at busy1 activity level. */
	DPDC_PE_PME_PMFA_BUSY1				=	265,

	/* Number of cycles in which the PMFA is at busy2 activity level */
	DPDC_PE_PME_PMFA_BUSY2				=	266,

	/* Number of cycles in which the PMFA is at busy3 activity level. */
	DPDC_PE_PME_PMFA_BUSY3				=	267,

	/* Number of read transactions issued on the system bus. Asserts high
	 * for one cycle for every read transaction issued */
	DPDC_PE_PME_READ_SYSTEM_BUS			=	268,

	/* Number of write transactions issued on the system bus. Asserts high
	 * for one cycle for every write transaction issued */
	DPDC_PE_PME_WRITE_SYSTEM_BUS			=	269,

	/* Number of hits in the PMFA's Flow Context Record Cache (number of
	 * times the cached copy of the Flow Context Record was referenced by a
	 * Flow Mode input Frame). */
	DPDC_PE_PME_HITS_PMFA_CONTEXT_CACHE		=	270,

	/* Number of hits in the PMFA's Residue Data Cache (number of times the
	 * held residue was recycled through the scanning pipeline without
	 * incurring a system memory write + read). */
	DPDC_PE_PME_HITS_PMFA_RESIDUE_CACHE		=	271,

	/* Number of cycles in which the Key Element Scanner (KES) is at busy1
	 * activity level. */
	DPDC_PE_PME_KES_BUSY1				=	272,

	/* Number of cycles in which the Key Element Scanner (KES) is at busy2
	 * activity level. */
	DPDC_PE_PME_KES_BUSY2				=	273,

	/*----- 274 - 275 entries are Allocated, tied to zero in IP Block ----*/

	/* Number of hits in the DXE's Pattern Description and Stateful Rule
	 * Table entry cache (number of times a cached test line was referenced
	 * without having to issue a system memory read). */
	DPDC_PE_PME_HITS_DXE_PATTERN_DESCRIPTION	=	276,

	/* Number of cycles in which the SRE Prefetch Sequencer is at busy1
	 * activity level. */
	DPDC_PE_PME_SRE_PREFETCH_SEQ_BUSY1		=	277,

	/* Number of cycles in which the SRE Prefetch Sequencer is at busy2
	 * activity level. */
	DPDC_PE_PME_SRE_PREFETCH_SEQ_BUSY2		=	278,

	/* Number of cycles in which the SRE Prefetch Sequencer is at busy3
	 * activity level. */
	DPDC_PE_PME_SRE_PREFETCH_SEQ_BUSY3		=	279,

	/* Number of cycles in which the SRE Execute Sequencer is at busy1
	 * activity level. */
	DPDC_PE_PME_SRE_EXECUTE_SEQ_BUSY1		=	280,

	/* Number of cycles in which the SRE Execute Sequencer is at busy2
	 * activity level. */
	DPDC_PE_PME_SRE_EXECUTE_SEQ_BUSY2		=	281,

	/* Number of cycles in which the SRE Execute Sequencer is at busy3
	 * activity level. */
	DPDC_PE_PME_SRE_EXECUTE_SEQ_BUSY3		=	282,

	/* Number of cycles in which the DXE Prefetch Sequencer is at busy1
	 * activity level. */
	DPDC_PE_PME_DXE_PREFETCH_SEQ_BUSY1		=	283,

	/* Number of cycles in which the DXE Prefetch Sequencer is at busy2
	 * activity level. */
	DPDC_PE_PME_DXE_PREFETCH_SEQ_BUSY2		=	284,

	/* Number of cycles in which the DXE Prefetch Sequencer is at busy3
	 * activity level. */
	DPDC_PE_PME_DXE_PREFETCH_SEQ_BUSY3		=	285,

	/* Number of cycles in which the DXE Execute Sequencer is at busy1
	 * activity level. */
	DPDC_PE_PME_DXE_EXECUTE_SEQ_BUSY1		=	286,

	/* Number of cycles in which the DXE Execute Sequencer is at busy2
	 * activity level. */
	DPDC_PE_PME_DXE_EXECUTE_SEQ_BUSY2		=	287,

	/******************************************************************
	 *      DPDC Performance Event Word 9 (events 288 - 319)          *
	 *                CAAM Engine Performance Events                  *
	 ******************************************************************/

	/* Pulsed for one cycle when dequeue from QMan to SEC4.0 with debug
	 * marking of 01. */
	DPDC_PE_SEC4_DEQ_MARK_01			=	288,

	/* Pulsed for one cycle when dequeue from QMan to SEC4.0 with debug
	 *  marking of 10. */
	DPDC_PE_SEC4_DEQ_MARK_10			=	289,

	/* Pulsed for one cycle when dequeue from QMan to SEC4.0 with debug
	 * marking of 01. */
	DPDC_PE_SEC4_DEQ_MARK_11			=	290,

	/* Pulsed for one cycle when enqueue from SEC4.0 to Qman with debug
	 * marking of 01. */
	DPDC_PE_SEC4_ENQ_MARK_01			=	291,

	/* Pulsed for one cycle when enqueue from SEC4.0 to Qman with debug
	 * marking of 10. */
	DPDC_PE_SEC4_ENQ_MARK_10			=	292,

	/* Pulsed for one cycle when enqueue from SEC4.0 to Qman with debug
	 * marking of 11. */
	DPDC_PE_SEC4_ENQ_MARK_11			=	293,

	/* Pulsed for one cycle when a job is inserted from Queue Interface to
	 * a JQC Holding Tank. */
	DPDC_PE_SEC4_JOB_INSERT_FROM_QUEUE_INTERFACE	=	294,

	/* Pulsed for one cycle when a job is inserted from RTIC to a JQC
	 * Holding Tank. */
	DPDC_PE_SEC4_JOB_INSERT_FROM_RTIC		=	295,

	/* Pulsed for one cycle when a job is inserted from Job Queue 0 to a
	 * JQC Holding Tank. */
	DPDC_PE_SEC4_JOB_INSERT_FROM_JOB_QUEUE0		=	296,

	/* Pulsed for one cycle when a job is inserted from Job Queue 1 to a
	 * JQC Holding Tank. */
	DPDC_PE_SEC4_JOB_INSERT_FROM_JOB_QUEUE1 	=	297,

	/* Pulsed for one cycle when a job is inserted from Job Queue 2 to a
	 * JQC Holding Tank. */
	DPDC_PE_SEC4_JOB_INSERT_FROM_JOB_QUEUE2		=	298,

	/* Pulsed for one cycle when a job is inserted from Job Queue 3 to a
	 * JQC Holding Tank. */
	DPDC_PE_SEC4_JOB_INSERT_FROM_JOB_QUEUE3		=	299,

	/* Pulsed for one cycle when a job is taken from a holding tank into
	 * DECO 0. */
	DPDC_PE_SEC4_JOB_TO_DECO0			=	300,

	/* Asserted whenever DECO 0 is idle. */
	DPDC_PE_SEC4_DECO0_IDLE				=	301,

	/* Asserted whenever the input FIFO is empty and DECO0 is awaiting a
	 * response to a DMA read or output FIFO is full, DECO0 is awaiting a
	 * response to a DMA write. */
	DPDC_PE_SEC4_DECO0_AWAITS_DMA			=	302,

	/* Pulsed for one cycle when an actual operation command in DECO0 is
	 * encountered in a job descriptor, a shared descriptor, or a trusted
	 * descriptor. */
	DPDC_PE_SEC4_CMD_IN_DECO0			=	303,

	/* Pulsed for one cycle when a job is taken from a holding tank into
	 * DECO 1. */
	DPDC_PE_SEC4_JOB_TO_DECO1			=	304,

	/* Asserted whenever DEC1 0 is idle. */
	DPDC_PE_SEC4_DECO1_IDLE				=	305,

	/* Asserted whenever the input FIFO is empty and DECO1 is awaiting a
	 * response to a DMA read or output FIFO is full, DECO1 is awaiting a
	 * response to a DMA write. */
	DPDC_PE_SEC4_DECO1_AWAITS_DMA			=	306,

	/* Pulsed for one cycle when an actual operation command in DECO1 is
	 * encountered in a job descriptor, a shared descriptor, or a trusted
	 * descriptor. */
	DPDC_PE_SEC4_CMD_IN_DECO1			=	307,

	/* Pulsed for one cycle when a job is taken from a holding tank into
	 * DECO 2. */
	DPDC_PE_SEC4_JOB_TO_DECO2			=	308,

	/* Asserted whenever DECO 2 is idle. */
	DPDC_PE_SEC4_DECO2_IDLE				=	309,

	/* Asserted whenever the input FIFO is empty and DECO2 is awaiting a
	 * response to a DMA read or output FIFO is full, DECO2 is awaiting a
	 * response to a DMA write. */
	DPDC_PE_SEC4_DECO2_AWAITS_DMA			=	310,

	/* Pulsed for one cycle when an actual operation command in DECO2 is
	 * encountered in a job descriptor, a shared descriptor, or a trusted
	 * descriptor. */
	DPDC_PE_SEC4_CMD_IN_DECO2			=	311,

	/* Pulsed for one cycle when a job is taken from a holding tank into
	 * DECO 3. */
	DPDC_PE_SEC4_JOB_TO_DECO3			=	312,

	/* Asserted whenever DECO 3 is idle. */
	DPDC_PE_SEC4_DECO3_IDLE				=	313,

	/* Asserted whenever the input FIFO is empty and DECO3 is awaiting a
	 * response to a DMA read or output FIFO is full, DECO3 is awaiting a
	 * response to a DMA write. */
	DPDC_PE_SEC4_DECO3_AWAITS_DMA			=	314,

	/* Pulsed for one cycle when an actual operation command in DECO3 is
	 * encountered in a job descriptor, a shared descriptor, or a trusted
	 * descriptor. */
	DPDC_PE_SEC4_CMD_IN_DECO3			=	315,

	/* Pulsed for one cycle when a job is taken from a holding tank into
	 * DECO 4. */
	DPDC_PE_SEC4_JOB_TO_DECO4			=	316,

	/* Asserted whenever DECO 4 is idle. */
	DPDC_PE_SEC4_DECO4_IDLE				=	317,

	/* Asserted whenever the input FIFO is empty and DECO4 is awaiting a
	 * response to a DMA read or output FIFO is full, DECO4 is awaiting a
	 * response to a DMA write. */
	DPDC_PE_SEC4_DECO4_AWAITS_DMA			=	318,

	/* Pulsed for one cycle when an actual operation command in DECO4 is
	 * encountered in a job descriptor, a shared descriptor, or a trusted
	 * descriptor. */
	DPDC_PE_SEC4_CMD_IN_DECO4			=	319,

	/******************************************************************
	 *      DPDC Performance Event Word 10 (events 320 - 351)         *
	 *                 SEC4 Performance Events                        *
	 ******************************************************************/

	/*---------------- 320 - 329 entries are reserved. -------------------*/

	/* PAMU PPAACT cache miss for the lookup request. */
	DPDC_PE_SEC4_PAMU_PPAACT_CACHE_MISS		=	330,

	/* PAMU PPAACT cache hit for the lookup request. */
	DPDC_PE_SEC4_PAMU_PPAACT_CACHE_HIT		=	331,

	/* PAMU SPAACT cache miss for the lookup request. */
	DPDC_PE_SEC4_PAMU_SPAACT_CACHE_MISS		=	332,

	/* PAMU SPAACT cache hit for the lookup request. */
	DPDC_PE_SEC4_PAMU_SPAACT_CACHE_HIT		=	333,

	/* PAMU OMT cache miss for the lookup request. */
	DPDC_PE_SEC4_PAMU_OMT_CACHE_MISS		=	334,

	/* PAMU OMT cache hit for the lookup request. */
	DPDC_PE_SEC4_PAMU_OMT_CACHE_HIT			=	335,

	/* Snoop invalidation hit in PAMU PPAACT cache */
	DPDC_PE_SEC4_PAMU_PPAACT_SNOOP_HIT		=	336,

	/* Snoop invalidation hit in PAMU SPAACT cache */
	DPDC_PE_SEC4_PAMU_SPAACT_SNOOP_HIT		=	337,

	/* Snoop invalidation hit in PAMU OMT cache */
	DPDC_PE_SEC4_PAMU_OMT_SNOOP_HIT			=	338,

	/*---------------- 339 - 342 entries are reserved. -------------------*/

	/* PAMU performs no address translation for the lookup request */
	DPDC_PE_SEC4_PAMU_NO_ADDR_TRANS			=	343,

	/* PAMU performs window address translation */
	DPDC_PE_SEC4_PAMU_WINDOW_ADDR_TRANS		=	344,

	/* PAMU performs no operation translation */
	DPDC_PE_SEC4_PAMU_NO_TRANS			=	345,

	/* PAMU performs immediate operation translation */
	DPDC_PE_SEC4_PAMU_IMMEDIATE_TRANS		=	346,

	/* PAMU performs index operation translation */
	DPDC_PE_SEC4_PAMU_INDEX_TRANS			=	347,

	/*---------------- 348 entry is reserved. ----------------------------*/

	/*------- 349 - 351 entries are reserved, tied to zero in DPDC -------*/

	/******************************************************************
	 *      DPDC Performance Event Word 11 (events 352 - 383)         *
	 *                    FM1 Performance Events                      *
	 ******************************************************************/

	/* Indicates the actual used RX FIFO size is equal or greater than the
	 * size specified in FMBM_RPCP[FUCV] for GMAC. */
	DPDC_PE_FM1_GMAC_USED_RX_FIFO_GE		=	352,

	/* Indicates the actual used RX FIFO size is equal or greater than the
	 * size specified in FMBM_RPCP[FUCV] for DTSEC0. */
	DPDC_PE_FM1_DTSEC0_USED_RX_FIFO_GE		=	353,

	/* Indicates the actual used RX FIFO size is equal or greater than the
	 * size specified in FMBM_RPCP[FUCV] for DTSEC1. */
	DPDC_PE_FM1_DTSEC1_USED_RX_FIFO_GE		=	354,

	/* Indicates the actual used RX FIFO size is equal or greater than the
	 * size specified in FMBM_RPCP[FUCV] for DTSEC2. */
	DPDC_PE_FM1_DTSEC2_USED_RX_FIFO_GE		=	355,

	/* Indicates the actual used RX FIFO size is equal or greater than the
	 * size specified in FMBM_RPCP[FUCV] for DTSEC3. */
	DPDC_PE_FM1_DTSEC3_USED_RX_FIFO_GE		=	356,

	/* Indicates the RX pause activation control is on for GMAC. */
	DPDC_PE_FM1_PAUSE_FOR_GMAC			=	357,

	/* Indicates the RX pause activation control is on for DTSEC0. */
	DPDC_PE_FM1_PAUSE_FOR_DTSEC0			=	358,

	/* Indicates the RX pause activation control is on for DTSEC1. */
	DPDC_PE_FM1_PAUSE_FOR_DTSEC1			=	359,

	/* Indicates the RX pause activation control is on for DTSEC2. */
	DPDC_PE_FM1_PAUSE_FOR_DTSEC2			=	360,

	/* Indicates the RX pause activation control is on for DTSEC3. */
	DPDC_PE_FM1_PAUSE_FOR_DTSEC3			=	361,

	/* Debug trap event occurred in BMI for the current packet with the
	 *  debug mark of 01 */
	DPDC_PE_FM1_BMI_TRAP_MARK_01			=	362,

	/* Debug trap event occurred in BMI for the current packet with the
	 *  debug mark of 10 */
	DPDC_PE_FM1_BMI_TRAP_MARK_10			=	363,

	/* Debug trap event occurred in BMI for the current packet with the
	 *  debug mark of 11 */
	DPDC_PE_FM1_BMI_TRAP_MARK_11			=	364,

	/* Indicates the default frame queue is used implying no Keygen scheme
	 *  is found or no classification match is found. */
	DPDC_PE_FM1_DEFAULT_QUEUE_USED			=	365,

	/* Debug trap event occurred in keygen for the current packet with the
	 *  debug mark of 01. */
	DPDC_PE_FM1_KEYGEN_TRAP_MARK_01			=	366,

	/* Debug trap event occurred in keygen for the current packet with the
	 *   debug mark of 10. */
	DPDC_PE_FM1_KEYGEN_TRAP_MARK_10			=	367,

	/* Debug trap event occurred in keygen for the current packet with the
	 * debug mark of 11. */
	DPDC_PE_FM1_KEYGEN_TRAP_MARK_11			=	368,

	/* Debug trap event occurred in Parser for the current packet with the
	 * debug mark of 01. */
	DPDC_PE_FM1_PARSER_TRAP_MARK_01			=	369,

	/* Debug trap event occurred in Parser for the current packet with the
	 * debug mark of 10. */
	DPDC_PE_FM1_PARSER_TRAP_MARK_10			=	370,

	/* Debug trap event occurred in Parser for the current packet with the
	 * debug mark of 11. */
	DPDC_PE_FM1_PARSER_TRAP_MARK_11			=	371,

	/* Pulsed for one cycle when the policer has change the color of the
	 * current packet to RED. It does not include the packets that are
	 * pre-colored RED (in color aware mode). */
	DPDC_PE_FM1_CHANGED_TO_RED			=	372,

	/* Pulsed for one cycle when the policer has change the color of the
	 * current packet to YELLOW. It does not include the packets that are
	 * pre-colored YELLOW. */
	DPDC_PE_FM1_CHANGED_TO_YELLOW			=	373,

	/* Debug trap event occurred in policer for the current packet with the
	 * debug mark of 01. */
	DPDC_PE_FM1_POLICER_TRAP_MARK_01		=	374,

	/* Debug trap event occurred in policer for the current packet with the
	 * debug mark of 10. */
	DPDC_PE_FM1_POLICER_TRAP_MARK_10		=	375,

	/* Debug trap event occurred in policer for the current packet with the
	 * debug mark of 11. */
	DPDC_PE_FM1_POLICER_TRAP_MARK_11		=	376,

	/* Debug trap event occurred in Classifier 1 for the current packet
	 * with the debug mark of 01. */
	DPDC_PE_FM1_CLASSIFIER1_TRAP_MARK_01		=	377,

	/* Debug trap event occurred in Classifier 1 for the current packet
	 * with the debug mark of 10. */
	DPDC_PE_FM1_CLASSIFIER1_TRAP_MARK_10		=	378,

	/* Debug trap event occurred in Classifier 1 for the current packet
	 * with the debug mark of 11. */
	DPDC_PE_FM1_CLASSIFIER1_TRAP_MARK_11		=	379,

	/* Debug trap event occurred in Classifier 2 for the current packet
	 * with the debug mark of 01. */
	DPDC_PE_FM1_CLASSIFIER2_TRAP_MARK_01		=	380,

	/* Debug trap event occurred in Classifier 2 for the current packet
	 * with the debug mark of 10. */
	DPDC_PE_FM1_CLASSIFIER2_TRAP_MARK_10		=	381,

	/* Debug trap event occurred in Classifier 2 for the current packet
	 * with the debug mark of 11. */
	DPDC_PE_FM1_CLASSIFIER2_TRAP_MARK_11		=	382,

	/*-------------- The 283 entry is tied to zero in DPDC ---------------*/

	/******************************************************************
	 *      DPDC Performance Event Word 12 (events 384 - 415)         *
	 *         DP Correlation Performance Events Group 1              *
	 ******************************************************************/

	/* Pulsed for one cycle when Command Queue emergency signal is asserted
	 * in DMA. */
	DPDC_PE_FM1_DMA_CMD_QUEUE_EMERGENCY		=	384,

	/* Pulsed for one cycle when Internal Read Buffer emergency signal is
	 * asserted in DMA. */
	DPDC_PE_FM1_DMA_READ_BUF_EMERGENCY		=	385,

	/* Pulsed for one cycle when Internal Write Buffer emergency signal is
	 * asserted in DMA. */
	DPDC_PE_FM1_DMA_WRITE_BUF_EMERGENCY		=	386,

	/* Pulsed for one cycle when FPM WAIT signal is asserted in DMA. */
	DPDC_PE_FM1_DMA_FPM_WAIT_EMERGENCY		=	387,

	/* Pulsed for one cycle when SOS emergency state is asserted in DMA. */
	DPDC_PE_FM1_DMA_FPM_SOS_EMERGENCY		=	388,

	/* Debug trap event occurred in QMI for the current packet with the
	 * debug mark of 01. */
	DPDC_PE_FM1_QMI_TRAP_MARK_01			=	389,

	/* Debug trap event occurred in QMI for the current packet with the
	 * debug mark of 10. */
	DPDC_PE_FM1_QMI_TRAP_MARK_10			=	390,

	/* Debug trap event occurred in QMI for the current packet with the
	 * debug mark of 11. */
	DPDC_PE_FM1_QMI_TRAP_MARK_11			=	391,

	/*---------------- 392 - 400 entries are reserved. -------------------*/

	/* Pulsed for one cycle when dequeue from QMan to SEC4.0 with debug
	 *  marking of 01 (duplicates 288). */
	DPDC_PE_SEC4_DEQ_MARK_01_DUP			=	401,

	/* Pulsed for one cycle when dequeue from QMan to SEC4.0 with debug
	 *  marking of 10 (duplicates 289). */
	DPDC_PE_SEC4_DEQ_MARK_10_DUP			=	402,

	/* Pulsed for one cycle when dequeue from QMan to SEC4.0 with debug
	 *  marking of 01 (duplicates 290. */
	DPDC_PE_SEC4_DEQ_MARK_11_DUP			=	403,

	/* Pulsed for one cycle when enqueue from SEC4.0 to Qman with debug
	 *  marking of 01 (duplicates 291). */
	DPDC_PE_SEC4_ENQ_MARK_01_DUP			=	404,

	/* Pulsed for one cycle when enqueue from SEC4.0 to Qman with debug
	 *  marking of 10 (duplicates 292). */
	DPDC_PE_SEC4_ENQ_MARK_10_DUP			=	405,

	/* Pulsed for one cycle when enqueue from SEC4.0 to Qman with debug
	 * marking of 11 (duplicates 293). */
	DPDC_PE_SEC4_ENQ_MARK_11_DUP			=	406,

	/* Pulsed for one cycle when Command Queue emergency signal is asserted
	 * in DMA. */
	DPDC_PE_FM2_DMA_CMD_QUEUE_EMERGENCY		=	407,

	/* Pulsed for one cycle when Internal Read Buffer emergency signal is
	 * asserted in DMA. */
	DPDC_PE_FM2_DMA_READ_BUF_EMERGENCY		=	408,

	/* Pulsed for one cycle when Internal Write Buffer emergency signal is
	 * asserted in DMA. */
	DPDC_PE_FM2_DMA_WRITE_BUF_EMERGENCY		=	409,

	/* Pulsed for one cycle when FPM WAIT signal is asserted in DMA. */
	DPDC_PE_FM2_DMA_FPM_WAIT_EMERGENCY		=	410,

	/* Pulsed for one cycle when SOS emergency state is asserted in DMA. */
	DPDC_PE_FM2_DMA_FPM_SOS_EMERGENCY		=	411,

	/* Debug trap event occurred in QMI for the current packet with the
	 *  debug mark of 01. */
	DPDC_PE_FM2_QMI_TRAP_MARK_01			=	412,

	/* Debug trap event occurred in QMI for the current packet with the
	 *  debug mark of 10. */
	DPDC_PE_FM2_QMI_TRAP_MARK_10			=	413,

	/* Debug trap event occurred in QMI for the current packet with the
	 *  debug mark of 11. */
	DPDC_PE_FM2_QMI_TRAP_MARK_11			=	414,

	/*-------------- The 415 entry is tied to zero in DPDC ---------------*/

	/******************************************************************
	 *      DPDC Performance Event Word 13 (events 416 - 447)         *
	 *                  FM1 Performance Events                        *
	 ******************************************************************/

	/*---------------- 416 - 425 entries are reserved. -------------------*/

	/* PAMU PPAACT cache miss for the lookup request. */
	DPDC_PE_FM1_PAMU_PPAACT_CACHE_MISS		=	426,

	/* PAMU PPAACT cache hit for the lookup request. */
	DPDC_PE_FM1_PAMU_PPAACT_CACHE_HIT		=	427,

	/* PAMU SPAACT cache miss for the lookup request. */
	DPDC_PE_FM1_PAMU_SPAACT_CACHE_MISS		=	428,

	/* PAMU SPAACT cache hit for the lookup request. */
	DPDC_PE_FM1_PAMU_SPAACT_CACHE_HIT		=	429,

	/* PAMU OMT cache miss for the lookup request. */
	DPDC_PE_FM1_PAMU_OMT_CACHE_MISS			=	430,

	/* PAMU OMT cache hit for the lookup request. */
	DPDC_PE_FM1_PAMU_OMT_CACHE_HIT			=	431,

	/* Snoop invalidation hit in PAMU PPAACT cache */
	DPDC_PE_FM1_PAMU_PPAACT_SNOOP_HIT		=	432,

	/* Snoop invalidation hit in PAMU SPAACT cache */
	DPDC_PE_FM1_PAMU_SPAACT_SNOOP_HIT		=	433,

	/* Snoop invalidation hit in PAMU OMT cache */
	DPDC_PE_FM1_PAMU_OMT_SNOOP_HIT			=	434,

	/*---------------- 435 - 438 entries are reserved. -------------------*/

	/* PAMU performs no address translation for the lookup request */
	DPDC_PE_FM1_PAMU_NO_ADDR_TRANS			=	439,

	/* PAMU performs window address translation */
	DPDC_PE_FM1_PAMU_WINDOW_ADDR_TRANS		=	440,

	/* PAMU performs no operation translation */
	DPDC_PE_FM1_PAMU_NO_TRANS			=	441,

	/* PAMU performs immediate operation translation */
	DPDC_PE_FM1_PAMU_IMMEDIATE_TRANS		=	442,

	/* PAMU performs index operation translation */
	DPDC_PE_FM1_PAMU_INDEX_TRANS			=	443,

	/*---------------- 444 entry is reserved. ----------------------------*/

	/*------- 445 - 447 entries are reserved, tied to zero in DPDC -------*/

	/******************************************************************
	 *      DPDC Performance Event Word 14 (events 448 - 479)         *
	 *                    FM2 Performance Events                      *
	 ******************************************************************/

	/* Indicates the actual used RX FIFO size is equal or greater than the
	 * size specified in FMBM_RPCP[FUCV] for GMAC. */
	DPDC_PE_FM2_GMAC_USED_RX_FIFO_GE		=	448,

	/* Indicates the actual used RX FIFO size is equal or greater than the
	 * size specified in FMBM_RPCP[FUCV] for DTSEC0. */
	DPDC_PE_FM2_DTSEC0_USED_RX_FIFO_GE		=	449,

	/* Indicates the actual used RX FIFO size is equal or greater than the
	 * size specified in FMBM_RPCP[FUCV] for DTSEC1. */
	DPDC_PE_FM2_DTSEC1_USED_RX_FIFO_GE		=	450,

	/* Indicates the actual used RX FIFO size is equal or greater than the
	 * size specified in FMBM_RPCP[FUCV] for DTSEC2. */
	DPDC_PE_FM2_DTSEC2_USED_RX_FIFO_GE		=	451,

	/* Indicates the actual used RX FIFO size is equal or greater than the
	 * size specified in FMBM_RPCP[FUCV] for DTSEC3. */
	DPDC_PE_FM2_DTSEC3_USED_RX_FIFO_GE		=	452,

	/* Indicates the RX pause activation control is on for GMAC. */
	DPDC_PE_FM2_PAUSE_FOR_GMAC			=	453,

	/* Indicates the RX pause activation control is on for DTSEC0. */
	DPDC_PE_FM2_PAUSE_FOR_DTSEC0			=	454,

	/* Indicates the RX pause activation control is on for DTSEC1. */
	DPDC_PE_FM2_PAUSE_FOR_DTSEC1			=	455,

	/* Indicates the RX pause activation control is on for DTSEC2. */
	DPDC_PE_FM2_PAUSE_FOR_DTSEC2			=	456,

	/* Indicates the RX pause activation control is on for DTSEC3. */
	DPDC_PE_FM2_PAUSE_FOR_DTSEC3			=	457,

	/* Debug trap event occurred in BMI for the current packet with the
	 * debug mark of 01 */
	DPDC_PE_FM2_BMI_TRAP_MARK_01			=	458,

	/* Debug trap event occurred in BMI for the current packet with the
	 * debug mark of 10 */
	DPDC_PE_FM2_BMI_TRAP_MARK_10			=	459,

	/* Debug trap event occurred in BMI for the current packet with the
	 * debug mark of 11 */
	DPDC_PE_FM2_BMI_TRAP_MARK_11			=	460,

	/* Indicates the default frame queue is used implying no Keygen scheme
	 * is found or no classification match is found. */
	DPDC_PE_FM2_DEFAULT_QUEUE_USED			=	461,

	/* Debug trap event occurred in keygen for the current packet with the
	 * debug mark of 01. */
	DPDC_PE_FM2_KEYGEN_TRAP_MARK_01			=	462,

	/* Debug trap event occurred in keygen for the current packet with the
	 * debug mark of 10. */
	DPDC_PE_FM2_KEYGEN_TRAP_MARK_10			=	463,

	/* Debug trap event occurred in keygen for the current packet with the
	 * debug mark of 11. */
	DPDC_PE_FM2_KEYGEN_TRAP_MARK_11			=	464,

	/* Debug trap event occurred in Parser for the current packet with the
	 * debug mark of 01. */
	DPDC_PE_FM2_PARSER_TRAP_MARK_01			=	465,

	/* Debug trap event occurred in Parser for the current packet with the
	 * debug mark of 10. */
	DPDC_PE_FM2_PARSER_TRAP_MARK_10			=	466,

	/* Debug trap event occurred in Parser for the current packet with the
	 * debug mark of 11. */
	DPDC_PE_FM2_PARSER_TRAP_MARK_11			=	467,

	/* Pulsed for one cycle when the policer has change the color of the
	 * current packet to RED. It does not include the packets that are
	 * pre-colored RED (in color aware mode). */
	DPDC_PE_FM2_CHANGED_TO_RED			=	468,

	/* Pulsed for one cycle when the policer has change the color of the
	 * current packet to YELLOW. It does not include the packets that are
	 * pre-colored YELLOW. */
	DPDC_PE_FM2_CHANGED_TO_YELLOW			=	469,

	/* Debug trap event occurred in policer for the current packet with the
	 * debug mark of 01. */
	DPDC_PE_FM2_POLICER_TRAP_MARK_01		=	470,

	/* Debug trap event occurred in policer for the current packet with the
	 * debug mark of 10. */
	DPDC_PE_FM2_POLICER_TRAP_MARK_10		=	471,

	/* Debug trap event occurred in policer for the current packet with the
	 * debug mark of 11. */
	DPDC_PE_FM2_POLICER_TRAP_MARK_11		=	472,

	/* Debug trap event occurred in Classifier 1 for the current packet
	 * with the debug mark of 01. */
	DPDC_PE_FM2_CLASSIFIER1_TRAP_MARK_01		=	473,

	/* Debug trap event occurred in Classifier 1 for the current packet
	 * with the debug mark of 10. */
	DPDC_PE_FM2_CLASSIFIER1_TRAP_MARK_10		=	474,

	/* Debug trap event occurred in Classifier 1 for the current packet
	 * with the debug mark of 11. */
	DPDC_PE_FM2_CLASSIFIER1_TRAP_MARK_11		=	475,

	/* Debug trap event occurred in Classifier 2 for the current packet
	 * with the debug mark of 01. */
	DPDC_PE_FM2_CLASSIFIER2_TRAP_MARK_01		=	476,

	/* Debug trap event occurred in Classifier 2 for the current packet
	 * with the debug mark of 10. */
	DPDC_PE_FM2_CLASSIFIER2_TRAP_MARK_10		=	477,

	/* Debug trap event occurred in Classifier 2 for the current packet
	 * with the debug mark of 11. */
	DPDC_PE_FM2_CLASSIFIER2_TRAP_MARK_11		=	478,

	/*-------------- The 479 entry is tied to zero in DPDC ---------------*/


	/******************************************************************
	 *      DPDC Performance Event Word 15 (events 480 - 511)         *
	 *            DP Correlation Performance Events Group 2           *
	 ******************************************************************/

	/*---------------- 480 - 487 entries are reserved. -------------------*/

	/* Number of read transactions issued on the system bus. Asserts high
	 * for one cycle for every read transaction issued (duplicates 268) */
	DPDC_PE_PME_READ_SYSTEM_BUS_DUP			=	488,

	/* Number of write transactions issued on the system bus. Asserts high
	 * for one cycle for every write transaction issued (duplicates 269) */
	DPDC_PE_PME_WRITE_SYSTEM_BUS_DUP		=	489,

	/*---------------- 490 - 499 entries are reserved. -------------------*/

	/*------------ 500 - 511 entries are tied to zero in DPDC ------------*/

	/******************************************************************
	 *      DPDC Performance Event Word 16 (events 512 - 543)         *
	 *                  FM2 Performance Events                        *
	 ******************************************************************/

	/*---------------- 512 - 521 entries are reserved. -------------------*/

	/* PAMU PPAACT cache miss for the lookup request. */
	DPDC_PE_FM2_PAMU_PPAACT_CACHE_MISS		=	522,

	/* PAMU PPAACT cache hit for the lookup request. */
	DPDC_PE_FM2_PAMU_PPAACT_CACHE_HIT		=	523,

	/* PAMU SPAACT cache miss for the lookup request. */
	DPDC_PE_FM2_PAMU_SPAACT_CACHE_MISS		=	524,

	/* PAMU SPAACT cache hit for the lookup request. */
	DPDC_PE_FM2_PAMU_SPAACT_CACHE_HIT		=	525,

	/* PAMU OMT cache miss for the lookup request. */
	DPDC_PE_FM2_PAMU_OMT_CACHE_MISS			=	526,

	/* PAMU OMT cache hit for the lookup request. */
	DPDC_PE_FM2_PAMU_OMT_CACHE_HIT			=	527,

	/* Snoop invalidation hit in PAMU PPAACT cache */
	DPDC_PE_FM2_PAMU_PPAACT_SNOOP_HIT		=	528,

	/* Snoop invalidation hit in PAMU SPAACT cache */
	DPDC_PE_FM2_PAMU_SPAACT_SNOOP_HIT		=	529,

	/* Snoop invalidation hit in PAMU OMT cache */
	DPDC_PE_FM2_PAMU_OMT_SNOOP_HIT			=	530,

	/*---------------- 531 - 534 entries are reserved. -------------------*/

	/* PAMU performs no address translation for the lookup request */
	DPDC_PE_FM2_PAMU_NO_ADDR_TRANS			=	535,

	/* PAMU performs window address translation */
	DPDC_PE_FM2_PAMU_WINDOW_ADDR_TRANS		=	536,

	/* PAMU performs no operation translation */
	DPDC_PE_FM2_PAMU_NO_TRANS			=	537,

	/* PAMU performs immediate operation translation */
	DPDC_PE_FM2_PAMU_IMMEDIATE_TRANS		=	538,

	/* PAMU performs index operation translation */
	DPDC_PE_FM2_PAMU_INDEX_TRANS			=	539,

	/*---------------- 540 entry is reserved. ----------------------------*/

	/*------- 541 - 543 entries are reserved, tied to zero in DPDC -------*/

	/******************************************************************
	 *      DPDC Performance Event Word 17 (events 544 - 575)         *
	 *            QM DCP0 Performance Events (redundant)              *
	 ******************************************************************/

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP0 exceeds threshold A in DCP0 (duplicates 0). */
	DPDC_PE_QM_DCP0_DEQ_EXCEEDS_THRESHOLD_A_DUP	=	544,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP0 exceeds threshold B in DCP0 (duplicates 1). */
	DPDC_PE_QM_DCP0_DEQ_EXCEEDS_THRESHOLD_B_DUP	=	545,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP0 exceeds threshold C in DCP0 (duplicates 2). */
	DPDC_PE_QM_DCP0_DEQ_EXCEEDS_THRESHOLD_C_DUP	=	546,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP0 exceeds threshold D in DCP0 (duplicates 3). */
	DPDC_PE_QM_DCP0_DEQ_EXCEEDS_THRESHOLD_D_DUP	=	547,

	/*---------------- 548 - 551 entries are reserved. -------------------*/

	/* Pulse high for one cycle for every enqueue command received in
	 * DCP0 (duplicates 55) */
	DPDC_PE_QM_DCP0_ENQ_CMD_RECEIVED_DUP		=	552,

	/* Asserted whenever the enqueue command FIFO in a direct connect
	 * portal is full in DCP0 (duplicates 79). */
	DPDC_PE_QM_DCP0_ENQ_CMD_FIFO_FULL_DUP		=	553,

	/* Asserted whenever the dequeue command FIFO in DCP0 is full
	 * (duplicates 84). */
	DPDC_PE_QM_DCP0_DEQ_CMD_FIFO_FULL_DUP		=	554,

	/* Asserted whenever the dequeue response FIFO in DCP0 is full
	 * (duplicates 88). */
	DPDC_PE_QM_DCP0_DEQ_RSP_FIFO_FULL_DUP		=	555,

	/* Pulses high for one cycle for every enqueue sequence that is
	 * dispatched for DCP0. This number may be lower than the number of
	 * enqueue commands received, because enqueue commands can be
	 * dispatched up to 3 at a time when they target the same FQ
	 * (duplicates 102). */
	DPDC_PE_QM_DCP0_ENQ_SEQ_DISPATCH_DUP		=	556,

	/* Pulses high for one cycle for every enqueue sequence that is
	 * dispatched for DCP0 when the corresponding command FIFO is full
	 * (duplicates 107). */
	DPDC_PE_QM_DCP0_ENQ_SEQ_DISPATCH_FIFO_FULL_DUP	=	557,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 1 or more frames for DCP0 (duplicates 112). */
	DPDC_PE_QM_DCP0_DEQ_SEQ_DELIVERS_1_DUP		=	558,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 2 or more frames for DCP0 (duplicates 117). */
	DPDC_PE_QM_DCP0_DEQ_SEQ_DELIVERS_2_DUP		=	559,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 3 frames for DCP0 (duplicates 122). */
	DPDC_PE_QM_DCP0_DEQ_SEQ_DELIVERS_3_DUP		=	560,

	/* Pulses high for one cycle for every dequeue command dispatched when
	 * the dequeue command FIFO in DCP0 is full (duplicates 127). */
	DPDC_PE_QM_DCP0_DEQ_CMD_DISPATCH_FIFO_FULL_DUP	=	561,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * in DCP0 (duplicates 140). */
	DPDC_PE_QM_DCP0_FRAME_ENQ_REJECTED_DUP		=	562,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to WRED discard in DCP0 (duplicates 145). */
	DPDC_PE_QM_DCP0_FRAME_ENQ_WRED_REJECTED_DUP	=	563,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to tail drop configured in the FQ's congestion group in DCP0
	 * (duplicates 150). */
	DPDC_PE_QM_DCP0_FRAME_ENQ_TD_CONG_REJECTED_DUP	=	564,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to tail drop configured in the FQ itself in DCP0
	 * (duplicates 155). */
	DPDC_PE_QM_DCP0_FRAME_ENQ_TD_FQ_REJECTED_DUP	=	565,

	/* Pulses high for one cycle for every frame enqueue received from
	 * direct connect portal containing a marked frame in a direct connect
	 * portal with debug mark code point 01 (duplicates 160). */
	DPDC_PE_QM_DCPx_FRAME_ENQ_MARK_01_DUP		=	566,

	/* Pulses high for one cycle for every frame enqueue received from
	 * direct connect portal containing a marked frame in a direct connect
	 * portal with debug mark code point 10 (duplicates 161). */
	DPDC_PE_QM_DCPx_FRAME_ENQ_MARK_10_DUP		=	567,

	/* Pulses high for one cycle for every frame enqueue received from
	 * direct connect portal containing a marked frame in a direct connect
	 * portal with debug mark code point 11 (duplicates 162). */
	DPDC_PE_QM_DCPx_FRAME_ENQ_MARK_11_DUP		=	568,

	/* Pulses high for one cycle for every frame dequeue produced containing
	 * a marked frame in a direct connect portal with debug mark code point
	 * 01 (duplicates 166) */
	DPDC_PE_QM_DCPx_FRAME_DEQ_MARK_01_DUP		=	569,

	/* Pulses high for one cycle for every frame dequeue produced containing
	 * a marked frame in a direct connect portal with debug mark code point
	 * 01 (duplicates 167) */
	DPDC_PE_QM_DCPx_FRAME_DEQ_MARK_10_DUP		=	570,

	/* Pulses high for one cycle for every frame dequeue produced containing
	 * a marked frame in a direct connect portal with debug mark code point
	 * 11 (duplicates 168) */
	DPDC_PE_QM_DCPx_FRAME_DEQ_MARK_11_DUP		=	571,

	/* Pulses high for one cycle for every marked frame that is enqueued
	 * after leaving an ORP with debug mark code point 01
	 * (duplicates 172). */
	DPDC_PE_QM_ORL_FRAME_ENQ_MARK_01_DUP		=	572,

	/* Pulses high for one cycle for every marked frame that is enqueued
	 * after leaving an ORP with debug mark code point 10
	 * (duplicates 173). */
	DPDC_PE_QM_ORL_FRAME_ENQ_MARK_10_DUP		=	573,

	/* Pulses high for one cycle for every marked frame that is enqueued
	 * after leaving an ORP with debug mark code point 11
	 * (duplicates 174). */
	DPDC_PE_QM_ORL_FRAME_ENQ_MARK_11_DUP		=	574,

	/*-------------- The 575 entry is tied to zero in DPDC ---------------*/


	/******************************************************************
	 *      DPDC Performance Event Word 18 (events 576 - 607)         *
	 *            QM DCP1 Performance Events (redundant)              *
	 ******************************************************************/

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP1 exceeds threshold A in DCP1 (duplicates 4). */
	DPDC_PE_QM_DCP1_DEQ_EXCEEDS_THRESHOLD_A_DUP	=	576,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP1 exceeds threshold B in DCP1 (duplicates 5). */
	DPDC_PE_QM_DCP1_DEQ_EXCEEDS_THRESHOLD_B_DUP	=	577,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP1 exceeds threshold C in DCP1 (duplicates 6). */
	DPDC_PE_QM_DCP1_DEQ_EXCEEDS_THRESHOLD_C_DUP	=	578,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP1 exceeds threshold D in DCP1 (duplicates 7). */
	DPDC_PE_QM_DCP1_DEQ_EXCEEDS_THRESHOLD_D_DUP	=	579,

	/*---------------- 580 - 583 entries are reserved. -------------------*/

	/* Pulse high for one cycle for every enqueue command received in
	 * DCP1 (duplicates 56) */
	DPDC_PE_QM_DCP1_ENQ_CMD_RECEIVED_DUP		=	584,

	/* Asserted whenever the enqueue command FIFO in a direct connect
	 * portal is full in DCP1 (duplicates 80). */
	DPDC_PE_QM_DCP1_ENQ_CMD_FIFO_FULL_DUP		=	585,

	/* Asserted whenever the dequeue command FIFO in DCP1 is full
	 * (duplicates 85). */
	DPDC_PE_QM_DCP1_DEQ_CMD_FIFO_FULL_DUP		=	586,

	/* Asserted whenever the dequeue response FIFO in DCP1 is full
	 * (duplicates 89). */
	DPDC_PE_QM_DCP1_DEQ_RSP_FIFO_FULL_DUP		=	587,

	/* Pulses high for one cycle for every enqueue sequence that is
	 * dispatched for DCP1. This number may be lower than the number of
	 * enqueue commands received, because enqueue commands can be
	 * dispatched up to 3 at a time when they target the same FQ
	 * (duplicates 103). */
	DPDC_PE_QM_DCP1_ENQ_SEQ_DISPATCH_DUP		=	588,

	/* Pulses high for one cycle for every enqueue sequence that is
	 * dispatched for DCP1 when the corresponding command FIFO is full
	 * (duplicates 108). */
	DPDC_PE_QM_DCP1_ENQ_SEQ_DISPATCH_FIFO_FULL_DUP	=	589,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 1 or more frames for DCP1 (duplicates 113). */
	DPDC_PE_QM_DCP1_DEQ_SEQ_DELIVERS_1_DUP		=	590,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 2 or more frames for DCP1 (duplicates 118). */
	DPDC_PE_QM_DCP1_DEQ_SEQ_DELIVERS_2_DUP		=	591,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 3 frames for DCP1 (duplicates 123). */
	DPDC_PE_QM_DCP1_DEQ_SEQ_DELIVERS_3_DUP		=	592,

	/* Pulses high for one cycle for every dequeue command dispatched when
	 * the dequeue command FIFO in DCP1 is full (duplicates 128). */
	DPDC_PE_QM_DCP1_DEQ_CMD_DISPATCH_FIFO_FULL_DUP	=	593,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * in DCP1 (duplicates 141). */
	DPDC_PE_QM_DCP1_FRAME_ENQ_REJECTED_DUP		=	594,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to WRED discard in DCP1 (duplicates 146). */
	DPDC_PE_QM_DCP1_FRAME_ENQ_WRED_REJECTED_DUP	=	595,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to tail drop configured in the FQ's congestion group in DCP1
	 * (duplicates 151). */
	DPDC_PE_QM_DCP1_FRAME_ENQ_TD_CONG_REJECTED_DUP	=	596,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to tail drop configured in the FQ itself in DCP1
	 * (duplicates 156). */
	DPDC_PE_QM_DCP1_FRAME_ENQ_TD_FQ_REJECTED_DUP	=	597,

	/* Pulses high for one cycle for every frame enqueue received from
	 * direct connect portal containing a marked frame in a direct connect
	 * portal with debug mark code point 01 (duplicates 160). */
	DPDC_PE_QM_DCPx_FRAME_ENQ_MARK_01_DUP2		=	598,

	/* Pulses high for one cycle for every frame enqueue received from
	 * direct connect portal containing a marked frame in a direct connect
	 * portal with debug mark code point 10 (duplicates 161). */
	DPDC_PE_QM_DCPx_FRAME_ENQ_MARK_10_DUP2		=	599,

	/* Pulses high for one cycle for every frame enqueue received from
	 * direct connect portal containing a marked frame in a direct connect
	 * portal with debug mark code point 11 (duplicates 162). */
	DPDC_PE_QM_DCPx_FRAME_ENQ_MARK_11_DUP2		=	600,

	/* Pulses high for one cycle for every frame dequeue produced containing
	 * a marked frame in a direct connect portal with debug mark code point
	 * 01 (duplicates 166) */
	DPDC_PE_QM_DCPx_FRAME_DEQ_MARK_01_DUP2		=	601,

	/* Pulses high for one cycle for every frame dequeue produced containing
	 * a marked frame in a direct connect portal with debug mark code point
	 * 10 (duplicates 167) */
	DPDC_PE_QM_DCPx_FRAME_DEQ_MARK_10_DUP2		=	602,

	/* Pulses high for one cycle for every frame dequeue produced containing
	 * a marked frame in a direct connect portal with debug mark code point
	 * 11 (duplicates 168) */
	DPDC_PE_QM_DCPx_FRAME_DEQ_MARK_11_DUP2		=	603,

	/* Pulses high for one cycle for every marked frame that is enqueued
	 * after leaving an ORP with debug mark code point 01
	 * (duplicates 172). */
	DPDC_PE_QM_ORL_FRAME_ENQ_MARK_01_DUP2		=	604,

	/* Pulses high for one cycle for every marked frame that is enqueued
	 * after leaving an ORP with debug mark code point 10
	 * (duplicates 173). */
	DPDC_PE_QM_ORL_FRAME_ENQ_MARK_10_DUP2		=	605,

	/* Pulses high for one cycle for every marked frame that is enqueued
	 * after leaving an ORP with debug mark code point 11
	 * (duplicates 174). */
	DPDC_PE_QM_ORL_FRAME_ENQ_MARK_11_DUP2		=	606,


	/*-------------- The 607 entry is tied to zero in DPDC ---------------*/

	/******************************************************************
	 *      DPDC Performance Event Word 19 (events 608 - 639)         *
	 *            QM DCP2 Performance Events (redundant)              *
	 ******************************************************************/

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP2 exceeds threshold A in DCP2 (duplicates 8). */
	DPDC_PE_QM_DCP2_DEQ_EXCEEDS_THRESHOLD_A_DUP	=	608,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP2 exceeds threshold B in DCP2 (duplicates 9). */
	DPDC_PE_QM_DCP2_DEQ_EXCEEDS_THRESHOLD_B_DUP	=	609,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP2 exceeds threshold C in DCP2 (duplicates 10). */
	DPDC_PE_QM_DCP2_DEQ_EXCEEDS_THRESHOLD_C_DUP	=	610,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP2 exceeds threshold D in DCP2 (duplicates 11). */
	DPDC_PE_QM_DCP2_DEQ_EXCEEDS_THRESHOLD_D_DUP	=	611,

	/*---------------- 612 - 615 entries are reserved. -------------------*/

	/* Pulse high for one cycle for every enqueue command received in
	 * DCP2 (duplicates 57) */
	DPDC_PE_QM_DCP2_ENQ_CMD_RECEIVED_DUP		=	616,

	/* Asserted whenever the enqueue command FIFO in a direct connect
	 * portal is full in DCP2 (duplicates 81). */
	DPDC_PE_QM_DCP2_ENQ_CMD_FIFO_FULL_DUP		=	617,

	/* Asserted whenever the dequeue command FIFO in DCP2 is full
	 * (duplicates 86). */
	DPDC_PE_QM_DCP2_DEQ_CMD_FIFO_FULL_DUP		=	618,

	/* Asserted whenever the dequeue response FIFO in DCP2 is full
	 * (duplicates 90). */
	DPDC_PE_QM_DCP2_DEQ_RSP_FIFO_FULL_DUP		=	619,

	/* Pulses high for one cycle for every enqueue sequence that is
	 * dispatched for DCP2. This number may be lower than the number of
	 * enqueue commands received, because enqueue commands can be
	 * dispatched up to 3 at a time when they target the same FQ
	 * (duplicates 104). */
	DPDC_PE_QM_DCP2_ENQ_SEQ_DISPATCH_DUP		=	620,

	/* Pulses high for one cycle for every enqueue sequence that is
	 * dispatched for DCP2 when the corresponding command FIFO is full
	 * (duplicates 109). */
	DPDC_PE_QM_DCP2_ENQ_SEQ_DISPATCH_FIFO_FULL_DUP	=	621,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 1 or more frames for DCP2 (duplicates 114). */
	DPDC_PE_QM_DCP2_DEQ_SEQ_DELIVERS_1_DUP		=	622,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 2 or more frames for DCP2 (duplicates 119). */
	DPDC_PE_QM_DCP2_DEQ_SEQ_DELIVERS_2_DUP		=	623,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 3 frames for DCP2 (duplicates 124). */
	DPDC_PE_QM_DCP2_DEQ_SEQ_DELIVERS_3_DUP		=	624,

	/* Pulses high for one cycle for every dequeue command dispatched when
	 * the dequeue command FIFO in DCP2 is full (duplicates 129). */
	DPDC_PE_QM_DCP2_DEQ_CMD_DISPATCH_FIFO_FULL_DUP	=	625,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * in DCP2 (duplicates 142). */
	DPDC_PE_QM_DCP2_FRAME_ENQ_REJECTED_DUP		=	626,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to WRED discard in DCP2 (duplicates 147). */
	DPDC_PE_QM_DCP2_FRAME_ENQ_WRED_REJECTED_DUP	=	627,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to tail drop configured in the FQ's congestion group in DCP2
	 * (duplicates 152). */
	DPDC_PE_QM_DCP2_FRAME_ENQ_TD_CONG_REJECTED_DUP	=	628,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to tail drop configured in the FQ itself in DCP2
	 * (duplicates 157). */
	DPDC_PE_QM_DCP2_FRAME_ENQ_TD_FQ_REJECTED_DUP	=	629,

	/* Pulses high for one cycle for every frame enqueue received from
	 * direct connect portal containing a marked frame in a direct connect
	 * portal with debug mark code point 01 (duplicates 160). */
	DPDC_PE_QM_DCPx_FRAME_ENQ_MARK_01_DUP3		=	630,

	/* Pulses high for one cycle for every frame enqueue received from
	 * direct connect portal containing a marked frame in a direct connect
	 * portal with debug mark code point 10 (duplicates 161). */
	DPDC_PE_QM_DCPx_FRAME_ENQ_MARK_10_DUP3		=	631,

	/* Pulses high for one cycle for every frame enqueue received from
	 * direct connect portal containing a marked frame in a direct connect
	 * portal with debug mark code point 11 (duplicates 162). */
	DPDC_PE_QM_DCPx_FRAME_ENQ_MARK_11_DUP3		=	632,

	/* Pulses high for one cycle for every frame dequeue produced containing
	 * a marked frame in a direct connect portal with debug mark code point
	 * 01 (duplicates 166) */
	DPDC_PE_QM_DCPx_FRAME_DEQ_MARK_01_DUP3		=	633,

	/* Pulses high for one cycle for every frame dequeue produced containing
	 * a marked frame in a direct connect portal with debug mark code point
	 * 10 (duplicates 167) */
	DPDC_PE_QM_DCPx_FRAME_DEQ_MARK_10_DUP3		=	634,

	/* Pulses high for one cycle for every frame dequeue produced containing
	 * a marked frame in a direct connect portal with debug mark code point
	 * 11 (duplicates 168) */
	DPDC_PE_QM_DCPx_FRAME_DEQ_MARK_11_DUP3		=	635,

	/* Pulses high for one cycle for every marked frame that is enqueued
	 * after leaving an ORP with debug mark code point 01
	 * (duplicates 172). */
	DPDC_PE_QM_ORL_FRAME_ENQ_MARK_01_DUP3		=	636,

	/* Pulses high for one cycle for every marked frame that is enqueued
	 * after leaving an ORP with debug mark code point 10
	 * (duplicates 173). */
	DPDC_PE_QM_ORL_FRAME_ENQ_MARK_10_DUP3		=	637,

	/* Pulses high for one cycle for every marked frame that is enqueued
	 * after leaving an ORP with debug mark code point 11
	 * (duplicates 174). */
	DPDC_PE_QM_ORL_FRAME_ENQ_MARK_11_DUP3		=	638,

	/*-------------- The 639 entry is tied to zero in DPDC ---------------*/

	/******************************************************************
	 *      DPDC Performance Event Word 20 (events 640 - 671)         *
	 *            QM DCP3 Performance Events (redundant)              *
	 ******************************************************************/

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP3 exceeds threshold A in DCP3 (duplicates 12). */
	DPDC_PE_QM_DCP3_DEQ_EXCEEDS_THRESHOLD_A_DUP	=	640,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP3 exceeds threshold B in DCP3 (duplicates 13). */
	DPDC_PE_QM_DCP3_DEQ_EXCEEDS_THRESHOLD_B_DUP	=	641,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP3 exceeds threshold C in DCP3 (duplicates 14). */
	DPDC_PE_QM_DCP3_DEQ_EXCEEDS_THRESHOLD_C_DUP	=	642,

	/* Pulses high for one cycle when the number of cycles to produce
	 * a response to a dequeue command received by QMAN on direct connect
	 * portal DCP3 exceeds threshold D in DCP3 (duplicates 15). */
	DPDC_PE_QM_DCP3_DEQ_EXCEEDS_THRESHOLD_D_DUP	=	643,

	/*---------------- 644 - 647 entries are reserved. -------------------*/

	/* Pulse high for one cycle for every enqueue command received in
	 * DCP3 (duplicates 58) */
	DPDC_PE_QM_DCP3_ENQ_CMD_RECEIVED_DUP		=	648,

	/* Asserted whenever the enqueue command FIFO in a direct connect
	 * portal is full in DCP3 (duplicates 82). */
	DPDC_PE_QM_DCP3_ENQ_CMD_FIFO_FULL_DUP		=	649,

	/* Asserted whenever the dequeue command FIFO in DCP3 is full
	 * (duplicates 87). */
	DPDC_PE_QM_DCP3_DEQ_CMD_FIFO_FULL_DUP		=	650,

	/* Asserted whenever the dequeue response FIFO in DCP3 is full
	 * (duplicates 91). */
	DPDC_PE_QM_DCP3_DEQ_RSP_FIFO_FULL_DUP		=	651,

	/* Pulses high for one cycle for every enqueue sequence that is
	 * dispatched for DCP3. This number may be lower than the number of
	 * enqueue commands received, because enqueue commands can be
	 * dispatched up to 3 at a time when they target the same FQ
	 * (duplicates 105). */
	DPDC_PE_QM_DCP3_ENQ_SEQ_DISPATCH_DUP		=	652,

	/* Pulses high for one cycle for every enqueue sequence that is
	 * dispatched for DCP3 when the corresponding command FIFO is full
	 * (duplicates 110). */
	DPDC_PE_QM_DCP3_ENQ_SEQ_DISPATCH_FIFO_FULL_DUP	=	653,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 1 or more frames for DCP3 (duplicates 115). */
	DPDC_PE_QM_DCP3_DEQ_SEQ_DELIVERS_1_DUP		=	654,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 2 or more frames for DCP3 (duplicates 120). */
	DPDC_PE_QM_DCP3_DEQ_SEQ_DELIVERS_2_DUP		=	655,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 3 frames for DCP3 (duplicates 125). */
	DPDC_PE_QM_DCP3_DEQ_SEQ_DELIVERS_3_DUP		=	656,

	/* Pulses high for one cycle for every dequeue command dispatched when
	 * the dequeue command FIFO in DCP3 is full (duplicates 130). */
	DPDC_PE_QM_DCP3_DEQ_CMD_DISPATCH_FIFO_FULL_DUP	=	657,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * in DCP3 (duplicates 143). */
	DPDC_PE_QM_DCP3_FRAME_ENQ_REJECTED_DUP		=	658,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to WRED discard in DCP3 (duplicates 148). */
	DPDC_PE_QM_DCP3_FRAME_ENQ_WRED_REJECTED_DUP	=	659,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to tail drop configured in the FQ's congestion group in DCP3
	 * (duplicates 153). */
	DPDC_PE_QM_DCP3_FRAME_ENQ_TD_CONG_REJECTED_DUP	=	660,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to tail drop configured in the FQ itself in DCP3
	 * (duplicates 158). */
	DPDC_PE_QM_DCP3_FRAME_ENQ_TD_FQ_REJECTED_DUP	=	661,

	/* Pulses high for one cycle for every frame enqueue received from
	 * direct connect portal containing a marked frame in a direct connect
	 * portal with debug mark code point 01 (duplicates 160). */
	DPDC_PE_QM_DCPx_FRAME_ENQ_MARK_01_DUP4		=	662,

	/* Pulses high for one cycle for every frame enqueue received from
	 * direct connect portal containing a marked frame in a direct connect
	 * portal with debug mark code point 10 (duplicates 161). */
	DPDC_PE_QM_DCPx_FRAME_ENQ_MARK_10_DUP4		=	663,

	/* Pulses high for one cycle for every frame enqueue received from
	 * direct connect portal containing a marked frame in a direct connect
	 * portal with debug mark code point 11 (duplicates 162). */
	DPDC_PE_QM_DCPx_FRAME_ENQ_MARK_11_DUP4		=	664,

	/* Pulses high for one cycle for every frame dequeue produced containing
	 * a marked frame in a direct connect portal with debug mark code point
	 * 01 (duplicates 166) */
	DPDC_PE_QM_DCPx_FRAME_DEQ_MARK_01_DUP4		=	665,

	/* Pulses high for one cycle for every frame dequeue produced containing
	 * a marked frame in a direct connect portal with debug mark code point
	 * 10 (duplicates 167) */
	DPDC_PE_QM_DCPx_FRAME_DEQ_MARK_10_DUP4		=	666,

	/* Pulses high for one cycle for every frame dequeue produced containing
	 * a marked frame in a direct connect portal with debug mark code point
	 * 11 (duplicates 168) */
	DPDC_PE_QM_DCPx_FRAME_DEQ_MARK_11_DUP4		=	667,

	/* Pulses high for one cycle for every marked frame that is enqueued
	 * after leaving an ORP with debug mark code point 01
	 * (duplicates 172). */
	DPDC_PE_QM_ORL_FRAME_ENQ_MARK_01_DUP4		=	668,

	/* Pulses high for one cycle for every marked frame that is enqueued
	 * after leaving an ORP with debug mark code point 10
	 * (duplicates 173). */
	DPDC_PE_QM_ORL_FRAME_ENQ_MARK_10_DUP4		=	669,

	/* Pulses high for one cycle for every marked frame that is enqueued
	 * after leaving an ORP with debug mark code point 11
	 * (duplicates 174). */
	DPDC_PE_QM_ORL_FRAME_ENQ_MARK_11_DUP4		=	670,

	/*-------------- The 671 entry is tied to zero in DPDC ---------------*/

	/******************************************************************
	 *      DPDC Performance Event Word 21 (events 672 - 703)         *
	 *          QM SP Performance Event Group 1 (redundant)           *
	 ******************************************************************/

	/*---------------- 672 - 675 entries are reserved. -------------------*/

	/* Asserted whenever the EQCR/CR command dispatch FIFO which services
	 * all software portals is full (duplicates 83). */
	DPDC_PE_QM_SPx_EQCR_CR_DISPATCH_FIFO_FULL_DUP	=	676,

	/* Pulses high for one cycle for every enqueue sequence that is
	 * dispatched for any software portal (Monitored at the output of the
	 * EQCR/CR dispatch FIFO) (duplicates 106). */
	DPDC_PE_QMAN_SPx_ENQ_SEQ_DISPATCHED_DUP		=	677,

	/* Pulses high for one cycle for every enqueue sequence that is
	 * dispatched for any software portal when the corresponding command
	 * FIFO is full (duplicates 111). */
	DPDC_PE_QM_SPx_ENQ_SEQ_DISPATCH_FIFO_FULL_DUP	=	678,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 1 or more frames for any software portal
	 * (duplicates 116). */
	 DPDC_PE_QM_SPx_DEQ_SEQ_DELIVERS_1_DUP		=	679,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 2 or more frames for any software portal
	 * (duplicates 121). */
	 DPDC_PE_QM_SPx_DEQ_SEQ_DELIVERS_2_DUP		=	680,

	/* Pulses high for one cycle for every dequeue sequence that completes
	 * and delivers 3 frames for any software portal
	 * (duplicates 126). */
	 DPDC_PE_QM_SPx_DEQ_SEQ_DELIVERS_3_DUP		=	681,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * in any software portal (duplicates 144). */
	DPDC_PE_QM_SPx_FRAME_ENQ_REJECTED_DUP		=	682,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to WRED discard in any software portal (duplicates 149). */
	DPDC_PE_QM_SPx_FRAME_ENQ_WRED_REJECTED_DUP	=	683,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to tail drop configured in the FQ's congestion group in any
	 * software portal (duplicates 154). */
	DPDC_PE_QM_SPx_FRAME_ENQ_TD_CONG_REJECTED_DUP	=	684,

	/* Pulses high for one cycle for every frame enqueue that is rejected
	 * due to tail drop configured in the FQ itself in any software portal
	 * (duplicates 159)*/
	DPDC_PE_QM_SPx_FRAME_ENQ_TD_FQ_REJECTED_DUP	=	685,

	/* Pulses high for one cycle for every frame enqueue received from
	 * software portal containing a marked frame in a direct connect portal
	 * with debug mark code point 01 (duplicates 163). */
	DPDC_PE_QM_SPx_FRAME_ENQ_MARK_01_DUP		=	686,

	/* Pulses high for one cycle for every frame enqueue received from
	 * software portal containing a marked frame in a direct connect portal
	 * with debug mark code point 10 (duplicates 164). */
	DPDC_PE_QM_SPx_FRAME_ENQ_MARK_10_DUP		=	687,

	/* Pulses high for one cycle for every frame enqueue received from
	 * software portal containing a marked frame in a direct connect portal
	 * with debug mark code point 11 (duplicates 165). */
	DPDC_PE_QM_SPx_FRAME_ENQ_MARK_11_DUP		=	688,

	/* Pulses high for one cycle for every frame dequeue produced containing
	 * a marked frame in a software portal with debug mark code point 01
	 * (duplicates 169). */
	DPDC_PE_QM_SPx_FRAME_DEQ_MARK_01_DUP		=	689,

	/* Pulses high for one cycle for every frame dequeue produced containing
	 * a marked frame in a software portal with debug mark code point 10
	 * (duplicates 170). */
	DPDC_PE_QM_SPx_FRAME_DEQ_MARK_10_DUP		=	690,

	/* Pulses high for one cycle for every frame dequeue produced containing
	 * a marked frame in a software portal with debug mark code point 11
	 * (duplicates 171). */
	DPDC_PE_QM_SPx_FRAME_DEQ_MARK_11_DUP		=	691,

	/* Pulses high for one cycle for every marked frame that is enqueued
	 * after leaving an ORP with debug mark code point 01
	 * (duplicates 172). */
	DPDC_PE_QM_ORL_FRAME_ENQ_MARK_01_DUP5		=	692,

	/* Pulses high for one cycle for every marked frame that is enqueued
	 * after leaving an ORP with debug mark code point 10
	 * (duplicates 173). */
	DPDC_PE_QM_ORL_FRAME_ENQ_MARK_10_DUP5		=	693,

	/* Pulses high for one cycle for every marked frame that is enqueued
	 * after leaving an ORP with debug mark code point 11
	 * (duplicates 174). */
	DPDC_PE_QM_ORL_FRAME_ENQ_MARK_11_DUP5		=	694,

	/*------------ 695 - 703 entries are tied to zero in DPDC ------------*/

	/******************************************************************
	 *      DPDC Performance Event Word 22 (events 704 - 735)         *
	 *        QM Common Performance Event Group (redundant)           *
	 ******************************************************************/

	/*---------------- 704 - 714 entries are reserved. -------------------*/

	/* Pulses high for one cycle when a PFDR prefetch is attempted and
	 * denied due to lack of prefetch catch box resources (duplicates 47).*/
	DPDC_PE_QM_PFDR_PREFETCH_DENIED_DUP		=	715,

	/* Pulses high for one cycle when a PFDR read is initiated for a PFDR
	 * which is in use in a FQ, and the read is not a prefetch
	 * (duplicates 48). */
	DPDC_PE_QM_USED_PFDR_NO_PREFETCH_READ_DUP	=	716,

	/* Pulses high for one cycle every time an SFDR allocation succeeds
	 * (duplicates 49). */
	DPDC_PE_QM_SFDR_ALLOCATION_SUCCEED_DUP		=	717,

	/* Pulses high for one cycle every time an SFDR allocation fails
	 * (duplicates 50). */
	DPDC_PE_QM_SFDR_ALLOCATION_FAILED_DUP		=	718,

	/* Pulses high for one cycle every time a write of a partially full
	 * PFDR occurs (duplicates 51). */
	DPDC_PE_QM_PARTIALLY_FULL_PFDR_WRITE_DUP	=	719,

	/* Pulses high for one cycle every time a FQ transitions to the Truly
	 * Scheduled state in a direct connect portal sequencer
	 * (duplicates 52). */
	DPDC_PE_QM_FQ_TRULY_SCHEDULED_DCPx_DUP		=	720,

	/* Pulses high for one cycle every time a FQ transitions to the Truly
	 * Scheduled state in a software portal sequencer (duplicates 53). */
	DPDC_PE_QM_FQ_TRULY_SCHEDULED_SPx_DUP		=	721,

	/* Pulses high for one cycle every time a FQ transitions to the
	 * Truly Scheduled state in a reschedule sequencer (duplicates 54). */
	DPDC_PE_QM_FQ_TRULY_SCHEDULED_RESCH_DUP		=	722,

	/* Pulses high for one cycle for every frame that is not next in
	 * sequence and is placed in an order restoration list (ORL)
	 * (duplicates 131). */
	DPDC_PE_QM_FRAME_IN_ORL_DUP			=	723,

	/* Pulses high for one cycle for every frame that is placed in an order
	 * restoration list and causes an auto advance of an ORP window
	 * (duplicates 132). */
	DPDC_PE_QM_FRAME_IN_ORL_ORP_ADVANCE_DUP		=	724,

	/* Pulses high for one cycle for every frame that is rejected as a late
	 * arrival at an ORP (duplicates 133). */
	DPDC_PE_QM_REJECTED_LATE_FRAME_DUP		=	725,

	/* Pulses high for one cycle for every frame that is accepted and falls
	 * in the acceptable late arrival window at an ORP (duplicates 134). */
	DPDC_PE_QM_ACCEPCTED_LATE_FRAME_DUP		=	726,

	/* Pulses high for one cycle for every frame that is rejected as an
	 * early arrival at an ORP, for example, falls in the early arrival
	 * rejection window (duplicates 135). */
	 DPDC_PE_QM_REJECTED_EARLY_FRAME_DUP		=	727,

	/*---------------- 728 - 731 entries are reserved. -------------------*/

	/*------------ 732 - 735 entries are tied to zero in DPDC ------------*/

	/******************************************************************
	 *      DPDC Performance Event Word 23 (events 736 - 767)         *
	 *          QM SP Performance Event Group 2 (redundant)           *
	 ******************************************************************/

	/* Pulse high for one cycle for every enqueue command received in SP0
	 * (duplicates 59) */
	DPDC_PE_QM_SP0_ENQ_CMD_RECEIVED_DUP		=	736,

	/* Pulse high for one cycle for every enqueue command received in SP1
	 * (duplicates 60) */
	DPDC_PE_QM_SP1_ENQ_CMD_RECEIVED_DUP		=	737,

	/* Pulse high for one cycle for every enqueue command received in SP2
	 * (duplicates 61) */
	DPDC_PE_QM_SP2_ENQ_CMD_RECEIVED_DUP		=	738,

	/* Pulse high for one cycle for every enqueue command received in SP3
	 * (duplicates 62) */
	DPDC_PE_QM_SP3_ENQ_CMD_RECEIVED_DUP		=	739,

	/* Pulse high for one cycle for every enqueue command received in SP4
	 * (duplicates 63) */
	DPDC_PE_QM_SP4_ENQ_CMD_RECEIVED_DUP		=	740,

	/* Pulse high for one cycle for every enqueue command received in SP5
	 * (duplicates 64) */
	DPDC_PE_QM_SP5_ENQ_CMD_RECEIVED_DUP		=	741,

	/* Pulse high for one cycle for every enqueue command received in SP6
	 * (duplicates 65) */
	DPDC_PE_QM_SP6_ENQ_CMD_RECEIVED_DUP		=	742,

	/* Pulse high for one cycle for every enqueue command received in SP7
	 * (duplicates 66) */
	DPDC_PE_QM_SP7_ENQ_CMD_RECEIVED_DUP		=	743,

	/* Pulse high for one cycle for every enqueue command received in SP8
	 * (duplicates 67) */
	DPDC_PE_QM_SP8_ENQ_CMD_RECEIVED_DUP		=	744,

	/* Pulse high for one cycle for every enqueue command received in SP9
	 * (duplicates 68) */
	DPDC_PE_QM_SP9_ENQ_CMD_RECEIVED_DUP		=	745,

	/* Pulses high for one cycle for every enqueue command pulled from the
	 * EQCR ring when that ring is full in SP0 (duplicates 69). */
	DPDC_PE_QM_SP0_ENQ_CMD_PULLED_EQCR_FULL_DUP	=	746,

	/* Pulses high for one cycle for every enqueue command pulled from the
	 * EQCR ring when that ring is full in SP1 (duplicates 70). */
	DPDC_PE_QM_SP1_ENQ_CMD_PULLED_EQCR_FULL_DUP	=	747,

	/* Pulses high for one cycle for every enqueue command pulled from the
	 * EQCR ring when that ring is full in SP2 (duplicates 71). */
	DPDC_PE_QM_SP2_ENQ_CMD_PULLED_EQCR_FULL_DUP	=	748,

	/* Pulses high for one cycle for every enqueue command pulled from the
	 * EQCR ring when that ring is full in SP3 (duplicates 72). */
	DPDC_PE_QM_SP3_ENQ_CMD_PULLED_EQCR_FULL_DUP	=	749,

	/* Pulses high for one cycle for every enqueue command pulled from the
	 * EQCR ring when that ring is full in SP4 (duplicates 73). */
	DPDC_PE_QM_SP4_ENQ_CMD_PULLED_EQCR_FULL_DUP	=	750,

	/* Pulses high for one cycle for every enqueue command pulled from the
	 * EQCR ring when that ring is full in SP5 (duplicates 74). */
	DPDC_PE_QM_SP5_ENQ_CMD_PULLED_EQCR_FULL_DUP	=	751,

	/* Pulses high for one cycle for every enqueue command pulled from the
	 * EQCR ring when that ring is full in SP6 (duplicates 75). */
	DPDC_PE_QM_SP6_ENQ_CMD_PULLED_EQCR_FULL_DUP	=	752,

	/* Pulses high for one cycle for every enqueue command pulled from the
	 * EQCR ring when that ring is full in SP7 (duplicates 76). */
	DPDC_PE_QM_SP7_ENQ_CMD_PULLED_EQCR_FULL_DUP	=	753,

	/* Pulses high for one cycle for every enqueue command pulled from the
	 * EQCR ring when that ring is full in SP8 (duplicates 77). */
	DPDC_PE_QM_SP8_ENQ_CMD_PULLED_EQCR_FULL_DUP	=	754,

	/* Pulses high for one cycle for every enqueue command pulled from the
	 * EQCR ring when that ring is full in SP9 (duplicates 78). */
	DPDC_PE_QM_SP9_ENQ_CMD_PULLED_EQCR_FULL_DUP	=	755,

	/* Asserted whenever a dequeue command is valid and ready to be
	 * dispatched from a software portal 0, but cannot proceed due to
	 * lack of space in the DQRR ring (duplicates 92). */
	DPDC_PE_QM_SP0_DEQ_CMD_READY_DQRR_FULL_DUP	=	756,

	/* Asserted whenever a dequeue command is valid and ready to be
	 * dispatched from a software portal 1, but cannot proceed due to
	 * lack of space in the DQRR ring (duplicates 93). */
	DPDC_PE_QM_SP1_DEQ_CMD_READY_DQRR_FULL_DUP	=	757,

	/* Asserted whenever a dequeue command is valid and ready to be
	 * dispatched from a software portal 2, but cannot proceed due to
	 * lack of space in the DQRR ring (duplicates 94). */
	DPDC_PE_QM_SP2_DEQ_CMD_READY_DQRR_FULL_DUP	=	758,

	/* Asserted whenever a dequeue command is valid and ready to be
	 * dispatched from a software portal 3, but cannot proceed due to
	 * lack of space in the DQRR ring (duplicates 95). */
	DPDC_PE_QM_SP3_DEQ_CMD_READY_DQRR_FULL_DUP	=	759,

	/* Asserted whenever a dequeue command is valid and ready to be
	 * dispatched from a software portal 4, but cannot proceed due to
	 * lack of space in the DQRR ring (duplicates 96). */
	DPDC_PE_QM_SP4_DEQ_CMD_READY_DQRR_FULL_DUP	=	760,

	/* Asserted whenever a dequeue command is valid and ready to be
	 * dispatched from a software portal 5, but cannot proceed due to
	 * lack of space in the DQRR ring (duplicates 97). */
	DPDC_PE_QM_SP5_DEQ_CMD_READY_DQRR_FULL_DUP	=	761,

	/* Asserted whenever a dequeue command is valid and ready to be
	 * dispatched from a software portal 6, but cannot proceed due to
	 * lack of space in the DQRR ring (duplicates 98). */
	DPDC_PE_QM_SP6_DEQ_CMD_READY_DQRR_FULL_DUP	=	762,

	/* Asserted whenever a dequeue command is valid and ready to be
	 * dispatched from a software portal 7, but cannot proceed due to
	 * lack of space in the DQRR ring (duplicates 99). */
	DPDC_PE_QM_SP7_DEQ_CMD_READY_DQRR_FULL_DUP	=	763,

	/* Asserted whenever a dequeue command is valid and ready to be
	 * dispatched from a software portal 8, but cannot proceed due to
	 * lack of space in the DQRR ring (duplicates 100). */
	DPDC_PE_QM_SP8_DEQ_CMD_READY_DQRR_FULL_DUP	=	764,

	/* Asserted whenever a dequeue command is valid and ready to be
	 * dispatched from a software portal 9, but cannot proceed due to
	 * lack of space in the DQRR ring (duplicates 101). */
	DPDC_PE_QM_SP9_DEQ_CMD_READY_DQRR_FULL_DUP	=	765

	/*------------ 766 - 767 entries are tied to zero in DPDC ------------*/
};

#endif  /* DCSR_DPAA_V1_H */
