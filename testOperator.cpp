#include <iostream>
#include <string>
#include "Operator.h"
#include "Task.h"

using namespace std;

int main() 
{	
	Operator op;
	cout << op << endl;
	op.makeBusy(5);
	op.makeBusy(7);
	op.makeFree();
	cout << op << endl;
	
	Task* task = new Task('A', 0, 2);
	op.addTask(task);
	cout << op << endl;
	
	op.startNextTask(5);
	cout << op << endl;
	
	return 0;
}