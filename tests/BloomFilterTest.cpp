// BloomFilterTest.cpp

#include <gtest/gtest.h>
// cmake -B build -S .#include "../src/BloomFilter.h"
#include "../src/BloomFilter.h"

// Test case for BloomFilter
TEST(BloomFilterTest, BasicTest) {
    // Test with one hash function
    BloomFilter filter1(1000, std::hash<std::string>{});

    // Test with two hash functions
    BloomFilter filter2(1000, std::hash<std::string>{}, [](const std::string& s) {
        return std::hash<std::string>{}(s + "second");
    });

    // Insert bad URLs
    filter1.insertBadUrl("https://www.malicious1.com");
    filter2.insertBadUrl("https://www.malicious2.com");

    // Check if URLs are allegedly in the blacklist
    EXPECT_TRUE(filter1.checkUrl("https://www.malicious1.com"));
    EXPECT_FALSE(filter1.checkUrl("https://www.nonmalicious1.com"));

    EXPECT_TRUE(filter2.checkUrl("https://www.malicious2.com"));
    EXPECT_FALSE(filter2.checkUrl("https://www.nonmalicious2.com"));
}

