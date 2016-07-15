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

//namespace cnsts
//{
//    //	Batch run details
//
//    const string OUTPUT_FILE = "/Users/Branch/Desktop/DES/DES/Output/runData.csv";
//    const int NUM_REPS = 5;
//    const bool OUTPUT_ON = true;
//    const bool RAND_RUN_ON = false;
//    
//    //	One run details
//    
//    const int END_TIME = 90;
//    const int INT_SIZE = 30;
//    const int NUM_HOURS = (END_TIME/60. + 0.5);
//    const int NUM_INTS = END_TIME/INT_SIZE;
//    const int NUM_TASK_TYPES = 9;
//    const int NUM_PHASES = 3;
//    const int NUM_STATS = 6;
//    const bool DEBUG_ON = true;
//    const bool TRAFFIC_ON = false;
//    const bool FATIGUE_ON = false;
//}

namespace cnsts
{
//  Get parameters
    
    int i = 0;
    Parameters pms("/Users/Branch/Desktop/DES/DES/Input/params.txt");
    
//  Set parameters
    
    const string OUTPUT_FILE = pms.getOutFile();
    const int NUM_HOURS = pms.getParam(i++);        //  input start and end time (can be random multiple)
	const int NUM_REPS = pms.getParam(i++);
	const bool OUTPUT_ON = pms.getParam(i++);       // do not input
	const bool RAND_RUN_ON = pms.getParam(i++);     // do not input
		
    const int END_TIME = NUM_HOURS * 60;
	const int INT_SIZE = pms.getParam(i++);         // do not input
    
    const int NUM_INTS = END_TIME/INT_SIZE;
	const int NUM_TASK_TYPES = pms.getParam(i++);
	const int NUM_PHASES = pms.getParam(i++);       // do not input (maybe pick a phase to run tho)
	const int NUM_STATS = 6;
    
    const vector<float> TRAFFIC = pms.getTraffic();
    const bool TRAFFIC_ON = pms.getParam(i++);      // do not input
    const bool FATIGUE_ON = pms.getParam(i++);      // do not input
    const bool DEBUG_ON = pms.getParam(i++);
}

#endif