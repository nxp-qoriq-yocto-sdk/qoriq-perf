/*
 * Copyright (C) 2013 Freescale Semiconductor, Inc.
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

#include "qoriq_raw_events.h"
#include "ddr_cmplx_events.h"
#include "qoriq_perf.h"


static inline int is_epu_event(unsigned int evt_num)
{
	int ret = 1;


	if (evt_num < QORIQ_EVENT_EPU_FIRST || 
			evt_num > QORIQ_EVENT_EPU_LAST)
		ret = 0;

	return ret;
}

static inline int is_corenet_event(unsigned int evt_num)
{
	int offset = evt_num - QORIQ_EVENT_BASE_CORENET;
	int ret = 1;
	
	if (evt_num < QORIQ_EVENT_CORENET_FIRST || 
			evt_num > QORIQ_EVENT_CORENET_LAST)
		ret = 0;

	/* check the unsupported "gaps" */
	if (offset == 67 ||
		(offset > 75 && offset < 80 ) ||
		(offset > 82 && offset < 84 ) ||
		(offset > 91 && offset < 96 ) ||
		(offset > 103 && offset < 128 ) ||
		(offset > 130 && offset < 132 ) ||
		(offset > 139 && offset < 144 ) ||
		(offset > 146 && offset < 148 ) ||
		(offset > 155 && offset < 160 ))
		ret = 0;

	return ret;
}

static inline int is_datapath_event(unsigned int evt_num)
{
	int offset = evt_num - QORIQ_EVENT_BASE_DATAPATH;
	int ret = 1;
	
	if (evt_num < QORIQ_EVENT_DATAPATH_FIRST || 
			evt_num > QORIQ_EVENT_DATAPATH_LAST)
		ret = 0;

	/* check the unsupported "gaps" */
	if (    (offset > 15  && offset < 47) ||	
			(offset > 174 && offset < 192) ||	
			(offset > 223 && offset < 234) ||	
			(offset > 242 && offset < 247) ||	
			(offset > 251 && offset < 264) ||
			(offset > 273 && offset < 276) ||
			(offset > 319 && offset < 330) ||	
			(offset > 338 && offset < 343) ||	
			(offset > 347 && offset < 352) ||	
			(offset > 382 && offset < 384) ||	
			(offset > 391 && offset < 401) ||	
			(offset > 414 && offset < 426) ||	
			(offset > 434 && offset < 439) ||	
			(offset > 443 && offset < 448) ||	
			(offset > 478 && offset < 488) ||	
			(offset > 489 && offset < 522) ||	
			(offset > 530 && offset < 535) ||	
			(offset > 539 && offset < 544) ||	
			(offset > 547 && offset < 552) ||	
			(offset > 579 && offset < 584) ||	
			(offset > 606 && offset < 608) ||	
			(offset > 611 && offset < 616) ||	
			(offset > 638 && offset < 640) ||	
			(offset > 643 && offset < 648) ||	
			(offset > 670 && offset < 676) ||	
			(offset > 694 && offset < 715) ||	
			(offset > 727 && offset < 736))	
		ret = 0;
	
	return ret;
}


static inline int is_ddr_event(unsigned int evt_num)
{
	int offset = evt_num - QORIQ_EVENT_BASE_DDR;
	int ret = 1;
	
	if (evt_num < QORIQ_EVENT_DDR_FIRST || 
			evt_num > QORIQ_EVENT_DDR_LAST)
		ret = 0;

	if ((offset > 5 && offset < 256 ) ||
		(offset > 261 && offset < 512) ||
		(offset > 517 && offset < 768))
		ret = 0;

	return ret;
}


static inline int is_npc_event(unsigned int evt_num)
{
	int ret = 1;
	
	if (evt_num < QORIQ_EVENT_NPC_FIRST || 
			evt_num > QORIQ_EVENT_NPC_LAST)
		ret = 0;

	return ret;
}


static inline int is_ddr_cmplx_event(unsigned int evt_num)
{
	int ret = 0;
	
	/* note that logic needs to be slightly modified from 
	 * other versions of this function
	 */
	/* non-filtered events */
	if (evt_num >= QORIQ_EVENT_DDR_COMPLEX_FIRST && 
			evt_num <= QORIQ_EVENT_DDR_COMPLEX_LAST)
		ret = 1;

	/* filtered events */
	if (evt_num & DDR_CMPLX_SRC_FILTER_BIT) {
		
		if ((evt_num >= (QORIQ_EVENT_DDR_COMPLEX_FIRST | 
								DDR_CMPLX_SRC_FILTER_BIT)) &&
		(evt_num <= (QORIQ_EVENT_DDR_COMPLEX_LAST |
					DDR_CMPLX_SRC_FILTER_BIT |
					DDR_CMPLX_SRC_ID_MASK |
					DDR_CMPLX_SRC_ID_MSK_MASK)))
			ret = 1;
	}

	return ret;
}

int qoriq_is_valid_event(unsigned int evt_num)
{
	/* this will handle most cases */
	if ((evt_num < QORIQ_EVENT_BASE_START) ||
		(evt_num > QORIQ_EVENT_BASE_END))
		return 0;
	
	if (is_epu_event(evt_num) ||
		is_corenet_event(evt_num) ||
		is_datapath_event(evt_num) ||
		is_ddr_event(evt_num) ||
		is_npc_event(evt_num) ||
		is_ddr_cmplx_event(evt_num))
		return 1;
		
	return 0;
}

