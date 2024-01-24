#include <gtest/gtest.h>
#include "../src/Hashs.cpp"

// Test fixture for Hashs
class HashsTest : public ::testing::Test {
protected:
    // No setup needed for this test fixture
};

// Test cases
TEST_F(HashsTest, GetRealHashFunctions) {
    // Test case for hash function type 1
    std::set<int> hashFunctions1 = {1};
    Hashs hashs1(hashFunctions1);
    const auto& realHashFunctions1 = hashs1.getRealHashFunctions();
    ASSERT_EQ(realHashFunctions1.size(), 1);
    EXPECT_TRUE(realHashFunctions1[0]("example") != 0);

    // Test case for hash function type 2
    std::set<int> hashFunctions2 = {2};
    Hashs hashs2(hashFunctions2);
    const auto& realHashFunctions2 = hashs2.getRealHashFunctions();
    ASSERT_EQ(realHashFunctions2.size(), 1);
    EXPECT_TRUE(realHashFunctions2[0]("example") != 0);
}


