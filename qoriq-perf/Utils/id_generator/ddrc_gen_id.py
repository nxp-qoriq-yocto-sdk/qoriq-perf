#!/usr/bin/env python

import sys
import ddrc_gen_lib

# DDR Complex Event group ID
ddrComplexGrp = 0xc0000000
ddrComplexFilteringBit = 0x04000000
srcIDShift = 18 
srcIDMaskShift = 10

# usage ddrc_id.py ddrCntlr hitOrMiss sourceID sourceIDMask enableFilter
#		
#	ddrCntlr     -- DDR controller (e.g, 1 or 2 for P5020)
#	hitOrMiss    -- "Hit" or "Miss"
#	sourceID     -- hex number (with 0x prefix) filter source ID (8 bits) 
#	sourceIDMask -- hex number (with 0x prefix) indicating which bit are cared (8 bits)
#	enableFilter -- 1 or 0 indicating whether the filter is enabled

ddrControl = sys.argv[1]
hitMiss = sys.argv[2]
srcID = int(sys.argv[3],0)
srcMask = int(sys.argv[4],0)
enableFilter = sys.argv[5]

debug = 1

perfEventID = ddrc_gen_lib.generateEventID(ddrControl,hitMiss, srcID, srcMask,
			enableFilter, debug)

print "r%x" % int(perfEventID)
	
