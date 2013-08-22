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

#ifndef DCSR_OCN_V1_H
#define DCSR_OCN_V1_H

#include "common.h"

/* size of OceaN struct in bytes */
#define OCN_STRUCT_SIZE			0x1000

/* Number of reference input mux selection registers */
#define OCN_NUM_REF_INPUT_MUX		4
/* Number of general input mux selection registers */
#define OCN_NUM_GEN_INPUT_MUX		32

/** structure defines the memory map of the OCN control block */
struct ocn {
	u32 ocdicr0; /* ocn control register */
	u32 reserved1[0x3f];
	u32 ocrimcr[OCN_NUM_REF_INPUT_MUX];
	u32 reserved2[0x3c];
	u32 ocgimcr[OCN_NUM_GEN_INPUT_MUX];
	u32 reserved3[0x360];
} PACKED;
CTASSERT(sizeof(struct ocn) == OCN_STRUCT_SIZE);

#endif  /* DCSR_OCN_V1_H */
