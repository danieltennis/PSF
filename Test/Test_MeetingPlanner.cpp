//
// Created by danie on 3/15/2026.
//
#include <gtest/gtest.h>
#include "../MeetingPlanner.h"

using namespace std;

TEST(MeetingPlannerTest, TestAddRoom)
{
    MeetingPlanner* planner = new MeetingPlanner();

    planner->addRoom("Room A", "A1", 10, "5", "4");

    Room result = planner->findRoom("A1");

    string expected = "A1";

    ASSERT_EQ(expected, result.getIdentifier());
}

TEST(MeetingPlannerTest, TestFindRoom)
{
    MeetingPlanner* planner = new MeetingPlanner();

    planner->addRoom("Room B", "B1", 20, "5", "4");

    Room result = planner->findRoom("B1");

    int expected = 20;

    ASSERT_EQ(expected, result.getCapacity());
}

TEST(MeetingPlannerTest, TestAddMeeting)
{
    MeetingPlanner* planner = new MeetingPlanner();

    planner->addRoom("Room A", "A1", 10, "5", "10");

    Room room = planner->findRoom("A1");

    planner->addMeeting("Weekly meeting", "M1", room, "2026-05-22", false);

    bool result = planner->isConsistent();

    ASSERT_TRUE(result);
}

TEST(MeetingPlannerTest, TestAddParticipation)
{
    MeetingPlanner* planner = new MeetingPlanner();

    planner->addRoom("Room A", "A1", 10, "5", "4");

    Room room = planner->findRoom("A1");

    planner->addMeeting("Weekly meeting", "M1", room, "2026-05-22", false);

    planner->addParticipation("M1", "Peter Selie");

    bool result = planner->isConsistent();

    ASSERT_TRUE(result);
}

TEST(MeetingPlannerTest, TestInconsistentCapacity)
{
    MeetingPlanner* planner = new MeetingPlanner();

    planner->addRoom("Room A", "A1", 2, "4", "2");

    Room room = planner->findRoom("A1");

    planner->addMeeting("Big meeting", "M1", room, "2026-05-22", false);

    planner->addParticipation("M1", "User1");
    planner->addParticipation("M1", "User2");
    planner->addParticipation("M1", "User3");

    bool result = planner->isConsistent();

    ASSERT_FALSE(result);
}

TEST(MeetingPlannerTest, TestAddMeetingDuringRenovationThrows)
{
    MeetingPlanner planner;

    planner.addRoom("Room A", "A1", 10, "5", "4");
    planner.addRenovation("A1", "2026-05-20", "2026-05-25");

    Room room = planner.findRoom("A1");

    EXPECT_THROW(
        planner.addMeeting("Weekly meeting", "M1", room, "2026-05-22", false),
        std::invalid_argument
    );
}

TEST(MeetingPlannerTest, TestMeetingOutsideRenovation)
{
    MeetingPlanner* planner = new MeetingPlanner();

    planner->addRoom("Room A", "A1", 10, "5", "4");

    planner->addRenovation("A1", "2026-05-20", "2026-05-25");

    Room room = planner->findRoom("A1");

    // Buiten renovatie
    planner->addMeeting("Weekly meeting", "M1", room, "2026-05-30", false);

    bool result = planner->isConsistent();

    ASSERT_TRUE(result);
}