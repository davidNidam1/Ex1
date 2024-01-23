
#ifndef BLACKLIST_H
#define BLACKLIST_H

#include <vector>
#include <iostream>

class BlackList {
private:
    // Private member variable to store blacklisted items
    std::vector<std::string> blackListedItems;

public:
    // Constructor
    BlackList();

    // Member function to check if an item is blacklisted
    bool isBlackListed(const std::string& item) const;

    // Member function to add an item to the blacklist
    void addToBlackList(const std::string& item);
};

#endif // BLACKLIST_H
