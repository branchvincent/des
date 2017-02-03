#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <memory>
#include "Util.h"
#include "distribution/UniformDistribution.h"
// #include "distribution/Exponential.h"
#include "distribution/ExponentialDistribution.h"
#include "TaskType.h"

#include <list>
#include <boost/thread.hpp>

using namespace std;

int main()
{
    // unique_ptr<A> a(new B());
    // a->print();
    //
    // vector<unique_ptr<Distribution>> l;
    // l.push_back(unique_ptr<ExponentialDistribution>(new ExponentialDistribution(1)));
    // l.push_back(unique_ptr<UniformDistribution>(new UniformDistribution(0,1)));
    // cout << l[1]->getParameters()[1] << endl;

    //
    // cout << l[0]->getMax() << endl;

    string name = "MyTask";
    vector<int> priority = {1,2,3};
    vector<bool> isAffectedByTraffic = {true, false, true};
    vector<Distribution*> interarrival = {new ExponentialDistribution(1)};
    vector<Distribution*> service = {new ExponentialDistribution(1)};
    vector<Distribution*> expiration = {new ExponentialDistribution(1)};
    cout << expiration << endl;

    TaskType t(name, priority, isAffectedByTraffic, interarrival, service, expiration);
    cout << t.genTask(0).getArrTime();
    cout << t.lastArrivalTime;


    // delete interarrival;
    // cout << interarrival[0]->getParameters()[0] << endl;
    // cout << t.getInterarrival()->rand() << endl;


    // srand((unsigned int) time(0));

    // Distribution* d = new UniformDistribution(0,1);
    // unique_ptr<Distribution> dd(new UniformDistribution(0,1));
    //
    // vector<Distribution*> v;
    // v.push_back(new ExponentialDistribution(0));
    // v.push_back(new UniformDistribution(0,1));
    //
    // // UniformDistribution* u = v[1];
    // unique_ptr<UniformDistribution> t(*dd);
    // cout << dd->getMax() << endl;
    // cout << ((unique_ptr<UniformDistribution>)dd)->getMax() << endl;

    // UniformDistribution d(1,2);
    // cout << d.getMax() << endl;

	return 0;
}
