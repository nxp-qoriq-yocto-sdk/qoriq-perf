/*
 * Copyright (C) 2010, 2011, 2012 Freescale Semiconductor, Inc.
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

#include "npc_events.h"
#include "qoriq_raw_events.h"
#include "epu_counters.h"

const struct npc_event npc_event[] = {
		{
			.code = QE_NPC_QWRITE,
			.epu_event_code = NPC_QWRITE,
		},
		{
			.code = QE_NPC_TGT_REGION_FULL,
			.epu_event_code = NPC_TGT_REGION_FULL,
		},
		{
			.code = QE_NPC_TRBFR_FULL,
			.epu_event_code = NPC_TRBFR_FULL,
		},
		{
			.code = QE_NPC_EV_OUT,
			.epu_event_code = NPC_EV_OUT,
		},
		{
			.code = QE_NPC_MMA_DONE,
			.epu_event_code = NPC_MMA_DONE,
		},
};

/* Return a pointer to the npc_event associated with the event_code.
 * Returns 0 if not found.
 */
const struct npc_event *npc_event_from_code( u32 event_code )
{
	const struct npc_event *ev = npc_event;
	static const int NUM_ELEMENTS = sizeof(npc_event)/sizeof(npc_event[0]);
	int i;
	for (i = 0; i<NUM_ELEMENTS; i++) {
		if (ev->code == event_code)
			return ev;
		ev++;
	}
	return 0;
}
