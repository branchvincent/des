#include "../src/Utility.h"
// #define BOOST_TEST_MODULE UtilityTest
#include <boost/test/included/unit_test.hpp>

using namespace std;

// struct UtilityFixture
// {
//     UtilityFixture() : m_configFile("test.tmp")
//     {
//         fclose( fopen(m_configFile.c_str(), "w+") );
//     }
//
//     ~UtilityFixture()
//     {
//         remove(m_configFile.c_str());
//     }
//
//     // TODO: Possibly put some common tests.
//     void TestSaveLoad(Utility& foo, bool asBinary)
//     {
//         // BOOST_CHECK(foo.Save(asBinary));
//     }
//
//     // TODO: Declare some common values accesses in tests here.
//     string m_configFile;
// };
//
// BOOST_FIXTURE_TEST_SUITE(UtilityTest, UtilityFixture);
BOOST_AUTO_TEST_SUITE(UtilityTest);

BOOST_AUTO_TEST_CASE(UtilityFixture)
{
    // To simplify this example test, let's suppose we'll test 'float'.
    // Some test are stupid, but all should pass.
    float x = 9.5f;

    BOOST_CHECK(x == 0.0f);
    BOOST_CHECK_EQUAL((int)x, 9);
    BOOST_CHECK_CLOSE(x, 9.5f, 0.0001f); // Checks differ no more then 0.0001%
}

BOOST_AUTO_TEST_SUITE_END();
