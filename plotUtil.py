#****************************************************************************
#																			*
#	File:		plotUtil.py													*
#																			*
#	Author:		Branch Vincent												*
#																			*
#	Date:		Jun 12, 2016												*
#																			*
#	Purpose:	This file plots the utilization data from either one or 	*
#				multiple simulation runs.									*
#																			*
#****************************************************************************

# Packages 

from __future__ import print_function
import matplotlib.pyplot as plt
import numpy as np
import csv

# Global variables

filePath = '/Users/Branch/Documents/Academic/Year 1/Entry Summer/Code/DES/Data/'
numTypes = 9
numRuns = 1
oneRun = True

#****************************************************************************
#																			*
#	Function:	main														*
#																			*
#****************************************************************************

def main():
	
#	Set input and output files
	
	if oneRun:
		inFile = filePath + 'singleRun.csv'
		outFile = filePath + 'singleGraph.pdf'
	else:
		inFile = filePath + 'batchRun.csv'
		outFile = filePath + 'batchGraph.pdf'
	
#	Get and plot data

	time, data, error = getData(inFile)		# time, utilization, std dev
	plotData(time, data, error, outFile)	

#****************************************************************************
#																			*
#	Function:	getData														*
#																			*
#	Purpose:	To get the utilization data from the specified csv file 	*
#																			*
#****************************************************************************

def getData(inputFile):
	
#	Set global variable to change value

	global numRuns
	
#	Initialize csv reader and data arrays

	reader = csv.reader(open(inputFile), delimiter=',')		# Open file
	header = next(reader)									# Skip header line
	time, error = [], []
	data = [[] for i in range(numTypes)]

#	Read csv file, depending on number of runs
	
	if oneRun:										# For one run,
		for row in reader:
			time.append(float(row[0]))				# Add time interval
			for i in range(numTypes):				
				data[i].append(float(row[i+1]))		# Add utilization for each task type
				
	else:											# For multiple runs,
		for row in reader:
			time.append(float(row[0]))				# Add time interval
			data[0].append(float(row[-3]))			# Add avg utilization
			error.append(float(row[-2]))			# Add std dev
			numRuns = len(row) - 4					# Update number of runs

	return time, data, error

#****************************************************************************
#																			*
#	Function:	plotData													*
#																			*
#	Purpose:	To plot the utilization data								*
#																			*
#****************************************************************************

def plotData(time, data, error, outFile):

#	Set variables

	intSize = time[1] - time[0]					# Interval size
	endTime = time[-1] + intSize				# Simulation end time
	endTimes = [30, endTime - 30, endTime]		# Phase end times
	numInts = endTimes[2]/intSize				# Number of intervals
	time[:] = [t + intSize/2 for t in time]		# Adjust to center bars
	
#	Initialize plot parameters

	colors = ['b', 'g', 'r', 'c', 'm', 'y', 'k']
	patterns = ['/', '\\', '|', '-', '+', 'x', 'o', 'O', '.', '*']
	legend = ['0: Communicating', '1: Exception Handling', '2: Paperwork', 
			'3: MOW', '4: Speed Restriction', '5: Signal Response', 
			'6: Monitoring In', '7: Monitoring Out', '8: Planning Ahead']

# 	Initialize graph

	plt.title("Utilization for %d Runs" %numRuns)
	plt.xlabel("Time (min)")
	plt.ylabel("Utilization (%)")
	plt.ylim(0, 110)
	plt.xlim(0, endTimes[2])
	plt.xticks(np.arange(0, endTimes[2], intSize))

#	Plot utilization

	if oneRun:												# For one run,
		for i in range(len(data)):	
			plt.bar(time, data[i], 							# Plot all task types
				width = intSize/2,							# Set bar width
				bottom = np.sum(data[:i], axis = 0),		# Set bottom bars
				color = colors[i % len(colors)],			# Set color
				hatch = patterns[i % len(patterns)],		# Set pattern
				align = 'center')							# Align bars
		lgd = plt.legend(legend, loc='center left', 		# Set legend
							bbox_to_anchor=(1, 0.5))
							
	else:													# For multiple runs,
		plt.bar(time, data[0], 								# Plot avg for all types
			width = intSize/2,								# Set bar width
			color = 'r',									# Set color
			align = 'center',								# Align bars
			yerr = error)									# Set error bars
		lgd = []											# Set legend
		
# 	Plot phase lines

	for i in range(2):
		plt.plot((endTimes[i], endTimes[i]), (0, 110), 'm--')

# 	Save file
	
	plt.savefig(outFile, additional_artists=lgd, bbox_inches="tight")

# Forward declaration
if __name__ == '__main__': main()