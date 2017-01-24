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
#include "libs/ArgParser.h"

using namespace std;

//void readInputArgs(int argc, char* argv[], string& paramFile);

/****************************************************************************
*																			*
*	Function:	main														*
*																			*
****************************************************************************/

int main(int argc, const char* argv[])
{
//  Start timer
    
    clock_t start = clock();

//  Read in parameter file
	
	ArgParser parser;
	parser.parse(argc, argv);
	
//	string paramFile;
//	readInputArgs(argc, argv, paramFile);
	
//	Get run parameters
	
//	LoadParameters pms(paramFile);
//	INIT_GLOBALS(pms);
	
//  Intialize and run simulation
    
//    Simulation sim(paramFile);
//	sim.run();
	
//  End timer
    
    float time = (clock() - start) / (float)CLOCKS_PER_SEC;
    cout << "Elapsed time = " << time << " s" <<endl;

	return 0;
}

/****************************************************************************
*																			*
*	Function:	readInputArgs												*
*																			*
*	Purpose:	To read the input arguments									*
*																			*
****************************************************************************/

//void readInputArgs(int argc, char* argv[], string& paramFile)
//{
////	Check for required parameter file
//	
//	if (argc < 2)
//	{
//		cerr << "Please specify parameter input file. Exiting..." << endl;
//		exit(1);
//	}
//	
////	for (char** c : argv)
////	{
////		printf(&c);
////	}
//	
//	paramFile = argv[1];
//	cout << "Reading parameters from " << paramFile << "..." << endl;
//}
