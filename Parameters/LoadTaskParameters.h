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

LoadTaskParameters::LoadTaskParameters() :

        //	P0,	P1,	P2
    prty{   {4, 3, 	4},		// Communicating
            {5, 4, 	5}, 	// Exception handling
            {3,	0, 	2},		// Paperwork
            {0, 5, 	0},		// Maintenance of way
            {0, 5, 	0},		// Temp speed restriction
            {0, 5, 	0},		// Signal response management
            {2, 2, 	1},		// Monitoring inside
            {1, 1, 	3},		// Monitoring outisde
            {0, 5, 	0}		// Planning ahead
            },

    arrDist('E'),                                                      //  not mutable


    serDists{   'E',	// Communicating
                'L', 	// Exception handling
                'U',	// Paperwork
                'U',	// Maintenance of way
                'U',	// Temp speed restriction
                'U',	// Signal response management
                'E',	// Monitoring inside
                'E',	// Monitoring outisde
                'E'		// Planning ahead
            },                                                          // not mutable (default E)

    expDist('E'),                                                      //  not mutable

                //	P0,		P1,		P2
    arrDistParams{	{1/3., 	0.2, 	1/3.},		// Communicating
                    {0, 	.1/30, 	.1/30}, 	// Exception handling       *change 0 to determinisitic*
                    {1/3., 	1/30., 	1/3.},		// Paperwork
                    {0, 	.05/30, .5/30},		// Maintenance of way
                    {0, 	1/30., 	0},			// Temp speed restriction
                    {1/30., 0.1, 	1/15.},		// Signal response management
                    {1/15., 0.1, 	0},			// Monitoring inside
                    {0.1, 	0.2, 	0.1},		// Monitoring outisde
                    {1/30., 1/15., 1/30.}		// Planning ahead
                    },

                //  Param1,     Param2
    serDistParams{	{1/0.133,	0},			// Communicating
                    {0.980297, 	1.389685}, 	// Exception handling
                    {0.05, 		2},			// Paperwork
                    {0.167, 	1},			// Maintenance of way
                    {0.1, 		0.5},		// Temp speed restriction
                    {0.1, 		0.5},		// Signal response management
                    {1/0.133,	0},			// Monitoring inside
                    {1/0.1,		0},			// Monitoring outisde
                    {1/0.33,	0}			// Planning ahead
                    },                                                      // same as serDist

                    //	P0,	P1,				P2
    expDistParamsLow{	{0,	0.107166667,	0},				// Communicating
                        {0,	0.044666667,	0.044666667}, 	// Exception handling
                        {0,	0,				0},				// Paperwork
                        {0,	0.184,			0},				// Maintenance of way
                        {0,	0.184,			0},				// Temp speed restriction
                        {0,	0.184,			0.184},			// Signal response management
                        {0,	0,				0},				// Monitoring inside
                        {0,	0,				0},				// Monitoring outisde
                        {0,	0.166,			0}				// Planning ahead
                    },                                                      // use formula (not mutable)

                    //	P0,	P1,				P2
    expDistParamsHigh{	{0,	0.086333333,	0},				// Communicating
                        {0,	0.055166667,	0.055166667}, 	// Exception handling
                        {0,	0,				0},				// Paperwork
                        {0,	0.184,			0},				// Maintenance of way
                        {0,	0.184,			0},				// Temp speed restriction
                        {0,	0.184,			0.184},			// Signal response management
                        {0,	0,				0},				// Monitoring inside
                        {0,	0,				0},				// Monitoring outisde
                        {0,	0.1795,			0}				// Planning ahead
                    },                                                      // use formula (not mutable)

            //	P0, P1,	P2
    affByTraff{ {0,	1,	0},		// Communicating
                {0, 1, 	0}, 	// Exception handling
                {0, 1, 	1},		// Paperwork
                {0, 1, 	0},		// Maintenance of way
                {0, 1, 	0},		// Temp speed restriction
                {0, 1, 	0},		// Signal response management
                {0, 0, 	0},		// Monitoring inside
                {0, 1, 	0},		// Monitoring outisde
                {0, 1, 	0}		// Planning ahead
                },                                                          // set (if add new, choose for that specific task type)

    opNum{	0,	// Communicating
            0, 	// Exception handling
            0,	// Paperwork
            0,	// Maintenance of way
            0,	// Temp speed restriction
            2,	// Signal response management
            2,	// Monitoring inside
            0,	// Monitoring outisde
            2	// Planning ahead
        }                                                               //  allow to vary by phase
{
    return;
}

#endif