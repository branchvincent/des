/****************************************************************************
*																			*
*	File:		LoadParameters.h                                            *
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jul 12, 2016												*
*																			*
*	Purpose:	This file defines the LoadParameters class.                 *
*																			*
****************************************************************************/

#ifndef LOADPARAMETERS_H
#define LOADPARAMETERS_H

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/****************************************************************************
*																			*
*	Definition of LoadParameters class                                      *
*																			*
****************************************************************************/

class LoadParameters
{
//	Public member functions

	public:

	//	Constructor
		
		LoadParameters();

	//	Inspectors
    
        string getOutFile() {return outFile;}
        vector<float> getTraffic() {return traffic;}
        float getParam(int i) {return params[i];}
	
//	Data members

	public:
        string outFile;
        vector<float> traffic;
        vector<float> params;
};

/****************************************************************************
*																			*
*	Function:	LoadParameters                                              *
*																			*
*	Purpose:	To construct new parameters                                 *
*																			*
****************************************************************************/

LoadParameters::LoadParameters()
{
//  Get parameter file
    
    string paramFile;
//    cout << "Input parameter file location: ";
//    cin >> paramFile;
    
    paramFile = "/Users/Branch/Documents/Academic/Year 1/Summer/DES Code/DES/Input/params.txt";
    
//  Open parameter file
    
    fstream fin(paramFile);
    
    if (!fin)
    {
        cerr << "Error: Cannot open parameter file. Exiting..." << endl;
        exit(1);
    }
    
//  Initialize variables
    
    char paramChar;
    float paramVal;
    string paramName;
    
//	Read in output file
    
    fin >> paramName >> outFile;
    replace(outFile.begin(), outFile.end(), '_', ' ');
    
//  Read in number of hours
    
    fin >> paramName >> paramVal;
    params.push_back(paramVal);
    
//  Read in traffic
    
    fin >> paramName;
    for (int i = 0; i < params[0]; i++)
    {
        fin >> paramChar;
        
        switch (paramChar)
        {
            case 'l': traffic.push_back(0.5); break;
            case 'm': traffic.push_back(1); break;
            case 'h': traffic.push_back(2); break;
            default: break;
        }
    }
    
//	Read in rest of parameters
    
    while (fin >> paramName >> paramVal)
        params.push_back(paramVal);
    
    return;
}

#endif
