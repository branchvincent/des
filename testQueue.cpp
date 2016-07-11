#include <iostream>
#include <string>
#include <queue>
//#include "Queue.h"
#include <vector>
#include "Task.h"

using namespace std;

bool comparePriority(Task* t1, Task* t2);
typedef priority_queue<Task*,vector<Task*>,decltype(&comparePriority)> stlQueue;
//typedef Queue myQueue;

int main() 
{
//	myQueue myQ;
	stlQueue stlQ(&comparePriority);
	
	srand(0);
	int phase = 1;
	int numTasks = 10;
	Task* task[numTasks];

	vector<float> traffic(5, 1);
	for (int i = 0; i < numTasks; i++)
		task[i] = new Task(rand() % 9, 0, rand(), phase, traffic);
	
	for (int i = 0; i < numTasks; i++)	
	{
		cout << "Push " << *task[i] << endl;
		stlQ.push(task[i]);
	}	
	cout << endl;

	for (int i = 0; i < numTasks; i++)
	{
		cout << "Pop " << *stlQ.top() << endl;
		stlQ.pop();
	}	

//	Task* front = myQ.pop();
//	cout << *delTask << endl;
//	delTask = myQ.pop();

	return 0;
}

bool comparePriority(Task* t1, Task* t2)
{
	if (t1->getPriority() == t2->getPriority())
		return t1->getExpTime() > t2->getExpTime();
	else
		return t1->getPriority() < t2->getPriority();
}

//	int maxPrty = 5;
//	int prty1 = t1->getPriority();
//	int prty2 = t2->getPriority();
//	
////	Check for max priority
//
//	if (prty1 == maxPrty)
//		return false;
//	else if (prty2 == maxPrty)
//		return true;
//
////	Check for higher priority and deadline
//	
//	bool higherPrty = prty1 > prty2;
//	bool soonerExpTime = t1->getExpTime() < t2->getExpTime();
//	
//	if (prty1 == prty2)
//		return t1->getArrTime() > t2->getArrTime();
//	else
//		return !higherPrty && !soonerExpTime;

//	return t1->getPriority() < t2->getPriority();