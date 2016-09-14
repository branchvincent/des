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

//  Read in parameter file
	
//	if (argc < 1) {
//		cerr << "Please specify paramter input file. Exiting..." << endl;
//		exit(1);
//	}
//    string paramFile = "/Users/Branch/Desktop/params";
//	argv[1];
	
	string paramFile;
	if (argc > 1)
		paramFile = argv[1];
	else
		paramFile = "/Users/Branch/Documents/Academic/Year 1/Summer/DES Code/DES/in/params_new.txt";
	
    cout << "inFile = " << paramFile << endl;
	
//	Get run parameters
	
	LoadParameters pms(paramFile);
	INIT_GLOBALS(pms);

//  Intialize and run simulation
    
    Simulation sim(paramFile);
	sim.run();
	
//  End timer
    
//    float time = (clock() - start) / (float)CLOCKS_PER_SEC;
//    cout << "Elapsed time = " << time << " s" <<endl;

	return 0;
}