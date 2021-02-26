#include "gtest/gtest.h"

namespace
{
// The fixture for testing Foo
class CFooTest : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.
    CFooTest()
    {
        // You can do set-up work for each test here.
    }

    ~CFooTest()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp()
    {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    void TearDown()
    {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Class members declared here can be used by all tests in the test suite
    // for Foo.
};

// Add a short description for the test here, eg. Tests that Foo does...
TEST_F(CFooTest, failingDummyTest1)
{
    // Arrange

    // Act

    // Assert
    ASSERT_TRUE(false);
}

// Add a short description for the test here, eg. Tests that Foo does...
TEST_F(CFooTest, failingDummyTest2)
{
    // Arrange

    // Act

    // Assert
    ASSERT_FALSE(true);
}

// if you want to compare data types for which EXPECT_EQ does not work directly
// and you do not want to define ==operator for the type
// you may use a matcher together with EXPECT_THAT - see example below:
//
// MATCHER_P(EqFoo, other, "Equality matcher for type Foo") {
//    return arg.m_selectedRois == other.m_selectedRois;
//}
// use matcher together with EXPECT_THAT - e.g. EXPECT_THAT(Foo(), EqFoo(<some other foo object>));
//
// EXPECT_THAT may be also of use if you want to compare the content of whole standard containers

} // namespace