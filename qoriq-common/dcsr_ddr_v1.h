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

#ifndef DCSR_DDR_V1_H
#define DCSR_DDR_V1_H

#include "common.h"

/* size of ddr struct */
#define DDR_STRUCT_SIZE		0x1000

/* structure defines the memory map of the DDR control block */
struct ddr {
	u32 ddicr0; /* ddr control register */
	u32 reserved[0x3ff];
} PACKED;
CTASSERT(sizeof(struct ddr) == DDR_STRUCT_SIZE);

#define DDDI_DDICR_VERB_SHIFT	4
#define DDDI_DDICR_VERB_MASK	0x00000010
#define DDDI_DDICR_PMOVR_SHIFT	1
#define DDDI_DDICR_PMOVR_MASK	0x00000002
#define DDDI_DDICR_TPEN_SHIFT	0
#define DDDI_DDICR_TPEN_MASK	0x00000001

#endif  /* DCSR_DDR_V1_H */
