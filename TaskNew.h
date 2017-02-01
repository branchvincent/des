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
#include "params/Parameters.h"

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

		void output(ostream& out) const
			{cout << "(Pr " << priority << ", Tp " << type << ", Arr " << arrTime;
			cout << ", Ser " << serTime <<  ", Dep " << depTime << ", Exp " << expTime << ")";}

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

#endif
