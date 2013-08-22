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

#ifndef DCSR_RCPM_V1_H
#define DCSR_RCPM_V1_H

#include "common.h"

/** size of rcpm struct */
#define RCPM_STRUCT_SIZE  0x2000
#define RCPM_NO_OF_CORE_GROUPS  8
#define RCPM_NO_OF_SCU  16
#define RCPM_NO_OF_CATTACR  2

/* Core Group Configuration Registers */
struct cgcr {
	u32 reserved;
	u32 cgcrl;	/* Core Group Configuration Registers */
};

/* structure defines the memory map of the RCPM control block */
struct rcpm {
	u8 reserved1[0x200];
	/* Core Group Configuration Register n */
	struct cgcr cgcr[RCPM_NO_OF_CORE_GROUPS];
	u8 reserved2[0x2c0];
	/* Core Group Action Control Register n for EPU Events */
	u32 cgacre[RCPM_NO_OF_SCU];
	u8 reserved3[0x40];
	/* Device Action Control Register n for EPU Events */
	u32 dacre[RCPM_NO_OF_SCU];
	u8 reserved4[0x140];
	/* Core State Action Control Register n  */
	u32 csttacr[RCPM_NO_OF_CATTACR];
	u8 reserved5[0x8F8];
	u8 reserved6[0x1000];
} PACKED;
CTASSERT(sizeof(struct rcpm) == RCPM_STRUCT_SIZE);

#define RCPM_CGCR_CORE_GROUP_MASK	0x000000ff
#define RCPM_CGCR_CORE_GROUP_SHIFT	0x0
#define RCPM_CGACRE_CGC_MASK		0x00000007
#define RCPM_CGACRE_CGC_SHIFT		0x0
#define RCPM_CGACRE_ICAC_MASK		0x000000f0
#define RCPM_CGACRE_ICAC_SHIFT		0x4
#define RCPM_CGACRE_PCAC_MASK		0x00ffff00
#define RCPM_CGACRE_PCAC_SHIFT		0x8

#endif  /* DCSR_RCPM_V1_H */
