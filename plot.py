#****************************************************************************
#																			*
#	File:		plot.py														*
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
import math
import csv

# Global variables

N = 10.
inFile = '/Users/Branch/Documents/Academic/Year 1/Entry Summer/Code/DES/Data/run.csv'
outFile = '/Users/Branch/Documents/Academic/Year 1/Entry Summer/Code/DES/Data/graph.pdf'

#****************************************************************************
#																			*
#	Function:	main														*
#																			*
#	Purpose:	To process and plot the specified utilization data 			*
#																			*
#****************************************************************************

def main():
	
	tasks = []
	for i in range(0,3):
		tasks.append(processData(i))	
	
	myColors = ['b','r','g']
	myLegend = ['A','B','C','D','E','F','G']
	t = np.linspace(0,sep*(N-1),N)

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
#		if int(row[2]) == tp or int(row[2]) == -1:
		x.append(float(row[0]))
		y.append(int(row[1]))
		z.append(int(row[2]))
	return x,y,z

def roundup(x):
	return int(math.ceil(x/10.0))*10
	
#****************************************************************************
#																			*
#	Function:	processData													*
#																			*
#	Purpose:	To process utilization data of the specified type			*
#																			*
#****************************************************************************

def processData(tp):
	global sep
	time, util, type = getData()
	sep = roundup(time[-1])/N
	results = []
	beginInt = 0
	endInt = sep
	
	while endInt <= sep*N:
		i = 0
		busy = 0
#		print("Interval: (%d, %d)" %(beginInt,endInt))
		
		while i != len(time) and time[i] <= beginInt:
			i = i + 1
#		print("\t\t i = %d, busy = %.2f" %(i,busy))					# 1
		
		if i == len(time):
			results.append(busy/sep*100)
#			print("\t\t Reached end.")

		else:
			if time[i] >= endInt and util[i] == 1 and type[i] == tp:
				busy = sep
#			print("\t\t i = %d, busy = %.2f" %(i,busy))				# 2

			if util[i] == 1 and time[i] < endInt and type[i] == tp:
				busy = busy + time[i] - beginInt
			i = i + 1
#			print("\t\t i = %d, busy = %.2f" %(i,busy))				# 3

			while i != len(time) and time[i] < endInt:
				if util[i] == 1 and type[i] == tp:
					busy = busy + time[i] - time[i-1]
				i = i+1
#			print("\t\t i = %d, busy = %.2f" %(i,busy))				# 4
				
			if i != len(time) and time[i-1] < endInt and util[i] == 1 and type[i] == tp:
				busy = busy + endInt - time[i-1]
#			print("\t\t i = %d, busy = %.2f" %(i,busy))				# 5

			results.append(busy/sep*100)

		beginInt = beginInt + sep
		endInt = endInt + sep
#		print("\t\t i = %d, busy = %.2f" %(i,busy))					# 6
	
#	for i in range(0,len(time)):
#			print("(Time, Util): (%.2f, %d)" %(time[i],util[i]))	
	
	return results

# Forward declaration
if __name__ == '__main__': main()