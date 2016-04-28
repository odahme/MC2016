# -*- coding: utf-8 -*-
"""
Spyder Editor

This temporary script file is located here:
/home/uzh/mivkov/.spyder2/.temp.py
"""
from pylab import *

ndim = 3
subd = 4
subcubes = subd**ndim

startwert = ([],[],[])

for i in range(0, ndim):
	wartezeit = subd ** i
	stand = 0
	
	for j in range(0, subcubes):
		if wartezeit > 0:
			calc = (stand % subd)/float(subd)
			startwert[i].append(calc)
		else:
			stand+=1
			wartezeit = subd**i
			calc = (stand % subd)/float(subd)
			startwert[i].append(calc)

		wartezeit+=-1

for i in range(len(startwert)):
	print "dimension ", i+1
	print len(startwert[i]), "elemente"
	print startwert[i]

			

