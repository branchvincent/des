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

	const int NUM_RUNS = 100;
	const bool OUTPUT = true;
	const bool RAND_RUN = true;
	
//	One run details
	
	const int END_TIME = 100;
	const int INT_SIZE = 10;
	const int NUM_HOURS = (END_TIME/60. + 0.5);
	const int NUM_INTS = END_TIME/INT_SIZE;
	const int NUM_TASK_TYPES = 9;
	const int NUM_PHASES = 3;
	const int NUM_STATS = 5;
	const bool DEBUG = false;
	
//	const int TASKS;
}
 
#endif