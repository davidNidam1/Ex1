#ifndef FALSE_POSITIVE_H
#define FALSE_POSITIVE_H
#include <iostream>
#include <vector>
#include <string>

class FalsePositive {
private:
    // Private constructor to prevent instantiation
    FalsePositive() {}

public:
    // Static member function to check if a URL is in the list
    static bool isUrlInList(const std::vector<std::string>& badUrls, const std::string& url);
};

#endif // FALSE_POSITIVE_H
