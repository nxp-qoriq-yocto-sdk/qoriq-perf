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

#include <linux/interrupt.h>
#include <linux/hardirq.h>
#include <linux/perf_event.h>
#include <linux/io.h>

#include "qoriq_pmu.h"
#include "qoriq_cntrs.h"
#include "qoriq_raw_events.h"
#include "qoriq_perf.h"

/*
 * If interrupts were soft-disabled when a PMU interrupt occurs, treat
 * it as an NMI.
 */
static inline int perf_intr_is_nmi(struct pt_regs *regs)
{
#ifdef __powerpc64__
	return !regs->softe;
#else
	return 0;
#endif
}

/* FUNCTIONS related to the operations of the PMU */

/*
 * The pmu_read() acquires the count from the hw counter
 * and adjusts the pef_event counters with the values.
 */
static void qoriq_pmu_read(struct perf_event *event)
{
	s64 val, delta, prev;

	if (event->hw.state & PERF_HES_STOPPED)
		return;

	/*
	 * Performance monitor interrupts come even when interrupts
	 * are soft-disabled, as long as interrupts are hard-enabled.
	 * Therefore we treat them like NMIs.
	 */
	do {
		prev = local64_read(&event->hw.prev_count);
		barrier();
		val = qoriq_cntrs_read(event);
	} while (local64_cmpxchg(&event->hw.prev_count, prev, val) != prev);

	delta = (val - prev) & QORIQ_EPU_V_COUNTER_MASK;

	local64_add(delta, &event->count);
	local64_sub(delta, &event->hw.period_left);

}

/*
 * This function is called whenever the perf_event comes into "scope".
 * Since the physical counter may have been used for other purposes,
 * all configuration needed to setup the counter needs to be performed
 * on each qoriq_pmu_add call.
 */
static noinline int qoriq_pmu_add(struct perf_event *event, int flags)
{
	u64 val;
	u64 left;
	int ret;

	/* allow add/del on events */
	perf_pmu_disable(event->pmu);

	/*
	 * Look for an available counter for this event type
	 */
	ret = qoriq_cntrs_add(event);
	if (ret) {
		
		if (ret == 0x10000000)
			ret = 0;
		
		goto out;
	}
	
	val = 0;
	if (event->hw.sample_period) {
		/* adjust for the sampling period */
		left = local64_read(&event->hw.period_left);
		if (left < QORIQ_EPU_V_COUNTER_MAX_VALUE)
		val = QORIQ_EPU_V_COUNTER_MAX_VALUE - left;
		else {
			printk(KERN_ERR "UNEXPECTED: left (0x%llx) > EPU_V_MAX (0x%llx)\n", left, QORIQ_EPU_V_COUNTER_MAX_VALUE);
		}
	}
	local64_set(&event->hw.prev_count, val);

	if (!(flags & PERF_EF_START)) {
		event->hw.state = PERF_HES_STOPPED | PERF_HES_UPTODATE;
		val = 0;
	}

	qoriq_cntrs_write(event, val);
	perf_event_update_userpage(event);

	if (flags && PERF_EF_START)
	qoriq_cntrs_start(event);
	else
	printk(KERN_ERR "UNEXPECTED: Perf flag not what was expected\n");

	ret = 0;
out:
	perf_pmu_enable(event->pmu);
	return ret;
}

/*
 * This function is called whenever the perf_event goes out of "scope".
 * Since the physical counter may have been used for other purposes, the
 * counter is stopped and its value is read and stored. Its optional
 * whether the counter is reset or not.
 */
static void qoriq_pmu_del(struct perf_event *event, int flags) 
{
	perf_pmu_disable(event->pmu);

	if (event->hw.idx < 0)
		goto out;

	qoriq_pmu_read(event);
	qoriq_cntrs_del(event);

out:
	perf_pmu_enable(event->pmu);
	return;
}

static void qoriq_pmu_enable(struct pmu *pmu)
{
	qoriq_cntrs_global_enable();
}

static void qoriq_pmu_disable(struct pmu *pmu)
{
	qoriq_cntrs_global_disable();
}

static void qoriq_pmu_start(struct perf_event *event, int ef_flags) {
	unsigned long flags;
	s64 left;

	if (event->hw.idx < 0 || !event->hw.sample_period)
		return;

	if (!(event->hw.state & PERF_HES_STOPPED))
		return;
	else {
		printk	(KERN_ERR "UNEXPECTED event state.\n");
	}
	
	if (ef_flags & PERF_EF_RELOAD)
		WARN_ON_ONCE(!(event->hw.state & PERF_HES_UPTODATE));

	local_irq_save(flags);
	perf_pmu_disable(event->pmu);

	event->hw.state = 0;
	left = local64_read(&event->hw.period_left);

	qoriq_cntrs_write(event, left);

	perf_event_update_userpage(event);
	perf_pmu_enable(event->pmu);
	local_irq_restore(flags);
}

static void qoriq_pmu_stop(struct perf_event *event, int ef_flags)
{
	unsigned long flags;

	if (event->hw.idx < 0 || !event->hw.sample_period)
		return;

	if (event->hw.state & PERF_HES_STOPPED) {
		printk(KERN_ERR "state included PERF_HES_STOPPED!!\n");
		return;
	}

	local_irq_save(flags);
	perf_pmu_disable(event->pmu);

	qoriq_pmu_read(event);

	event->hw.state |= PERF_HES_STOPPED | PERF_HES_UPTODATE;
	qoriq_cntrs_write(event, 0);

	perf_event_update_userpage(event);
	perf_pmu_enable(event->pmu);
	local_irq_restore(flags);
}

/*
 * This PMU function is called whenever a new event measurement is required.
 * Purpose is to qualify if this PMU will handle the event.
 */
static int qoriq_pmu_event_init(struct perf_event *event)
{
	int ret;

	/* This PMU only handles RAW events */
	if (event->attr.type != PERF_TYPE_RAW)
		return -ENOENT;

	/* only handle the range of raw event numbers for this PMU */
	if (!qoriq_is_valid_event(event->attr.config))
		return -ENOENT;

	/* do detailed qualification for this event request */
	ret = qoriq_cntrs_event_init(event);
	if (ret)
		return ret;

	/* configure the event sample counts */
	event->hw.last_period = event->hw.sample_period;
	local64_set(&event->hw.period_left, event->hw.last_period);

	return 0;
}

/* defines the PMU operations for the qoriq-pmu */
static struct pmu qoriq_pmu = {
				.pmu_enable = qoriq_pmu_enable,
				.pmu_disable = qoriq_pmu_disable, 
				.event_init = qoriq_pmu_event_init,
				.add = qoriq_pmu_add, 
				.del = qoriq_pmu_del, 
				.start = qoriq_pmu_start, 
				.stop = qoriq_pmu_stop, 
				.read = qoriq_pmu_read, };

/*
 * A counter has overflowed; update its count and record
 * things if requested.  Note that interrupts are hard-disabled
 * here so there is no possibility of being interrupted.
 */
void record_and_restart(struct perf_event *event, u64 val)
{
	u64 period = event->hw.sample_period;
	s64 prev, delta, left;
	int record = 0;
	struct pt_regs *regs;
	int nmi;

	if (event->hw.state & PERF_HES_STOPPED) {
		qoriq_cntrs_write(event, 0);
		return;
	} else {
		printk	(KERN_ERR "UNEXPECTED: Counters not stopped.\n");
	}
	
	regs = get_irq_regs();
	nmi = perf_intr_is_nmi(regs);

	/* we don't have to worry about interrupts here */
	prev = local64_read(&event->hw.prev_count);
	delta = (val - prev) & QORIQ_EPU_V_COUNTER_MASK;
	local64_add(delta, &event->count);

	/*
	 * See if the total period for this event has expired,
	 * and update for the next period.
	 */
	val = 0;
	left = local64_read(&event->hw.period_left) - delta;
	if (period) {
		if (left <= 0) {
			left += period;
			if (left <= 0)
				left = period;
			record = 1;
			event->hw.last_period = event->hw.sample_period;
		}
		if (left < QORIQ_EPU_V_COUNTER_MAX_VALUE)
			val = QORIQ_EPU_V_COUNTER_MAX_VALUE - left;
	}

	qoriq_cntrs_write(event, 0);
	local64_set(&event->hw.prev_count, val);
	local64_set(&event->hw.period_left, left);
	perf_event_update_userpage(event);

	/*
	 * Finally record data if requested.
	 */
	if (record) {
		struct perf_sample_data data;
		perf_sample_data_init(&data, 0, period);
		data.period = event->hw.last_period;

		if (perf_event_overflow(event, &data, regs))
			qoriq_pmu_stop(event, 0);
	}
}

/* PMU Initialization Functions */
/* This gets called at boot time */
int qoriq_pmu_init()
{
	int ret;

	ret = qoriq_cntrs_init();
	if (!ret)
		ret = perf_pmu_register(&qoriq_pmu, QORIQ_PMU_NAME, QORIQ_PMU_TYPE);
	return ret;
}

void qoriq_pmu_remove()
{
	qoriq_cntrs_remove();
	perf_pmu_unregister(&qoriq_pmu);
}
