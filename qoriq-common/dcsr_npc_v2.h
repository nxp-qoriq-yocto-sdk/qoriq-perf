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

#ifndef DCSR_NPC_V2_H
#define DCSR_NPC_V2_H

#include "common.h"

#define NPC_STRUCT_SIZE		0x1000

#define NPC_NUM_MMA_UNITS	3
#define NUM_STCR_REGISTERS 	4
#define NUM_MSG_TYPE_FILTERS	4
#define NUM_SOURCE_FILTERS 	4
#define NUM_WATERMARK_REGISTERS	4

struct npc_mma {
	u32 mcsr;	/* MMA Control/Status Register n */
	u32 mmarlo;	/* MMA Address Register Low n */
	u32 mmarhi;	/* MMA Address Register High n */
	u32 mmdr;	/* MMA Data Register n */
} PACKED;

/* structure defines the memory map of the C-NPC control block */
struct npc_v2 {
	u32 ncr; 	/* NPC Control Register */
	u32 nst;	/* NPC Status Register */
	u32 tbsr;	/* Trace Buffer Status Register */
	u32 oqcr;	/* Output Queue Control Register */
	u32 tscr;	/* Time Stamp Control Register */
	u32 fcr;	/* Filter Control Register */
	u32 sfr[NUM_SOURCE_FILTERS]; /* Source Filter Register */
	u8 reserved1[0x38-0x28];
	u32 mtfr[NUM_MSG_TYPE_FILTERS]; /* Message Type Filter Register */
	u8 reserved2[0x58-0x48];
	u32 cdr;	/* Client Disable Register */
	u32 cdsr;	/* Client Disable Status Register */
	u32 cscr;	/* Client Stall Control Register */
	u32 cssr;	/* Client Suppress Status */
	u32 stcr[NUM_STCR_REGISTERS]; /* Suppress Trigger Control Register n */
	u8 reserved3[0x80-0x78];
	u32 mbalo;	/* Memory Base Address low */
	u32 mbahi;	/* Memory Base Address high */
	u32 mcr;	/* Memory Port Control Register */
	u32 mpxfr;	/* Memory Port Transfer Count Register */
	u32 apbalo;	/* AXI Port Base Address low */
	u32 apbahi;	/* AXI Port Base Address high */
	u32 apcr;	/* AXI Port Control Register */
	u32 apxfr;	/* AXI Port Transfer Count Register */
	u32 wmkr[NUM_WATERMARK_REGISTERS]; /* Target Space Water Mark Register n */
	u8 reserved4[0xcc-0xb0];
	u32 mccr;	/* tMMA Counter Control Register */
	struct npc_mma mma[NPC_NUM_MMA_UNITS];\
	u8 reserved5[0x1000-0x100];
} PACKED;
CTASSERT(sizeof(struct npc_v2) == NPC_STRUCT_SIZE);

/* structure defines the memory map of the S-NPC control block */
struct snpc_v2 {
	u32 ncr; 	/* NPC Control Register */
	u32 nst;	/* NPC Status Register */
	u32 tbsr;	/* Trace Buffer Status Register */
	u32 oqcr;	/* Output Queue Control Register */
	u32 tscr;	/* Time Stamp Control Register */
	u32 fcr;	/* Filter Control Register */
	u32 sfr[NUM_SOURCE_FILTERS]; /* Source Filter Register */
	u8 reserved1[0x38-0x28];
	u32 mtfr[NUM_MSG_TYPE_FILTERS]; /* Message Type Filter Register */
	u8 reserved2[0x58-0x48];
	u32 cdr;	/* Client Disable Register */
	u32 cdsr;	/* Client Disable Status Register */
	u32 cscr;	/* Client Stall Control Register */
	u32 cssr;	/* Client Suppress Status */
	u32 stcr[NUM_STCR_REGISTERS]; /* Suppress Trigger Control Register n */
	u8 reserved3[0xa0-0x78];
	u32 wmkr[NUM_WATERMARK_REGISTERS]; /* Target Space Water Mark Register n */
	u8 reserved4[0x1000-0xb0];

} PACKED;
CTASSERT(sizeof(struct snpc_v2) == NPC_STRUCT_SIZE);

#endif  /* DCSR_NPC_V2_H */
