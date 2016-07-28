/****************************************************************************
*																			*
*	File:		Constants.h													*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jun 24, 2016												*
*																			*
*	Purpose:	This file defines the global variables used by the 			*
*				simulation.													*
*																			*
****************************************************************************/

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Parameters.h"
#include <vector>

// Notes
// - Add ability to pick phase to run
// - Input start and end time (can be random multiple)

namespace cnsts
{
//  Get parameters
    
    int i = 0;
    Parameters pms;
    
//  Set parameters
    
    const string OUTPUT_PATH = pms.getOutFile();
    const int NUM_HOURS = pms.getParam(i++);
	const int NUM_REPS = pms.getParam(i++);
    const bool OUTPUT_ON = 1;
    const bool RAND_RUN_ON = 0;
		
    const int END_TIME = NUM_HOURS * 60;
    const int INT_SIZE = 10;
    
    const int NUM_INTS = END_TIME/INT_SIZE;
	const int NUM_TASK_TYPES = pms.getParam(i++);
    const int NUM_PHASES = 3;
	const int NUM_STATS = 6;
    
    const vector<float> TRAFFIC = pms.getTraffic();
    const bool TRAFFIC_ON = 0;
    const bool FATIGUE_ON = 0;
    const bool DEBUG_ON = 1;
}

#endif