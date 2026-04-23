cmake_minimum_required(VERSION 3.20)
project(PSF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

enable_testing()

# =========================
# CORE LIBRARY (JOUW CODE)
# =========================
set(CORE_SOURCES
        Meeting.cpp
        Participation.cpp
        Room.cpp
        MeetingPlanner.cpp
        XMLreader.cpp
        Campus.cpp
        Building.cpp
        Renovation.cpp

        tinyxml_2_6_2/tinyxml.cpp
        tinyxml_2_6_2/tinyxmlparser.cpp
        tinyxml_2_6_2/tinyxmlerror.cpp
        tinyxml_2_6_2/tinystr.cpp
        Catering.cpp
        Catering.h
)

# =========================
# APP (MAIN PROGRAMMA)
# =========================
add_executable(app
        main.cpp
        ${CORE_SOURCES}
)

# Copy XML file to build folder (BELANGRIJK)
configure_file(
        ${CMAKE_SOURCE_DIR}/Meeting.xml
        ${CMAKE_BINARY_DIR}/Meeting.xml
        COPYONLY
)

# =========================
# TEST EXECUTABLE
# =========================
add_executable(runUnitTests
        Test/Test.cpp

        Test/Test_Meeting.cpp
        Test/Test_MeetingPlanner.cpp
        Test/Test_Participation.cpp
        Test/Test_XMLreader.cpp
        Test/Test_Renovation.cpp
        Test/Building/Test_Building.cpp
        Test/Campus/Test_Campus.cpp

        ${CORE_SOURCES}
)

target_link_libraries(runUnitTests
        gtest
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(runUnitTests)