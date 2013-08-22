/*
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
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
#ifndef DDR_CMPLX_EVENTS_H
#define DDR_CMPLX_EVENTS_H

#include "common.h"
/* The number of hitgens available; correlates with number of counters */
#define DDR_CMPLX_NUM_HITGENS 3

enum ddr_cmplx_mhm {DDRC_MISS, DDRC_HIT, DDRC_MODIFY};

/* Bit fields specific to DDR complex */
#define DDR_CMPLX_SRC_FILTER_BIT  0x04000000
#define DDR_CMPLX_SRC_ID_MASK     0x03FC0000
#define DDR_CMPLX_SRC_ID_SHIFT 18
#define DDR_CMPLX_SRC_ID_MSK_MASK 0x0003FC00
#define DDR_CMPLX_SRC_ID_MSK_SHIFT 10

/* from PCI Express 1 (SRC ID = 0x0) */
/* from PCI Express 2 (SRC ID = 0x1) */
/* from PCI Express 3 (SRC ID = 0x2) */
/* from PCI Express 4 (SRC ID = 0x3) */
/* from Serial Rapid I/O 1 (SRC ID = 0x8) */
/* from Serial Rapid I/O 2 (SRC ID = 0x9) */
/* from Buffer manager (control) (SRC ID = 0x18) */
/* from PAMU (SRC ID = 0x1C) */
/* from PME (SRC ID = 0x20) */
/* from Security 4.2 (SRC ID = 0x21) */
/* from RAID (SRC ID = 0x28) */
/* from QMAN (SRC ID = 0x3C) */
/* from USB1 (SRC ID = 0x40) */
/* from USB2 (SRC ID = 0x41) */
/* from eSDHC (SRC ID = 0x44) */
/* from Pre-boot loader (PBL) (SRC ID = 0x48) */
/* from Nexus Port Controller (NPC) (SRC ID = 0x4B) */
/* from RapidIO message manager (SRC ID = 0x5D) */
/* from SATA 1 (SRC ID = 0x60) */
/* from SATA 2 (SRC ID = 0x61) */
/* from DMA 1 (SRC ID = 0x70) */
/* from DMA 2 (SRC ID = 0x71) */
/* from Core 0 (instruction) (SRC ID = 0x80) */
/* from Core 0 (data) (SRC ID = 0x81) */
/* from Core 1 (instruction) (SRC ID = 0x82) */
/* from Core 1 (data) (SRC ID = 0x83) */
/* from Core 2 (instruction) (SRC ID = 0x84) */
/* from Core 2 (data) (SRC ID = 0x85) */
/* from Core 3 (instruction) (SRC ID = 0x86) */
/* from Core 3 (data) (SRC ID = 0x87) */
/* from Core 4 (instruction) (SRC ID = 0x88) */
/* from Core 4 (data) (SRC ID = 0x89) */
/* from Core 5 (instruction) (SRC ID = 0x8A) */
/* from Core 5 (data) (SRC ID = 0x8B) */
/* from Core 6 (instruction) (SRC ID = 0x8C) */
/* from Core 6 (data) (SRC ID = 0x8D) */
/* from Core 7 (instruction) (SRC ID = 0x8E) */
/* from Core 7 (data) (SRC ID = 0x8F) */
/* from Frame Manager XAUI (SRC ID = 0xC0) */
/* from Frame Manager Offline, host 1 (SRC ID = 0xC1) */
/* from Frame Manager Offline, host 2 (SRC ID = 0xC2) */
/* from Frame Manager Offline, host 3 (SRC ID = 0xC3) */
/* from Frame Manager Offline, host 4 (SRC ID = 0xC4) */
/* from Frame Manager Offline, host 5 (SRC ID = 0xC5) */
/* from Frame Manager Offline, host 6 (SRC ID = 0xC6) */
/* from Frame Manager Offline, host 7 (SRC ID = 0xC7) */
/* from Frame Manager GE 1 (SRC ID = 0xC8) */
/* from Frame Manager GE 2 (SRC ID = 0xC9) */
/* from Frame Manager GE 3 (SRC ID = 0xCA) */
/* from Frame Manager GE 4 (SRC ID = 0xCB) */
/* from Frame Manager GE 5 (SRC ID = 0xCC) */


/*
 * Provides a mapping from the DDR Complex events
 * to the EPU events and counters.
 */

struct ddr_cmplx_event {
	u32	code;		/* qoriq raw event code */
	u32	ddr_ind;  	/* DDR1 (0) or DDR2 (1) */
	enum ddr_cmplx_mhm	miss_hit_modify; 
};

/* Public interface */

/* Return a pointer to the ddr_event associated with the event_code.
 * Returns 0 if not found.
 */
const struct ddr_cmplx_event *ddr_cmplx_event_from_code(u32 event_code);

#endif /*DDR_CMPLX_EVENTS_H */
