# Ex1 - Bloom Filter Implementation
## Overview
This project implements a Bloom filter in C++ for a URL filtering system. A Bloom filter is a probabilistic data structure that efficiently determines if an item is a member of a set without storing the items themselves. The system uses hash functions to add URLs to a blacklist and check if a URL is blacklisted.

## Useful links
### Link to the current repository (GitHub):
https://github.com/davidNidam1/Ex1

### Link to jira:
https://davidnidam.atlassian.net/jira/software/projects/EX1/boards/3/backlog?epics=visible

### Link to the docker repository:
https://hub.docker.com/repository/docker/davidnidam/foobar_app/general

## Running instructions:
In this task we built a Bloom-Filter system to our social-network app.
Those are the steps needed to be performed:
- Download the Dockerized project (a container that is consist of our code and a respective image), and save it in a directory.
- Open a terminal from this directory and run the next command:
   g++ -o ex1 ./Main.cpp ./BlackList.cpp ./BloomFilter.cpp ./Hashs.cpp ./InputOutput.cpp
Nou you can insert inputs to check the Bloom-Filter.


## Key Elements (work depiction):
- Test-Driven Development (TDD)
We followed TDD principles to write tests before implementing the Bloom filter.
This allowed code integrity and functionality through iterative testing.
- Header Files (.h)
We utilized header files to declare class function prototypes, and constants.
This promoted modularity and code organization by separating declaration from implementation.
- Object-Oriented Programming (OOP)
We embraced OOP principles to structure code using classes and objects.
To sum up, we implemented a Bloom filter class that works in accordance with another classes (BlackList, Hashs, InputOutput) in order to build the system in an organized and independent way. After that, we used workflows to test our code every time the main branch got merged and dockerized our project on every release.



