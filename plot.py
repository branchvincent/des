#!/usr/bin/python

import matplotlib.pyplot as plt
import csv

def getColumn(filename, column):
	results = csv.reader(open(filename), delimiter=',')
	return [result[column] for result in results]
	
time = getColumn('/Users/Branch/Desktop/run1.csv',0)
util = getColumn('/Users/Branch/Desktop/run1.csv',1)
time.pop(0)
util.pop(0)

for i in range(len(util)-1,0,-1):
	print(time[i], util[i-1])
	time.insert(i,time[i])
	util.insert(i,util[i-1])

i = len(util)-1
time.insert(i,time[i])
util.insert(i,0)

plt.figure("Utilization")
plt.xlabel("Time (s)")
plt.ylabel("Utilization (%)")
plt.ylim(0,1.2)
plt.plot(time,util)
plt.savefig('/Users/Branch/Desktop/graph.pdf')
#plt.close(fig)
#plt.show()