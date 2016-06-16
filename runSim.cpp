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

// Global variables

string filePath = "/Users/Branch/Documents/Academic/Year 1/Entry Summer/Code/DES/Data/run.csv";
typedef vector< vector<float> > Matrix;
int intSize = 10;
int numRuns = 1;

int main() 
{
//	Initialize variables

	srand(time(0));
	int endTime = 90;
	int numInts = endTime/intSize;
	int numTypes = 9;
	Matrix util(numInts, vector<float>(numTypes,0));
	
//	Open output stream

	ofstream fout(filePath);
	if (!fout)
	{
		cerr << "Failed to open output file. Exiting...";
		exit(1);
	}

//	Run simulations for specified times

	for (int i = 0; i < numRuns; i++)
	{
		Simulation sim(endTime,rand());		// 43200		
		sim.run();	
		sim.processData(util,intSize);
//		sim.reportStats();
	}
	
	int interval = intSize;
	fout << "Time (min), Utilization by Type" << endl;
	for (int i = 0; i < util.size(); i++)
	{
		fout << interval << ", ";
		for (int j = 0; j < util[i].size(); j++)
			fout << util[i][j]/numRuns << ", ";
		fout << endl;
		interval += intSize;
	}

	return 0;
}