/****************************************************************************
*																			*
*	File:		DateTime.h												    *
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the DateTime class.	   				 	*
*																			*
****************************************************************************/

#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "Utility.h"

using namespace std;

/****************************************************************************
*																			*
*	Definition of DateTime class		     						        *
*																			*
****************************************************************************/

class DateTime
{
//	Public member functions

	public:

    //  Constructor

		inline DateTime(string dateTime = "01-10 9:00");
		DateTime(time_t time) : time(time) {}

	//	Inspectors

		tm getDateTime() const {return *gmtime(&time);}
		const time_t& getRawTime() const {return time;}
		inline string getDateTimeString(string format = "%b-%d-%Y, %H:%M:%S") const;

	//	Mutators

		void addSecs(float secs) {time += secs;}
		void addMins(float mins) {time += util::minToSec(mins);}

	//	Operators

		DateTime& operator+=(const time_t& time) {this->time += time; return *this;}
		DateTime& operator-=(const time_t& time) {this->time -= time;
			ASSERT(time >= 0, "Time cannot be negative."); return *this;}

	//	Other member functions

		time_t secondsAfter(const DateTime& date) const {return time - date.time;}
		bool before(const DateTime& date) const {return time < date.time;}
		void output(ostream& out) const {out << getDateTimeString();}

//	Data members

	public:
		time_t time;
};

//	Operators

inline ostream& operator<<(ostream& out, const DateTime& d) {d.output(out); return out;}
inline bool operator<(const DateTime& d1, const DateTime& d2) {return d1.before(d2);}
inline bool operator>(const DateTime& d1, const DateTime& d2) {return !d1.before(d2);}
inline time_t operator-(const DateTime& d1, const DateTime& d2) {return d1.secondsAfter(d2);}
inline DateTime operator+(const DateTime& d, const time_t& seconds) {return DateTime(d.time + seconds);}

/****************************************************************************
*																			*
*	Function:	Shift       												*
*																			*
*	Purpose:	To construct a shift                                        *
*																			*
****************************************************************************/

DateTime::DateTime(string dateTime)
{
//  Convert string to date

	tm temp;
	istringstream stream("2017-" + dateTime + ":00");
	stream >> get_time(&temp, "%Y-%m-%d %H:%M:%S");
	ASSERT(!stream.fail(), "Failed to read time " << dateTime <<
		". DateTime must be of 'Mon-Day Hr:Min' format");

//	Convert date to time

	time = timegm(&temp);
	ASSERT(time != -1, "Failed to convert " << dateTime << " to time");
}

/****************************************************************************
*																			*
*	Function:	getDateTimeString											*
*																			*
*	Purpose:	To return the date as a string		                        *
*																			*
****************************************************************************/

string DateTime::getDateTimeString(string format) const
{
//	Get date time

	const char* f = format.c_str();
	tm* temp = gmtime(&time);

//	Convert to string and return

	stringstream stream;
	stream << put_time(temp, f);
	return stream.str();
}

#endif
