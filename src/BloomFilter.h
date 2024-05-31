#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <iostream>
#include <bitset>
#include <functional>
#include <vector>

class BloomFilter
{
private:
    size_t size;
    std::vector<int> bitArraySelector;
    std::vector<std::function<size_t(const std::string &)>> hashFunctions;

public:
    // Default constructor
    BloomFilter();

    // Constructor for one hash function
    BloomFilter(size_t size, const std::vector<std::function<size_t(const std::string &)>> &hashFunctions);

    // Function to insert a bad URL into the BloomFilter
    void insertBadUrl(const std::string &url);

    // Function to check if a URL is allegedly in the blacklist
    bool checkUrl(const std::string &url) const;
};

#endif // BLOOMFILTER_H
