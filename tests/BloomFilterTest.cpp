#include <gtest/gtest.h>
#include "../src/BloomFilter.cpp"

// Test fixture for BloomFilter
class BloomFilterTest : public ::testing::Test {
protected:
    // No setup needed for this test fixture
};

// Test cases
TEST_F(BloomFilterTest, InsertAndCheckUrls) {
    // Define some hash functions for testing
    auto hashFunction1 = [](const std::string& str) { return std::hash<std::string>{}(str); };
    auto hashFunction2 = [](const std::string& str) { return std::hash<std::string>{}(str) * 31; };

    // Create BloomFilter with two hash functions
    BloomFilter bloomFilter(100, {hashFunction1, hashFunction2});

    // Insert bad URLs
    bloomFilter.insertBadUrl("example.com");
    bloomFilter.insertBadUrl("test.com");

    // Check URLs
    EXPECT_TRUE(bloomFilter.checkUrl("example.com"));
    EXPECT_TRUE(bloomFilter.checkUrl("test.com"));
    EXPECT_FALSE(bloomFilter.checkUrl("google.com"));
}

