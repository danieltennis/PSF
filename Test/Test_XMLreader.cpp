//
// Created by danie on 3/15/2026.
//
#include <gtest/gtest.h>
#include "../XMLreader.h"
#include "../MeetingPlanner.h"

using namespace std;

TEST(XMLreaderTest, TestReadValidFile)
{
    XMLreader* reader = new XMLreader();
    MeetingPlanner* planner = new MeetingPlanner();

    bool result = reader->readFile("../Meeting.xml", *planner);

    ASSERT_TRUE(result);
}

TEST(XMLreaderTest, TestFileNotFound)
{
    XMLreader* reader = new XMLreader();
    MeetingPlanner* planner = new MeetingPlanner();

    bool result = reader->readFile("nonexistent.xml", *planner);

    ASSERT_FALSE(result);
}