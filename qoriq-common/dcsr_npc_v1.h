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

#ifndef DCSR_NPC_V1_H
#define DCSR_NPC_V1_H

#include "common.h"

/* size of npc struct */
#define NPC_STRUCT_SIZE		0x1000

/* structure defines the memory map of the NPC control block */
struct npc_v1 {
	u32 ncr;		/* NPC Control Register */
	u32 nst;		/* NPC Status Register */
	u32 sfr;		/* Source Filter Register */
	u32 mtfr;		/* Message Type Filter Register */
	u32 mbalo;		/* Memory Bus Base Address low */
	u32 mbahi;		/* Memory Bus Base Address high */
	u32 mcr;		/* Memory Bus Control Register */
	u32 stcr1;		/* Suppress Trigger Control Register 1 */
	u32 stcr2;		/* Suppress Trigger Control Register 2 */
	u32 stcr3;		/* Suppress Trigger Control Register 3 */
	u32 stcr4;		/* Suppress Trigger Control Register 4 */
	u32 cssr;		/* Client Suppress Status */
	u32 cdr;		/* Client Disable Register */
	u32 reserved1;
	u32 reserved2;
	u32 mcsr1;		/* MMA Control/Status Register 1 */
	u32 mmar1lo;		/* MMA Address Register Low 1 */
	u32 mmar1hi;		/* MMA Address Register High 1 */
	u32 mmdr1;		/* MMA Data Register 1 */
	u32 mcsr2;		/* MMA Control/Status Register 2 */
	u32 mmar2lo;		/* MMA Address Register Low 2 */
	u32 mmar2hi;		/* MMA Address Register High 2 */
	u32 mmdr2;		/* MMA Data Register 2 */
	u32 mcsr3;		/* MMA Control/Status Register 3 */
	u32 mmar3lo;		/* MMA Address Register Low 3 */
	u32 mmar3hi;		/* MMA Address Register High 3 */
	u32 mmdr3;		/* MMA Data Register 3 */
	u32 reserved3[0x03E5];
} PACKED;
CTASSERT(sizeof(struct npc_v1) == NPC_STRUCT_SIZE);

/* NCR */
#define NPC_NCR_NEN_MASK	0x80000000
#define NPC_NCR_NEN_SHIFT	31
#define NPC_NCR_NCD_MASK	0x40000000
#define NPC_NCR_NCD_SHIFT	30
#define NPC_NCR_TEN_MASK	0x20000000
#define NPC_NCR_TEN_SHIFT	29
#define NPC_NCR_TRS_MASK	0x10000000
#define NPC_NCR_TRS_SHIFT	28
#define NPC_NCR_TSG_MASK	0x0C000000
#define NPC_NCR_TSG_SHIFT	26
#define NPC_NCR_SED_MASK	0x02000000
#define NPC_NCR_SED_SHIFT	25
#define NPC_NCR_SRD_MASK	0x01000000
#define NPC_NCR_SRD_SHIFT	24
#define NPC_NCR_TBW_MASK	0x00800000
#define NPC_NCR_TBW_SHIFT	23
#define NPC_NCR_AQP_MASK	0x00600000
#define NPC_NCR_AQP_SHIFT	21
#define NPC_NCR_EOE_MASK	0x00100000
#define NPC_NCR_EOE_SHIFT	20
#define NPC_NCR_WPE_MASK	0x0000E000
#define NPC_NCR_WPE_SHIFT	13
#define NPC_NCR_MSP_MASK	0x00000600
#define NPC_NCR_MSP_SHIFT	9
#define NPC_NCR_ALT_MASK	0x000000C0
#define NPC_NCR_ALT_SHIFT	6
#define NPC_NCR_ATF_MASK	0x00000020
#define NPC_NCR_ATF_SHIFT	5
#define NPC_NCR_AFA_MASK	0x00000010
#define NPC_NCR_AFA_SHIFT	4
#define NPC_NCR_MTF_MASK	0x00000008
#define NPC_NCR_MTF_SHIFT	3
#define NPC_NCR_FSD_MASK	0x00000004
#define NPC_NCR_FSD_SHIFT	2
#define NPC_NCR_PUS_MASK	0x00000002
#define NPC_NCR_PUS_SHIFT	1
#define NPC_NCR_NSR_MASK	0x00000001
#define NPC_NCR_NSR_SHIFT	0

/* NST */
#define NPC_NST_NEN_MASK	0x80000000
#define NPC_NST_NEN_SHIFT	31
#define NPC_NST_NUM_MASK	0x70000000
#define NPC_NST_NUM_SHIFT	28
#define NPC_NST_NCE_MASK	0x0F000000
#define NPC_NST_NCE_SHIFT	24
#define NPC_NST_MPF_MASK	0x00800000
#define NPC_NST_MPF_SHIFT	23
#define NPC_NST_MLV_MASK	0x00600000
#define NPC_NST_MLV_SHIFT	21
#define NPC_NST_APF_MASK	0x00100000
#define NPC_NST_APF_SHIFT	20
#define NPC_NST_ALV_MASK	0x000C0000
#define NPC_NST_ALV_SHIFT	18
#define NPC_NST_HPR_MASK	0x00008000
#define NPC_NST_HPR_SHIFT	15
#define NPC_NST_HPE_MASK	0x00004000
#define NPC_NST_HPE_SHIFT	14
#define NPC_NST_MPE_MASK	0x00002000
#define NPC_NST_MPE_SHIFT	13
#define NPC_NST_MOV_MASK	0x00001000
#define NPC_NST_MOV_SHIFT	12
#define NPC_NST_TOV_MASK	0x00000400
#define NPC_NST_TOV_SHIFT	10
#define NPC_NST_QWA_MASK	0x000003FF
#define NPC_NST_QWA_SHIFT	0

/* STRCn */
#define NPC_STCRn_GST_MASK	0x80000000
#define NPC_STCRn_GST_SHIFT	31

#endif  /* DCSR_NPC_V1_H */
