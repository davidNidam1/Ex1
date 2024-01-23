#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include "BloomFilter.cpp"
#include "Hashs.cpp"


class InputOutput {
//private:
//    BloomFilter bloomFilter;

public:  //supoused to be in header.
//    InputOutput() : bloomFilter(0, {}) {}

    void run() {
        // Process input lines in an infinite loop
        while (true) {
            std::cout << "Enter the size of the Bloom filter array and hash functions (1 or 2): ";
            std::string firstLine;
            std::getline(std::cin, firstLine);

            std::istringstream firstLineStream(firstLine);

            // Read the bloom size
            size_t bloomSize;
            firstLineStream >> bloomSize;

            // Check if the bloom size is valid (greater than 0)
            if (firstLineStream.fail() || bloomSize <= 0) {
                // Invalid input, ask again
                std::cout << "Invalid bloom size. Please enter a positive integer." << std::endl;
                continue;  // Restart the loop to get valid input
            }

            // Read the hash functions into a set to ensure uniqueness
            std::set<int> hashFunctions;
            int currentHashFunction;

            while (firstLineStream >> currentHashFunction) {
                hashFunctions.insert(currentHashFunction);
            }

            // Check if all hash functions are valid (1 or 2)
            bool allValid = true;

            for (int hashFunction : hashFunctions) {
                if (hashFunction != 1 && hashFunction != 2) {
                    allValid = false;
                    break; 

                }
            }


            if (firstLineStream.fail() || hashFunctions.empty() || !allValid) {
                // Invalid input, ask again
                std::cout << "Invalid input. Please enter the correct format." << std::endl;
                continue;
            }
            

            // Here we will create an instance of the class Hashs, which contains the hashs suitable for 1/2.
            
            Hashs hashs(hashFunctions);

            // Create Bloom filter based on input parameters
            BloomFilter bloomFilter(bloomSize, hashs.getRealHashFunctions());
            
            ////////////Untill here we confirm and build the Bloom-Filter////////////////////////////
            // Process input lines in an infinite loop
            while (true) {
                std::string inputLine;
                std::getline(std::cin, inputLine);

                std::istringstream lineStream(inputLine);
                int command;
                lineStream >> command;

                if (lineStream.fail()) {
                    // Ignore invalid input lines
                    continue;
                }

                std::string url;
                lineStream >> url;

                if (lineStream.fail()) {
                    // Ignore invalid input lines
                    continue;
                }


                //create instance of an empty black list
                if (command == 1) {
                    // Add URL to the blacklist
                    bloomFilter.insertBadUrl(url);
                    //TODO BlackList::addtoBlacklist
                } else if (command == 2) {
                    // Check if URL is blacklisted
                    bool isBlacklisted = bloomFilter.checkUrl(url);
                    // Output the result
                    std::cout << "URL: " << url << " - Blacklisted: " << isBlacklisted << std::endl;
                    if(isBlacklisted){
                        //std::cout BlackList::isBlackListed
                    }
                }
            }

        }
        
    }
};


