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

#ifndef DCSR_NXC_V1_H
#define DCSR_NXC_V1_H

#include "common.h"

/* size of nxc struct */
#define NXC_STRUCT_SIZE		0x1000

/* size of nxc hit gen struct */
#define NXC_HIT_GEN_STRUCT_SIZE	0x100

/* Number of counting units in the NXC */
#define NXC_NO_OF_HITGENS		3
/* Number of mask units in a HitGen */
#define NXC_HG_NO_OF_MASK_UNITS		5
/** Number of Filter Control   */
#define NXC_NO_OF_FILTER_TRACE_CLIENTS	7

/* structure defines the memory map of the NXC HitGen control block */
struct nxc_hit_gen {
	/* HitGen Configuration Register 0 */
	u32 hgcfg0;
	/* HitGen Mask Unit Configuration Registers */
	u32 hgmsk_cfg[NXC_HG_NO_OF_MASK_UNITS];
	/* HitGen EC Configuration Registers */
	u32 hgecr[NXC_HG_NO_OF_MASK_UNITS];
	u32 reserved1[0x1];
	/* HitGen Comparator A Compare Value Hi MSB bits */
	u32 cmpavalhi_msb;
	/* HitGen Comparator A Compare Value Hi LSB bits */
	u32 cmpavalhi_lsb;
	/* HitGen Comparator A Compare Value Lo MSB bits */
	u32 cmpavalmsklo_msb;
	/* HitGenm Comparator A Compare Value Lo LSB bits */
	u32 cmpavalmsklo_lsb;
	u32 reserved2[0x04];

	/* HitGenm ComparatorB Compare Value Hi and Lo */
	u32 cmpbvalhilo;
	/* HitGenm ComparatorB Compare Value and Mask for masked compare */
	u32 cmpbvalmsk;
	/* HitGenm ComparatorB Compare Value for vector compare */
	u32 cmpbvector;
	u32 reserved3[0x1];

	/* HitGenm ComparatorB Compare Values for Match0/1 */
	u32 cmpcval;
	/* HitGenm ComparatorB Compare Value and Mask for masked compare */
	u32 cmpcvalmsk;

	u32 reserved[0x26];
} PACKED;
CTASSERT(sizeof(struct nxc_hit_gen) == NXC_HIT_GEN_STRUCT_SIZE);

/* structure defines the memory map of the NXC control block */
struct nxc {
	u32 nxccr0; /* Nearend Trace Message Control Register 0 */
	u32 reserved1[0x3F];

	u32 fccfg0; /* NXC Filter Control Configuration Register 0 */
	u32 fccfg1; /* NXC Filter Control Configuration Register 1 */
	u32 fccfg2; /* NXC Filter Control Configuration Register 2 */
	u32 fccfg3; /* NXC Filter Control Configuration Register 3 */
	u32 fccfg4; /* NXC Filter Control Configuration Register 4 */
	u32 reserved2[0xBB];

	struct nxc_hit_gen hit_gen[NXC_NO_OF_HITGENS];

	u32 reserved[0x240];
} PACKED;
CTASSERT(sizeof(struct nxc) == NXC_STRUCT_SIZE);

#define NXC_NXCCR0_TEN_MASK		0x00000001
#define NXC_NXCCR0_TEN_SHIFT 		0
#define NXC_NXCCR0_ARB_MASK		0x00000002
#define NXC_NXCCR0_ARB_SHIFT		1
#define NXC_NXCCR0_TSEN_MASK		0x00000ff0
#define NXC_NXCCR0_TSEN_SHIFT		4
#define NXC_NXCCR0_LZCDIS_MASK		0x00100000
#define NXC_NXCCR0_LZCDIS_SHIFT		20
#define NXC_HGMCFG0_SRC_SEL_MASK	0x00000007
#define NXC_HGMCFG0_SRC_SEL_SHIFT	0x0
#define NXC_HGMCFG0_CMPR_A_MASK		0x00000030
#define NXC_HGMCFG0_CMPR_A_SHIFT	0x4
#define NXC_HGMCFG0_CMPR_B_MASK		0x00000300
#define NXC_HGMCFG0_CMPR_B_SHIFT	0x8
#define NXC_HGMCFG0_CMPR_C_MASK		0x00001000
#define NXC_HGMCFG0_CMPR_C_SHIFT	0xc
#define NXC_CMPAVALHIM_MSB_MASK		0x000003ff
#define NXC_CMPAVALHIM_MSB_SHIFT	0x0
#define NXC_CMPAVALMSKLOM_MSB_MASK	0x000003ff
#define NXC_CMPAVALMSKLOM_MSB_SHIFT	0x0
#define NXC_CMPBVALHILOM_LO_MASK	0x000000ff
#define NXC_CMPBVALHILOM_LO_SHIFT	0x0
#define NXC_CMPBVALHILOM_HI_MASK	0x0000ff00
#define NXC_CMPBVALHILOM_HI_SHIFT	0x8
#define NXC_CMPBVALMSKM_VAL_MASK	0x000000ff
#define NXC_CMPBVALMSKM_VAL_SHIFT	0x0
#define NXC_CMPBVALMSKM_MSK_MASK	0x0000ff00
#define NXC_CMPBVALMSKM_MSK_SHIFT	0x8
#define NXC_CMPBVECTORM_VEC_MASK	0x0000ffff
#define NXC_CMPBVECTORM_VEC_SHIFT	0x0
#define NXC_CMPCVALM_VAL0_MASK		0x000000ff
#define NXC_CMPCVALM_VAL0_SHIFT		0x0
#define NXC_CMPCVALM_VAL1_MASK		0x0000ff00
#define NXC_CMPCVALM_VAL1_SHIFT		0x8
#define NXC_CMPCVALMSKM_VAL_MASK	0x000000ff
#define NXC_CMPCVALMSKM_VAL_SHIFT	0x0
#define NXC_CMPCVALMSKM_MSK_MASK	0x0000ff00
#define NXC_CMPCVALMSKM_MSK_SHIFT	0x8
#define NXC_HGMCFG_MSK_MASK		0x0000ffff
#define NXC_HGMCFG_MSK_SHIFT		0x0
#define NXC_HGMCFG_ECCMPMSK_MASK	0xffff0000
#define NXC_HGMCFG_ECCMPMSK_SHIFT	0x10
#define NXC_HGMCFG_HG_MASK_MASK		0x0000ffff
#define NXC_HGMCFG_HG_MASK_SHIFT	0x0
#define NXC_HGMECR_INV_MASK		0x000007ff
#define NXC_HGMECR_INV_SHIFT		0x0
#define NXC_FCCFG0_EVENT1_MASK		0x0f000000
#define NXC_FCCFG0_EVENT1_SHIFT		0x18
#define NXC_FCCFG0_EVENT2_MASK		0xf0000000
#define NXC_FCCFG0_EVENT2_SHIFT		0x1c
#define NXC_FCCFG0_SET2_MASK		0x00FF0000
#define NXC_FCCFG0_SET2_SHIFT		16
#define NXC_FCCFG0_SET1_MASK		0x0000FF00
#define NXC_FCCFG0_SET1_SHIFT		0x8
#define NXC_FCCFG0_FCQUAL_MASK		0x000000FF
#define NXC_FCCFG0_FCQUAL_SHIFT		0x0
#define NXC_FCCFG1_FCNESS_MASK		0x0000ffff
#define NXC_FCCFG1_FCNESS_SHIFT		0x0
#define NXC_FCCFG1_FCSUFF_MASK		0xffff0000
#define NXC_FCCFG1_FCSUFF_SHIFT		0x10
#define NXC_FCCFG2_FCNESS_MASK		0x0000ffff
#define NXC_FCCFG2_FCNESS_SHIFT		0x0
#define NXC_FCCFG2_FCSUFF_MASK		0xffff0000
#define NXC_FCCFG2_FCSUFF_SHIFT		0x10
#define NXC_FCCFG3_FCNESS_MASK		0x0000ffff
#define NXC_FCCFG3_FCNESS_SHIFT		0x0
#define NXC_FCCFG3_FCSUFF_MASK		0xffff0000
#define NXC_FCCFG3_FCSUFF_SHIFT		0x10
#define NXC_FCCFG4_FILTER_0_MASK	0x0000000f
#define NXC_FCCFG4_FILTER_0_SHIFT	0
#define NXC_FCCFG4_FILTER_1_MASK	0x000000f0
#define NXC_FCCFG4_FILTER_1_SHIFT	4
#define NXC_FCCFG4_FILTER_2_MASK	0x00000f00
#define NXC_FCCFG4_FILTER_2_SHIFT	8
#define NXC_FCCFG4_FILTER_3_MASK	0x0000f000
#define NXC_FCCFG4_FILTER_3_SHIFT	12
#define NXC_FCCFG4_FILTER_4_MASK	0x000f0000
#define NXC_FCCFG4_FILTER_4_SHIFT	16
#define NXC_FCCFG4_FILTER_5_MASK	0x00f00000
#define NXC_FCCFG4_FILTER_5_SHIFT	20
#define NXC_FCCFG4_FILTER_6_MASK	0x0f000000
#define NXC_FCCFG4_FILTER_6_SHIFT	24

#endif  /* DCSR_NXC_V1_H */
