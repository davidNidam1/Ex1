#include <gtest/gtest.h>
#include "../src/BlackList.cpp"

// Test fixture for BlackList
class BlackListTest : public ::testing::Test {
protected:
    BlackList blackList;

    void SetUp() override {
        // Add some initial items to the blacklist
        blackList.addToBlackList("item1");
        blackList.addToBlackList("item2");
    }
};

// Test cases
TEST_F(BlackListTest, IsBlackListed) {
    // Check if an item that is in the blacklist is detected
    EXPECT_TRUE(blackList.isBlackListed("item1"));
    // Check if an item that is not in the blacklist is not detected
    EXPECT_FALSE(blackList.isBlackListed("item3"));
}

TEST_F(BlackListTest, AddToBlackList) {
    // Add a new item to the blacklist
    blackList.addToBlackList("item3");
    // Check if the new item is now in the blacklist
    EXPECT_TRUE(blackList.isBlackListed("item3"));
}
