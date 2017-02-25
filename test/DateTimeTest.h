#include "../src/DateTime.h"
// #define BOOST_TEST_MODULE DateTimeTest
#include <boost/test/included/unit_test.hpp>

using namespace std;

struct DateTimeFixture
{
    DateTimeFixture() : m_configFile("test.tmp")
    {
        fclose( fopen(m_configFile.c_str(), "w+") );
    }

    ~DateTimeFixture()
    {
        remove(m_configFile.c_str());
    }

    // TODO: Possibly put some common tests.
    void TestSaveLoad(DateTime& foo, bool asBinary)
    {
        // BOOST_CHECK(foo.Save(asBinary));
    }

    // TODO: Declare some common values accesses in tests here.
    string m_configFile;
};

BOOST_FIXTURE_TEST_SUITE(DateTimeTest, DateTimeFixture);
// BOOST_AUTO_TEST_SUITE(DateTimeTest);

BOOST_AUTO_TEST_CASE(DateTimeFixture)
{
    // To simplify this example test, let's suppose we'll test 'float'.
    // Some test are stupid, but all should pass.
    float x = 9.5f;

    BOOST_CHECK(x == 0.0f);
    BOOST_CHECK_EQUAL((int)x, 9);
    BOOST_CHECK_CLOSE(x, 9.5f, 0.0001f); // Checks differ no more then 0.0001%
}

BOOST_AUTO_TEST_SUITE_END();
