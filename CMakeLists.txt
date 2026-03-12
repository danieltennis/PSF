cmake_minimum_required(VERSION 3.20)
project(PSF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

# 1. Zoek GTest op het systeem
find_package(GTest REQUIRED)

# 2. De bronbestanden (zonder main.cpp!)
set(COMMON_SOURCES
        Meeting.cpp
        Participation.cpp
        Room.cpp
        MeetingPlanner.cpp
        XMLreader.cpp
        tinyxml_2_6_2/tinyxml.cpp
        tinyxml_2_6_2/tinyxmlparser.cpp
        tinyxml_2_6_2/tinyxmlerror.cpp
        tinyxml_2_6_2/tinystr.cpp
)

# 3. De Test Executable
add_executable(runUnitTests Test.cpp ${COMMON_SOURCES})

target_link_libraries(runUnitTests GTest::GTest GTest::Main pthread)