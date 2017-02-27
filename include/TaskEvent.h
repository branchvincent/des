/****************************************************************************
*																			*
*	File:		TaskEvent.h											        *
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the TaskEvent class.	   					*
*																			*
****************************************************************************/

#ifndef TASKEVENT_H
#define TASKEVENT_H

#include <iostream>
#include <string>
// #include "../DateTime.h"
#include "Event.h"
#include "Task.h"

using namespace std;

// class Task;
// class Agent;

/****************************************************************************
*																			*
*	Definition of TaskEvent class	     						            *
*																			*
****************************************************************************/

class TaskEvent : public Event
{
//	Public member functions

	public:

    //  Constructor

		TaskEvent(DateTime time, Task* task); //, Agent& agent);

	//	Inspectors

		// const Task& getTask() const;

	//	Other member functions

		// virtual void output(ostream& out) const = 0;

//	Data members

	protected:
		Task* task;
};

//	Operators

// ostream& operator<<(ostream& out, const Event& e);

#endif
