/****************************************************************************
*																			*
*	File:		run.cpp													    *
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
#include "src/Simulation.h"
#include "src/libs/ArgParser.h"

using namespace std;

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

	// ArgParser parser;
	// parser.parse(argc, argv);

//	string paramFile;
//	readInputArgs(argc, argv, paramFile);

//	Get run parameters

//  Parameters pms(paramFile);

//  Intialize and run simulation

//    Simulation sim(paramFile);
//	sim.run();

//  End timer

    float time = (clock() - start) / (float)CLOCKS_PER_SEC;
    cout << "Elapsed time = " << time << " s" <<endl;

	return 0;
}
