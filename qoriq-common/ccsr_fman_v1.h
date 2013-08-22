/*
 * Copyright (C) 2010, 2011 Freescale Semiconductor, Inc.
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

#ifndef CCSR_FMAN_V1_H
#define CCSR_FMAN_V1_H

#include "common.h"

/* FMAN Constants */
#define FMAN_NUM_DEBUG_FLOWS	3
#define FMAN_NUM_DEBUG_TRAPS	4
#define FMAN_NUM_DEBUG_EVENT_TRAPS	5
/* Number of 32bit registers to represent 128bit FD value */
#define FMAN_NUM_REGS_PER_FRAME		4

#define FMAN_NUM_OH_PORTS	7
#define FMAN_NUM_RX_PORTS	10
#define FMAN_NUM_TX_PORTS	FMAN_NUM_RX_PORTS

/* Fman QMI debug trap */
struct fman_qmi_debug_trap {
	/* FMQM_DTCA1 Debug Trap Configuration A1 Register */
	u32 cfg1;
	/* FMQM_DTVA1 Debug Trap Value A1 Register */
	u32 val1;
	/* FMQM_DTMA1—Debug Trap Mask A1 Register */
	u32 mask1;
	/* FMQM_DTCA—Debug Trap Counter A Register */
	u32 cnt;
	/* FMQM_DTCA2 Debug Trap Configuration A2 Register */
	u32 cfg2;
	/* FMQM_DTVA2 Debug Trap Value A2 Register */
	u32 val2;
	/* FMQM_DTMA2—Debug Trap Mask A2 Register */
	u32 mask2;
	u8 reserved1[0x4];
} PACKED;

/* Fman common registers */
struct fman_common {
	/* BMI registers common for all ports */
	u8 reserved0[0x90];
	/* FMBM Debug Trap Counters */
	u32 fmbm_dtc[FMAN_NUM_DEBUG_FLOWS];
	u32 reserved1;
	/* FMBM Debug Compare Value */
	u32 fmbm_dcv[FMAN_NUM_DEBUG_FLOWS][FMAN_NUM_REGS_PER_FRAME];
	/* FMBM Debug Compare Mask */
	u32 fmbm_dcm[FMAN_NUM_DEBUG_FLOWS][FMAN_NUM_REGS_PER_FRAME];
	/* FMBM_GDE Global Debug Enable */
	u32 fmbm_gde;
	u8 reserved2[0x2FC];

	/* QMI registers common for all ports */
	/* General Configuration Register */
	u32 fmqm_gc;
	u8 reserved3[0x28 - 0x04];
	/* Enqueue Total Frame Counter */
	u32 fmqm_etfc;
	/* Dequeue Total Frame Counter */
	u32 fmqm_dtfc;
	/* Dequeue Counter 0 */
	u32 fmqm_dc0;
	/* Dequeue Counter 1 */
	u32 fmqm_dc1;
	/* Dequeue Counter 2 */
	u32 fmqm_dc2;
	/* Dequeue Counter 3 */
	u32 fmqm_dc3;
	u8 reserved4[0x80 - 0x40];
	/* FMQM_DTRC Debug Trace Configuration Register */
	u32 fmqm_dtrc;
	/* FMQM_EFDDD Enqueue Frame Descriptor Dynamic Debug */
	u32 fmqm_efddd;
	u8 reserved5[8];

	/* Fman QMI debug trap */
	struct fman_qmi_debug_trap fmqm_dt[FMAN_NUM_DEBUG_FLOWS];

	u8 reserved6[0x310];
	u8 reserved7[0x800];
} PACKED;
CTASSERT(sizeof(struct fman_common) == 0x1000);

/* Fman Rx port */
struct fman_rx {
	/* BMI registers */
	u8 reserved1[0x300];
	/* FMBM_RDCFG Rx Debug Configuration Flow A */
	u32 fmbm_rdcfg_a;
	/* FMBM_RDCFG Rx Debug Configuration Flow B */
	u32 fmbm_rdcfg_b;
	/* FMBM_RDCFG Rx Debug Configuration Flow C */
	u32 fmbm_rdcfg_c;
	u8 reserved2[0xF4];

	/* QMI registers */
	u8 reserved3[0x400];

	/* reserved */
	u8 reserved4[0x800];
} PACKED;
CTASSERT(sizeof(struct fman_rx) == 0x1000);

/* Fman Tx port */
struct fman_tx {
	/* BMI registers */
	u8 reserved1[0x300];
	/* FMBM_TDCFG Tx Debug Configuration Flow A */
	u32 fmbm_tdcfg_a;
	/* FMBM_TDCFG Tx Debug Configuration Flow B */
	u32 fmbm_tdcfg_b;
	/* FMBM_TDCFG Tx Debug Configuration Flow C */
	u32 fmbm_tdcfg_c;
	u8 reserved2[0xF4];
	/* QMI registers */
	u8 reserved3[0x400];
	u8 reserved4[0x800];
} PACKED;
CTASSERT(sizeof(struct fman_tx) == 0x1000);

/* Fman O/H port (Offline Parsing/Host Command) */
struct fman_oh {
	u8 reserved1[0x300];
	/* FMBM_ODCFG O/H Debug Configuration Flow A */
	u32 fmbm_odcfg_a;
	/* FMBM_ODCFG O/H Debug Configuration Flow B */
	u32 fmbm_odcfg_b;
	/* FMBM_ODCFG O/H Debug Configuration Flow C */
	u32 fmbm_odcfg_c;
	u8 reserved2[0xF4];
	u8 reserved3[0x400];
	u8 reserved4[0x800];
} PACKED;
CTASSERT(sizeof(struct fman_oh) == 0x1000);

/* Fman Rx and Tx ports */
struct fmports {
	/* BMI Common Registers */
	struct fman_common common_reg;
	/* (Offline Parsing/Host Command) Port Registers */
	struct fman_oh ophc[FMAN_NUM_OH_PORTS];
	/* Rx ports */
	struct fman_rx rx[FMAN_NUM_RX_PORTS];
	u8 reserved2[0x16000];
	/* Tx ports */
	struct fman_tx tx[FMAN_NUM_TX_PORTS];
	u8 reserved4[0xE000];
} PACKED;
CTASSERT(sizeof(struct fmports) == 0x40000);

/* Fman policer debug trap */
struct fman_policer_debug_trap {
	/* FMan Policer Flow N Debug Trap Configuration Register 0 */
	u32 dbtcr0;
	/* FMan Policer Flow N Debug Trap Value Register 0 */
	u32 dbvalr0;
	/* FMan Policer Flow N Debug Trap Mask Register 0 */
	u32 dbtmr0;
	/* FMan Policer Flow N Debug Trap Match Counter */
	u32 dbtmc;
	/* FMan Policer Flow N Debug Trap Configuration Register 1 */
	u32 dbtcr1;
	/* FMan Policer Flow N Debug Trap Value Register 1 */
	u32 dbvalr1;
	/* FMan Policer Flow N Debug Trap Mask Register 1 */
	u32 dbtmr1;
	u8 reserved1[0x4];
} PACKED;

/* FMan policer */
struct fmpl {
	u8 reserved1[0x10C];
	/* FMan Policer Debug Trace Configuration Register */
	u32 dtrcr;
	/* Fman policer Flow Debug Trap A,B,C */
	struct fman_policer_debug_trap dt[FMAN_NUM_DEBUG_FLOWS];
	u8 reserved2[0xE90];
} PACKED;
CTASSERT(sizeof(struct fmpl) == 0x1000);

/* FMan key generator  Flow Trap Configuration, Value and Mask*/
struct fmkg_flowtrap {
	/* Configuration Register*/
	u32 cr;
	/* Value Register*/
	u32 vr;
	/* Mask Register*/
	u32 mr;
	u8 reserved1[0x4];
} PACKED;

/* FMan key generator  */
struct fmkg {
	u8 reserved1[0x28];
	/* KeyGen Total Packet Counter */
	u32 tpc;
	/* KeyGen Soft Error Capture */
	u32 serc;
	u8 reserved2[0x1d0];
	/* KeyGen Debug Control Register */
	u32 dcr;
	/* KeyGen Debug J Trap Counter */
	u32 dJtc[FMAN_NUM_DEBUG_FLOWS];
	/* KeyGen Debug Flow J Trap K Configuration Register  */
	struct fmkg_flowtrap dJtK[FMAN_NUM_DEBUG_FLOWS][FMAN_NUM_DEBUG_EVENT_TRAPS];
	u8 reserved3[0xd00];
} PACKED;
CTASSERT(sizeof(struct fmkg) == 0x1000);

/* Frame Processing Manager */
struct fpm {
	u8 reserved1[0x60];
	/* Timestamp control 1 */
	u32 tsc1;
	/* Timestamp control 2 */
	u32 tsc2;
	/* Timestamp */
	u32 tsp;
	/* Timestamp fraction*/
	u32 tsf;
	u8 reserved2[0xC4 - 0x70];
	/* IP block rev 1 */
	u32 ip_rev1;
	/* IP block rev 2 */
	u32 ip_rev2;
	u8 reserved3[0xD0 - 0xCC];
	/* FMFP_CLDC FMan Classifier Debug Control */
	u32 cldc;
	u8 reserved4[0x12C];
	/* FMFP_CLFABC FMan Classifier Flow AB Control */
	u32 clfabc;
	/* FMFP_CLFCC FMan Classifier Flow C Control */
	u32 clfcc;
	/* FMFP_CLFAVAL—FMan Controller Flow A Value */
	u32 clfaval;
	/* FMFP_CLFBVAL—FMan Controller Flow B Value */
	u32 clfbval;
	/* FMFP_CLFCVAL—FMan Controller Flow C Value */
	u32 clfcval;
	/* FMFP_CLFAMSK—FMan Controller Flow A Mask */
	u32 clfamsk;
	/* FMFP_CLFBMSK—FMan Controller Flow B Mask */
	u32 clfbmsk;
	/* FMFP_CLFCMSK—FMan Controller Flow C Mask */
	u32 clfcmsk;
	/* FMFP_CLFAMC—FMan Controller Flow A Match Count */
	u32 clfamc;
	/* FMFP_CLFBMC—FMan Controller Flow B Match Count */
	u32 clfbmc;
	/* FMFP_CLFCMC—FMan Controller Flow C Match Count */
	u32 clfcmc;
	u8 reserved5[0xDD4];
} PACKED;
CTASSERT(sizeof(struct fpm) == 0x1000);

/* FMan parser Debug flow Configuration, value and mask registers */
struct fmpr_debug_flow_trap {
	/* FMPR_PDxTnC Parser Debug Flow x Trap n Configuration Register */
	u32 fmpr_pdtc;
	/* FMPR_PDxTnV Parser Debug Flow x Trap n Value Register */
	u32 fmpr_pdtv;
	/* FMPR_PDxTnM Parser Debug Flow x Trap n Mask Register */
	u32 fmpr_pdtm;
};
/* FMan parser */
struct fmpr {
	u8 reserved1[0x8ec];
	/* FMPR_PDxTES Parser Debug Flow x Trap event Statistic Register */
	u32 fmpr_pdtes[FMAN_NUM_DEBUG_FLOWS];
	u8 reserved2[0x8];
	/* FMPR_PDC Parser Debug Control Register */
	u32 fmpr_pdc;
	/* FMPR_PDxTn[CVM] Parser Debug Flow x Trap n Registers */
	struct fmpr_debug_flow_trap
		debug_flow_trap[FMAN_NUM_DEBUG_FLOWS][FMAN_NUM_DEBUG_TRAPS];
	u8 reserved3[0x66c];
} PACKED;
CTASSERT(sizeof(struct fmpr) == 0x1000);

/* Memory mapping for FMan */
struct fman {
	u8 reserved1[0x80000];
	/* BMI, QMI, Parser */
	struct fmports ports;
	/* FMan Policer */
	struct fmpl policer;
	/* FMan Key Generator */
	struct fmkg key_gen;
	u8 reserved2[0x1000];
	/* FMan Frame Processing Manager */
	struct fpm fpm;
	u8 reserved3[0x3000];
	/* FMan Parser */
	struct fmpr parser;
	u8 reserved4[0x38000];
} PACKED;
CTASSERT(sizeof(struct fman) == 0x00100000);

#endif /* CCSR_FMAN_V1_H */
