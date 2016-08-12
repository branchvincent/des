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
//#include "LoadTaskParameters.h"


using namespace std;
typedef vector<vector<int> > Matrix;

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
    int NUM_OPS;
    
    vector<float> TRAFFIC;
    vector<int> OPS;
    const bool TRAFFIC_ON = 1;
    const bool FATIGUE_ON = 1;
    const bool DEBUG_ON = 0;
    
//  Task parameters
    
                            //	P0,	P1,	P2
    const int PRTY[][3] =   {   {4, 3, 	4},		// Communicating
                                {5, 4, 	5}, 	// Exception handling
                                {3,	0, 	2},		// Paperwork
                                {0, 5, 	0},		// Maintenance of way
                                {0, 5, 	0},		// Temp speed restriction
                                {0, 5, 	0},		// Signal response management
                                {2, 2, 	1},		// Monitoring inside
                                {1, 1, 	3},		// Monitoring outisde
                                {0, 5, 	0}		// Planning ahead
                            };
    
    const char ARR_DIST = 'E';                                     //  not mutable
    
    const char SER_DISTS[] =    {   'E',	// Communicating
                                    'L', 	// Exception handling
                                    'U',	// Paperwork
                                    'U',	// Maintenance of way
                                    'U',	// Temp speed restriction
                                    'U',	// Signal response management
                                    'E',	// Monitoring inside
                                    'E',	// Monitoring outisde
                                    'E'		// Planning ahead
                                };                                                      // not mutable (default E)
    
    const char EXP_DIST = 'E';                                                   //  not mutable
    
                                        //	P0,		P1,		P2
    const float ARR_DIST_PARAMS[][3] = {	{1/3., 	0.2, 	1/3.},		// Communicating
                                            {0, 	.1/30, 	.1/30}, 	// Exception handling       *change 0 to determinisitic*
                                            {1/3., 	1/30., 	1/3.},		// Paperwork
                                            {0, 	.05/30, .5/30},		// Maintenance of way
                                            {0, 	1/30., 	0},			// Temp speed restriction
                                            {1/30., 0.1, 	1/15.},		// Signal response management
                                            {1/15., 0.1, 	0},			// Monitoring inside
                                            {0.1, 	0.2, 	0.1},		// Monitoring outisde
                                            {1/30., 1/15., 1/30.}		// Planning ahead
                                        };
    
                                        //  Param1,     Param2
    const float SER_DIST_PARAMS[][2] = {	{1/0.133,	0},			// Communicating
                                            {0.980297, 	1.389685}, 	// Exception handling
                                            {0.05, 		2},			// Paperwork
                                            {0.167, 	1},			// Maintenance of way
                                            {0.1, 		0.5},		// Temp speed restriction
                                            {0.1, 		0.5},		// Signal response management
                                            {1/0.133,	0},			// Monitoring inside
                                            {1/0.1,		0},			// Monitoring outisde
                                            {1/0.33,	0}			// Planning ahead
                                        };                                                  // same as serDist
    
                                            //	P0,	P1,				P2
    const float EXP_DIST_PARAMS_LOW[][3] =  {	{0,	0.107166667,	0},				// Communicating
                                                {0,	0.044666667,	0.044666667}, 	// Exception handling
                                                {0,	0,				0},				// Paperwork
                                                {0,	0.184,			0},				// Maintenance of way
                                                {0,	0.184,			0},				// Temp speed restriction
                                                {0,	0.184,			0.184},			// Signal response management
                                                {0,	0,				0},				// Monitoring inside
                                                {0,	0,				0},				// Monitoring outisde
                                                {0,	0.166,			0}				// Planning ahead
                                            };                                                      // use formula (not mutable)
    
                                            //	P0,	P1,				P2
    const float EXP_DIST_PARAMS_HIGH[][3] = {	{0,	0.086333333,	0},				// Communicating
                                                {0,	0.055166667,	0.055166667}, 	// Exception handling
                                                {0,	0,				0},				// Paperwork
                                                {0,	0.184,			0},				// Maintenance of way
                                                {0,	0.184,			0},				// Temp speed restriction
                                                {0,	0.184,			0.184},			// Signal response management
                                                {0,	0,				0},				// Monitoring inside
                                                {0,	0,				0},				// Monitoring outisde
                                                {0,	0.1795,			0}				// Planning ahead
                                            };                                                      // use formula (not mutable)
    
                                    //	P0, P1,	P2
    const int AFF_BY_TRAFF[][3] =   {   {0,	1,	0},		// Communicating
                                        {0, 1, 	0}, 	// Exception handling
                                        {0, 1, 	1},		// Paperwork
                                        {0, 1, 	0},		// Maintenance of way
                                        {0, 1, 	0},		// Temp speed restriction
                                        {0, 1, 	0},		// Signal response management
                                        {0, 0, 	0},		// Monitoring inside
                                        {0, 1, 	0},		// Monitoring outisde
                                        {0, 1, 	0}		// Planning ahead
                                    };                                                          // set (if add new, choose for that specific task type)
    
    const Matrix OP_NUM{    {0},        // Communicating
                            {0, 2}, 	// Exception handling
                            {0},        // Paperwork
                            {0},     // Maintenance of way
                            {0},     // Temp speed restriction
                            {0, 1, 2},	// Signal response management
                            {0, 1, 2},	// Monitoring inside
                            {0},        // Monitoring outisde
                            {0, 1, 3},	// Planning ahead
                        };

//  Set parameters
    
    void setOutputPath(string path) {OUTPUT_PATH = path;}
    void setNumHours(int num)
        {NUM_HOURS = num; END_TIME = NUM_HOURS * 60; NUM_INTS = END_TIME/INT_SIZE;}
    void setNumReps(int reps) {NUM_REPS = reps;}
    void setTraffic(vector<float> traff)
        {for (int i = 0; i < traff.size(); i++) TRAFFIC.push_back(traff[i]);}
    void setOps(vector<int> ops)
        {NUM_OPS = ops.size(); for (int i = 0; i < ops.size(); i++) OPS.push_back(ops[i]);}
}

#endif