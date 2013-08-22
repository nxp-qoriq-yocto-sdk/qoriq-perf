/*
 * Copyright (C) 2013 Freescale Semiconductor, Inc.
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

#ifndef DCSR_DPAA_V2_H
#define DCSR_DPAA_V2_H

#include "common.h"

/* Number of QMAN Software Portals */
#define DPAA_V2_NO_OF_QMAN_SP		50
/* Number of QMAN Direct Connect Portals */
#define DPAA_V2_NO_OF_QMAN_DCP		6
/* Number of Halt Control Status Registers */
#define DPAA_V2_NO_OF_HALTSTATUS	16
/* Number of Queue Operation Event Registers */
#define DPAA_V2_NO_OF_QOER		4
/* Number of Frame Operation Event Registers */
#define DPAA_V2_NO_OF_FOER		4
/* Number of Event Generation Control Registers */
#define DPAA_V2_NO_OF_EGCR		4
/* Number of General Purpose Comparators */
#define DPAA_V2_NO_OF_GPC		4
/** Number of DP Performance Event Selection Control Registers */
#define DPAA_V2_NO_OF_DPPESCRS		32
/* Number of Group Configuration Registers */
#define DPAA_V2_NO_OF_GCR		4
/* Number of Group Configuration Registers */
#define DPAA_V2_NO_OF_SPGCR		4
/* Number of Trace General Control Registers */
#define DPAA_V2_NO_OF_TGCR		2
/* Number of Trace Filter Control Registers */
#define DPAA_V2_NO_OF_TFTCR		4
/* Number of Reference Event Selection Control Registers */
#define DPAA_V2_NO_OF_DPRESCR		2

/* Data Path General Purpose Comparator */
struct dpgp {
	/* Compare Control Register */
	u32 ccr;
	/* Compare Mask Register */
	u32 cmr;
	/* Compare Value Register */
	u32 cvr;
	u8 reserved0[4];
};

/* Data Path Group Configuration */
struct dpgc {
	/* Portal Register */
	u32 pr;
	/* Engine Register */
	u32 er;
};

/* The Data Path Debug Register Memory Map */
struct dpaa_v2 {
	/* Data Path External Halt Control Register */
	u32 dpehcr;
	/* Data Path Resume Control Register */
	u32 dprcr;
	u8 reserved0[0x20-0x08];
	/* FMan 1 Halt Control Status Register */
	u32 fmhsr0;
	u8 reserved1[0x28-0x24];
	/* FMan 2 Halt Control Status Register */
	u32 fmhsr1;
	u8 reserved2[0x60-0x2c];
	/* Halt Control Status Registers */
	u32 dppehsr[DPAA_V2_NO_OF_HALTSTATUS];
	/* QMan Direct Connect Portal Halt Status Registers */
	u32 qdcphsr[DPAA_V2_NO_OF_QMAN_DCP];
	u8 reserved3[0x100-0x0b8];
	/* QMan Software Portal Halt Status Registers */
	u32 qsphsr[DPAA_V2_NO_OF_QMAN_SP];
	u8 reserved4[0x500-0x1c8];
	/* Data Path Queue Operation Event Registers */
	u32 dpqoer[DPAA_V2_NO_OF_QOER];
	u8 reserved5[0x540-0x510];
	/* Data Path Frame Operation Event Registers */
	u32 dpfoer[DPAA_V2_NO_OF_FOER];
	u8 reserved6[0x560-0x550];
	/* Data Path Event Generation Control Registers */
	u32 dpegcr[DPAA_V2_NO_OF_EGCR];
	u8 reserved7[0x580-0x570];
	/* Data Path General Purpose Comparator Registers */
	struct dpgp dpgpcmp[DPAA_V2_NO_OF_GPC];
	/* Data Path Event Port General Control Register */
	u32 dpepgcr;
	u8 reserved7a[0x5c8-0x5c4];
	/* Data Path Reference Event Selection Control Register */
	u32 dprescr[DPAA_V2_NO_OF_DPRESCR];
	u8 reserved8[0x5fc-0x5d0];
	/* Data Path Checkstop Control Register */
	u32 dpckstpcr;
	/* Data Path Performance Event Selection Control Register */
	u32 dppescr[DPAA_V2_NO_OF_DPPESCRS];
	u8 reserved9[0x700-0x680];
	/* Data Path Group Configuration */
	struct dpgc dpgc[DPAA_V2_NO_OF_GCR];
	u8 reserved10[0x780-0x720];
	/* Data Path Software Portal Group Configuration Register Group A */
	u32 dpspgcra[DPAA_V2_NO_OF_SPGCR];
	/* Data Path Software Portal Group Configuration Register Group B */
	u32 dpspgcrb[DPAA_V2_NO_OF_SPGCR];
	u8 reserved11[0x7c0-0x7a0];
	/* Data Path Group Action Configuration Register */
	u32 dpgacr[DPAA_V2_NO_OF_GCR];
	u8 reserved12[0x800-0x7d0];
	/* Data Path Trace Armed Register */
	u32 dptarm;
	/* Data Path Trace General Control Register */
	u32 dptgcr[DPAA_V2_NO_OF_TGCR];
	u8 reserved13[0x820-0x80c];
	/* Data Path Trace Filter Trigger Control Register */
	u32 dptftcr[DPAA_V2_NO_OF_TFTCR];
	u8 reserved14[0x900-0x830];
	/* Data Path Watch point Mask Control Register */
	u32 dpwmsk;
	u8 reserved15[0xA00-0x904];
	/* Data Path Circuit Trace Static Control Register */
	u32 dpctscr;
	/* Data Path Circuit Trace Dynamic Control Register */
	u32 dpctdcr;
	u8 reserved16[0x1000-0xA08];
} PACKED;
CTASSERT(sizeof(struct dpaa_v2) == 0x1000);

#endif  /* DCSR_DPAA_V2_H */
