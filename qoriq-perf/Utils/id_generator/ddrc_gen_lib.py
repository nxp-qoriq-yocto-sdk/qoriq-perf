#!/usr/bin/env python

import sys

# DDR Complex Event group ID
ddrComplexGrp = 0xc0000000
ddrComplexFilteringBit = 0x04000000
srcIDShift = 18 
srcIDMaskShift = 10
ddrCntrlShift = 1

################################################################################
# usage ddrc_id.py ddrCntlr hitOrMiss sourceID sourceIDMask enableFilter
#		
#	ddrCntlr     -- DDR controller (e.g, 1 or 2 for P5020); specify in 
#			decimal, not hex format
#	hitOrMiss    -- "Hit" or "Miss"
#	sourceID     -- hex number (with 0x prefix) filter source ID (8 bits) 
#	sourceIDMask -- hex number (with 0x prefix) indicating which bit are 
#			"cared" (8 bits)
#	enableFilter -- "1" or "0" indicating whether the filter is enabled
################################################################################

def generateEventID(ddrControl,hitMiss, srcID, srcMask, enableFilter, debug=0):
 
	if debug:
		print("DDR Controller = %s" % ddrControl)
		print("Hit or Miss = %s" % hitMiss)
		print("Source ID = 0x%x" % srcID)
		print("Source ID Mask = 0x%x" % srcMask)
		print("Enable Filter Bit = %s" % enableFilter)

	# Construct the ID

	perfEventID = ddrComplexGrp
	if debug:
		print("\nBit-field OR-ing")
		print("================")
		print("DDRCmplx   = 0x%08x" % ddrComplexGrp)
	
	if hitMiss == "Miss":
		perfEventID |= 0x1

		if debug:
			print("HitMiss    = 0x%08x" % 1)
	else:
		if debug:
			print("HitMiss    = 0x%08x" % 0)

	ddrCntlrVal = (int(ddrControl) - 1) << ddrCntrlShift
	perfEventID |= ddrCntlrVal

	if debug:
        	print ("ddrCntlr   = 0x%08x" % ddrCntlrVal)

	if enableFilter == "0":
		if debug:
			print("enableFilt = 0x%08x" % 0)
	
		print "r%x" % int(perfEventID)
		sys.exit(0)
	
	perfEventID |= ddrComplexFilteringBit

	if debug:
		print("enableFilt = 0x%08x" % ddrComplexFilteringBit)


	perfEventID |= int(srcID) << srcIDShift
	if debug:
		print("srcID      = 0x%08x" % (int(srcID) << srcIDShift) )

	perfEventID |= int(srcMask) << srcIDMaskShift
	
	if debug:
		print("srcIDMask  = 0x%08x" % (int(srcMask) << srcIDMaskShift) )
		print("perfEventID= 0x%08x" % perfEventID)


	return perfEventID

