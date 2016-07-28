/****************************************************************************
*																			*
*	File:		TaskParameters.h											*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jul 12, 2016												*
*																			*
*	Purpose:	This file defines the TaskParameters class.					*
*																			*
****************************************************************************/

#ifndef TASKPARAMETERS_H
#define TASKPARAMETERS_H

#include <iostream>
#include <string>
#include <random>
#include <cmath>
#include "Parameters.h"

using namespace std;
using namespace params;

/****************************************************************************
*																			*
*	Definition of TaskParameters class										*
*																			*
****************************************************************************/

class TaskParameters
{
//	Public member functions

	public:

	//	Constructor
		
		TaskParameters();

	//	Inspectors
		

	//	Mutators
	
	
//	Data members

	private:
		int* prty[NUM_TASK_TYPES][NUM_PHASES];
		char* arrDists[NUM_TASK_TYPES][NUM_PHASES];
		char* serDists[NUM_TASK_TYPES][NUM_PHASES];
		char* expDists[NUM_TASK_TYPES][NUM_PHASES];
		float* arrDistParams[NUM_TASK_TYPES][NUM_PHASES];
		float* serDistParams[NUM_TASK_TYPES][NUM_PHASES];
		float* expDistParams[2][NUM_TASK_TYPES][NUM_PHASES];
		bool* affByTraff[NUM_TASK_TYPES][NUM_PHASES];
		float percAllowed[NUM_TASK_TYPES];
};

//	Operators

ostream& operator<<(ostream& out, const Task& t) {t.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	TaskParameters												*
*																			*
*	Purpose:	To construct a task of the specified type using the 		*
*				specified previous arrival time and distribution seed		*
*																			*
****************************************************************************/

TaskParameters::TaskParameters()
{
//	Set priorities

			//	P0,	P1,	P2
	prty = 	{	{4, 3, 	4},		// Communicating
				{5, 4, 	5}, 	// Exception handling
				{3,	0, 	2},		// Paperwork
				{0, 5, 	0},		// Maintenance of way
				{0, 5, 	0},		// Temp speed restriction
				{0, 5, 	0},		// Signal response management
				{2, 2, 	1},		// Monitoring inside
				{1, 1, 	3},		// Monitoring outisde
				{0, 5, 	0}		// Planning ahead
		 	};
	
//	Set arrival distributions

	arrDists = 'E';     //  not mutable

						//	P0,		P1,		P2
	arrDistParams = 	{	{1/3., 	0.2, 	1/3.},		// Communicating
							{0, 	.1/30, 	.1/30}, 	// Exception handling
							{1/3., 	1/30., 	1/3.},		// Paperwork
							{0, 	.05/30, .5/30},		// Maintenance of way
							{0, 	1/30., 	0},			// Temp speed restriction
							{1/30., 0.1, 	1/15.},		// Signal response management
							{1/15., 0.1, 	0},			// Monitoring inside
							{0.1, 	0.2, 	0.1},		// Monitoring outisde
							{1/30., 1/15., 1/30.}		// Planning ahead
				 	 	};	

//	Set service distributions

	serDists = 	{	'E',	// Communicating
					'L', 	// Exception handling
					'U',	// Paperwork
					'U',	// Maintenance of way
					'U',	// Temp speed restriction
					'U',	// Signal response management
					'E',	// Monitoring inside
					'E',	// Monitoring outisde
					'E'		// Planning ahead
		 	 	};	// not mutable (default E)

	serDistParams = {	{1/0.133,	0},			// Communicating
						{0.980297, 	1.389685}, 	// Exception handling
						{0.05, 		2},			// Paperwork
						{0.167, 	1},			// Maintenance of way
						{0.1, 		0.5},		// Temp speed restriction
						{0.1, 		0.5},		// Signal response management
						{1/0.133,	0},			// Monitoring inside
						{1/0.1,		0},			// Monitoring outisde
						{1/0.33,	0}			// Planning ahead
			 	 	};	// same as serDist


//	Set expiration distributions

	expDists = 'E';     // not mutable
	
						//	P0,	P1,				P2
	expDistParams[0] = {	{0,	0.086333333,	0},				// Communicating
							{0,	0.055166667,	0.055166667}, 	// Exception handling
							{0,	0,				0},				// Paperwork
							{0,	0.184,			0},				// Maintenance of way
							{0,	0.184,			0},				// Temp speed restriction
							{0,	0.184,			0.184},			// Signal response management
							{0,	0,				0},				// Monitoring inside
							{0,	0,				0},				// Monitoring outisde
							{0,	0.1795,			0}				// Planning ahead
				 	 	}; // use formula (not mutable)
				
						//	P0,	P1,				P2
	expDistParams[1] =	{	{0,	0.107166667,	0},				// Communicating
							{0,	0.044666667,	0.044666667}, 	// Exception handling
							{0,	0,				0},				// Paperwork
							{0,	0.184,			0},				// Maintenance of way
							{0,	0.184,			0},				// Temp speed restriction
							{0,	0.184,			0.184},			// Signal response management
							{0,	0,				0},				// Monitoring inside
							{0,	0,				0},				// Monitoring outisde
							{0,	0.166,			0}				// Planning ahead
				 	 	};	// use formula (not mutable)

//	Set tasks affected by traffic
	
					//	P0, P1,	P2
	affByTraff =	{	{0,	1,	0},		// Communicating
						{0, 1, 	0}, 	// Exception handling
						{0, 1, 	1},		// Paperwork
						{0, 1, 	0},		// Maintenance of way
						{0, 1, 	0},		// Temp speed restriction
						{0, 1, 	0},		// Signal response management
						{0, 0, 	0},		// Monitoring inside
						{0, 1, 	0},		// Monitoring outisde
						{0, 1, 	0}		// Planning ahead
		 		 	}; // set (if add new, choose for that specific task type)

//	Set percent of tasks to be completed before jockeying

                    //  allow to vary by phase
	percAllowed[9] = {	0.1,	// Communicating
						0.8, 	// Exception handling
						0.5,	// Paperwork
						0.25,	// Maintenance of way
						0.5,	// Temp speed restriction
						1,		// Signal response management
						1,		// Monitoring inside
						0.5,	// Monitoring outisde
						1		// Planning ahead
		 	 		};	
    
	return;
}

#endif