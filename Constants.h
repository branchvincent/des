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
 
namespace cnsts
{
//	Batch run details

	const int NUM_RUNS = 5;
	const bool OUTPUT_ON = true;
	const bool RAND_RUN_ON = false;
	
//	One run details
	
	const int END_TIME = 90;
	const int INT_SIZE = 30;
	const int NUM_HOURS = (END_TIME/60. + 0.5);
	const int NUM_INTS = END_TIME/INT_SIZE;
	const int NUM_TASK_TYPES = 9;
	const int NUM_PHASES = 3;
	const int NUM_STATS = 6;
	const bool DEBUG_ON = true;
	const bool TRAFFIC_ON = false;
	const bool FATIGUE_ON = false;
	
//	const int TASKS;
}
 
#endif