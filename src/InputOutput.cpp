#include "InputOutput.h"
#include <iostream>
#include <set>
#include <unistd.h>
#include <regex> // Include regex library
#include "BloomFilter.h"
#include "Hashs.h"
#include "BlackList.h"

InputOutput::InputOutput() : bloomFilter(0, {}) {}

void InputOutput::run(int clientSocket)
{
    // Process input lines from client in an infinite loop
    while (true)
    {
        if (!processBloomParameters(clientSocket))
        {
            continue; // Restart the loop to get valid input
        }
        processInputLines(clientSocket);
    }
}

bool InputOutput::processBloomParameters(int clientSocket)
{
    std::string firstLine;
    if (!receiveLine(clientSocket, firstLine))
    {
        return false; // Failed to receive input
    }

    std::istringstream firstLineStream(firstLine);
    size_t bloomSize;

    if (!getBloomSize(bloomSize, firstLineStream))
    {
        return false; // Input is invalid
    }

    // Read the hash functions into a set to ensure uniqueness
    std::set<int> hashFunctions;
    if (!getHashFunctions(hashFunctions, firstLineStream))
    {
        return false; // Input is invalid
    }

    if (!createBloomFilter(bloomSize, hashFunctions, bloomFilter))
    {
        return false; // Input is invalid
    }
    return true; // Input is valid
}

bool InputOutput::areHashFunctionsValid(const std::set<int> &hashFunctions) const
{
    for (int hashFunction : hashFunctions)
    {
        if (hashFunction != 1 && hashFunction != 2)
        {
            return false; // Invalid hash function type
        }
    }
    return true; // All hash functions are valid
}

void InputOutput::processInputLines(int clientSocket)
{
    // Create an instance of an empty blacklist
    BlackList blackList;

    // Process input lines from client
    while (true)
    {
        std::string inputLine;
        if (!receiveLine(clientSocket, inputLine))
        {
            // Failed to receive input, terminate connection
            break;
        }

        std::istringstream lineStream(inputLine);
        int command;
        std::string url;

        if (!processInputLine(lineStream, command, url))
        {
            // Ignore invalid input lines
            continue;
        }

        // Handle the command logic
        handleCommand(command, url, bloomFilter, blackList, clientSocket);
    }
}

bool InputOutput::getBloomSize(size_t &bloomSize, std::istringstream &firstLineStream)
{
    firstLineStream >> bloomSize;

    if (firstLineStream.fail() || bloomSize <= 0)
    {
        return false; // Input is invalid
    }

    return true; // Input is valid
}

bool InputOutput::getHashFunctions(std::set<int> &hashFunctions, std::istringstream &firstLineStream)
{
    int currentHashFunction;
    while (firstLineStream >> currentHashFunction)
    {
        hashFunctions.insert(currentHashFunction);
    }

    if (hashFunctions.empty() || !areHashFunctionsValid(hashFunctions))
    {
        return false; // Input is invalid
    }

    return true; // Input is valid
}

bool InputOutput::createBloomFilter(const size_t &bloomSize, const std::set<int> &hashFunctions, BloomFilter &bloomFilter)
{
    // Create an instance of the class Hashs, which contains the hash functions suitable for 1/2.
    Hashs hashs(hashFunctions);

    // Create Bloom filter based on input parameters
    bloomFilter = BloomFilter(bloomSize, hashs.getRealHashFunctions());
    return true; // Input is valid
}

void InputOutput::handleCommand(const int command, const std::string &url, BloomFilter &bloomFilter, BlackList &blackList, int clientSocket)
{
    std::string response;
    if (command == 1)
    {
        // Add URL to the blacklist
        blackList.addToBlackList(url);
        bloomFilter.insertBadUrl(url);
        response = "Added\n";
    }
    else if (command == 2)
    {
        // Check if URL is blacklisted
        bool isBlacklisted = bloomFilter.checkUrl(url);
        response = (isBlacklisted ? "true" : "false");
        if (isBlacklisted)
        {
            bool positiveOrNegative = blackList.isBlackListed(url);
            response += (positiveOrNegative ? " true\n" : " false\n");
        }
        else
        {
            response += "\n";
        }
    }
    sendResponse(clientSocket, response);
}

bool InputOutput::processInputLine(std::istringstream &lineStream, int &command, std::string &url)
{
    lineStream >> command;
    if (lineStream.fail())
    {
        return false;
    }

    lineStream >> url;
    if (lineStream.fail())
    {
        return false;
    }

    // Regex to check if the URL is valid
    std::regex url_regex(R"((https?:\/\/)?((([a-zA-Z0-9\-]+\.)+[a-zA-Z]{2,})|((\d{1,3}\.){3}\d{1,3}))(:\d+)?(\/\S*)?)");
    if (!std::regex_match(url, url_regex))
    {
        if (command == 2) // Only return false if the command is to check URL
        {
            return false;
        }
    }

    return true; // Input is valid
}

bool InputOutput::receiveLine(int clientSocket, std::string &line)
{
    char buffer[1024] = {0};
    int valread = read(clientSocket, buffer, 1024);
    if (valread <= 0)
    {
        return false;
    }
    line = std::string(buffer, valread);
    return true;
}

void InputOutput::sendResponse(int clientSocket, const std::string &response)
{
    send(clientSocket, response.c_str(), response.size(), 0);
}
