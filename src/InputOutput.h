#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

#include <set>
#include <sstream>
#include <sys/socket.h>
#include "BloomFilter.h"
#include "BlackList.h"

class InputOutput
{
public:
    InputOutput();
    void run(int clientSocket);

private:
    BloomFilter bloomFilter;
    bool processBloomParameters(int clientSocket);
    bool areHashFunctionsValid(const std::set<int> &hashFunctions) const;
    void processInputLines(int clientSocket);
    bool getBloomSize(size_t &bloomSize, std::istringstream &firstLineStream);
    bool getHashFunctions(std::set<int> &hashFunctions, std::istringstream &firstLineStream);
    bool createBloomFilter(const size_t &bloomSize, const std::set<int> &hashFunctions, BloomFilter &bloomFilter);
    void handleCommand(const int command, const std::string &url, BloomFilter &bloomFilter, BlackList &blackList, int clientSocket);
    bool processInputLine(std::istringstream &lineStream, int &command, std::string &url);
    bool receiveLine(int clientSocket, std::string &line);
    void sendResponse(int clientSocket, const std::string &response);
};

#endif // INPUTOUTPUT_H

