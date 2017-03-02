///****************************************************************************
//*																			*
//*	File:		Operator.h													*
//*																			*
//*	Author:		Branch Vincent												*
//*																			*
//*	Date:		Jun 9, 2016													*
//*																			*
//*	Purpose:	This file defines the Operator class.						*
//*																			*
//****************************************************************************/
//
//#ifndef OPERATOR_H
//#define OPERATOR_H
//
//#include <iostream>
//#include <string>
//#include <queue>
//#include <algorithm>
//#include "task.h"
//#include "Operator.h"
//#include "Statistics.h"
//
//using namespace std;
//using namespace params;
//
////	Functions and definitions
//
//bool cmpPrty(Task* t1, Task* t2)
//{
//	if (t1->getPriority() == t2->getPriority())
//		return t1->getExpTime() > t2->getExpTime();
//    else
//		return t1->getPriority() < t2->getPriority();
//}
//
//typedef priority_queue<Task*,vector<Task*>,decltype(&cmpPrty)> Queue;
//
///****************************************************************************
//*																			*
//*	Definition of Operator class											*
//*																			*
//****************************************************************************/
//
//class Operator
//{
////	Public member functions
//
//	public:
//
//	//	Constructor
//
////        Operator(string nm, NewParams& pms, Statistics& sts) :
////        Operator() :
////            name(""),
////            currTask(NULL),
////            taskQueue(&cmpPrty),
////            sharedStats(NULL),
////            stats() {}
//        Operator(string nm, vector<int> tasks, Statistics& sts, int tNum) :
//            name(nm),
//			taskNums(tasks),
//            currTask(NULL),
//            taskQueue(&cmpPrty),
//            sharedStats(sts),
//            stats(),
//			trainNum(tNum) {}
//
//	//	Inspectors
//
//        string getName() const {return name;}
//        bool isIdle() const {return currTask == NULL;}
//		bool isBusy() const {return !isIdle();}
//        int getQueueSize() const {return (int)taskQueue.size();}
////		bool isQueueEmpty() const {return taskQueue.empty();}
////		int tasksLeft() const {return taskQueue.size();}
////		Task* getTop() {return taskQueue.top();}
//		Task* getCurrTask() {return currTask;}
//        float getDepTime();
//        bool needToIntrp(Queue& queue);
//		vector<int> getTaskNums() {return taskNums;}
//		float getUtil(int i) {return stats.getUtil(i);}
//
//	//	Mutators
//
//		void procArr(Task* task);
//		void procIntrp(float currTime);
//		void procDep(Task* task, bool stop);
//        void servNextTask(float currTime);
//        void clear();
//        void endRep() {stats.endRep(); clear();}
//
//	//	Other member functions
//
//        void output();
//        void output(ostream& out) const {out << stats << endl;}
////		Operator& operator=(Operator& op) {
////			cout << "Here" << endl;
////			return op;
////		}
//
//	//	void plot() {stats.plot(name);}
//
////  Private member functions
//
//    private:
//        float getFatigueFactor(float time) {return 1 + (time/60 * 0.01);}
//        bool currTaskExp();
//        void procExp(float currTime);
//        void updateUtil(Task* task, float currTime);
//
////	Data members
//
//	private:
//        string name;
//		vector<int> taskNums;		// tasks to handle
////		Params pms;					// parameters
//		Task* currTask;             // current task
//		Queue taskQueue;            // task queue
////        Queue taskQueues[NUM_OPS];  // task queues
//		Statistics& sharedStats;	// shared stats
//        Statistics stats;           // local stats
//		int trainNum;
//};
//
////	Operators
//
//ostream& operator<<(ostream& out, const Operator& op) {op.output(out); return out;}
//
///****************************************************************************
//*																			*
//*	Function:	getDepTime													*
//*																			*
//*	Purpose:	To get the depature time of the current task				*
//*																			*
//****************************************************************************/
//
//float Operator::getDepTime()
//{
//	if (isBusy())
//		return currTask->getDepTime();
//	else
//		return INFINITY;
//}
//
///****************************************************************************
//*																			*
//*	Function:	needToIntrp                                                 *
//*																			*
//*	Purpose:	To determine if the current task needs to be interrupted by *
//*               by the specified task                                       *
//*																			*
//****************************************************************************/
//
//bool Operator::needToIntrp(Queue& queue)
//{
//    if (isBusy() && queue.size() > 0)
//        return cmpPrty(currTask, queue.top());
//    else
//        return false;
//}
//
///****************************************************************************
//*																			*
//*	Function:	procArr                                                     *
//*																			*
//*	Purpose:	To enqueue the specified task								*
//*																			*
//****************************************************************************/
//
//void Operator::procArr(Task* task)
//{
////	Enqueue task
//
//    taskQueue.push(task);
//
//    if (DEBUG_ON) cout << name << ": Adding " << *task << " of " << taskQueue.size() << endl;
////    if (taskQueue.size() > 50) cout << "\t\t\tQueue size = " << taskQueue.size() << endl;
//
////  Get task attributes
//
//    float currTime = task->getArrTime();
//    int type = task->getType();
//    int timeInt = currTime/INT_SIZE;
//    task->setQueTime(currTime);
//
////  Update stats
//
//    stats.incNumTasksIn(type, timeInt, 1);
//
////	Service next task, if idle
//
//    if (isIdle())
//        servNextTask(currTime);
//
////  Interrupt current task, if applicable
//
//    else if (needToIntrp(taskQueue))
//        procIntrp(currTime);
//
//	return;
//}
//
///****************************************************************************
//*																			*
//*	Function:	processIntrp												*
//*																			*
//*	Purpose:	To process an interruption of the current task              *
//*																			*
//****************************************************************************/
//
//void Operator::procIntrp(float currTime)
//{
////  Check that the operator is busy
//
//    if (isIdle())
//    {
//        cerr << "Error: Cannot process task interruption. Exiting..." << endl;
//        exit(1);
//    }
//
//    if (DEBUG_ON) cout << "\t\t " << name << ": Task interrupted at " << currTime << endl; //" " << *currTask << endl;
//
////	Update stats
//
//    updateUtil(currTask, currTime);
//    float depTime = currTask->getDepTime();
//    currTask->setSerLeft(depTime - currTime);
//    currTask->setDepTime(INFINITY);
//    currTask->setQueTime(currTime);
//
////	Add current task to queue and service next task
//
//    taskQueue.push(currTask);
//    currTask = NULL;
//    servNextTask(currTime);
//
//    return;
//}
//
///****************************************************************************
//*																			*
//*	Function:	procDep                                                     *
//*																			*
//*	Purpose:	To process a task depature								 	*
//*																			*
//****************************************************************************/
//
//void Operator::procDep(Task* task, bool stop)
//{
////	Get task attributes
//
//    float depTime = task->getDepTime();
//    float begTime = task->getBegTime();
//    int type = task->getType();
//    int timeInt = begTime/INT_SIZE;
//
////	Update stats
//
//    if (DEBUG_ON) cout << "\t " << name << ": Task departing at " << depTime << " and busy for " << depTime - begTime << endl;
//    updateUtil(task, depTime);
//    stats.incNumTasksOut(type, timeInt, 1);
//
////  Start next task, if applicable
//
////    delete currTask;
//    currTask = NULL;
//
//	if (!stop)
//		servNextTask(depTime);
//
//    return;
//}
//
///****************************************************************************
//*																			*
//*	Function:	clear														*
//*																			*
//*	Purpose:	To clear the operator                                       *
//*																			*
//****************************************************************************/
//
//void Operator::clear()
//{
////  Clear current task
//
//    currTask = NULL;
//
////  Clear queue
//
//    while (!taskQueue.empty())
//        taskQueue.pop();
//
//    return;
//}
//
///****************************************************************************
//*																			*
//*	Function:	output														*
//*																			*
//*	Purpose:	To output an operator										*
//*																			*
//****************************************************************************/
//
////void Operator::output(ostream& out) const
////{
//////  Output operator's status and number of enqueued tasks
////
////    if (currTask != NULL)
////        cout << "Operator is busy until " << currTask->getDepTime();
////    else
////        cout << "Operator is not busy";
////
////    cout << " and has " << taskQueue.size() << " tasks in queue." << endl;
////
//////  Output queue
////
////    cout << "Queue = {" << endl;
////
////    Queue tmpQ = taskQueue;
////
////    while (!tmpQ.empty())
////    {
////        cout << *tmpQ.top() << endl;
////        tmpQ.pop();
////    }
////
////    cout << "}" << endl;
////
////    return;
////}
//
///****************************************************************************
//*																			*
//*	Function:	servNextTask												*
//*																			*
//*	Purpose:	To service the next task in the queue, if applicable		*
//*																			*
//****************************************************************************/
//
//// Bug here?
//
//void Operator::servNextTask(float currTime)
//{
////  Check that a task can be serviced
//
//	if (!taskQueue.empty())
//	{
//	//	Get next task
//
//        if (DEBUG_ON) cout << "\t " << name << ": Task starting at " << currTime;
//
//        currTask = taskQueue.top();
//        taskQueue.pop();
//        currTask->setBegTime(currTime);
//
//        if (DEBUG_ON) cout << " " << *currTask << endl;
//
//	//	Account for fatigue, if applicable
//
//		float serTime = currTask->getSerLeft();
//
//		if (FATIGUE_ON)
//		{
//			serTime *= getFatigueFactor(currTime);
//            currTask->setSerLeft(serTime);
//            serTime = currTask->getSerLeft();
//		}
//
//    //  Set depature time
//
//        float depTime = currTime + serTime;
//        currTask->setDepTime(depTime);
//
//    //  Update stats
//
//        int timeInt = currTime/INT_SIZE;
//        int type = currTask->getType();
//        float waitTime = currTime - currTask->getQueTime();
//        stats.incWaitTime(type, timeInt, waitTime);
//        sharedStats.incWaitTime(type, timeInt, waitTime);
//
//    //	Check to see if task expired
//
//        if (currTaskExp())
//            procExp(currTime);
//    }
//
//	return;
//}
//
///****************************************************************************
//*																			*
//*	Function:	currTaskExp                                                 *
//*																			*
//*	Purpose:	To check if the current task has expired                    *
//*																			*
//****************************************************************************/
//
//bool Operator::currTaskExp()
//{
////  Get task attributes
//
//    float depTime = currTask->getDepTime();
//    float expTime = currTask->getExpTime();
//
////  Check if depature time has been set
//
//    if (isinf(depTime))
//    {
//        cerr << "Error: Current task has not started. Exiting..." << endl;
//        exit(1);
//    }
//
////  Check for expiration
//
//    if (expTime < depTime)
//        return true;
//    else
//        return false;
//}
//
///****************************************************************************
//*																			*
//*	Function:	procExp                                                     *
//*																			*
//*	Purpose:	To process a task expiration                                *
//*																			*
//****************************************************************************/
//
//void Operator::procExp(float currTime)
//{
//    if (DEBUG_ON) cout << "\t\t Task expired at " << currTime << endl;
//
////  Get task attributes and update stats
//
//    int type = currTask->getType();
//    int timeInt = currTime/INT_SIZE;
//    stats.incNumTasksExp(type, timeInt, 1);
//    sharedStats.incNumTasksExp(type, timeInt, 1);
//
////  Start next task
//
//    currTask = NULL;
//    servNextTask(currTime);
//
//    return;
//}
//
///****************************************************************************
//*																			*
//*	Function:	updateUtil													*
//*																			*
//*	Purpose:	To update the utilization									*
//*																			*
//****************************************************************************/
//
////  Fix wait time
////  change to updatestat and seed each array here (or implement in stats class)
//
//void Operator::updateUtil(Task* task, float currTime)
//{
////	Get task attributes
//
//    float begTime = task->getBegTime();
//    int type = task->getType();
//
////	Get interval times and update time
//
//    int timeInt = begTime/INT_SIZE;
//	float beginInt = timeInt * INT_SIZE;
//	float endInt = beginInt + INT_SIZE;
//	float timeBusy = 0;
//	float percBusy = 0;
//
////	Record utilization
//
//	while (currTime > endInt)
//	{
//		timeBusy = endInt - max(begTime, beginInt);
//		percBusy = timeBusy/INT_SIZE;
//		stats.incUtil(type, timeInt, percBusy);
//		stats.incSerTime(type, timeInt, timeBusy);
//        sharedStats.incSerTime(type, timeInt++, timeBusy);
//
//        if (timeBusy < 0)
//        {
//            cout << "WARNING: timeBusy = " << timeBusy << endl;
//            cout << "\t task = " << *task << endl;
//        }
//
//        beginInt = endInt;
//		endInt += INT_SIZE;
//	}
//
//	timeBusy = currTime - max(begTime, beginInt);
//	percBusy = timeBusy/INT_SIZE;
//	stats.incUtil(type, timeInt, percBusy);
//	stats.incSerTime(type, timeInt, timeBusy);
//    sharedStats.incSerTime(type, timeInt, timeBusy);
//
//    if (timeBusy < 0)
//    {
//        cout << "WARNING: timeBusy = " << timeBusy << endl;
//        cout << "\t task = " << *task << endl;
//    }
//
//	return;
//}
//
///****************************************************************************
//*																			*
//*	Function:	output                                                      *
//*																			*
//*	Purpose:	To output...                                                *
//*																			*
//****************************************************************************/
//
//void Operator::output()
//{
////  Output stats
//
//	string file_name = name;
//	transform(file_name.begin(), file_name.end(), file_name.begin(), ::tolower);
//	replace(file_name.begin(), file_name.end(), ' ', '_');
//    string file = OUTPUT_PATH + "/stats_" + file_name + to_string(trainNum) + ".csv";
//    ofstream fout(file);
//    if (!fout)
//    {
//        cerr << "Error: Cannot open " << file << ". Exiting..." << endl;
//        exit(1);
//    }
//
//    fout << stats;
//
//////	Output idle trip
////
////	file = OUTPUT_PATH + "/" + name + "_idle_trip.csv";
////	ofstream fout2(file);
////	if (!fout2)
////	{
////		cerr << "Error: Cannot open " << file << ". Exiting..." << endl;
////		exit(1);
////	}
////	stats.outputIdle(fout2);
////
//////	Output busy trip
////
////	file = OUTPUT_PATH + "/" + name + "_busy_trip.csv";
////	ofstream fout3(file);
////	if (!fout3)
////	{
////		cerr << "Error: Cannot open " << file << ". Exiting..." << endl;
////		exit(1);
////	}
////	stats.outputBusy(fout3);
//
//    return;
//}
//
//#endif
