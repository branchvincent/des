/****************************************************************************
*																			*
*	File:		Queue.h														*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jul 6, 2016													*
*																			*
*	Purpose:	This file defines the Queue class. 							*
*																			*
****************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <list>

using namespace std;

template<class T>
class Queue
{
//	Public member functions
	
	public:
	
	// 	Inspector
		
		T head() const {return list.front();}
		int size() const {return list.size();}
		
	// 	Mutators
		
		void enqueue(const T& value) {list.push_back(value);}
		T dequeue() {T temp = list.front(); list.pop_front(); return temp;}
		
	//	Facilitators
		
		void output(ostream& out) const {list.output(out);}
		
	//	Other
		
		void makeEmpty() {list.makeEmpty();}
		bool isEmpty() {return list.isEmpty();}	

//	Data members

	private:
		list<float> list;
};

template <class T>
ostream& operator<<(ostream& out, const LinkedQueue<T>& q) {q.output(out); return out;}

#endif
