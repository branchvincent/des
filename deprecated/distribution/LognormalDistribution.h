///****************************************************************************
//*																			*
//*	File:		LognormalDistribution.h										*
//*																			*
//*	Author:		Branch Vincent												*
//*																			*
//*	Purpose:	This file defines the LognormalDistribution class.			*
//*																			*
//****************************************************************************/
//
//#ifndef LOGNORMALDISTRIBUTION_H
//#define LOGNORMALDISTRIBUTION_H
//
//#include <iostream>
//#include <string>
//#include "Distribution.h"
//#include "../Utility.h"
//
//using namespace std;
//
///****************************************************************************
//*																			*
//*	Definition of LognormalDistribution class		     					*
//*																			*
//****************************************************************************/
//
//class LognormalDistribution : public Distribution
//{
////	Public member functions
//
//	public:
//
//    //  Constructor
//
//		LognormalDistribution(float mean, float stdDev) :
//			Distribution(mean, stdDev), distribution(mean, stdDev) {}
//
//	//	Inspectors
//
//		float getMean() const {return distribution.m();}
//		float getStdDev() const {return distribution.s();}
//
//    //  Other member functions
//
//        float rand() {return distribution(util::randNumGen);}
//
////	Data members
//
//	private:
//		lognormal_distribution<float> distribution;
//};
//
//#endif
