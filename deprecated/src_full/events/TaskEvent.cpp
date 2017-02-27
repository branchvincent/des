/****************************************************************************
*																			*
*	File:		TaskEvent.cpp												*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the TaskEvent class.	   					*
*																			*
****************************************************************************/

#include <iostream>
#include <string>
#include "TaskEvent.h"
// #include "Task.h"
// #include "Agent.h"
// #include "../Utility.h"

using namespace std;

/****************************************************************************
*																			*
*	Function:	TaskEvent       										    *
*																			*
*	Purpose:	To construct an event                                       *
*																			*
****************************************************************************/

TaskEvent::TaskEvent(DateTime time, Task* task) : Event(time), task(task) //, agent(agent)
{}

// const Task& TaskEvent::getTask() const {return &task;}

/****************************************************************************
*																			*
*	Function:	output       												*
*																			*
*	Purpose:	To output an event                                       	*
*																			*
****************************************************************************/

// void Event::output(ostream& out) const
// {
// 	out << "Time: " << time << endl;
// 	// out << "Agent: " << agent << endl;
// }
