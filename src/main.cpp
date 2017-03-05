/****************************************************************************
*																			*
*	File:		shado.cpp													*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file executes the discrete event simulation for the    *
*               specified parameters.                                       *
*																			*
****************************************************************************/

#include <iostream>
#include <string>
#include "simulation.h"
INITIALIZE_EASYLOGGINGPP

using namespace std;

// Extern variables

int util::seed = 0;
default_random_engine util::randNumGen = default_random_engine(0);

/****************************************************************************
*																			*
*	Function:	main														*
*																			*
****************************************************************************/

int main(int argc, const char* argv[])
{
//  Read command line options

	util::Timer t;
	util::initLogger();
	OptionParser p;
	Options opts = p.parse(argc, argv);

//  Intialize and run simulation

    Simulation sim(opts);
    sim.run();
    LOG(INFO) << "Runtime: " << t.elapsed() << " s";

	return 0;
}
