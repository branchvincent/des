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

#from __future__ import print_function
import matplotlib.pyplot as plt
import numpy as np
import csv
import sys

# Set arguments

#inFile = sys.argv[1]
#outFile1 = '/Users/Branch/Desktop/engGraph.pdf'
#outFile2 = '/Users/Branch/Desktop/conGraph.pdf'
#numInts = 24

# Global variables

filePath = '/Users/Branch/Documents/Academic/Year 1/Summer/DES Code/Data/'
numTypes = 9
numRuns = 1000
oneRun = 0

#****************************************************************************
#																			*
#	Function:	main														*
#																			*
#****************************************************************************

def main():
	
#	Set input and output files
	
	inFile = '/Users/Branch/Documents/Research/FRA/SHOW/out/stats_dispatcher0.csv'
	outFile = '/Users/Branch/Documents/Research/FRA/SHOW/out/stats_dispatcher0.jpg'
	
#	if oneRun:
#		inFile = filePath + 'singleRun.csv'
#		outFile = filePath + 'singleGraph.pdf'
#	else:
#		inFile = filePath + 'batchRun.csv'
#		outFile = filePath + 'batchGraph.pdf'
	
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
		print("Time, Util, Std Dev")
		for row in reader:
#			if (row[0] == 'Utilization'):
#				for i in xrange(24):
			print("%s, %s, %s" %(row[0], row[-3], row[-2]))
			time.append(float(row[0]))				# Add time interval
			data[0].append(float(row[-3]))			# Add avg utilization
			error.append(float(row[-2]))			# Add std dev
			numRuns = len(row) - 2					# Update number of runs

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

#	colors = ['b', 'g', 'r', 'c', 'm', 'y', 'k']
	colors = color_list = plt.cm.Set1(np.linspace(0, 1, numTypes))
#	patterns = ['/', '\\', '|', '-', '+', 'x', 'o', 'O', '.', '*']
	labels = ['0: Communicating', '1: Exception Handling', '2: Paperwork', 
			'3: MOW', '4: Speed Restriction', '5: Signal Response', 
			'6: Monitoring In', '7: Monitoring Out', '8: Planning Ahead']

# 	Initialize graph

	plt.title("Engineer's Utilization for %d Runs" %numRuns)
	plt.xlabel("Time (min)")
	plt.ylabel("Utilization (%)")
	plt.ylim(0, 1.1)
	plt.xlim(0, endTimes[2])
#	plt.xticks(np.arange(0, endTimes[2] + intSize, intSize))
	ax = plt.gca()

#	Plot utilization

	if oneRun:												# For one run,
		for i in range(len(data)):	
			plt.bar(time, data[i], 							# Plot all task types
					width = intSize/2,						# Set bar width
					bottom = np.sum(data[:i], axis = 0),	# Set bottom bars
					color = colors[i % len(colors)],		# Set bar color
					linewidth = 0.1,
#					edgecolor = colors[i % len(colors)],	# Set bar edge color
#					hatch = patterns[i % len(patterns)],	# Set pattern
					label = labels[i],						# Set label
					align = 'center')						# Align bars
#		lgd = plt.legend(title='Task Types',				# Set legend
#						loc='center left', 		
#						bbox_to_anchor=(1, 0.5))
		handles, labels = ax.get_legend_handles_labels()
		lgd = ax.legend(handles[::-1], labels[::-1], 
						title='Task Types', loc='center left', 
						bbox_to_anchor=(1, 0.5), prop={'size':'medium'})
#		lgd.get_title().set_fontsize('6') #legend 'Title' fontsize
#		plt.setp(plt.gca().get_legend().get_texts(), fontsize='12')

	else:													# For multiple runs,
		plt.bar(time, data[0], 								# Plot avg for all types
			width = intSize/2,								# Set bar width
			color = 'r',									# Set color
			linewidth = 0.1,								# Set bar border width
			align = 'center',								# Align bars
			yerr = error)									# Set error bars
#		lgd = []											# Set legend
		lgd = ax.legend(['All task types', 'Std Dev'], loc=9, bbox_to_anchor=(0.5, -0.1))
		
# 	Plot phase lines

	for i in range(2):
		plt.plot((endTimes[i], endTimes[i]), (0, 1.10), 'm--')

# 	Save file
	
	plt.savefig(outFile, additional_artists=lgd, bbox_inches="tight")

# Forward declaration
if __name__ == '__main__': main()
