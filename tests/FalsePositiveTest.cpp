#include <gtest/gtest.h>
#include "../src/FalsePositive.cpp"

// Test fixture for FalsePositive
class FalsePositiveTest : public ::testing::Test {
protected:
    // No setup needed for this test fixture
};

// Test cases
TEST_F(FalsePositiveTest, IsUrlInList) {
    // Check if an URL that is in the list is detected
    std::vector<std::string> badUrls = {"badurl1", "badurl2", "badurl3"};
    EXPECT_TRUE(FalsePositive::isUrlInList(badUrls, "badurl2"));

    // Check if an URL that is not in the list is not detected
    EXPECT_FALSE(FalsePositive::isUrlInList(badUrls, "notinlist"));
}