/****************************************************************************
*																			*
*	File:		LoadTaskParameters.h										*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jul 12, 2016												*
*																			*
*	Purpose:	This file defines the LoadTaskParameters class.				*
*																			*
****************************************************************************/

#ifndef LOADTASKPARAMETERS_H
#define LOADTASKPARAMETERS_H

#include <iostream>
#include <string>
#include <random>
#include <cmath>
#include "Parameters.h"

using namespace std;
using namespace params;

/****************************************************************************
*																			*
*	Definition of LoadTaskParameters class									*
*																			*
****************************************************************************/

// Notes
// - This class is not being used
// - Update to work

class LoadTaskParameters
{
//	Public member functions

	public:

	//	Constructor
		
		LoadTaskParameters();

	//	Inspectors
		
	//	Mutators
	
//	Data members

	public:
		int prty[NUM_TASK_TYPES][NUM_PHASES];
		char arrDist;
		char serDists[NUM_TASK_TYPES];
		char expDist;
		float arrDistParams[NUM_TASK_TYPES][NUM_PHASES];
		float serDistParams[NUM_TASK_TYPES][2];
		float expDistParamsLow[NUM_TASK_TYPES][NUM_PHASES];
        float expDistParamsHigh[NUM_TASK_TYPES][NUM_PHASES];
		bool affByTraff[NUM_TASK_TYPES][NUM_PHASES];
        int opNum[NUM_TASK_TYPES];
};

/****************************************************************************
*																			*
*	Function:	LoadTaskParameters											*
*																			*
*	Purpose:	To construct a task of the specified type using the 		*
*				specified previous arrival time and distribution seed		*
*																			*
****************************************************************************/

LoadTaskParameters::LoadTaskParameters() //  allow to vary by phase
{
    return;
}

#endif