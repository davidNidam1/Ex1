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
    // Constructor for hash functions
    BloomFilter(size_t size, const std::vector<std::function<size_t(const std::string&)>>& hashFunctions)
        : size(size), bitArraySelector(size, false) {
        if (hashFunctions.size() >= 1) {
            hashFunction1 = hashFunctions[0];
        }

        if (hashFunctions.size() >= 2) {
            hashFunction2 = hashFunctions[1];
        }
    }


 // Function to insert a bad URL into the BloomFilter
 // 1[URL]
    void insertBadUrl(const std::string& url) {
        if (hashFunction1) {
            size_t hash1 = hashFunction1(url) % size;
            bitArraySelector[hash1] = true;
        }

        if (hashFunction2) {
            size_t hash2 = hashFunction2(url) % size;
            bitArraySelector[hash2] = true;
        }
    }


// Function to check if a URL is allegedly in the blacklist
// 2[URL]
    bool checkUrl(const std::string& url) const {
        if (hashFunction1) {
            size_t hash1 = hashFunction1(url) % size;
            if (!bitArraySelector[hash1]) {
                return false;  // URL is definitely not in the blacklist
            }
        }

        if (hashFunction2) {
            size_t hash2 = hashFunction2(url) % size;
            if (!bitArraySelector[hash2]) {
                return false;  // URL is definitely not in the blacklist
            }
        }

        // If both hash functions (or the single function) have set bits, the URL is allegedly in the blacklist
        // It is important TODO a real check in the Black-List (Chek false positive)
        return true;
    }


};

