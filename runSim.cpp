/****************************************************************************
*																			*
*	File:		runSim.cpp													*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jun 6, 2016													*
*																			*
*	Purpose:	This file runs the simulation for the specified time and 	*
*				OUTPUTs the results to the specified file					*
*																			*
****************************************************************************/

// Header files

#include <iostream>
#include <string>
#include "Simulation.h"

using namespace std;
using namespace cnsts;

// Function prototypes

void stdDev(vector<float>& data);
void outputBatchUtil(Matrix2D data, string filePath);
void outputStats(Matrix2D data, string filePath);

/****************************************************************************
*																			*
*	Function:	main														*
*																			*
****************************************************************************/

int main() 
{
//	Initialize variables

	srand((unsigned int) time(0));
	Matrix3D util(NUM_RUNS, Matrix2D(NUM_INTS, vector<float>(NUM_TASK_TYPES + 2,0)));
	Matrix2D data(NUM_INTS, vector<float>(NUM_RUNS + 2,0));
	Matrix2D stats(NUM_STATS * NUM_TASK_TYPES, vector<float>(NUM_RUNS + 2,0));

	float processTimes[9];
	float waitTimes[9];
	int totalTasks[9];
	
	int mySeed = 0;
	vector<float> traffic(NUM_HOURS, 0);
	
//	Run simulations for specified times

	for (int i = 0; i < NUM_RUNS; i++)
	{
	//	Set simulation seed and traffic levels
		
		if (RAND_RUN) mySeed = rand();
		
		for (int j = 0; j < END_TIME/60; j++)
		{
			traffic[j] = j % 3;
			if (traffic[j] == 0) traffic[j] = 0.5;
		}
		
	//	Run simulation	
	
		cout << "Run " << i << endl;
		Simulation sim(END_TIME, mySeed, traffic);	
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
			if (j < NUM_TASK_TYPES)
				stats[j][i] = processTimes[j];
			else if (j < 2 * NUM_TASK_TYPES)
				stats[j][i] = waitTimes[j % NUM_TASK_TYPES];
			else
				stats[j][i] = totalTasks[j % NUM_TASK_TYPES];
		}
			
	//	Output data, if applicable

		if (OUTPUT && NUM_RUNS == 1)
		{
			sim.outputUtil(ONE_RUN_FILE);
			outputStats(stats, ONE_RUN_STATS_FILE);
		}
	}
	
//	Calculate mean and standard deviation

	for (int i = 0; i < data.size(); i++)
		stdDev(data[i]);
	
	for (int i = 0; i < stats.size(); i++)
		stdDev(stats[i]);
	
//	Output data, if applicable

	if (OUTPUT && NUM_RUNS != 1)		
	{
		outputBatchUtil(data, BATCH_RUN_FILE);
		outputStats(stats, BATCH_RUN_STATS_FILE);
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
*	Function:	outputBatchUtil												*
*																			*
*	Purpose:	To output the utilization data for all the runs, including 	*
*				the average and standard deviation 							*
*																			*
****************************************************************************/

void outputBatchUtil(Matrix2D data, string filePath)
{
//	Open file

	ofstream fout(filePath);
	if (!fout)
	{
		cerr << "Failed to open OUTPUT file. Exiting...";
		exit(1);
	}
	
//	Output header

	int interval = 0;
	fout << "Interval,";
	for (int i = 0; i < NUM_RUNS; i++)
		fout << "Run " << i << ","; 
	fout << "Mean, StdDev" << endl;

//	Output utilization data

	for (int i = 0; i < data.size(); i++)
	{
		fout << interval << ", ";
		for (int j = 0; j < data[i].size(); j++)
			fout << data[i][j] << ", ";
		fout << endl;
		interval += INT_SIZE;
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

void outputStats(Matrix2D data, string filePath)
{
//	Open file

	ofstream fout(filePath);
	if (!fout)
	{
		cerr << "Failed to open OUTPUT file. Exiting...";
		exit(1);
	}
	
//	Output header

	fout << "Statistic, Task Type,";
	for (int i = 0; i < NUM_RUNS; i++)
		fout << "Run " << i << ","; 
	fout << "Mean, StdDev" << endl;

//	Output utilization data

	for (int i = 0; i < data.size(); i++)
	{
		if (i == 0)
			fout << "Processing Time";
		else if (i == NUM_TASK_TYPES)
			fout << "Wait Times";
		else if (i == 2*NUM_TASK_TYPES)
			fout << "Total Tasks";
		
		fout << "," << i%NUM_TASK_TYPES << ",";
		
		for (int j = 0; j < data[i].size(); j++)
			fout << data[i][j] << ", ";
		fout << endl;
	}
	
	return;           
}