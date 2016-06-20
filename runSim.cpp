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
#include "Simulation.h"
#include <time.h>
#include <vector>

using namespace std;

// Function protypes and definitions

typedef vector< vector<float> > Matrix2D;
typedef vector< vector<vector<float> > > Matrix3D;
void stdDev(vector<float>& data);
void outputData(Matrix2D data, string filePath);

string filePath1 = "/Users/Branch/Documents/Academic/Year 1/Entry Summer/Code/DES/Data/run1.csv";
string filePath2 = "/Users/Branch/Documents/Academic/Year 1/Entry Summer/Code/DES/Data/run2.csv";
int intSize = 10;
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
	int endTime = 100;
	int numInts = endTime/intSize;
	int numTypes = 9;
	Matrix3D util(numRuns, vector<vector<float> >(numInts, vector<float>(numTypes,0)));
//	Matrix2D util(numInts, vector<float>(numTypes + 1,0));
	Matrix2D data(numInts, vector<float>(numRuns + 2,0));

//	Open output stream

//	ofstream fout(filePath);
//	if (!fout)
//	{
//		cerr << "Failed to open output file. Exiting...";
//		exit(1);
//	}

//	Run simulations for specified times

	float ser = 0;
	float tas = 0;
	
	for (int i = 0; i < numRuns; i++)
	{
		cout << "Run " << i << endl;
		Simulation sim(endTime, rand());		// 43200		
		sim.run();	
		sim.processData(util[i], intSize);

		for (int j = 0; j < numInts; j++)
			data[j][i] = util[i][j][9];
		
//		for (int j = 0; j < numInts; j++)
//			data[j][i] = util[i][j][9]/100 * intSize;
		
//		sim.outputData(util[i], intSize, filePath1);
		cout << endl;
	}
	
	for (int i = 0; i < data.size(); i++)
		stdDev(data[i]);
	
	outputData(data, filePath2);
	
//	int interval = intSize;
//	fout << "Time (min), Utilization by Type" << endl;
//	for (int i = 0; i < util.size(); i++)
//	{
//		fout << interval << ", ";
//		for (int j = 0; j < util[i].size(); j++)
//			fout << util[i][j]/numRuns << ", ";
//		fout << endl;
//		interval += intSize;
//	}

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