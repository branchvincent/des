///****************************************************************************
//*																			*
//*	File:		ExponentialDistribution.h									*
//*																			*
//*	Author:		Branch Vincent												*
//*																			*
//*	Purpose:	This file defines the ExponentialDistribution class.		*
//*																			*
//****************************************************************************/
//
//#ifndef EXPONENTIALDISTRIBUTION_H
//#define EXPONENTIALDISTRIBUTION_H
//
//#include <iostream>
//#include <string>
//#include "Distribution.h"
//#include "../Utility.h"
//#include <boost/property_tree/ptree.hpp>
//
//using namespace std;
//using boost::property_tree::ptree;
//
///****************************************************************************
//*																			*
//*	Definition of Exponential class		     								*
//*																			*
//****************************************************************************/
//
//class ExponentialDistribution : public Distribution
//{
////	Public member functions
//
//	public:
//
//    //  Constructor
//
//		ExponentialDistribution(ptree data);
//		ExponentialDistribution(float lambda) :
//			Distribution(lambda), distribution(lambda) {}
//
//	//	Inspectors
//
//		float getLambda() const {return distribution.lambda();}
//
//    //  Other member functions
//
//        float rand() {return distribution(util::randNumGen);}
//
////	Data members
//
//	private:
//		exponential_distribution<float> distribution;
//};
//
//ExponentialDistribution::ExponentialDistribution(ptree data)
//{
//	
//}
//
//#endif
