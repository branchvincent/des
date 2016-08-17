/****************************************************************************
*																			*
*	File:		runSim.cpp													*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jun 6, 2016													*
*																			*
*	Purpose:	This file executes a discrete event simulation for the      *
*               specified parameters and outputs the results to the         *
*               specified file.                                             *
*																			*
****************************************************************************/

#include <iostream>
#include <string>
#include "Simulation.h"
#include "Parameters/LoadParameters.h"

using namespace std;
using namespace params;

/****************************************************************************
*																			*
*	Function:	main														*
*																			*
****************************************************************************/

//  Notes:
//  - change rand() to default_random_engine (minstd_rand0 rand; rand();)

int main(int argc, char* argv[])
{
//  Start timer
    
    clock_t start = clock();

//  Readin parameter file
    
    string paramFile = "/Users/Branch/Documents/Academic/Year 1/Summer/DES Code/DES/in/params.txt";
    if (argc > 1) paramFile = argv[1];
    cout << "inFile = " << paramFile << endl;

//  Initialize parameters
    
    LoadParameters pms(paramFile);
    setOutputPath(pms.getOutFile());
    setNumHours(pms.getNumHours());
    setNumReps(pms.getNumReps());
    setTraffic(pms.getTraffic());
    setOps(pms.getOps());

//  Intialize and run simulation
    
//    Simulation sim(paramFile);
//	sim.run();
	
//  End timer
    
    float time = (clock() - start) / (float)CLOCKS_PER_SEC;
    cout << "Elapsed time = " << time << " s" <<endl;

	return 0;
}