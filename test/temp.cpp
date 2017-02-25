#include <iostream>
#include <string>
// #include "../src/distributions/Distribution.h"
// #include "../src/distributions/ExponentialDistribution.h"
// #include "../src/distributions/LognormalDistribution.h"
// #include "../src/distributions/UniformDistribution.h"

#include <boost/random/normal_distribution.hpp>
#include <boost/random/exponential_distribution.hpp>

using namespace std;

int main()
{
    boost::normal_distribution<float> s; // (default mean = zero, and standard deviation = unity)
    cout << "Normal distribution, mean = "<< s.mean() << ", standard deviation = " << s.sigma() << endl;

    boost::exponential_distribution<float> d;
    cout << "Exponential distribution, mean = " << d.max() << endl;

    // boost::variate_generator<boost::mt19937&,boost::normal_distribution<> > rng(gener, normal);
    // boost::variate_generator rng;

    // for (int i = 0; i < 100; i++)
    //     cout << s() << endl;
    // ExponentialDistribution d(0);
    // LognormalDistribution d;
    // UniformDistribution d;
    // cout << d.rand() << endl;
    return 0;
}
