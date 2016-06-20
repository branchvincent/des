/****************************************************************************
*																			*
*	File:		runSim.cpp													*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jun 6, 2016													*
*																			*
*	Purpose:	This file runs the simulation for the specified time and 	*
*				outputs the results to the specified file					*
*																			*
****************************************************************************/

#include <iostream>
#include <string>
#include "Simulation2.h"
#include <time.h>
#include <vector>

using namespace std;

// Function prototypes and definitions

//typedef vector< vector<float> > Matrix2D;
typedef vector< vector<vector<float> > > Matrix3D;
void stdDev(vector<float>& data);
void outputData(Matrix data, string filePath);

// Global variables

const string filePath = "/Users/Branch/Documents/Academic/Year 1/Entry Summer/Code/DES/Data/runTest.csv";
const string filePath2 = "/Users/Branch/Documents/Academic/Year 1/Entry Summer/Code/DES/Data/runTests.csv";
const int numRuns = 1;

/****************************************************************************
*																			*
*	Function:	main														*
*																			*
****************************************************************************/

int main() 
{
//	Initialize variables

	srand(time(0));
	int endTime = 90;
	int numInts = endTime/intSize;
	Matrix3D util(numRuns, vector<vector<float> >(numInts, vector<float>(numTypes + 2,0)));
	Matrix data(numInts, vector<float>(numRuns + 2,0));

	float processTimes[9];
	float waitTimes[9];
	int totalTasks[9];
	
//	Run simulations for specified times

	for (int i = 0; i < numRuns; i++)
	{
	//	Run simulation
	
		cout << "Run " << i << endl;
		Simulation sim(endTime, rand());		// rand()		
		sim.run();	
	
	//	Get stats
	
//		cout << endl;
//		sim.getStats(processTimes, waitTimes, totalTasks);
//		cout << endl;
		sim.getUtil(util[i]);
		sim.outputUtil(filePath);
		
	//	Copy total utilization 

//		for (int j = 0; j < numInts; j++)
//			data[j][i] = util[i][j][10];
	}
	
//	for (int i = 0; i < data.size(); i++)
//		stdDev(data[i]);
//	outputData(data, filePath2);

	return 0;
}

/****************************************************************************
*																			*
*	Function:	stdDev														*
*																			*
*	Purpose:	To calculate the mean and standard deviation for the 		*
*				specified array												*
*																			*
****************************************************************************/

void stdDev(vector<float>& data)
{
//	Initialize variables

	int N = numRuns;
	float mean = 0;
	float devSum = 0;

//	Calculate mean

	for (int i = 0; i < N; i++)
		mean += data[i];
	mean /= N;
	data[N] = mean;
	
//	Calculate standard deviation

	for (int i = 0; i < N; i++)
		devSum += (data[i] - mean) * (data[i] - mean);
	data[N + 1] = sqrt(devSum/(N-1));
	
	return;           
}

/****************************************************************************
*																			*
*	Function:	outputData													*
*																			*
*	Purpose:	To output the average and standard deviation for the 		*
*				utilization data											*
*																			*
****************************************************************************/

void outputData(Matrix data, string filePath)
{
//	Open file

	ofstream fout(filePath);
	if (!fout)
	{
		cerr << "Failed to open output file. Exiting...";
		exit(1);
	}
	
//	Output header

	int interval = 0;
	fout << "Interval, Utilization, StdDev" << endl;

//	Output data

	for (int i = 0; i < data.size(); i++)
	{
		fout << interval << ", ";
		for (int j = numRuns; j < data[i].size(); j++)
			fout << data[i][j] << ", ";
		fout << endl;
		interval += intSize;
	}
	
	return;           
}