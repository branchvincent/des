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
//	Data analysis details
	
	const string FILE_PATH = "/Users/Branch/Documents/Academic/Year 1/Summer/DES Code/Data/";
	const string ONE_RUN_FILE = FILE_PATH + "singleRun.csv";
	const string BATCH_RUN_FILE = FILE_PATH + "batchRun.csv";
	const string ONE_RUN_STATS_FILE = FILE_PATH + "singleStats.csv";
	const string BATCH_RUN_STATS_FILE = FILE_PATH + "batchStats.csv";
	
//	Batch run details

	const int NUM_RUNS = 100;
	const bool OUTPUT = false;
	const bool RAND_RUN = true;
	
//	One run details
	
	const int END_TIME = 90;
	const int INT_SIZE = 10;
	const int NUM_HOURS = (END_TIME/60. + 0.5);
	const int NUM_INTS = END_TIME/INT_SIZE;
	const int NUM_TASK_TYPES = 9;
	const int NUM_PHASES = 3;
	const int NUM_STATS = 3;
	int TRAFFIC_LEVELS;
	const bool DEBUG = false;
}
 
#endif