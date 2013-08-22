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
#ifndef QORIQ_CNTRS_H
#define QORIQ_CNTRS_H

#include <linux/perf_event.h>
#include "epu_counters.h"

#ifdef EPU_COUNTER_SIZE_16
#undef EPU_COUNTER_SIZE_16
#endif

#ifdef EPU_COUNTER_SIZE_32
#undef EPU_COUNTER_SIZE_32
#endif


/********************************/
/* Global defs*/
/* These defines apply to all processors. Override if necessary in the processor
 * specific section. */
/********************************/
#define QORIQ_EPU_NUM_COUNTERS	32
/* the following define refers to the high order virtual (SW) counter*/
#define QORIQ_EPU_V_CNTER_SIZE 32




/******************************/
#if defined (B4860_R1)
/******************************/
#define EPU_COUNTER_SIZE_16 1
#undef QORIQ_CHAINED_COUNTERS

/******************************/
#elif defined (PROCESSOR_B4860)   //default for B4860 is R2
/******************************/
#define EPU_COUNTER_SIZE_32 1
#undef QORIQ_CHAINED_COUNTERS

/******************************/
#elif defined (T4240_R1)
/******************************/
#define EPU_COUNTER_SIZE_16 1
#define QORIQ_CHAINED_COUNTERS 1

/******************************/
#elif defined (PROCESSOR_T4240) //default for T4240 is R2
/******************************/
#define EPU_COUNTER_SIZE_32 1
#undef QORIQ_CHAINED_COUNTERS

/******************************/
#elif defined (P5020)
/******************************/
#define EPU_COUNTER_SIZE_16 1
#define QORIQ_CHAINED_COUNTERS 1

/******************************/
#elif defined (P4080)
/******************************/
#define EPU_COUNTER_SIZE_16 1
#define QORIQ_CHAINED_COUNTERS 1


/******************************/
#elif defined (PROCESSOR_E500) 
/******************************/
#define EPU_COUNTER_SIZE_16 1
#define QORIQ_CHAINED_COUNTERS 1

#else 
#error "Processor Type is not defined"
#endif


/**********************************/
#if defined(EPU_COUNTER_SIZE_16)
/**********************************/
#define QORIQ_EPU_COUNTER_NUM_BITS 16ULL
#define QORIQ_EPU_COUNTER_MASK 0xffff
//delete #define QORIQ_EPU_COUNTER_MAX_VALUE 0xffff
/**********************************/

#elif defined(EPU_COUNTER_SIZE_32)
/**********************************/
#define QORIQ_EPU_COUNTER_NUM_BITS 32ULL
#define QORIQ_EPU_COUNTER_MASK 0xffffffff
// delete #define QORIQ_EPU_COUNTER_MAX_VALUE 0xffffffff
/**********************************/
#endif /* EPU_COUNTER_SIZE_32 */
/**********************************/


/**********************************/
#if defined (QORIQ_CHAINED_COUNTERS)
/**********************************/
/* assume only 2 counters are chained, if there is any chaining */
#define QORIQ_EPU_NUM_CHAINED 2
/* assume only 16 counters are chained */
#define QORIQ_EPU_COUNTER_OF_MASK 0xffff0000


/**********************************/
#else  /* not defined (QORIQ_CHAINED_COUNTERS) */
/**********************************/
#define QORIQ_EPU_NUM_CHAINED 1
#endif   /* QORIQ_CHAINED_COUNTERS */


#define QORIQ_EPU_V_COUNTER_MASK 0x7fffffffffffffffUL
/* The following refers to the total counter size including the virtual (SW)
 * counter appened with the HW counter.
 *
 * Virtual counter = 31 bits + 
 * 						16 bit HW counter * num_chained_counters */
#define QORIQ_EPU_V_COUNTER_NUM_BITS (QORIQ_EPU_V_CNTER_SIZE - 1 + \
							QORIQ_EPU_NUM_CHAINED*QORIQ_EPU_COUNTER_NUM_BITS)
#define QORIQ_EPU_V_COUNTER_MAX_VALUE (1ULL<<QORIQ_EPU_V_COUNTER_NUM_BITS)
#define QORIQ_EPU_V_COUNTER_OVFLOW_VALUE \
						(1ULL<<(QORIQ_EPU_V_COUNTER_NUM_BITS - \
							QORIQ_EPU_COUNTER_NUM_BITS*QORIQ_EPU_NUM_CHAINED))


/* Counter Unit initialization Functions */
int qoriq_cntrs_init(void);
void qoriq_cntrs_remove(void);

int qoriq_cntrs_event_init(struct perf_event *event);
int qoriq_cntrs_add(struct perf_event *event);
void qoriq_cntrs_del(struct perf_event *event);
void qoriq_cntrs_start(struct perf_event *event);
void qoriq_cntrs_stop(struct perf_event *event);
u64 qoriq_cntrs_read(struct perf_event *event);
void qoriq_cntrs_write(struct perf_event *event, u64 val);
void qoriq_cntrs_global_enable(void);
void qoriq_cntrs_global_disable(void);

int qoriq_perf_event_from_id(u64 in_evt_id);

#endif /*QORIQ_CNTRS_H */
