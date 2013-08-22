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

#include <linux/module.h>
#include <linux/err.h>
#include <linux/of_platform.h>
#include <linux/io.h>

#include "qoriq_perf.h"
#include "qoriq_pmu.h"

/* platform_driver operations */
static int driver_probe( struct platform_device * pdev);
static int driver_remove( struct platform_device *pdev);
static int dcsr_probe_success;

const struct of_device_id driver_id[] = {
		{ .compatible = "fsl,dcsr-epu"},
		{},
};
MODULE_DEVICE_TABLE(of, driver_id);

static struct platform_driver pmu_driver = {
		.driver = {
				.name = DRIVER_NAME,
				.owner = THIS_MODULE,
				.of_match_table = driver_id,
		},
		.probe = driver_probe,
		.remove = driver_remove,
};

/* maintains information on each sub-device managed by the driver */
struct dbg_devices dbg_dev;

static struct device_node *dbgfs_map_fqcompatible(const char *compatible,
		struct device_node *from,
		const char *type,
		int instance,
		struct dbg_device *dev_ptr)
{
	struct device_node *np;
	
	np = of_find_compatible_node(from, type, compatible);
	if (np) {
		dev_ptr->mem_ptr = of_iomap(np, instance);
		dev_ptr->np = np;
	} else {
		dev_ptr->mem_ptr = 0;
		dev_ptr->np = 0;
	}
	return np;
}

#define DBGFS_MAP_FROM_COMPATIBLE(compatible, from, dev_ptr) \
		dbgfs_map_fqcompatible(compatible, from, NULL, 0, dev_ptr)

#define DBGFS_MAP_COMPATIBLE(compatible, dev_ptr) \
		dbgfs_map_fqcompatible(compatible, NULL, NULL, 0, dev_ptr)

static void dbgfs_unmap( struct dbg_device *dev_ptr)
{
	if (dev_ptr->mem_ptr) {
		iounmap(dev_ptr->mem_ptr);
		dev_ptr->mem_ptr = 0;
	}
}

static void map_devices(void)
{
	int i;
	struct device_node *np;
	
	DBGFS_MAP_COMPATIBLE("fsl,dcsr-corenet", &dbg_dev.cndc1);
	/* map the second corenet range */
	dbgfs_map_fqcompatible("fsl,dcsr-corenet", NULL, NULL, 1,
			&dbg_dev.cndc2);
	DBGFS_MAP_COMPATIBLE("fsl,dcsr-dpaa", &dbg_dev.dpaa);
	DBGFS_MAP_COMPATIBLE("fsl,dcsr-epu", &dbg_dev.epu);
	DBGFS_MAP_COMPATIBLE("fsl,dcsr-nxc", &dbg_dev.nxc);
	DBGFS_MAP_COMPATIBLE("fsl,dcsr-ocn", &dbg_dev.ocn);
	DBGFS_MAP_COMPATIBLE("fsl,qman", &dbg_dev.qman);

	DBGFS_MAP_COMPATIBLE("fsl,qoriq-memory-controller", &dbg_dev.memctrl);	
	
		
	/* start at the top (NULL) and search for
	 * at most MAX_NUM_DDR ddr devices
	 */
	np = NULL;
	for (i = 0; i < MAX_NUM_DDR; ++i) {
		np = DBGFS_MAP_FROM_COMPATIBLE("fsl,dcsr-ddr", np, &dbg_dev.ddr[i]);
		if (!np)
			break;
	}
	/* start at the top (NULL) and search for
	 *  at most MAX_NUM_FMAN fman devices
	 */
	np = NULL;
	for (i = 0; i < MAX_NUM_FMAN; ++i) {
		np = DBGFS_MAP_FROM_COMPATIBLE("fsl,fman", np, &dbg_dev.fman[i]);
		if (!np)
			break;
	}
	
}

static void unmap_devices(void)
{
	int i;

	dbgfs_unmap(&dbg_dev.cndc1);
	dbgfs_unmap(&dbg_dev.cndc2);
	dbgfs_unmap(&dbg_dev.dpaa);
	dbgfs_unmap(&dbg_dev.epu);
	dbgfs_unmap(&dbg_dev.nxc);
	dbgfs_unmap(&dbg_dev.ocn);
	dbgfs_unmap(&dbg_dev.qman);
	dbgfs_unmap(&dbg_dev.epu);
	dbgfs_unmap(&dbg_dev.memctrl);

	for (i = 0; i < MAX_NUM_DDR; ++i)
		dbgfs_unmap(&dbg_dev.ddr[i]);
	
	for (i = 0; i < MAX_NUM_FMAN; ++i)
		dbgfs_unmap(&dbg_dev.fman[i]);
}

static int driver_probe( struct platform_device * pdev)
{
	int ret = -ENOMEM;

	/* Map devices from the device tree  */
	map_devices();

	/* add support for perf events via a PMU */
	ret = qoriq_pmu_init();
	if (ret)
		goto err_out;

	dcsr_probe_success = 1;
	return ret;

err_out:
	unmap_devices();
	dcsr_probe_success = 0;

	return ret;
}

static int driver_remove( struct platform_device *pdev)
{
	if (dcsr_probe_success) {
		qoriq_pmu_remove();
		unmap_devices();
	}

	return 0;
}

/*
 * Load and unload the perf pmu driver
 */
static int __init pmu_driver_init(void)
{	
	return platform_driver_register(&pmu_driver);
}
module_init(pmu_driver_init);

static void __exit pmu_driver_exit(void)
{
	platform_driver_unregister(&pmu_driver);
}
module_exit(pmu_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("freescale.com");
MODULE_DESCRIPTION("QorIQ Performance Monitoring Unit");
MODULE_SUPPORTED_DEVICE("Freescale QorIQ P4080 P4040 P3041 P5010 P5020");
