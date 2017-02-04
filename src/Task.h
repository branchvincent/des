/****************************************************************************
*																			*
*	File:		Task.h														*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Task class.							*
*																			*
****************************************************************************/

#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <string>
#include <random>
#include <cmath>
#include <algorithm>
// #include "params/Parameters.h"

using namespace std;

/****************************************************************************
*																			*
*	Definition of Task class												*
*																			*
****************************************************************************/

class Task
{
//	Public member functions

	public:

	//	Constructor

		// Task()  :   type(type),
		//     priority(priority),
		//     arrTime(arrTime),
		//     serTime(serTime),
		// 	depTime(INFINITY),
		// 	expTime(expTime),
		//     begTime(0),
		//     queTime(arrTime),
		//     serLeft(serTime)
		// 	{}
		Task(string type, float priority, float arrTime, float serTime, float expTime);

	//	Inspectors

		string getType() const {return type;}
		int getPriority() const {return priority;}
		float getArrTime() const {return arrTime;}
		float getSerTime() const {return serTime;}
		float getDepTime() const {return depTime;}
		float getExpTime() const {return expTime;}
        float getBegTime() const {return begTime;}
        float getQueTime() const {return queTime;}
        float getSerLeft() const {return serLeft;}

	//	Mutators

		// void setArrTime(float t) {arrTime = t;}
		// void setSerTime(float t) {serTime = t;}
		// void setDepTime(float t) {depTime = t;}
        // void setSerLeft(float t) {serLeft = t;}
        // void setBegTime(float t) {begTime = t;}
        // void setQueTime(float t) {queTime = t;}

	//	Other member functions

		void output(ostream& out) const;
		bool higherPriority(const Task& task) const;
		bool arrivesSooner(const Task& task) const
			{return this->getArrTime() < task.getArrTime();}

//	Data members

	private:
		string type;		// type
		int priority;		// priority level
		float arrTime;		// arrival time (min)
		float serTime; 		// service time (min)
		float depTime;		// depature time (min)
		float expTime;		// expiration time (min)
		float begTime;		// begin service time (min)
        float queTime;      // enter queue time (min)
        float serLeft;      // service time left
};

//	Operators

ostream& operator<<(ostream& out, const Task& t) {t.output(out); return out;}
bool operator>(const Task& t1, const Task& t2) {return t1.higherPriority(t2);}
bool operator<(const Task& t1, const Task& t2) {return !t1.higherPriority(t2);}

/****************************************************************************
*																			*
*	Function:	Task														*
*																			*
*	Purpose:	To construct a task of the specified type using the 		*
*				specified previous arrival time and distribution seed		*
*																			*
****************************************************************************/

Task::Task(string type, float priority, float arrTime, float serTime, float expTime) :
    type(type),
    priority(priority),
    arrTime(arrTime),
    serTime(serTime),
	depTime(INFINITY),
	expTime(expTime),
    begTime(0),
    queTime(arrTime),
    serLeft(serTime)
{
// //	if (aTime != -1)
// 	{
// 		arrTime = aTime;
// 	}

}

/****************************************************************************
*																			*
*	Function:	output														*
*																			*
*	Purpose:	To output a task											*
*																			*
****************************************************************************/

void Task::output(ostream& out) const
{
	cout << "Priority: " << priority << ", ";
	cout << "Type " << type << ", ";
	cout << "Arr " << arrTime << ", ";
	cout << "Ser " << serTime <<  ", ";
	cout << "Dep " << depTime << ", ";
	cout << "Exp " << expTime << ")";
	return;
}

/****************************************************************************
*																			*
*	Function:	greaterPriority												*
*																			*
*	Purpose:	To return if the specified task if of higher priority		*
*																			*
****************************************************************************/

bool Task::higherPriority(const Task& task) const
{
	if (this->getPriority() == task.getPriority())
		return this->getExpTime() < task.getExpTime();
	else
		return this->getPriority() > task.getPriority();
}

#endif
