#include "InputOutput.h"
#include <iostream>
#include <set>
#include <unistd.h>
#include <regex>
#include <algorithm>
#include "BloomFilter.h"
#include "Hashs.h"
#include "BlackList.h"

InputOutput::InputOutput() : blackList() // Initialize BlackList here
{
    // Initialize the Bloom filter with a fixed size and hash functions
    size_t bloomSize = 1000;
    std::set<int> hashFunctions = {1, 2}; // Example: Using hash functions 1 and 2
    createBloomFilter(bloomSize, hashFunctions, bloomFilter);
}

void InputOutput::run(int clientSocket)
{
    // std::cout << "Client connected, processing input..." << std::endl;
    // sendResponse(clientSocket, "Initialization successful\n");

    // Move on to processing input lines in an infinite loop
    while (true)
    {
        processInputLines(clientSocket);
    }
    close(clientSocket);
    std::cout << "Client disconnected." << std::endl;
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
    std::string inputLine;
    if (!receiveLine(clientSocket, inputLine))
    {
        std::cerr << "Failed to receive input, terminating connection..." << std::endl;
        return; // Exit the method if receiving input fails
    }

    std::istringstream lineStream(inputLine);
    int command;
    std::string url;

    if (!processInputLine(lineStream, command, url))
    {
        std::cerr << "Invalid input line, ignoring..." << std::endl;
        return; // Exit the method if the input line is invalid
    }

    handleCommand(command, url, bloomFilter, blackList, clientSocket); // Use the class member blackList
}

bool InputOutput::getBloomSize(size_t &bloomSize, std::istringstream &firstLineStream)
{
    firstLineStream >> bloomSize;
    if (firstLineStream.fail() || bloomSize <= 0)
    {
        return false;
    }
    return true;
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
        return false;
    }
    return true;
}

bool InputOutput::createBloomFilter(const size_t &bloomSize, const std::set<int> &hashFunctions, BloomFilter &bloomFilter)
{
    Hashs hashs(hashFunctions);
    bloomFilter = BloomFilter(bloomSize, hashs.getRealHashFunctions());
    return true;
}

void InputOutput::handleCommand(const int command, const std::string &url, BloomFilter &bloomFilter, BlackList &blackList, int clientSocket)
{
    std::string response;
    if (command == 1)
    {
        blackList.addToBlackList(url);
        bloomFilter.insertBadUrl(url);
        response = "Added\n";
    }
    else if (command == 2)
    {
        // Remove all spaces and delimiters from the URL string
        std::string cleaned_url = url;
        cleaned_url.erase(std::remove_if(cleaned_url.begin(), cleaned_url.end(), [](unsigned char c)
                                         { return std::isspace(c); }),
                          cleaned_url.end());

        std::regex url_regex(R"((http|ftp|https):\/\/([\w_-]+(?:(?:\.[\w_-]+)+))([\w.,@?^=%&:\/~+#-]*[\w@?^=%&\/~+#-]))");
        std::smatch url_match;
        if (!std::regex_search(cleaned_url, url_match, url_regex))
        {
            response = "false\n";
        }
        else
        {
            std::string matched_part = url_match.str();
            bool isBlacklisted = bloomFilter.checkUrl(matched_part);
            response = (isBlacklisted ? "true" : "false");
            if (isBlacklisted)
            {
                bool positiveOrNegative = blackList.isBlackListed(matched_part);
                response += (positiveOrNegative ? " true\n" : " false\n");
            }
            else
            {
                response += "\n";
            }
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

    // Read the rest of the line as the URL
    std::getline(lineStream, url);
    if (url.empty())
    {
        return false;
    }
    // Remove leading spaces
    url.erase(0, url.find_first_not_of(' '));

    std::cout << url << std::endl;
    return true;
}

bool InputOutput::receiveLine(int clientSocket, std::string &line)
{
    char buffer[4096] = {0};
    long int valread = recv(clientSocket, buffer, 4096, 0);
    if (valread <= 0)
    {
        return false;
    }
    line = std::string(buffer, valread);
    return true;
}

void InputOutput::sendResponse(int clientSocket, const std::string &response)
{
    std::cout << "Sending response: " << response << std::endl;

    const char *data = response.c_str();
    size_t totalSent = 0;
    size_t dataLength = response.size();

    while (totalSent < dataLength)
    {
        ssize_t sent = send(clientSocket, data + totalSent, dataLength - totalSent, 0);
        if (sent == -1)
        {
            std::cerr << "Failed to send data, terminating connection..." << std::endl;
            break;
        }
        totalSent += sent;
    }
}
