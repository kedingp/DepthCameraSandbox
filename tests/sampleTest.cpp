#include "DepthCamera.h"
#include "gtest/gtest.h"

namespace
{
// The fixture for testing Foo
class DepthCameraTest : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.
    DepthCameraTest()
    {
        // You can do set-up work for each test here.
    }

    ~DepthCameraTest()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() { camera.start(); }

    void TearDown()
    {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    camera::DepthCamera camera;
};

// Add a short description for the test here, eg. Tests that Foo does...
TEST_F(DepthCameraTest, grabFrame)
{
    // Arrange

    // Act
    const auto frame = camera.grabFrame();

    // Assert
    ASSERT_TRUE(frame != nullptr);
    ASSERT_EQ(frame->getId(), 0);
}

} // namespace