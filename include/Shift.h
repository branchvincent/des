/****************************************************************************
*																			*
*	File:		Shift.h												        *
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Shift class.	   					    *
*																			*
****************************************************************************/

#ifndef SHIFT_H
#define SHIFT_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "datetime.h"
#include "utility.h"

using namespace std;

/****************************************************************************
*																			*
*	Definition of Shift class		     						            *
*																			*
****************************************************************************/

class Shift
{
//	Public member functions

	public:

    //  Constructor

		inline Shift(vector<string> times);
		inline Shift(string t1 = "01-01 9:00", string t2 = "01-01 17:00");

	//	Inspectors

		const DateTime& getStart() const {return start;}
		const DateTime& getStop() const {return stop;}
		const time_t& getDuration() const {return duration;}
        // float getHours() const {return duration/3600.;}

	//	Other member functions

		inline void output(ostream& out) const {out << start << " to " << stop << endl;}

//	Data members

	public:
        DateTime start;
		DateTime stop;
		time_t duration;
};

//	Operators

inline ostream& operator<<(ostream& out, const Shift& s) {s.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	Shift       												*
*																			*
*	Purpose:	To construct a shift                                        *
*																			*
****************************************************************************/

Shift::Shift(vector<string> times)
{
	ASSERT(times.size() == 2, "A shift requires two times");
	*this = Shift(times[0], times[1]);
}

/****************************************************************************
*																			*
*	Function:	Shift       												*
*																			*
*	Purpose:	To construct a shift                                        *
*																			*
****************************************************************************/

Shift::Shift(string t1, string t2) : start(t1), stop(t2)
{
	ASSERT(start < stop, "Shift cannot end before it begins");
	duration = stop - start;
}

#endif
