#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

#include <iostream>
#include <sstream>
#include <set>
#include "BloomFilter.h"
#include "Hashs.h"
#include "BlackList.h"

class InputOutput {
private:
    BloomFilter bloomFilter;

public:
    InputOutput();

    void run();

private:
    bool processBloomParameters();
    bool areHashFunctionsValid(const std::set<int>& hashFunctions) const;
    void processInputLines();
    bool getBloomSize(size_t &bloomSize, std::istringstream &firstLineStream);
    bool getHashFunctions(std::set<int> &hashFunctions, std::istringstream &firstLineStream);
    bool createBloomFilter(const size_t &bloomSize, const std::set<int> &hashFunctions, BloomFilter &bloomFilter);
    void handleCommand(const int command, const std::string &url, BloomFilter &bloomFilter, BlackList &blackList);
    bool processInputLine(std::istringstream &lineStream, int &command, std::string &url);
};

#endif // INPUTOUTPUT_H
