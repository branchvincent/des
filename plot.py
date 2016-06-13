#!/usr/bin/python

import matplotlib.pyplot as plt
from numpy import *
import math
import csv

def getData(filename):
	reader = csv.reader(open(filename), delimiter=',')
	header = next(reader)
	x, y = [], []
	for row in reader:
		x.append(int(row[0]))
		y.append(int(row[1]))
	return x,y

def roundup(x):
	return int(math.ceil(x / 10.0)) * 10

time, util = getData('/Users/Branch/Desktop/run1.csv')
endTime = time[-1] 

#for i in range(0,len(time)):
#	print(time[i],util[i])

interval = roundup(endTime)/10.
beginInt = 0
endInt = interval
results = []
print(time)
print(util)

while endInt <= interval*10:
	i = 0
	busy = 0
	while time[i] <= beginInt:
		i = i + 1
	print(beginInt, endInt, i)
	
	if time[i] >= endInt and util[i] == 1:
		busy = interval
	
	if util[i] == 1 and time[i] < endInt:
		busy = busy + time[i] - beginInt
	i = i + 1
	print('\t', i, busy)

	while i != len(time) and time[i] < endInt:
		if util[i] == 1:
			busy = busy + time[i] - time[i-1]
		i = i+1
	print('\t', i, busy)
		
	if i != len(time) and time[i-1] < endInt and util[i] == 1:
		busy = busy + endInt - time[i-1]

	if i == len(time):
		results.append(busy/(time[-1] - beginInt)*100)
	else:
		results.append(busy/interval*100)

	beginInt = beginInt + interval
	endInt = endInt + interval
	print('\t', i, busy)
	
t = linspace(0,interval*9,10)
print(t)
print(results)

width = interval
plt.figure("Utilization")
plt.xlabel("Time (s)")
plt.ylabel("Utilization (%)")
plt.bar(t,results,interval)
plt.ylim(0,110 )
plt.savefig('/Users/Branch/Desktop/graph.pdf')