/****************************************************************************
*																			*
*	File:		Parameters.h												*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jun 24, 2016												*
*																			*
*	Purpose:	This file defines the global variables used by the 			*
*				simulation.													*
*																			*
****************************************************************************/

#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <vector>
#include <string>

using namespace std;

// Notes
// - Add ability to pick phase to run
// - Input start and end time (can be random multiple)

namespace params
{
//  Declare parameters
        
    string OUTPUT_PATH;
    int NUM_HOURS;
	int NUM_REPS;
    const bool OUTPUT_ON = 1;
    const bool RAND_RUN_ON = 0;
		
    int END_TIME;
    const int INT_SIZE = 10;
    
    int NUM_INTS;
	const int NUM_TASK_TYPES = 9;
    const int NUM_PHASES = 3;
	const int NUM_STATS = 6;
    const int NUM_OPS = 1;
    
    vector<float> TRAFFIC;
    const bool TRAFFIC_ON = 1;
    const bool FATIGUE_ON = 1;
    const bool DEBUG_ON = 0;
    
//  Set parameters
    
    void setOutputPath(string path) {OUTPUT_PATH = path;}
    void setNumHours(int num)
        {NUM_HOURS = num; END_TIME = NUM_HOURS * 60; NUM_INTS = END_TIME/INT_SIZE;}
    void setNumReps(int reps) {NUM_REPS = reps;}
    void setTraffic(vector<float> traff)
        {for (int i = 0; i < traff.size(); i++) TRAFFIC.push_back(traff[i]);}
}

#endif