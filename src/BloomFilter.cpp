#include "BloomFilter.h"

// Default constructor
BloomFilter::BloomFilter() : size(0), bitArraySelector(0), hashFunctions() {}

// Constructor for hash functions
BloomFilter::BloomFilter(size_t size, const std::vector<std::function<size_t(const std::string &)>> &hashFunctions)
    : size(size), bitArraySelector(size, 0), hashFunctions(hashFunctions)
{
}

// Function to insert a bad URL into the BloomFilter
void BloomFilter::insertBadUrl(const std::string &url)
{
    for (const auto &hashFunction : hashFunctions)
    {
        if (hashFunction)
        {
            size_t hash = hashFunction(url) % size;
            bitArraySelector[hash] = 1;
        }
    }
}

// Function to check if a URL is allegedly in the blacklist
bool BloomFilter::checkUrl(const std::string &url) const
{
    for (const auto &hashFunction : hashFunctions)
    {
        if (hashFunction)
        {
            size_t hash = hashFunction(url) % size;
            if (bitArraySelector[hash] == 0)
            {
                return false; // URL is definitely not in the blacklist
            }
        }
    }
    // If all hash functions have set bits, the URL is allegedly in the blacklist
    // It is important to do a real check in the Black-List (Check false positive)
    return true;
}
