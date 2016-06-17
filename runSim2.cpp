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

// Function protypes and definitions

typedef vector< vector<float> > Matrix2D;
typedef vector< vector<vector<float> > > Matrix3D;
void stdDev(vector<float>& data);
void outputData(Matrix2D data, string filePath);

string filePath = "/Users/Branch/Documents/Academic/Year 1/Entry Summer/Code/DES/Data/runTest.csv";
//int intSize = 10;
int numRuns = 1;

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
	int numInts = endTime/10;
	int numTypes = 9;
	Matrix3D util(numRuns, vector<vector<float> >(numInts, vector<float>(numTypes,0)));
//	Matrix2D util(numInts, vector<float>(numTypes + 1,0));
	Matrix2D data(numInts, vector<float>(numRuns + 2,0));

//	Run simulations for specified times

	for (int i = 0; i < numRuns; i++)
	{
		cout << "Run " << i << endl;
		Simulation sim(endTime, rand());		// 43200		
		sim.run();	
		sim.outputData(filePath);
		
		for (int j = 0; j < numInts; j++)
			data[j][i] = util[i][j][9];
	}
	
	for (int i = 0; i < data.size(); i++)
		stdDev(data[i]);
	outputData(data, filePath2);

	return 0;
}

/****************************************************************************
*																			*
*	Function:	stdDev														*
*																			*
*	Purpose:	To calculate the standard deviation of the specified array	*
*																			*
****************************************************************************/

void stdDev(vector<float>& data)
{
	int N = numRuns;
	float mean = 0;
	float devSum = 0;
	
	for (int i = 0; i < N; i++)
		mean += data[i];
	mean /= N;
	data[N] = mean;
	
	for (int i = 0; i < N; i++)
		devSum += (data[i] - mean) * (data[i] - mean);
	data[N + 1] = sqrt(devSum/(N-1));
	
	return;           
}

/****************************************************************************
*																			*
*	Function:	outputData													*
*																			*
*	Purpose:	To output the average and stddev of the utilization data	*
*																			*
****************************************************************************/

void outputData(Matrix2D data, string filePath)
{
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