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

#ifndef DCSR_NAL_V1_H
#define DCSR_NAL_V1_H

#include "common.h"

/* size of nal struct */
#define NAL_STRUCT_SIZE		0x1000

/* structure defines the memory map of the NAL control block */
struct nal {
	u32 gsr;			/* General Status Register */
	u32 esr;			/* Error Status Register */
	u32 gcr;			/* General Control Register */
	u32 tcr;			/* Training Control Register */
	u8 reserved[0xFF0];
} PACKED;
CTASSERT(sizeof(struct nal) == NAL_STRUCT_SIZE);

#define NAL_GCR_ALCPD_MASK	0x40000000
#define NAL_GCR_ALCPD_SHIFT	30

#define NAL_GSR_AS_MASK		0x00000001
#define NAL_GSR_AS_SHIFT	0

#endif  /* DCSR_NAL_V1_H */
