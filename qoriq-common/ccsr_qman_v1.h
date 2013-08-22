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

#ifndef CCSR_QMAN_V1_H
#define CCSR_QMAN_V1_H

#include "common.h"

/* number of software portals */
#define QMAN_SOFT_PORTALS	10
/* number of direct connect portals */
#define QMAN_DIRECT_PORTALS	5
/* Number of Work Queue S/W Debug Configuration Registers */
#define QMAN_NUM_WQ_SW_DD_CFG_REGS	QMAN_SOFT_PORTALS/2
/* Number of Work Queue Pool Debug Configuration Registers */
#define QMAN_NUM_WQ_POOL_DD_CFG_REGS	8
/* Number of Work Queue Direct Connect[n] Debug Configuration Registers */
#define QMAN_NUM_WQ_DC0_DD_CFG_REGS	6
#define QMAN_NUM_WQ_DC1_DD_CFG_REGS	6
#define QMAN_NUM_WQ_DC2_DD_CFG_REGS	1
#define QMAN_NUM_WQ_DC3_DD_CFG_REGS	1
#define QMAN_NUM_WQ_DC4_DD_CFG_REGS	1

/* QMan Software Portal Configuration */
struct qman_soft_portal_config {
	/* QMan Software Portal LIO Configuration */
	u32 lio_cfg;
	/* QMan Software Portal IO Configuration */
	u32 io_cfg;
	/* reserved */
	u32 reserved;
	/* Software Portal Dynamic Debug Configuration */
	u32 dd_cfg;
} PACKED;

/* QMan Direct Connect Portal (DCP) Configuration */
struct qman_direct_portal_config {
	/* DCP Configuration */
	u32 dcp_cfg;
	/* DCP Dynamic Debug Configuration */
	u32 dd_cfg;
	/* DCP Dequeue Latency Monitor Configuration */
	u32 dlm_cfg;
	/* DCP Dequeue Latency Monitor Average */
	u32 dlm_avg;
} PACKED;

/* QMAN configuration registers */
struct qman {
	/* QMan Software Portal Configuration Registers */
	struct qman_soft_portal_config
		soft_portal_config[QMAN_SOFT_PORTALS];
	u8 reserved1[0x160];

	/* Dynamic Debug (DD) Configuration Registers */
	u32 qman_dd_cfg;
	u32 reserved2[0x3];
	u32 qcsp_dd_ihrsr;
	u32 qcsp_dd_ihrfr;
	u32 qcsp_dd_hasr;
	u32 reserved3[0x1];
	u32 dcp_dd_ihrsr;
	u32 dcp_dd_ihrfr;
	u32 dcp_dd_hasr;
	u8 reserved4[0xD4];

	/* Direct Connect Portal (DCP) Configuration Registers */
	struct qman_direct_portal_config
		direct_portal_config[QMAN_DIRECT_PORTALS];
	u8 reserved5[0xB0];

	u8 reserved6[0x240];
	/* WQ S/W Channel Dynamic Debug Config n */
	u32 wq_sc_dd_cfg[QMAN_NUM_WQ_SW_DD_CFG_REGS];
	u8 reserved7[0x2c];
	/* WQ Channel Pool Dynamic Debug Config n */
	u32 wq_pc_dd_cfg[QMAN_NUM_WQ_POOL_DD_CFG_REGS];
	u8 reserved8[0x20];
	/* WQ Direct Connect Port 0 Dynamic Debug Config n */
	u32 wq_dc0_dd_cfg[QMAN_NUM_WQ_DC0_DD_CFG_REGS];
	u8 reserved9[0x28];
	/* WQ Direct Connect Port 1 Dynamic Debug Config n */
	u32 wq_dc1_dd_cfg[QMAN_NUM_WQ_DC1_DD_CFG_REGS];
	u8 reserved10[0x28];
	/* WQ Direct Connect Port 2 Dynamic Debug Config */
	u32 wq_dc2_dd_cfg[QMAN_NUM_WQ_DC2_DD_CFG_REGS];
	u8 reserved11[0x3c];
	/* WQ Direct Connect Port 3 Dynamic Debug Config */
	u32 wq_dc3_dd_cfg[QMAN_NUM_WQ_DC3_DD_CFG_REGS];
	u8 reserved12[0x3c];
	/* WQ Direct Connect Port 4 Dynamic Debug Config */
	u32 wq_dc4_dd_cfg[QMAN_NUM_WQ_DC4_DD_CFG_REGS];
	u8 reserved13[0x3c];
	u8 reserved14[0x3F8];
	u32 qman_ip_rev_1; /* QM IP Block Revision 1 register */
	u32 qman_ip_rev_2; /* QM IP Block Revision 2 register */
	u8 reserved15[0x400];
} PACKED;
CTASSERT(sizeof(struct qman) == 0x1000);

#endif /* CCSR_QMAN_V1_H */
