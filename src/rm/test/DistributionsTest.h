#include "../src/distributions/Distribution.h"
#include "../src/distributions/ExponentialDistribution.h"
#include "../src/distributions/LognormalDistribution.h"
#include "../src/distributions/UniformDistribution.h"
#include <boost/test/included/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(DistributionTest);

BOOST_AUTO_TEST_CASE(ConstructorTest)
{
    BOOST_CHECK_EXEPTION(Distribution());
}

BOOST_AUTO_TEST_SUITE(ExponentialTest);

BOOST_AUTO_TEST_CASE(ConstructorTest)
{
    vector<float> lambdas = {0.5, 1, 100, 10034};

    for (float li : lambdas)
    {
        ExponentialDistribution e(li);
        BOOST_CHECK(e.getLambda() == li);

        float sum = 0;
        int N = 100;
        for (int i = 0; i < N; i++)
            sum += e.rand();
        BOOST_CHECK_CLOSE(sum/float(N), e.getMean(), 0.1f);
    }
    // BOOST_CHECK_EQUAL((int)x, 9);
    // BOOST_CHECK_CLOSE(x, 9.5f, 0.0001f); // Checks differ no more then 0.0001%
}

BOOST_AUTO_TEST_SUITE_END();
