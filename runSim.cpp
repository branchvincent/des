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

// Header files

#include <iostream>
#include <string>
#include "Simulation.h"

using namespace std;

// Function prototypes and definitions

//typedef vector< vector<float> > Matrix2D;
typedef vector< vector<vector<float> > > Matrix3D;
void stdDev(vector<float>& data);
void outputBatchUtil(Matrix data, string filePath);

// Global variables

const string singleRunFile = "/Users/Branch/Documents/Academic/Year 1/Entry Summer/Code/DES/Data/singleRun.csv";
const string batchRunFile = "/Users/Branch/Documents/Academic/Year 1/Entry Summer/Code/DES/Data/batchRun.csv";
const int numRuns = 100;
const bool output = false;

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
	Matrix stats(numRuns, vector<float>(numTypes + 2,0));
		
	float processTimes[9];
	float waitTimes[9];
	int totalTasks[9];
	
//	Run simulations for specified times

	for (int i = 0; i < numRuns; i++)
	{
	//	Run simulation
	
		cout << "Run " << i << endl;
		Simulation sim(endTime, rand());	
		sim.run();	
	
	//	Get stats
	
//		cout << endl;
//		sim.getStats(processTimes, waitTimes, totalTasks);
//		cout << endl;
		sim.getUtil(util[i]);
		
	//	Copy total utilization 

		for (int j = 0; j < numInts; j++)
			data[j][i] = util[i][j][10];
			
	//	Output data, if applicable

		if (output && numRuns == 1)
			sim.outputUtil(singleRunFile);
	}
	
//	Calculate mean and standard deviation

	for (int i = 0; i < data.size(); i++)
		stdDev(data[i]);
	
//	Output data, if applicable

	if (output && numRuns != 1)		
		outputBatchUtil(data, batchRunFile);

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
*	Function:	outputBatchUtil												*
*																			*
*	Purpose:	To output the utilization data for all the runs, including 	*
*				the average and standard deviation 							*
*																			*
****************************************************************************/

void outputBatchUtil(Matrix data, string filePath)
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
	fout << "Interval,";
	for (int i = 0; i < numRuns; i++)
		fout << "Run " << i << ","; 
	fout << "Mean, StdDev" << endl;

//	Output utilization data

	for (int i = 0; i < data.size(); i++)
	{
		fout << interval << ", ";
		for (int j = 0; j < data[i].size(); j++)
			fout << data[i][j] << ", ";
		fout << endl;
		interval += intSize;
	}
	
	return;           
}