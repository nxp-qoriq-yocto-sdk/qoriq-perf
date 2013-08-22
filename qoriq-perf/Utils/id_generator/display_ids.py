#!/usr/bin/env python

import sys
import ddrc_gen_lib


e500eventSources = [                                                      
	[ "PCI1", 0x0 ],  # PCI Express 1
	[ "PCI2", 0x1 ],  # 
	[ "PCI3", 0x2 ],  # 
	[ "PCI4", 0x3 ],  # 
	[ "SRIO1", 0x08 ],  # 
	[ "SRIO2", 0x09 ],  # 
	[ "BMANControl", 0x18 ],  # 
	[ "PAMU", 0x1C ],  # 
	[ "PME", 0x20 ],  # 
	[ "SEC4_2", 0x21 ],  # 
	[ "QMANControl", 0x3C ],  # 
	[ "USB1", 0x40 ],  # 
	[ "USB2", 0x41 ],  # 
	[ "eSDHC", 0x44 ],  # 
	[ "PBL", 0x48 ],  # 
	[ "NPC", 0x4B ],  # 
	[ "RIO", 0x5D ],  # 
	[ "SATA1", 0x60 ],  # 
	[ "SATA2", 0x61 ],  # 
	[ "DMA1", 0x70 ],  # 
	[ "DMA2", 0x71 ],  # 
	[ "CORE0_I", 0x80 ],  # 
	[ "CORE0_D", 0x81 ],  # 
	[ "CORE1_I", 0x82 ],  # 
	[ "CORE1_D", 0x83 ],  # 
	[ "FMAN_XAUI", 0xC0 ],  # 
	[ "FMAN_OFF_H1", 0xC1 ],  # 
	[ "FMAN_OFF_H2", 0xC2 ],  # 
	[ "FMAN_OFF_H3", 0xC3 ],  # 
	[ "FMAN_OFF_H4", 0xC4 ],  # 
	[ "FMAN_OFF_H5", 0xC5 ],  # 
	[ "FMAN_OFF_H6", 0xC6 ],  # 
	[ "FMAN_OFF_H7", 0xC7 ],  # 
	[ "FMAN_GE1", 0xC8 ],  # 
	[ "FMAN_GE2", 0xC9 ],  # 
	[ "FMAN_GE3", 0xCA ],  # 
	[ "FMAN_GE4", 0xCB ],  # 
	[ "FMAN_GE5", 0xCC ],  # 
]  

for source in e500eventSources:
	for DDR_cont in range(1, 3):
		for hitMiss in ['Hit', 'Miss']:
			perfEventID = ddrc_gen_lib.generateEventID(DDR_cont,hitMiss, source[1], 0xFF, 1)
			print "Source: {} ({}), DDR{} {} {}".format(source[0], hex(int(source[1])),DDR_cont,hitMiss, hex(perfEventID))

#print "r%x" % int(perfEventID)
	
