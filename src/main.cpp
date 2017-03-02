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

// #define ELPP_NO_DEFAULT_LOG_FILE
// #define ELPP_THREAD_SAFE
// #define ELPP_DISABLE_LOGS
#include <iostream>
#include <string>
#include "simulation.h"
#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP

using namespace std;

void initLogger();
int util::seed = 0;	// not yet set
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
	initLogger();
	OptionParser p;
	Options opts = p.parse(argc, argv);

//  Intialize and run simulation

    Simulation sim(opts);
    sim.run();
    LOG(INFO) << "Runtime: " << t.elapsed() << " s";

	return 0;
}

/****************************************************************************
*																			*
*	Function:	initLogger		 											*
*																			*
*	Purpose:	To initialize the logger							       	*
*																			*
****************************************************************************/

void initLogger()
{
//	TODO
	el::Configurations conf("config/logger.conf");
    el::Loggers::reconfigureAllLoggers(conf);
	// el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime %level %ip_addr : %msg");
	// el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
    // el::Loggers::addFlag(el::LoggingFlag::HierarchicalLogging);
    // START_EASYLOGGINGPP(argc, argv);
}
