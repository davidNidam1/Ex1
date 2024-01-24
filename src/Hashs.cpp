// Class is biased: we know we get 1/2/both.
#include <functional>
#include <iostream>
#include <set>
#include <vector>
#include "Hashs.h"

// Constructor takes a set of hash function types
Hashs::Hashs(const std::set<int>& hashFunctions) : hashFunctions(hashFunctions) {
    // Iterate through each hash function type
    for (int hashFunction : hashFunctions) {
        // If hash function type is 1
        if (hashFunction == 1) {
            // Use std::hash<std::string> as the real hash function
            realHashFunctions.push_back(std::hash<std::string>{});
        }
        // If hash function type is 2
        else if (hashFunction == 2) {
            // Use a lambda function applying std::hash<std::string> twice
            realHashFunctions.push_back([](const std::string& str) {
                std::hash<std::string> hashFunc;
                return hashFunc(std::to_string(hashFunc(str)));
            });
        }
        // Add more conditions if needed for other hash function types
    }
}

// Getter to retrieve the vector of real hash functions
const std::vector<std::function<size_t(const std::string&)>>& Hashs::getRealHashFunctions() const {
    return realHashFunctions;
}
