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

#ifndef CCSR_DDR_V1_H
#define CCSR_DDR_V1_H

#include "common.h"

/* number of buffer pools */
//#define BMAN_NUM_POOLS			64
/* number of performance monitors */
//#define BMAN_NUM_PERF_MONITORS		8
/* Number of words containing error data */
//#define BMAN_NUM_DATA_ERROR_WORDS	8

/* DDR configuration registers */
struct ccsr_memctrl {
	
	
/* The following is a rough, un-verified map of the ccsr_ddr registers.
 * Since most of the registers are not needed for qoriq-perf/qoriq-dbg,
 * the effort to accurrately map them out has not been undertaken. Instead,
 * required registers should be mapped (uncommented/verified) as needed.
 * 
 * Until then, treat unmapped areas as "reserved".
 * 
	u32 cs0_bnds;
	u32 cs1_bnds;
	u32 cs2_bnds;
	u32 cs3_bnds;
	u32 cs0_config;
	u32 cs1_config;
	u32 cs2_config;
	u32 cs3_config;
	u32 cs0_config_2;
	u32 cs1_config_2;
	u32 cs2_config_2;
	u32 cs3_config_2;
	u32 timing_cfg_3;
	u32 timing_cfg_0;
	u32 timing_cfg_1;
	u32 timing_cfg_2;
	u32 ddr_sdram_cfg;
	u32 ddr_sdram_cfg_2;
	u32 ddr_sdram_mode;
	u32 ddr_sdram_mode_2;
	u32 ddr_sdram_md_cntl;
	u32 ddr_sdram_interval;
	u32 ddr_data_init;
	u32 ddr_sdram_clk_cntl;
reserved
	u32 ddr_init_addr;
	u32 ddr_init_ext_address;
reserved
	u32 timing_cfg_4;
	u32 timing_cfg_5;
	u32 ddr_zq_cntl;
	u32 ddr_wrlvl_cntl;
reserved
	u32 ddr_sr_cntr;
	u32 ddr_sdram_rcw_1;
	u32 ddr_sdram_rcw_2;
	u32 ddr_wrlvl_cntl_2;
	u32 ddr_wrlvl_cntl_3;
reserved
	u32 ddr_sdram_rcw_3;
	u32 ddr_sdram_rcw_4;
	u32 ddr_sdram_rcw_5;
	u32 ddr_sdram_rcw_6;
reserved
	u32 ddr_sdram_mode_3;
	u32 ddr_sdram_mode_4;
	u32 ddr_sdram_mode_5;
	u32 ddr_sdram_mode_6;
	u32 ddr_sdram_mode_7;
	u32 ddr_sdram_mode_8;
reserved
	u32 ddr_sdram_mode_9;
	u32 ddr_sdram_mode_10;
	u32 ddr_sdram_mode_11;
	u32 ddr_sdram_mode_12;
	u32 ddr_sdram_mode_13;
	u32 ddr_sdram_mode_14;
	u32 ddr_sdram_mode_15;
	u32 ddr_sdram_mode_16;
reserved
	u32 timing_cfg_8;
	u32 timing_cfg_9;
reserved
	u32 ddr_sdram_cfg_3
reserved
	u32 ddr_sdram_md_cntl2;
	u32 ddr_sdram_mpr1;
	u32 ddr_sdram_mpr2;
	u32 ddr_sdram_mpr3;
reserved
	u32 ddr_deskew_cntl;
reserved
	u32 ddr_sdram_bscan_cntl;
	u32 ddr_sdram_bscan_cntl_2;
	u32 ddr_sdram_bscan_stat;
reserved
	u32 ddrdsr_1;
	u32 ddrdsr_2;
	u32 ddrcdr_1;
	u32 ddrcdr_2;
reserved
	u32 ddr_ip_rev1;
	u32 ddr_ip_rev2;
	u32 ddr_eor;
	u32 ddr_mtcr;
	u32 ddr_mtp1;
	u32 ddr_mtp2;
	u32 ddr_mtp3;
	u32 ddr_mtp4;
	u32 ddr_mtp5;
	u32 ddr_mtp6;
	u32 ddr_mtp7;
	u32 ddr_mtp8;
	u32 ddr_mtp9;
	u32 ddr_mtp10;

	u32 ddr_mt_st_ext_adr;
	u32 ddr_mt_st_addr;
	u32 ddr_mt_end_ext_addr;
	u32 ddr_mt_end_addr;
	u32 data_err_inject_hi;
	u32 daa_err_inject_lo;
	u32 ecc_err_inject;
	u32 capture_data_hi;
	u32 capture_data_lo;
	u32 capture_ecc;
	u32 err_detect;
	u32 err_disable;
	u32 err_int_en;
	u32 capture_attributes;
	u32 capture_address;
	u32 capture_ext_address;
	u32 err_sbe;
*/	
	u8 reserved0[0xf48];
	u32 debug_19;
	u8 reserved1[0xfff-0xf4b];
} PACKED;
CTASSERT(sizeof(struct ccsr_memctrl) == 0x1000);

#define DDR_C_DBG19_PRF_EN_OVRD_SHIFT 21
#define DDR_C_DBG19_PRF_EN_OVRD_MASK  0x00200000
#endif /* CCSR_DDR_V1_H */
