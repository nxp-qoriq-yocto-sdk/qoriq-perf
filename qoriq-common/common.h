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

#ifndef QORIQ_COMMON_H
#define QORIQ_COMMON_H

#include <linux/types.h>

#ifndef PACKED
#define PACKED __attribute__ ((__packed__))
#endif

/* Compile time assert. This doesn't compile if a is false.
 * Used to check struct sizes at compile-time.
 */
#define CTASSERT(a) extern char __dummy[(a) ? 1 : -1]

/* Access to specific device registers */
#define CNDC1_REG_PTR(x) (&((struct cndc_1 *)dbg_dev.cndc1.mem_ptr)->x)
#define CNDC2_REG_PTR(x) (&((struct cndc_2 *)dbg_dev.cndc2.mem_ptr)->x)
#define EPU_REG_PTR(x) (&((struct epu *)dbg_dev.epu.mem_ptr)->x)
#define DDR_REG_PTR(i, x) (&((struct ddr *)dbg_dev.ddr[i].mem_ptr)->x)
#define DDR_C_REG_PTR(x) (&((struct ccsr_memctrl *)dbg_dev.memctrl.mem_ptr)->x)
#define DPAA_REG_PTR(x) (&((struct dpaa *)dbg_dev.dpaa.mem_ptr)->x)
#define FMAN_REG_PTR(i, x) (&((struct fman *)dbg_dev.fman[i].mem_ptr)->x)
#define NAL_REG_PTR(x) (&((struct nal *)dbg_dev.nal.mem_ptr)->x)
#define NPC_REG_PTR(x) (&((struct npc *)dbg_dev.npc.mem_ptr)->x)
#define NXC_REG_PTR(x) (&((struct nxc *)dbg_dev.nxc.mem_ptr)->x)
#define OCN_REG_PTR(x) (&((struct ocn *)dbg_dev.ocn.mem_ptr)->x)
#define CPU_REG_PTR(i, x) (&((struct core_proxy *)dbg_dev.cpu[i].mem_ptr)->x)
#define RCPM_REG_PTR(x) (&((struct rcpm *)dbg_dev.rcpm.mem_ptr)->x)

/* Check for null ptrs */
#define CNDC1_REG_PTR_VALID (dbg_dev.cndc1.mem_ptr != 0)
#define CNDC2_REG_PTR_VALID (dbg_dev.cndc2.mem_ptr != 0)
#define EPU_REG_PTR_VALID (dbg_dev.epu.mem_ptr != 0)
#define DDR_REG_PTR_VALID(i) (dbg_dev.ddr[i].mem_ptr != 0)
#define DPAA_REG_PTR_VALID (dbg_dev.dpaa.mem_ptr != 0)
#define FMAN_REG_PTR_VALID(i) (dbg_dev.fman[i].mem_ptr != 0)
#define NAL_REG_PTR_VALID (dbg_dev.nal.mem_ptr != 0)
#define NPC_REG_PTR_VALID (dbg_dev.npc.mem_ptr != 0)
#define NXC_REG_PTR_VALID (dbg_dev.nxc.mem_ptr != 0)
#define OCN_REG_PTR_VALID (dbg_dev.ocn.mem_ptr != 0)
#define CPU_REG_PTR_VALID(i) (dbg_dev.cpu[i].mem_ptr != 0)
#define RCPM_REG_PTR_VALID (dbg_dev.rcpm.mem_ptr != 0)

#endif /* QORIQ_COMMON_H */
