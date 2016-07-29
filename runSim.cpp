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

using namespace std;
using namespace params;
//using namespace tparams;

/****************************************************************************
*																			*
*	Function:	main														*
*																			*
****************************************************************************/

//  Notes:
//  - change rand() to default_random_engine (minstd_rand0 rand; rand();)

int main() 
{
//  Input parameter file
    
//    string paramFile;
//    cout << "Input parameter file location: ";
//    cin >> paramFile;
    
    string paramFile = "/Users/Branch/Documents/Academic/Year 1/Summer/DES Code/DES/Input/params.txt";

//  Intialize and run simulation
    
    Simulation sim(paramFile);
	sim.run();
    
	return 0;
}