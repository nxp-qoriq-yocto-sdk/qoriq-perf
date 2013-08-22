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
#ifndef QORIQ_PERF_H
#define QORIQ_PERF_H

#include "dcsr_corenet_v1.h"
#include "dcsr_ddr_v1.h"
#include "dcsr_dpaa_v1.h"
#include "dcsr_epu_v1.h"
#include "ccsr_fman_v1.h"
#include "dcsr_nxc_v1.h"
#include "dcsr_ocn_v1.h"
#include "ccsr_qman_v1.h"

#define DRIVER_NAME "qoriq-perf"
/*
#define DEBUG_QORIQ_PERF 1
#define DEBUG_QORIQ_PERF_ON 1
#define DEBUG_QORIQ_PERF_CONFIG 1
#define DEBUG_QORIQ_PERF_ADD_DEL 1
#define DEBUG_QORIQ_PERF_CONFIG_COUNTERS 1
#define DEBUG_QORIQ_PERF_READ_COUNTERS 1
#define DEBUG_QORIQ_PERF_WRITE_COUNTERS 1
#define DEBUG_QORIQ_PERF_FUNC_CALLS 1
#define DEBUG_QORIQ_PERF_DDR 1
#define DEBUG_QORIQ_PERF_INTERRUPTS 1
*/

#ifdef DEBUG_QORIQ_PERF
#define NOINLINE noinline
#define DBG_PRINT(DBG_LVL, STR, ARGS...) \
	printk(DBG_LVL "%s	(%d): " STR, __FUNCTION__, __LINE__, ##ARGS )
#else 
#define DBG_PRINT(DBG_LVL, STR, ARGS...)
#define NOINLINE
#endif /* DEBUG_QORIQ_PERF */


/* Max number of components by type in QoriQ Arch */
#define MAX_NUM_FMAN		2

/* E500 based devices and B4860 have 2 DDR controllers. */
#define MAX_NUM_DDR		2

/* dbg_device maintains the association between the mapped dcsr memory
 * and the debugfs directory where the device files are located
 */
struct dbg_device {
	/* index number for this device */
	int index;
	/* mapped memory address */
	void *mem_ptr;
	/* device tree node pointer */
	struct device_node *np;
};

/* maintains information on each sub-device managed by the driver */
struct dbg_devices {
	struct dbg_device cndc1;
	struct dbg_device cndc2;
	struct dbg_device ddr[MAX_NUM_DDR];
	struct dbg_device dpaa;
	struct dbg_device epu;
	struct dbg_device fman[MAX_NUM_FMAN];
	struct dbg_device nxc;
	struct dbg_device ocn;
	struct dbg_device qman;
	struct dbg_device memctrl;
//	struct dbg_device rcpm;
};

#endif /* QORIQ_PERF_H */
