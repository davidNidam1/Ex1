#include "FalsePositive.h"
#include <iostream>
#include <vector>
#include <string>

bool FalsePositive::isUrlInList(const std::vector<std::string>& badUrls, const std::string& url) {
    // Perform the check and return the result
    for (const std::string& badUrl : badUrls) {
        if (badUrl == url) {
            return true; // URL is in the list
        }
    }
    return false; // URL is not in the list
}

