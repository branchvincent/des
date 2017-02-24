#include <iostream>
#include <string>
#include <queue>
#include <boost/optional.hpp>
#include <list>
#include "Utility.h"

using namespace std;

class A
{
public:
    A(int x) : x(x) {}
    int x;
};

boost::optional<A&> get(const string& attribute_name)
{
//search collection
//if found at i
    // return attributes[i];
//if not found
    return boost::optional<A&>();
}

int main()
{
    boost::optional<A&> opt = get("name");
    if (opt) cout << "True" << endl;
    list<int> l;
    // l.push_back(1);
    // l.push_back(2);

    cout << l;
    // A a;
    // queue<int> q;
    // cout << q.front() << endl;
    // q.push(1);

    return 0;
}
