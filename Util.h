/****************************************************************************
*																			*
*	File:		Util.h														*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Util class.							*
*																			*
****************************************************************************/

#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <random>
#include <sstream>

using namespace std;

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
//	Public member functions

	float seed = rand();
	default_random_engine randNumGen(seed);
	string x = "hi";

	vector<float> TRAFFIC = {1,1,1};

    template <class T>
    vector<T> stringToVector(string data, char delimiter = ',')
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

    string toLower(string s)
    {
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
    }
}

// void Assert(bool condition, string message)
// {
// 	if (!condition)
// 	{
// 		cout << message << endl;
// 		assert(condition);
// 	// 	cerr << "Assertion `" #condition "` failed in " << __FILE__ << " line " << __LINE__ << ": " << message << endl;
// 	// 	terminate();
// 	}
// }



template <class T>
ostream& operator <<(ostream& out, vector<T>& v)
{
    out << "[";

    if (v.size() > 0)
        out << v[0];

    for (int i = 1; i < v.size(); i++)
        out << ", " << v[i];

    out << "]";

    return out;
}

template <class T>
ostream& operator <<(ostream& out, const vector<T>& v)
{
    out << "[";

    if (v.size() > 0)
        out << v[0];

    for (int i = 1; i < v.size(); i++)
        out << ", " << v[i];

    out << "]";

    return out;
}

#endif
