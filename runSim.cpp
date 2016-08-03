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

using  ns = chrono::nanoseconds;
using get_time = chrono::steady_clock;

/****************************************************************************
*																			*
*	Function:	main														*
*																			*
****************************************************************************/

//  Notes:
//  - change rand() to default_random_engine (minstd_rand0 rand; rand();)
//  - executable is not plotting (not recongizing matplotib)

int main(int argc, char* argv[])
{
    auto start = get_time::now();
    
//  Readin parameter file
    
    string paramFile = "/Users/Branch/Documents/Academic/Year 1/Summer/DES Code/DES/Input/params.txt";

    if (argc > 1)
        paramFile = argv[1];

//  Initialize parameters
    
    LoadParameters pms(paramFile);
    setOutputPath(pms.getOutFile());
    setNumHours(pms.getParam(0));
    setNumReps(pms.getParam(1));
    setTraffic(pms.getTraffic());

//  Intialize and run simulation
    
    Simulation sim(paramFile);
	sim.run();
    
    auto end = get_time::now();
    auto diff = end - start;
    cout<<"Elapsed time = " << chrono::duration_cast<ns>(diff).count()/1000000000 << " s" <<endl;
    
	return 0;
}