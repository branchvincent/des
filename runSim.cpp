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
using namespace cnsts;

// Function prototypes

void getStdDev(vector<float>& data);
void outputStats(Simulation& sim, string filePath);
void outputBatchStats(Matrix2D data, string filePath);
void setTrafficLevels(vector<float>& traffic);
void setSeed(int& seed);

/****************************************************************************
*																			*
*	Function:	main														*
*																			*
****************************************************************************/

int main() 
{
//	Set folder paths

	const string filePath = "/Users/Branch/Documents/Academic/Year 1/Summer/DES Code/Data/";
	const string oneRunFile = filePath + "singleRun.csv";
	const string batchRunFile = filePath + "batchRun.csv";

//	Initialize variables

	srand((unsigned int) time(0));
	Matrix2D stats(NUM_STATS * NUM_TASK_TYPES, vector<float>(NUM_RUNS + 2,0));
	vector<float> traffic(NUM_HOURS, 0);
	int seed = 0;

//	Run simulations for specified times

	for (int i = 0; i < NUM_RUNS; i++)
	{
	//	Set simulation seed and traffic levels
	
		setSeed(seed);
		setTrafficLevels(traffic);
		
	//	Run simulation	
	
		cout << "Run " << i << endl;
		Simulation sim(END_TIME, seed, traffic);	
		sim.run();	
	
	//	Output data, if applicable
	
		if (OUTPUT && NUM_RUNS == 1)
			outputStats(sim, oneRunFile);
		else if (NUM_RUNS != 1)
			sim.getStatSums(stats, i);
	}

//	Output data, if applicable

	if (OUTPUT && NUM_RUNS != 1)		
		outputBatchStats(stats, batchRunFile);

	return 0;
}

/****************************************************************************
*																			*
*	Function:	getStdDev													*
*																			*
*	Purpose:	To calculate the mean and standard deviation for the 		*
*				specified array												*
*																			*
****************************************************************************/

void getStdDev(vector<float>& data)
{
//	Initialize variables

	int N = NUM_RUNS;
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
*	Function:	outputBatchStats											*
*																			*
*	Purpose:	To output the stats compiled by the simulation				*
*																			*
****************************************************************************/

void outputBatchStats(Matrix2D data, string filePath)
{
//	Calculate mean and standard deviation

	for (int i = 0; i < data.size(); i++)		
		getStdDev(data[i]);	
	
//	Open file

	ofstream fout(filePath);
	if (!fout)
	{
		cerr << "Failed to open output file. Exiting...";
		exit(1);
	}
	
//	Output header

	fout << "Statistic Type, Task Type, ";
	for (int i = 0; i < NUM_RUNS; i++)
		fout << "Run " << i << ", ";
	fout << "Mean, Std Dev" << endl;

//	Output statistical data

	fout << "Utilization";
	for (int i = 0; i < NUM_TASK_TYPES; i++)
	{
		fout << ", " << i << ", ";
		for (int j = 0; j < NUM_RUNS + 2; j++)
			fout << data[i][j] << ", ";	
		fout << endl;
	}
	
	fout << "Avg Service Time";
	for (int i = NUM_TASK_TYPES; i < 2 * NUM_TASK_TYPES; i++)
	{
		fout << ", " << i % NUM_TASK_TYPES << ", ";
		for (int j = 0; j < NUM_RUNS + 2; j++)
			fout << data[i][j] << ", ";	
		fout << endl;
	}
	
	fout << "Avg Wait Time";
	for (int i = 2 * NUM_TASK_TYPES; i < 3 * NUM_TASK_TYPES; i++)
	{
		fout << ", " << i % NUM_TASK_TYPES << ", ";
		for (int j = 0; j < NUM_RUNS + 2; j++)
			fout << data[i][j] << ", ";	
		fout << endl;
	}
	
	fout << "Number In";
	for (int i = 3 * NUM_TASK_TYPES; i < 4 * NUM_TASK_TYPES; i++)
	{
		fout << ", " << i % NUM_TASK_TYPES << ", ";
		for (int j = 0; j < NUM_RUNS + 2; j++)
			fout << data[i][j] << ", ";	
		fout << endl;
	}
	
	fout << "Number Out";
	for (int i = 4 * NUM_TASK_TYPES; i < 5 * NUM_TASK_TYPES; i++)
	{
		fout << ", " << i % NUM_TASK_TYPES << ", ";
		for (int j = 0; j < NUM_RUNS + 2; j++)
			fout << data[i][j] << ", ";	
		fout << endl;
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

void outputStats(Simulation& sim, string filePath)
{
//	Open file

	ofstream fout(filePath);
	if (!fout)
	{
		cerr << "Failed to open output file. Exiting...";
		exit(1);
	}
	
	fout << sim << endl;
	
	return;           
}

/****************************************************************************
*																			*
*	Function:	setTrafficLevels											*
*																			*
*	Purpose:	To set the traffic levels for the simulation				*
*																			*
****************************************************************************/

void setTrafficLevels(vector<float>& traffic)
{
//	Set random traffic, if applicable

	if (RAND_RUN)
	{
		for (int i = 0; i < traffic.size(); i++)
		{
			traffic[i] = rand() % 3;
			if (traffic[i] == 0) traffic[i] = 0.5;
		}
	}
	
//	Otherwise, set specific traffic

	else
	{
		for (int i = 0; i < traffic.size(); i++)
		{
			traffic[i] = i % 3;
			if (traffic[i] == 0) traffic[i] = 0.5;
		}
	}
	
	return;
}

/****************************************************************************
*																			*
*	Function:	setSeed														*
*																			*
*	Purpose:	To set the seed for the simulation							*
*																			*
****************************************************************************/

void setSeed(int& seed)
{
	if (RAND_RUN) 
		seed = rand();
	else 
		seed++;
	return;
}