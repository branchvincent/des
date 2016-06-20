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
		
	Task* task1 = new Task(4, 0, 2, 0); 
	Task* task2 = new Task(3, 0, 2, 0);
	Task* task3 = new Task(2, 0, 2, 0);

	cout << "Task 1:  " << *task1 << endl;
//	cout << "Task 2:  " << *task2 << endl;
//	cout << "Task 3:  " << *task3 << endl;

	cout << task1 << endl;
	op.addTask(task1);
//	op.addTask(task2);
//	op.addTask(task3);
	
	cout << op.getTop() << endl;
	cout << op.getCurrTask() << endl;
	
	op.makeIdle();
	cout << *op.getTop() << endl;

	
	op.startNextTask(5);
	cout << op << endl;
	
	return 0;
}