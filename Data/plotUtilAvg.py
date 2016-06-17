#!/usr/bin/python

#****************************************************************************
#																			*
#	File:		plotUtil.py													*
#																			*
#	Author:		Branch Vincent												*
#																			*
#	Date:		Jun 12, 2016												*
#																			*
#	Purpose:	This file plots the utilization data from a simulation.		*
#																			*
#****************************************************************************
#!/usr/bin/python

# Packages 
from __future__ import nested_scopes,generators,division,absolute_import,with_statement,print_function
import matplotlib.pyplot as plt
import numpy as np
import operator
import math
import csv

# Global variables

numRuns = 100;
inFile = '/Users/Branch/Documents/Academic/Year 1/Entry Summer/Code/DES/Data/run2.csv'
outFile = '/Users/Branch/Documents/Academic/Year 1/Entry Summer/Code/DES/Data/graph2.pdf'
sep = 10

#****************************************************************************
#																			*
#	Function:	main														*
#																			*
#****************************************************************************

def main():

#	Get data

	t, tasks, error = [],[],[]
	t, tasks, error = getData()
	N = roundup(t[-1])/sep

# 	Initialize plot	

	fig, ax = plt.subplots()
	plt.title("Utilization for %d Runs" %numRuns)
	plt.xlabel("Time (min)")
	plt.ylabel("Utilization (%)")

# 	Plot data

	plt.bar(t, tasks, 
			width = sep/2,
			color = 'r',
			align = 'center',
			yerr = error)

# 	Edit plot attributes

	plt.ylim(0,110)
	plt.xlim(0,sep*N)
	plt.xticks(np.arange(0, sep*(N+1), sep))
	
#	fig.autofmt_xdate()
	xticks = ax.xaxis.get_major_ticks()
	for i in range(0,int(N+1),2):
		xticks[i].label1.set_visible(False) #set_ticklabel('')
		
	plt.plot((30, 30), (0, 110), 'k--')
	plt.plot((t[-1]-30, t[-1]-30), (0, 110), 'k--')
	
	plt.savefig(outFile)

#****************************************************************************
#																			*
#	Function:	getData														*
#																			*
#	Purpose:	To get utilization data from the specified csv file 		*
#																			*
#****************************************************************************

def getData():
	reader = csv.reader(open(inFile), delimiter=',')
	header = next(reader)
	t,d,e = [],[],[]
	for row in reader:
		t.append(float(row[0]) + sep/2)
		d.append(float(row[1]))
		e.append(float(row[2]))
	return t,d,e

def roundup(x):
	return int(math.ceil(x/10.0))*10

# Forward declaration
if __name__ == '__main__': main()