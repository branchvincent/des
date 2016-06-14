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

int main() 
{
	int N = 1;

	srand(time(0));
	for (int i = 0; i < N; i++)
	{
		Simulation sim(10,rand());		// 43200		
		sim.run();	
		sim.outputData("/Users/Branch/Documents/Academic/Year 1/Entry Summer/Code/DES/Data/run.csv");
	}

	return 0;
}