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

N = 9.
inFile = '/Users/Branch/Documents/Academic/Year 1/Entry Summer/Code/DES/Data/run.csv'
outFile = '/Users/Branch/Documents/Academic/Year 1/Entry Summer/Code/DES/Data/graph.pdf'
sep = 10

#****************************************************************************
#																			*
#	Function:	main														*
#																			*
#	Purpose:	To process and plot the specified utilization data 			*
#																			*
#****************************************************************************

def main():
	
	np.set_printoptions(formatter={'float': lambda x: "{0:0.3f}".format(x)})

	tasks = []
	x,y,z = [],[],[]
	x,y,z = getData()
	
	tasks.append(x)
	tasks.append(y)
	tasks.append(z)

		
	myColors = ['b','r','g']
	myLegend = ['A','B','C','D','E','F','G']
	t = np.linspace(0,sep*(N-1),N)
	print(t)
	
	plt.figure("Utilization")
	plt.xlabel("Time (min)")
	plt.ylabel("Utilization (%)")
	
	for i in range(len(tasks)):
		plt.bar(t, tasks[i], 
			width = sep,
			bottom = np.sum(tasks[:i], axis = 0),
			color = myColors[i % len(myColors)])
	
	plt.ylim(0,110)
	plt.xlim(0,sep*N)
	plt.xticks(np.arange(0, sep*(N+1), sep))
	plt.legend(myLegend,loc='upper right')
	plt.plot((30, 30), (0, 110), 'm--')
	plt.plot((60, 60), (0, 110), 'm--')
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
	x,y,z = [],[],[]
	for row in reader:
		x.append(float(row[1]))
		y.append(float(row[2]))
		z.append(float(row[3]))
	return x,y,z

def roundup(x):
	return int(math.ceil(x/10.0))*10

# Forward declaration
if __name__ == '__main__': main()