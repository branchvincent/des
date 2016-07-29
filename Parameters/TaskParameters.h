/****************************************************************************
*																			*
*	File:		TaskParameters.h											*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jun 24, 2016												*
*																			*
*	Purpose:	This file defines the global task variables used by the 	*
*				simulation.													*
*																			*
****************************************************************************/

#ifndef TASKPARAMETERS_H
#define TASKPARAMETERS_H

#include "LoadTaskParameters.h"
#include <vector>

using namespace std;

namespace tparams
{
//  Load parameters
    
    cout << "Called TASK PARAMETERS" << endl;
    
    LoadTaskParameters T_PMS;
}

#endif
