#include "BlackList.h"
#include <vector>
#include <iostream>
 

// Constructor
BlackList::BlackList(){}


// Member function to check if an item is blacklisted
bool BlackList::isBlackListed(const std::string& item) const {
    // Search for the item in the blacklisted items
    for (const std::string& blackListedItem : blackListedItems) {
        if (blackListedItem == item) {
            return true; // Item is blacklisted
        }
    }
    return false; // Item is not blacklisted
}

// Member function to add an item to the blacklist
void BlackList::addToBlackList(const std::string& item) {
    // Check if the item is already in the blacklist
    if (!isBlackListed(item)) {
        // If not, add it to the blacklist
        blackListedItems.push_back(item);
    } 
}    

