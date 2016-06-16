#include <iostream>
#include <string>
#include "Operator.h"
#include "Task.h"
#include <queue>

using namespace std;

int main() 
{	
	Operator op;
	
	if (op.isBusy())
		cout << "Busy." << endl;	
	else
		cout << "Not busy." << endl;
		
	if (op.isQueueEmpty())
		cout << "Empty queue." << endl;	
	else
		cout << "Non-empty queue." << endl;
		
	if (op.getCurrTask() == NULL)
		cout << "No current tasks." << endl;
	else
		cout << "Current task." << endl;
	
	cout << op << endl;
	
	op.makeIdle();
	cout << op << endl;
		
	Task* task = new Task(0, 0, 2);
	op.addTask(task);
	cout << op << endl;
	
	op.startNextTask(5);
	cout << op << endl;
	
//	for (int i = 0; i < 4900000; i++)
//		Operator op;
	
	return 0;
}