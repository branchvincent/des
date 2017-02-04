/****************************************************************************
*																			*
*	File:		Util.h														*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Util(ity) namespace.					*
*																			*
****************************************************************************/

#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <random>
#include <sstream>
#include <algorithm>

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

    template <class T>
    bool contains(vector<T>& vec, const T& data)
    {
        return find(vec.begin(), vec.end(), data) != vec.end();
    }
    //
    // template <class T>
    // vector<T> contains(map<T>& vec, const T& data)
    // {
    //     return ind(vec.begin(), vec.end(), data) != vec.end();
    // }

    template <typename T>
    void checkIndex(const vector<T>& vec, int index)
    {
        ASSERT(index >= 0 && index < vec.size(), "Invalid array index");
    }
}

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
