#include "InputOutput.h"
#include <iostream>
#include <sstream>
#include <set>
#include "BloomFilter.h"
#include "Hashs.h"
#include "BlackList.h"

InputOutput::InputOutput() : bloomFilter(0, {}) {}

void InputOutput::run() {
    // Process input lines in an infinite loop
    while (true) {
        if (!processBloomParameters()) {
            continue;  // Restart the loop to get valid input
        }
        processInputLines();
    }
}

//std::cout << "Enter the size of the Bloom filter array and hash functions (1 or 2): ";
bool InputOutput::processBloomParameters() {
    std::string firstLine;
    std::getline(std::cin, firstLine);

    std::istringstream firstLineStream(firstLine);
    size_t bloomSize;

    if (!getBloomSize(bloomSize, firstLineStream)) {
        return false;  // Input is invalid
    }

    // Read the hash functions into a set to ensure uniqueness
    std::set<int> hashFunctions;
    if (!getHashFunctions(hashFunctions, firstLineStream)) {
        return false;  // Input is invalid
    }

    if (!createBloomFilter(bloomSize, hashFunctions, bloomFilter)) {
        return false;  // Input is invalid
    }
    return true;  // Input is valid
}

bool InputOutput::areHashFunctionsValid(const std::set<int>& hashFunctions) const {
    for (int hashFunction : hashFunctions) {
        if (hashFunction != 1 && hashFunction != 2) {
            return false;  // Invalid hash function type
        }
    }
    return true;  // All hash functions are valid
}

void InputOutput::processInputLines() {
    // create instance of an empty black list
    BlackList blackList;
    // Process input lines in an infinite loop
    while (true) {
        std::string inputLine;
        std::getline(std::cin, inputLine);

        std::istringstream lineStream(inputLine);
        int command;
        std::string url;

        if (!processInputLine(lineStream, command, url)) {
            // Ignore invalid input lines
            continue;
        }
        
        // Handle the command logic
        handleCommand(command, url, bloomFilter, blackList);
    }
}

bool InputOutput::getBloomSize(size_t &bloomSize, std::istringstream &firstLineStream) {
    firstLineStream >> bloomSize;

    if (firstLineStream.fail() || bloomSize <= 0) {
        std::cout << std::endl;
        return false;  // Input is invalid
    }

    return true;  // Input is valid
}

bool InputOutput::getHashFunctions(std::set<int> &hashFunctions, std::istringstream &firstLineStream) {
    int currentHashFunction;
    while (firstLineStream >> currentHashFunction) {
        hashFunctions.insert(currentHashFunction);
    }

    //firstLineStream.fail() ||
    if (hashFunctions.empty() || !areHashFunctionsValid(hashFunctions)) {
        std::cout << std::endl;
        return false;  // Input is invalid
    }

    return true;  // Input is valid
}

bool InputOutput::createBloomFilter(const size_t &bloomSize, const std::set<int> &hashFunctions, BloomFilter &bloomFilter) {
    // Here we will create an instance of the class Hashs, which contains the hashs suitable for 1/2.
    Hashs hashs(hashFunctions);

    // Create Bloom filter based on input parameters
    bloomFilter = BloomFilter(bloomSize, hashs.getRealHashFunctions());
    return true;  // Input is valid
}

void InputOutput::handleCommand(const int command, const std::string &url, BloomFilter &bloomFilter, BlackList &blackList) {
    // Create an instance of an empty blacklist
    if (command == 1) {
        // Add URL to the blacklist
        blackList.addToBlackList(url);
        bloomFilter.insertBadUrl(url);
    } else if (command == 2) {
        // Check if URL is blacklisted
        bool isBlacklisted = bloomFilter.checkUrl(url);
        // Output the result
        std::cout << (isBlacklisted ? "true" : "false");
        if (isBlacklisted == false){std::cout << std::endl;}
        if (isBlacklisted) {
            bool positiveOrNegative = blackList.isBlackListed(url);
            std::cout << (positiveOrNegative ? " true" : " false") << std::endl;
        }
    }
}

bool InputOutput::processInputLine(std::istringstream &lineStream, int &command, std::string &url) {
    lineStream >> command;
    if (lineStream.fail()) {
        // Ignore invalid input lines
        return false;
    }

    lineStream >> url;
    if (lineStream.fail()) {
        // Ignore invalid input lines
        return false;
    }

    return true;  // Input is valid
}
