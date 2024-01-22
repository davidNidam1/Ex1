// BloomFilter.h

#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <iostream>
#include <bitset>
#include <functional>
#include <vector>

class BloomFilter {
private:
    size_t size;
    std::vector<bool> bitArraySelector;
    std::function<size_t(const std::string&)> hashFunction1;
    std::function<size_t(const std::string&)> hashFunction2;

public:
    // Constructor for one hash function
    BloomFilter(size_t size, const std::function<size_t(const std::string&)>& hashFunction);

    // Constructor for two hash functions
    BloomFilter(size_t size, const std::function<size_t(const std::string&)>& hashFunction1,
                 const std::function<size_t(const std::string&)>& hashFunction2);

    // Function to insert a bad URL into the BloomFilter
    void insertBadUrl(const std::string& url);

    // Function to check if a URL is allegedly in the blacklist
    bool checkUrl(const std::string& url) const;
};

#endif // BLOOMFILTER_H
