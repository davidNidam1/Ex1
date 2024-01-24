cmake_minimum_required(VERSION 3.14)
project("Ex1") # Check if "ex1" or "Ex1"

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
googletest
URL
https://github.com/google/googletest/archive/03597a01ee50ed
33e9dfd640b249b4be3799d395.zip
)

enable_testing()
set(SOURCE_FILES
src/FalsePositive.cpp # this is where the code we want to test
src/Hashs.cpp
src/BlackList.cpp
src/BloomFilter.cpp
)

set(TEST_FILES
tests/test_main.cpp # this is the main for tests
tests/FalsePositiveTest.cpp # this file contain the tests
tests/HashsTest.cpp
tests/BlackListTest.cpp
tests/BloomFilterTest.cpp
)

add_executable(CalcTests ${TEST_FILES})

# Link Google Test to the test executable
target_link_libraries(CalcTests PRIVATE gtest gtest_main pthread)

# Include the source directory for tests
target_include_directories(CalcTests PRIVATE src)

include(GoogleTest)
add_test(NAME CalcTests COMMAND CalcTests)