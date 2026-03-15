#include <gtest/gtest.h>
#include "../Meeting.h"
#include "../Room.h"

using namespace std;
using namespace std::chrono;

TEST(MeetingTest, TestGetLabel) {
    Room* room = new Room("A1", "RoomA", 10);
    year_month_day date = year{2026}/5/22;

    Meeting* meeting = new Meeting("Weekly meeting", "M1", *room, date);

    string result = meeting->getLabel();
    string expected = "Weekly meeting";

    ASSERT_EQ(expected, result);
}

TEST(MeetingTest, TestGetIdentifier) {
    Room* room = new Room("A1", "RoomA", 10);
    year_month_day date = year{2026}/5/22;

    Meeting* meeting = new Meeting("Weekly meeting", "M1", *room, date);

    string result = meeting->getIdentifier();
    string expected = "M1";

    ASSERT_EQ(expected, result);
}

TEST(MeetingTest, TestGetRoom) {
    Room* room = new Room("A1", "RoomA", 10);
    year_month_day date = year{2026}/5/22;

    Meeting* meeting = new Meeting("Weekly meeting", "M1", *room, date);

    string result = meeting->getRoom().getIdentifier();
    string expected = "RoomA";

    ASSERT_EQ(expected, result);
}

TEST(MeetingTest, TestSetLabel) {
    Room* room = new Room("A1", "RoomA", 10);
    year_month_day date = year{2026}/5/22;

    Meeting* meeting = new Meeting("Weekly meeting", "M1", *room, date);

    meeting->setLabel("Project meeting");

    string result = meeting->getLabel();
    string expected = "Project meeting";

    ASSERT_EQ(expected, result);
}

TEST(MeetingTest, TestSetIdentifier) {
    Room* room = new Room("A1", "RoomA", 10);
    year_month_day date = year{2026}/5/22;

    Meeting* meeting = new Meeting("Weekly meeting", "M1", *room, date);

    meeting->setIdentifier("M2");

    string result = meeting->getIdentifier();
    string expected = "M2";

    ASSERT_EQ(expected, result);
}