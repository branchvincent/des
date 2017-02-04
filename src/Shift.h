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
#include "Util.h"

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

		Shift(string start = "19:00", string stop = "17:00");

	//	Inspectors

        string getStart() const {return asctime(&start);}
        string getStop() const {return asctime(&stop);}
        // string getStart() {return string(put_time(&start, "%c"));}
        float getHours() const
            {ASSERT(duration > 0, "Shift duration cannot be negative");
            return duration/3600.;}

	//	Other member functions

		void output(ostream& out) const;

//  Private member members

    private:
        void readTimeString(string time, tm& date);

//	Data members

	private:
        tm start;
        tm stop;
        time_t duration;
};

//	Operators

ostream& operator<<(ostream& out, const Shift& s) {s.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	Shift       												*
*																			*
*	Purpose:	To construct a shift                                        *
*																			*
****************************************************************************/

Shift::Shift(string start, string stop)
{
//  Read times

    readTimeString(start, this->start);
    readTimeString(stop, this->stop);

//  Calculate duration

	duration = difftime(timegm(&(this->stop)), timegm(&(this->start)));
    if (duration < 0)
    {
        (this->stop).tm_mday += 1;
        duration = difftime(mktime(&(this->stop)), mktime(&(this->start)));
    }
}

/****************************************************************************
*																			*
*	Function:	readTimeString												*
*																			*
*	Purpose:	To create a date from a time string                         *
*																			*
****************************************************************************/

void Shift::readTimeString(string time, tm& date)
{
    istringstream stream("2017-01-01 " + time);
    stream >> get_time(&date, "%Y-%m-%d %H:%M");
    ASSERT(!stream.fail(), "Failed to read time " << time);
    return;
}

/****************************************************************************
*																			*
*	Function:	output														*
*																			*
*	Purpose:	To output a shift					                        *
*																			*
****************************************************************************/

void Shift::output(ostream& out) const
{
    out << put_time(&start, "%H:%M") << " to " << put_time(&stop, "%H:%M");
    return;
}

#endif
