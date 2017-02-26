///****************************************************************************
//*																			*
//*	File:		Parameters.h												*
//*																			*
//*	Author:		Branch Vincent												*
//*																			*
//*	Date:		Jun 24, 2016												*
//*																			*
//*	Purpose:	This file defines the global variables used by the 			*
//*				simulation.													*
//*																			*
//****************************************************************************/
//
//#ifndef PARAMETERS_H
//#define PARAMETERS_H
//
//#include <vector>
//#include <string>
//#include "LoadParameters.h"
//
//using namespace std;
//
//template <typename T>
//using Matrix2D = vector<vector<T> >;
//template <typename T>
//using Matrix3D = vector<Matrix2D<T> >;
//
//// Notes
//// - Add ability to pick phase to run
//// - Input start and end time (can be random multiple)
//
//namespace params
//{
////  Declare parameters
//
//	string OUTPUT_PATH;
//	int NUM_HOURS;
//	int NUM_REPS;
//	int END_TIME;
//	int NUM_INTS;
//	int NUM_TASK_TYPES;
//	vector<float> TRAFFIC;
//	vector<int> OPS;
//
//	const int INT_SIZE = 10;
//	const int NUM_PHASES = 3;
//	int CURR_TRAIN = 0;
//
////	Debugging
//
//	const bool TRAFFIC_ON = 1;
//	const bool FATIGUE_ON = 1;
//	const bool DEBUG_ON = 0;
//	const bool OUTPUT_ON = 1;
//	const bool RAND_RUN_ON = 1;
//	const bool VERBOSE = 1;
//
////	Operator parameters
//
//	int NUM_OPS;
//	vector<string> OP_NAMES;
//	Matrix2D<int> OP_TASKS;
//	Matrix2D<int> OP_NUMS;
//
//	Matrix2D<int> DP_TASKS;
//	Matrix2D<int> DP_NUMS;
//
////  Task parameters
//
//	vector<string> TASK_NAMES;
//	Matrix2D<int> PRTY;
//	vector<char> ARR_DISTS;
//	Matrix2D<float> ARR_DIST_PARAMS;
//	vector<char> SER_DISTS;
//	Matrix2D<float> SER_DIST_PARAMS;
//	vector<char> EXP_DISTS;
//	Matrix2D<float> EXP_DIST_PARAMS_LOW;
//	Matrix2D<float> EXP_DIST_PARAMS_HIGH;
//	Matrix2D<int> AFF_BY_TRAFF;
//
////  Initialize global parameters
//
//	void INIT_GLOBALS(LoadParameters& pms)
//	{
//	//	General
//
//		OUTPUT_PATH = pms.outputPath;
//		NUM_HOURS = pms.numHours;
//		NUM_REPS = pms.numReps;
//		END_TIME = NUM_HOURS * 60;
//		NUM_INTS = END_TIME / INT_SIZE;
//		NUM_OPS = (int)pms.ops.size();
//		NUM_TASK_TYPES = pms.numTaskTypes;
//		TRAFFIC = pms.traffic;
//		OPS = pms.ops;
//
//	//	Operators
//
//		NUM_OPS = pms.numOps;
//		OP_NAMES = pms.opNames;
//		OP_TASKS = pms.opTasks;
//		OP_NUMS = pms.opNums;
//
//		DP_TASKS = pms.dpTasks;
//		DP_NUMS = pms.dpNums;
//
//	//	Tasks
//
//		TASK_NAMES = pms.taskNames;
//		PRTY = pms.taskPrty;
//		ARR_DISTS = pms.arrDists;
//		ARR_DIST_PARAMS = pms.arrPms;
//		SER_DISTS = pms.serDists;
//		SER_DIST_PARAMS = pms.serPms;
//		EXP_DISTS = pms.expDists;
//		EXP_DIST_PARAMS_LOW = pms.expPmsLo;
//		EXP_DIST_PARAMS_HIGH = pms.expPmsHi;
//		AFF_BY_TRAFF = pms.affByTraff;
//
////		for (int i = 0; i < NUM_TASK_TYPES; i++)
////			DP_TASKS.push_back(i);
//	}
//}
//
//#endif
