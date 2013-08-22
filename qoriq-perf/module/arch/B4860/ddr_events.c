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

#include <linux/io.h>

#include "ddr_events.h"
#include "qoriq_raw_events.h"
#include "epu_counters.h"
#include "qoriq_perf.h"
#include "ccsr_ddr_v1.h"

/* maintains information on each sub-device managed by the driver */
extern struct dbg_devices dbg_dev;

/* Table of DDR event mappings */
const struct ddr_event ddr_event[] = {
		{
			.code = QE_DDR1_READ_CYCLES,
			.dev_index = 0,
			.epu_event_code = DDR1_0,
		},
		{
			.code = QE_DDR1_WRITE_CYCLES,
			.dev_index = 0,
			.epu_event_code = DDR1_1,
		},
		{
			.code = QE_DDR1_PAGE_CLOSING_NON_REFRESH,
			.dev_index = 0,
			.epu_event_code = DDR1_2,
		},
		{
			.code = QE_DDR1_PAGE_CLOSING,
			.dev_index = 0,
			.epu_event_code = DDR1_3,
		},
		{
			.code = QE_DDR1_PAGE_CLOSING_COLLISION,
			.dev_index = 0,
			.epu_event_code = DDR1_4,
		},
		{
			.code = QE_DDR1_DIVIDE_BY_4_DDRC_CLOCK_PULSE,
			.dev_index = 0,
			.epu_event_code = DDR1_5,
		},
/*		{
			.code = QE_DDR1_MISC_PERFMON,
			.dev_index = 0,
			.epu_event_code = DDR1_,
		},
		{
			.code = QE_DDR1_FIFO_OVERFLOW,
			.dev_index = 0,
			.epu_event_code = DDR1_,
		},
*/		
	
		{
			.code = QE_DDR2_READ_CYCLES,
			.dev_index = 1,
			.epu_event_code = DDR2_0,
		},
		{
			.code = QE_DDR2_WRITE_CYCLES,
			.dev_index = 1,
			.epu_event_code = DDR2_1,
		},
		{
			.code = QE_DDR2_PAGE_CLOSING_NON_REFRESH,
			.dev_index = 1,
			.epu_event_code = DDR2_2,
		},
		{
			.code = QE_DDR2_PAGE_CLOSING,
			.dev_index = 1,
			.epu_event_code = DDR2_3,
		},
		{
			.code = QE_DDR2_PAGE_CLOSING_COLLISION,
			.dev_index = 1,
			.epu_event_code = DDR2_4,
		},

		{
			.code = QE_DDR2_DIVIDE_BY_4_DDRC_CLOCK_PULSE,
			.dev_index = 1,
			.epu_event_code = DDR2_5,
		},
/*		{
			.code = QE_DDR2_MISC_PERFMON,
			.dev_index = 1,
			.epu_event_code = DDR2_,
		},
		{
			.code = QE_DDR2_FIFO_OVERFLOW,
			.dev_index = 1,
			.epu_event_code = DDR2_,
		},
*/
		/* B4860 only uses 2 ddr controllers
		
		{
			.code = QE_DDR3_READ_CYCLES,
			.dev_index = 2,
			.epu_event_code = DDR3_0,
		},
		{
			.code = QE_DDR3_WRITE_CYCLES,
			.dev_index = 2,
			.epu_event_code = DDR3_1,
		},
		{
			.code = QE_DDR3_PAGE_CLOSING_NON_REFRESH,
			.dev_index = 2,
			.epu_event_code = DDR3_2,
		},
		{
			.code = QE_DDR3_PAGE_CLOSING,
			.dev_index = 2,
			.epu_event_code = DDR3_3,
		},
		{
			.code = QE_DDR3_PAGE_CLOSING_COLLISION,
			.dev_index = 2,
			.epu_event_code = DDR3_4,
		},

		{
			.code = QE_DDR3_DIVIDE_BY_4_DDRC_CLOCK_PULSE,
			.dev_index = 2,
			.epu_event_code = DDR3_5,
		}, 
		{
			.code = QE_DDR3_MISC_PERFMON,
			.dev_index = 1,
			.epu_event_code = DDR2_,
		},
		{
			.code = QE_DDR3_FIFO_OVERFLOW,
			.dev_index = 1,
			.epu_event_code = DDR2_,
		},	
		{
			.code = QE_DDR4_READ_CYCLES,
			.dev_index = 3,
			.epu_event_code = DDR4_0,
		},
		{
			.code = QE_DDR4_WRITE_CYCLES,
			.dev_index = 3,
			.epu_event_code = DDR4_1,
		},
		{
			.code = QE_DDR4_PAGE_CLOSING_NON_REFRESH,
			.dev_index = 3,
			.epu_event_code = DDR4_2,
		},
		{
			.code = QE_DDR4_PAGE_CLOSING,
			.dev_index = 3,
			.epu_event_code = DDR4_3,
		},
		{
			.code = QE_DDR4_PAGE_CLOSING_COLLISION,
			.dev_index = 3,
			.epu_event_code = DDR4_4,
		},

		{
			.code = QE_DDR4_DIVIDE_BY_4_DDRC_CLOCK_PULSE,
			.dev_index = 3,
			.epu_event_code = DDR4_5,
		}, 
		{
			.code = QE_DDR4_MISC_PERFMON,
			.dev_index = 2,
			.epu_event_code = DDR4_,
		},
		{
			.code = QE_DDR4_FIFO_OVERFLOW,
			.dev_index = 2,
			.epu_event_code = DDR4_,
		}, 
*/
};

/* Return a pointer to the ddr_event associated with the event_code.
 * Returns 0 if not found.
 */
const struct ddr_event *ddr_event_from_code( u32 event_code )
{
	const struct ddr_event *ev = ddr_event;
	static const int NUM_ELEMENTS = sizeof(ddr_event)/sizeof(ddr_event[0]);
	int i;
	for (i = 0; i<NUM_ELEMENTS; i++) {
		if (ev->code == event_code)
			return ev;
		ev++;
	}
	return 0;
}

NOINLINE void qoriq_ddr_enable_events(u32 ddr_cntlr_ind, int enable)
{
	/* DDR - TPEN  */
	static const u32 enable_val = 0x00000003;
	static const u32 disable_val = 0x0;
	u32 debug19_val;

	debug19_val = in_be32(DDR_C_REG_PTR(debug_19));


    if (enable) {
    	out_be32(DDR_REG_PTR(ddr_cntlr_ind, ddicr0), enable_val);
    	debug19_val |= (0x1 << DDR_C_DBG19_PRF_EN_OVRD_SHIFT);
    }
    else {
    	out_be32(DDR_REG_PTR(ddr_cntlr_ind, ddicr0), disable_val);
    	debug19_val &= ~DDR_C_DBG19_PRF_EN_OVRD_MASK;
    }

	out_be32(DDR_C_REG_PTR(debug_19), debug19_val);
}
