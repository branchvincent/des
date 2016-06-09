#include <iostream>
#include <string>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <list>
#include "Task.h"
#include "Operator.h"
#include <iterator>

using namespace std;

int main() 
{
	list<Task*> taskList;
	Operator op;
	int simTime = 0;
	
	for (int i = 0; i < 5; i++)
	{
		Task* task = new Task('A', 1);
		taskList.push_back(task);
		int arrTime = task->getArr();
	}
	
	//const_iterator it = taskList.begin();
	list<Task*>::iterator it = taskList.begin();
	int arrTime;
	int depTime;
	Task* task;
	
	for (int i = 0; i < 5; i++) //&& simTime < endTime) 
	{
		task = *it;
		arrTime = task->getArr();
		depTime = op.getDep();
		
		if (arrTime < depTime)
		{
			cout << "Task arriving at " << arrTime << endl;
			op.addTask(task);
			simTime = arrTime;	
		}
		else 
		{
			cout << "Task departing at " << depTime << endl;
			op.makeFree();
			simTime = depTime;
		}
	}
	return 0;
}