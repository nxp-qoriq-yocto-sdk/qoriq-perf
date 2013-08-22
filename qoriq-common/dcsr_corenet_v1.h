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

#ifndef DCSR_CORENET_V1_H
#define DCSR_CORENET_V1_H

#include "common.h"

/* Number of reference event selection registers */
#define CNDC_NO_REF_EVENTS			4
/* Number of general event selection registers */
#define CNDC_NO_GENERAL_EVENTS			4
/* Number of CNDC Event Comparators */
#define CNDC_NO_EVENT_COMPARATORS		4
/* Number of CNDC comparator debug event control registers */
#define CNDC_NO_COMPARATORS_CONTROL_REGS	2
/* Number of CNDC Address Comparators */
#define CNDC_NO_ADDRESS_COMPARATORS		4
/* Number of CNDC Event Comparators */
#define CNDC_NO_TRANS_COMPARATORS		4

/* CoreNet Debug Client Performance events */
enum CNDC_PE {
	/* 0-31 Address and attribute - 32 */
	/* 32 -63    Data Value events - 32 */
	/* 64 - 127  CPC0 - 64 */

	/* L3 write miss */
	CNDC_PE_CPC0_WRITE_MISS = 64,
	/* L3 write hit */
	CNDC_PE_CPC0_WRITE_HIT = 65,
	/* L3 write allocate */
	CNDC_PE_CPC0_WRITE_ALLOC = 66,
	/* 67 is reserved */
	/* L3 stash allocate */
	CNDC_PE_CPC0_STASH_ALLOC = 68,
	/* L3 read miss */
	CNDC_PE_CPC0_READ_MISS = 69,
	/* L3 read hit */
	CNDC_PE_CPC0_READ_HIT = 70,
	/* L3 read allocate */
	CNDC_PE_CPC0_READ_ALLOC = 71,
	/* L3 other miss */
	CNDC_PE_CPC0_OTHER_MISS = 72,
	/* L3 other hit */
	CNDC_PE_CPC0_OTHER_HIT = 73,
	/* L3 decorated */
	CNDC_PE_CPC0_DECORATED = 74,
	/* L3 castout */
	CNDC_PE_CPC0_CASTOUT = 75,

	/* Marked transaction - L3 write miss */
	CNDC_PE_CPC0_MARKED_WRITE_MISS = 80,
	/* Marked transaction - L3 write hit */
	CNDC_PE_CPC0_MARKED_WRITE_HIT = 81,
	/* Marked transaction - L3 write allocate */
	CNDC_PE_CPC0_MARKED_WRITE_ALLOC = 82,

	/* Marked transaction - L3 stash allocate */
	CNDC_PE_CPC0_MARKED_STASH_ALLOC = 84,
	/* Marked transaction - L3 read miss */
	CNDC_PE_CPC0_MARKED_READ_MISS = 85,
	/* Marked transaction - L3 read hit */
	CNDC_PE_CPC0_MARKED_READ_HIT = 86,
	/* Marked transaction - L3 read allocate */
	CNDC_PE_CPC0_MARKED_READ_ALLOC = 87,
	/* Marked transaction - L3 other miss */
	CNDC_PE_CPC0_MARKED_OTHER_MISS = 88,
	/* Marked transaction - L3 other hit */
	CNDC_PE_CPC0_MARKED_OTHER_HIT = 89,
	/* Marked transaction - L3 decorated */
	CNDC_PE_CPC0_MARKED_DECORATED = 90,
	/* Marked transaction - L3 castout */
	CNDC_PE_CPC0_MARKED_CASTOUT = 91,

	/* L3 data write */
	CNDC_PE_CPC0_DATA_WRITE = 96,
	/* L3 data read-modify-write */
	CNDC_PE_CPC0_DATA_RMW = 97,
	/* L3 data read */
	CNDC_PE_CPC0_DATA_READ = 98,
	/* L3 data access */
	CNDC_PE_CPC0_DATA_ACCESS = 99,

	/* Marked transaction - L3 data write */
	CNDC_PE_CPC0_MARKED_DATA_WRITE = 100,
	/* Marked transaction - L3 data read-modify-write */
	CNDC_PE_CPC0_MARKED_DATA_RMW = 101,
	/* Marked transaction - L3 data read */
	CNDC_PE_CPC0_MARKED_DATA_READ = 102,
	/* Marked transaction - L3 data access */
	CNDC_PE_CPC0_MARKED_DATA_ACCESS = 103,

	/* 128 - 191 CPC1 - 64 */
	/* L3 write miss */
	CNDC_PE_CPC1_WRITE_MISS = 128,
	/* L3 write hit */
	CNDC_PE_CPC1_WRITE_HIT = 129,
	/* L3 write allocate */
	CNDC_PE_CPC1_WRITE_ALLOC = 130,
	/* 131 is reserved */
	/* L3 stash allocate */
	CNDC_PE_CPC1_STASH_ALLOC = 132,
	/* L3 read miss */
	CNDC_PE_CPC1_READ_MISS = 133,
	/* L3 read hit */
	CNDC_PE_CPC1_READ_HIT = 134,
	/* L3 read allocate */
	CNDC_PE_CPC1_READ_ALLOC = 135,
	/* L3 other miss */
	CNDC_PE_CPC1_OTHER_MISS = 136,
	/* L3 other hit */
	CNDC_PE_CPC1_OTHER_HIT = 137,
	/* L3 decorated */
	CNDC_PE_CPC1_DECORATED = 138,
	/* L3 castout */
	CNDC_PE_CPC1_CASTOUT = 139,

	/* Marked transaction - L3 write miss */
	CNDC_PE_CPC1_MARKED_WRITE_MISS = 144,
	/* Marked transaction - L3 write hit */
	CNDC_PE_CPC1_MARKED_WRITE_HIT = 145,
	/* Marked transaction - L3 write allocate */
	CNDC_PE_CPC1_MARKED_WRITE_ALLOC = 146,

	/* Marked transaction - L3 stash allocate */
	CNDC_PE_CPC1_MARKED_STASH_ALLOC = 148,
	/* Marked transaction - L3 read miss */
	CNDC_PE_CPC1_MARKED_READ_MISS = 149,
	/* Marked transaction - L3 read hit */
	CNDC_PE_CPC1_MARKED_READ_HIT = 150,
	/* Marked transaction - L3 read allocate */
	CNDC_PE_CPC1_MARKED_READ_ALLOC = 151,
	/* Marked transaction - L3 other miss */
	CNDC_PE_CPC1_MARKED_OTHER_MISS = 152,
	/* Marked transaction - L3 other hit */
	CNDC_PE_CPC1_MARKED_OTHER_HIT = 153,
	/* Marked transaction - L3 decorated */
	CNDC_PE_CPC1_MARKED_DECORATED = 154,
	/* Marked transaction - L3 castout */
	CNDC_PE_CPC1_MARKED_CASTOUT = 155,


	/* L3 data write */
	CNDC_PE_CPC1_DATA_WRITE = 160,
	/* L3 data read-modify-write */
	CNDC_PE_CPC1_DATA_RMW = 161,
	/* L3 data read */
	CNDC_PE_CPC1_DATA_READ = 162,
	/* L3 data access */
	CNDC_PE_CPC1_DATA_ACCESS = 163,

	/* Marked transaction - L3 data write */
	CNDC_PE_CPC1_MARKED_DATA_WRITE = 164,
	/* Marked transaction - L3 data read-modify-write */
	CNDC_PE_CPC1_MARKED_DATA_RMW = 165,
	/* Marked transaction - L3 data read */
	CNDC_PE_CPC1_MARKED_DATA_READ = 166,
	/* Marked transaction - L3 data access */
	CNDC_PE_CPC1_MARKED_DATA_ACCESS = 167,
	/* 192 - 255 Reserved */
};

#define CNDC_CPRESCRN_REFSEL_MASK	0x000000ff
#define CNDC_CPRESCRN_REFSEL_SHIFT	0x0

#define CNDC_CPMSR1_B3_SEL_MASK		0x0000001f
#define CNDC_CPMSR1_B3_SEL_SHIFT	0x0
#define CNDC_CPMSR1_B2_SEL_MASK		0x00001f00
#define CNDC_CPMSR1_B2_SEL_SHIFT	0x8
#define CNDC_CPMSR1_B1_SEL_MASK		0x001f0000
#define CNDC_CPMSR1_B1_SEL_SHIFT	0x10
#define CNDC_CPMSR1_B0_SEL_MASK		0x1f000000
#define CNDC_CPMSR1_B0_SEL_SHIFT	0x18

enum CNDC_CPMSR1_BYTE_SELECTION{
	/* Platform Cache 0 byte 0 */
	CNDC_CPMSR1_PLATFORM_0_BYTE_0 = 0x10,
	/* Platform Cache 0 byte 1  */
	CNDC_CPMSR1_PLATFORM_0_BYTE_1 = 0x11,
	/* Platform Cache 0 byte 2 */
	CNDC_CPMSR1_PLATFORM_0_BYTE_2 = 0x12,
	/* Platform Cache 0 byte 3 */
	CNDC_CPMSR1_PLATFORM_0_BYTE_3 = 0x13,
	/* Platform Cache 0 byte 4 */
	CNDC_CPMSR1_PLATFORM_0_BYTE_4 = 0x14,
	/* Platform Cache 0 byte 5 */
	CNDC_CPMSR1_PLATFORM_0_BYTE_5 = 0x15,
	/* Platform Cache 0 byte 6 */
	CNDC_CPMSR1_PLATFORM_0_BYTE_6 = 0x16,
	/* Platform Cache 1 byte 0 */
	CNDC_CPMSR1_PLATFORM_1_BYTE_0 = 0x18,
	/* Platform Cache 1 byte 1 */
	CNDC_CPMSR1_PLATFORM_1_BYTE_1 = 0x19,
	/* Platform Cache 1 byte 2 */
	CNDC_CPMSR1_PLATFORM_1_BYTE_2 = 0x1a,
	/* Platform Cache 1 byte 3 */
	CNDC_CPMSR1_PLATFORM_1_BYTE_3 = 0x1b,
	/* Platform Cache 1 byte 4 */
	CNDC_CPMSR1_PLATFORM_1_BYTE_4 = 0x1c,
	/* Platform Cache 1 byte 5 */
	CNDC_CPMSR1_PLATFORM_1_BYTE_5 = 0x1d,
	/* Platform Cache 1 byte 6 */
	CNDC_CPMSR1_PLATFORM_1_BYTE_6 = 0x1e,
	/* End of Enum marker */
	CNDC_CPMSR1_BYTE_SELECTION_END = 0xffff
};

/* size of cndc section 1 struct */
#define CNDC1_STRUCT_SIZE		0x1000
/* size of cndc section 2 struct */
#define CNDC2_STRUCT_SIZE		0x1000

/* CNDC Compare Debug Event Control Register */
struct cndc_comp {
	u32 cc_decr[CNDC_NO_COMPARATORS_CONTROL_REGS];
	u32 reserved[0x02];
} PACKED;
CTASSERT(sizeof(struct cndc_comp) == 0x10);

/* CNDC memory map section 1 in the DCSR block */
struct cndc_1 {
	u32 reserved1[0x18];
	u32 ctarm;
	u32 ctcr1;
	u32 reserved2[0x06];
	u32 cwmsk;
	u32 reserved7[0x2];
	u32 ctscr;
	u32 reserved3[0x1c];

	struct cndc_comp comp[CNDC_NO_EVENT_COMPARATORS];
	u32 reserved4[0x1B0];

	u32 cpmsr1;
	u32 reserved5[0x03];

	u32 cprescr[CNDC_NO_REF_EVENTS];
	u32 reserved6[0x1F8];
} PACKED;
CTASSERT(sizeof(struct cndc_1) == CNDC1_STRUCT_SIZE);

/* Debug address compare registers */
struct cndc_addr_comp {
	u32 cdac_h;
	u32 cdac_l;
};

/* CNDC memory map section 2 */
struct cndc_2 {
	u32 reserved1[0x3C0];
	/* CoreNetCCM_AP Debug Control Registers */
	u32 cdbcr0; /* enables CDACs */
	u32 cdbcr1; /* CDBCR1 - config for CDACs 1/2*/
	u32 cdbcr2; /* CDBCR2 - config for CDACs 3/4*/
	u32 cdbcr3; /* data compare */

	/* Debug Address Compare registers */
	struct cndc_addr_comp addr_comp[CNDC_NO_ADDRESS_COMPARATORS];

	/*Transaction Attribute Compare Registers */
	u32 ctac[CNDC_NO_TRANS_COMPARATORS];
	u32 reserved2[0x4];

	/* Data Value Compare Registers */
	u32 cdvchh;
	u32 cdvchl;
	u32 cdvclh;
	u32 cdvcll;
	u32 reserved3[0x8];
	u32 perfmon_enable;
	u32 reserved4[0x3];

	/* Performance Monitor Control Register */
	u32 cdpmcr;
	u32 reserved5[0x1B];
} PACKED;
CTASSERT(sizeof(struct cndc_2) == CNDC2_STRUCT_SIZE);

#endif  /* DCSR_CORENET_V1_H */
