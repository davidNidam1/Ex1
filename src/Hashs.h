// Hashs.h

#ifndef HASHS_H
#define HASHS_H

#include <iostream>
#include <functional>
#include <set>
#include <vector>

class Hashs
{
private:
    // Set to store hash function types
    std::set<int> hashFunctions;
    // Vector to store real hash functions
    std::vector<std::function<size_t(const std::string &)>> realHashFunctions;

public:
    // Constructor takes a set of hash function types
    Hashs(const std::set<int> &hashFunctions);

    // Getter to retrieve the vector of real hash functions
    const std::vector<std::function<size_t(const std::string &)>> &getRealHashFunctions() const;
};

#endif // HASHS_H