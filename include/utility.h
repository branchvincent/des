/****************************************************************************
*																			*
*	File:		Utility.h													*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Util namespace.					    *
*																			*
****************************************************************************/

#ifndef UTILITY_H
#define UTILITY_H

#include <sys/stat.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <sstream>
#include <algorithm>
#include <list>
#include <iterator>
#include "easylogging++.h"

using namespace std;

//  Assert function to output error message

#define MAX_TIME numeric_limits<int>::max()
#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            cerr << "ASSERTION ERROR: " << message << "." << endl; \
            cerr << "In " << __FILE__ << ", line " << __LINE__ << ": '" << #condition << "' failed" << endl; \
			cerr << "Exiting..." << endl; \
            terminate(); \
        } \
    } while (false)


/****************************************************************************
*																			*
*	Definition of Util namespace											*
*																			*
****************************************************************************/

namespace util
{
//  Classes

    class Timer;

//	Public member functions

    inline void initLogger();

    inline bool exists(string file) {//{return (access(file.c_str(), F_OK) != -1 );}
        struct stat buffer;
        return stat(file.c_str(), &buffer) == 0;
    }

    template <class T> vector<T> toVector(string data, char delimiter = ',');

    inline string toLower(string s)
        {transform(s.begin(), s.end(), s.begin(), ::tolower); return s;}

    inline float secToMin(const float& t) {return t/60.;}
    inline float minToSec(const float& t) {return t*60.;}

    // inline float secToHr(const time_t& t) {return t/3600.;}
    // inline float MinToHr(const time_t& t) {return t/60.;}
    // inline float HrToMin(const time_t& t) {return t*60.;}
    // inline float HrToSec(const time_t& t) {return t*3600.;}
    // void convertInf(time_t& time) {if isinf(time) time }

    template <class T> bool contains(const vector<T>& vec, const T& data)
        {return find(vec.begin(), vec.end(), data) != vec.end();}

    template <class T, class P> bool contains(const map<T,P>& m, const T& key)
        {return m.find(key) != m.end();}

    template <typename T> void checkIndex(const vector<T>& vec, int index)
        {ASSERT(index >= 0 && index < vec.size(), "Invalid array index");}

//  Data members

    extern int seed;
    extern default_random_engine randNumGen;
}

//  Operators

template <class T> ostream& operator<<(ostream& out, vector<T>& v);
template <class T> ostream& operator<<(ostream& out, const vector<T>& v);

/****************************************************************************
*																			*
*	Definition of Timer class												*
*																			*
****************************************************************************/

class util::Timer
{
    public:
        Timer() : start_t(clock()) {}
        void start(clock_t t) {start_t = t;}
        float elapsed() {return float(clock() - start_t)/CLOCKS_PER_SEC;}
    private:
       float start_t;
};

/****************************************************************************
*																			*
*	Function:	initLogger		 											*
*																			*
*	Purpose:	To initialize the logger							       	*
*																			*
****************************************************************************/

void util::initLogger()
{
	using namespace el;
	string format = "%datetime{%Y-%M-%d %H:%m:%s} %level : %msg";
	string format_d = "%datetime{%Y-%M-%d %H:%m:%s} %level [%fbase-%func:%line] : %msg";
//	string file = "log/shado-%datetime{%M-%d-%H.%m}.log";

//	Global configurations

	Configurations conf;
	conf.setGlobally(ConfigurationType::Format, format);
//	conf.setGlobally(ConfigurationType::Filename, file);//"log/shado.log");
	conf.setGlobally(ConfigurationType::ToFile, "true");
	conf.setGlobally(ConfigurationType::ToStandardOutput, "false");

//	Specific configurations

	conf.set(Level::Debug, ConfigurationType::Format, format_d);
	conf.set(Level::Warning, ConfigurationType::ToStandardOutput, "true");
	conf.set(Level::Error, ConfigurationType::ToStandardOutput, "true");
	conf.set(Level::Fatal, ConfigurationType::ToStandardOutput, "true");
	Loggers::reconfigureAllLoggers(conf);

//	Logging level

	Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
    Loggers::addFlag(LoggingFlag::HierarchicalLogging);
	Loggers::setLoggingLevel(Level::Fatal);
}

/****************************************************************************
*																			*
*	Function:	toVector       												*
*																			*
*	Purpose:	To convert the string to a vector                           *
*																			*
****************************************************************************/

template <class T>
vector<T> util::toVector(string data, char delimiter)
{
//  Replace delimiter with white space

    for (int i = 0; i < data.size(); i++)
        if (data[i] == delimiter)
            data[i] = ' ';

//  Fill vector

    T temp;
    vector<T> vec;
    istringstream in(data);
    while (in >> temp)
        vec.push_back(temp);

    return vec;
}

/****************************************************************************
*																			*
*	Function:	operator<<     												*
*																			*
*	Purpose:	To output a vector                                          *
*																			*
****************************************************************************/

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
    out << "[";
    if (v.size() > 0) out << v[0];
    for (int i = 1; i < v.size(); i++) out << ", " << v[i];
    out << "]";
    return out;
}

/****************************************************************************
*																			*
*	Function:	operator<<     												*
*																			*
*	Purpose:	To output a list                                            *
*																			*
****************************************************************************/

template <class T>
ostream& operator<<(ostream& out, const list<T>& l)
{
    out << "[";
    bool first = true;
    for (const auto& li : l)
    {
        if (first)
        {
            out << li;
            first = false;
        }
        else out << ", " << li;
    }
    out << "]";
    return out;
}

#endif
