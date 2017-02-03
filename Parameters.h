/****************************************************************************
*																			*
*	File:		Parameters.h												*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Parameters class.						*
*																			*
****************************************************************************/

#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <iostream>
#include <string>

using namespace std;

/****************************************************************************
*																			*
*	Definition of Parameters class		     						        *
*																			*
****************************************************************************/

class Parameters
{
//	Public member functions

	public:

    //  Constructor

		Parameters(string file);

	//	Inspectors

    //  Other member functions

//	Data members

	public:
    //	General settings

    //     string outputPath;
    //     float numHours;
    //     vector<float> traffic;
    //     float numReps;
    //     vector<int> ops;
    //
	// //	Operator settings
    //
	// 	int numOps;
	// 	vector<string> opNames;
	// 	Matrix2D<int> opTasks;
	// 	Matrix2D<int> opNums;
    //
	// 	Matrix2D<int> dpTasks;
	// 	Matrix2D<int> dpNums;
};

#endif
