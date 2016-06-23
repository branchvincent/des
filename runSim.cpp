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
void outputStats(Matrix data, string filePath);

// Global variables

const string filePath = "/Users/Branch/Documents/Academic/Year 1/Entry Summer/Code/DES/Data/"
const string singleRunFile = path + "singleRun.csv";
const string batchRunFile = path + "batchRun.csv";
const string singleStatsFile = path + "singleStats.csv";
const string batchStatsFile = path + "batchStats.csv";
const int numRuns = 1;
const bool output = false;
const bool randRun = false;

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
	Matrix stats(numTypes * 3, vector<float>(numRuns + 2,0));

	float processTimes[9];
	float waitTimes[9];
	int totalTasks[9];
	
//	Run simulations for specified times

	for (int i = 0; i < numRuns; i++)
	{
	//	Run simulation
		
		int mySeed = 0;
		if (randRun) mySeed = rand();
		
		cout << "Run " << i << endl;
		Simulation sim(endTime, mySeed);	
		sim.run();	
	
	//	Get stats
	
		sim.getStats(processTimes, waitTimes, totalTasks);
		sim.getUtil(util[i]);
		
	//	Copy total utilization 

		for (int j = 0; j < data.size(); j++)
			data[j][i] = util[i][j][10];
	
	//	Copy stats
	
		for (int j = 0; j < stats.size(); j++)
		{
			if (j < numTypes)
				stats[j][i] = processTimes[j];
			else if (j < 2*numTypes)
				stats[j][i] = waitTimes[j%numTypes];
			else
				stats[j][i] = totalTasks[j%numTypes];
		}
			
	//	Output data, if applicable

		if (output && numRuns == 1)
		{
			sim.outputUtil(singleRunFile);
			outputStats(stats, singleStatsFile);
		}
	}
	
//	Calculate mean and standard deviation

	for (int i = 0; i < data.size(); i++)
		stdDev(data[i]);
	
	for (int i = 0; i < stats.size(); i++)
		stdDev(stats[i]);
	
//	Output data, if applicable

	if (output && numRuns != 1)		
	{
		outputBatchUtil(data, batchRunFile);
		outputStats(stats, batchStatsFile);
	}

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

/****************************************************************************
*																			*
*	Function:	outputStats													*
*																			*
*	Purpose:	To output the utilization data for all the runs, including 	*
*				the average and standard deviation 							*
*																			*
****************************************************************************/

void outputStats(Matrix data, string filePath)
{
//	Open file

	ofstream fout(filePath);
	if (!fout)
	{
		cerr << "Failed to open output file. Exiting...";
		exit(1);
	}
	
//	Output header

	fout << "Statistic, Task Type,";
	for (int i = 0; i < numRuns; i++)
		fout << "Run " << i << ","; 
	fout << "Mean, StdDev" << endl;

//	Output utilization data

	for (int i = 0; i < data.size(); i++)
	{
		if (i == 0)
			fout << "Processing Time";
		else if (i == numTypes)
			fout << "Wait Times";
		else if (i == 2*numTypes)
			fout << "Total Tasks";
		
		fout << "," << i%numTypes << ",";
		
		for (int j = 0; j < data[i].size(); j++)
			fout << data[i][j] << ", ";
		fout << endl;
	}
	
	return;           
}