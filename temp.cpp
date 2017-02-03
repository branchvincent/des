#include <iostream>
#include <string>
#include <cassert>

using namespace std;

#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            cerr << "ASSERTION ERROR: " << message << "endl; \
            cerr << "In " << __FILE__ << ", line " << __LINE__ << ": '" << #condition << "' failed" << endl; \
            terminate(); \
        } \
    } while (false)

const int SIZE = 3;

void Assert(bool condition, string message)
{
    // cerr << "Assertion '" << #condition << "' failed in " << __FILE__;
    cerr << " line " << __LINE__ << ": " << message << endl;
    terminate();
}

void manipulate(int (&arr)[SIZE])
{
    arr[0] = 10000;
    for (int i = 0; i < SIZE; i++)
        cout << arr[i] << endl;
}

int main()
{
    // int a[] = {0,1,2};
    // manipulate(a);
    int x = 3;
    // Assert(false, "string");
    ASSERT(x == 5, "x is not " << x);
    return 0;
}
