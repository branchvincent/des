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

string filePath1 = "/Users/Branch/Documents/Academic/Year 1/Entry Summer/Code/DES/Data/runConfirm.csv";
int intSize = 10;
int numRuns = 100;

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
	int numTypes = 9;
//	Matrix3D util(numRuns, vector<vector<float> >(numInts, vector<float>(numTypes,0)));
	Matrix2D util(numInts, vector<float>(numTypes + 1,0));
//	Matrix2D data(numInts, vector<float>(numRuns + 2,0));

//	Run simulations for specified times

	for (int i = 0; i < numRuns; i++)
	{
		cout << "Run " << i << endl;
		Simulation sim(endTime, 10);	
		sim.run();	
		sim.processData(util, intSize);
		sim.outputData(util, intSize, filePath1);
	}

	return 0;
}
