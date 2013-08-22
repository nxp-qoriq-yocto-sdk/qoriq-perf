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

/* we use asserts for the test case - force it on */
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

/* Since this is user-space test of kernel code
 * we typedef the types here instead of polluting
 * the module code.
 */
typedef uint32_t u32;
typedef uint8_t u8;

#include "ccsr_fman_v1.h"
#include "ccsr_qman_v1.h"
#include "dcsr_corenet_v1.h"
#include "dcsr_cpu_v1.h"
#include "dcsr_ddr_v1.h"
#include "dcsr_dpaa_v1.h"
#include "dcsr_dpaa_v2.h"
#include "dcsr_epu_v1.h"
#include "dcsr_epu_v2.h"
#include "dcsr_nal_v1.h"
#include "dcsr_npc_v1.h"
#include "dcsr_nxc_v1.h"
#include "dcsr_ocn_v1.h"
#include "dcsr_rcpm_v1.h"
#include "pmr_cpu_v1.h"

/* this function will be generated */
#include "testmasks.h"

/* Test the same structure that will be used in the actual code
 */
struct dbg_device {
	/* index number for this device */
	int index;
	/* mapped memory address */
	void *mem_ptr;
};

#define N_CPUS 2

/* maintains information on each sub-device managed by the driver */
struct dbg_devices {
	struct dbg_device cpu[N_CPUS];
	struct dbg_device epu;
} dbg_dev;

void testptr()
{
	struct epu epu;
	struct core_proxy cpu[N_CPUS];

	dbg_dev.cpu[0].mem_ptr = &cpu[0];
	dbg_dev.cpu[1].mem_ptr = 0;

	dbg_dev.epu.mem_ptr = &epu;

	/* valid ptr */
	assert(EPU_REG_PTR_VALID);

	/* valid ptr */
	assert(CPU_REG_PTR_VALID(0));

	/* invalid ptr */
	assert(!CPU_REG_PTR_VALID(1));

	printf("qoriq-common PTR macro test complete\n");
}

/* test some FMAN addresses */
void run_test_fman_mmap()
{
	struct fman *p;
	p = 0;

	assert( (uint32_t)&p->key_gen.dJtK[0][0].cr == 0x000c1210 );
	assert( (uint32_t)&p->key_gen.dJtK[0][1].cr == 0x000c1220 );
	assert( (uint32_t)&p->key_gen.dJtK[0][2].cr == 0x000c1230 );
	assert( (uint32_t)&p->key_gen.dJtK[0][3].cr == 0x000c1240 );
	assert( (uint32_t)&p->key_gen.dJtK[0][4].cr == 0x000c1250 );
	assert( (uint32_t)&p->key_gen.dJtK[1][0].cr == 0x000c1260 );
}

void run_test_dpaa_v2_mmap()
{
	struct dpaa_v2 *p;
	p = 0;

	assert( (uint32_t)&p->fmhsr1 == 0x28 );
	assert( (uint32_t)&p->reserved4[0] == 0x1c8 );
	assert( (uint32_t)&p->dpqoer[0] == 0x500 );
	assert( (uint32_t)&p->dpgpcmp[0].ccr == 0x580 );
	assert( (uint32_t)&p->dpepgcr == 0x5c0 );
	assert( (uint32_t)&p->reserved8[0] == 0x5d0 );
	assert( (uint32_t)&p->dpckstpcr == 0x5fc );
	assert( (uint32_t)&p->reserved10[0] == 0x720 );
	assert( (uint32_t)&p->dpspgcrb[3] == 0x79c );
	assert( (uint32_t)&p->dptarm == 0x800 );
	assert( (uint32_t)&p->dptftcr[0] == 0x820 );
	assert( (uint32_t)&p->dptftcr[3] == 0x82c );
	assert( (uint32_t)&p->dpwmsk == 0x900 );
	assert( (uint32_t)&p->dpctdcr == 0xA04 );
}

int main(int argc, char **argv)
{

	/* test the pointer macros */
	testptr();

	/* test the masks and shift values */
	run_testmasks();

	/* test some FMAN addresses */
	run_test_fman_mmap();

	/* test some DPAA addresses */
	run_test_dpaa_v2_mmap();

	printf("qoriq-common ALL complete\n");
	return 0;
}
