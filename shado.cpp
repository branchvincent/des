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
#include "src/ArgParser.h"
#include "src/Timer.h"

using namespace std;

Flags getFlags(int argc, const char* argv[]);

/****************************************************************************
*																			*
*	Function:	main														*
*																			*
****************************************************************************/

int main(int argc, const char* argv[])
{
//  Read in parameter file

    Timer t;
    Flags flags = getFlags(argc, argv);
    string file = argv[2];

//  Intialize and run simulation

    Simulation sim(file, flags);
//	sim.run();
    cout << "Runtime: " << t.elapsed() << " s";

	return 0;
}

Flags getFlags(int argc, const char* argv[])
{
    ArgParser parser;
	parser.parse(argc, argv);
    return parser.getFlags();
}
