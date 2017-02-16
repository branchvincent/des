#include <iostream>
#include <string>
#include <queue>
#include <boost/optional.hpp>

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

    A a;
    // queue<int> q;
    // cout << q.front() << endl;
    // q.push(1);

    return 0;
}
