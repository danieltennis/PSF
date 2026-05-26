#include <gtest/gtest.h>
#include "../Meeting.h"
#include "../Room.h"

using namespace std;
using namespace std::chrono;

TEST(MeetingTest, TestGetLabel) {
    Room* room = new Room("RoomA", "A1", 10, "Main Campus", "Building 1");
    year_month_day date = year{2026}/5/22;

    Meeting* meeting = new Meeting("Weekly meeting", "M1", *room, date);

    string result = meeting->getLabel();
    string expected = "Weekly meeting";

    ASSERT_EQ(expected, result);
}

TEST(MeetingTest, TestGetIdentifier) {
    Room* room = new Room("RoomA", "A1", 10, "Main Campus", "Building 1");
    year_month_day date = year{2026}/5/22;

    Meeting* meeting = new Meeting("Weekly meeting", "M1", *room, date);

    string result = meeting->getIdentifier();
    string expected = "M1";

    ASSERT_EQ(expected, result);
}

TEST(MeetingTest, TestGetRoom) {
    Room* room = new Room("RoomA", "A1", 10, "Main Campus", "Building 1");
    year_month_day date = year{2026}/5/22;

    Meeting* meeting = new Meeting("Weekly meeting", "M1", *room, date);

    string result = meeting->getRoom().getIdentifier();
    string expected = "A1";

    ASSERT_EQ(expected, result);
}

TEST(MeetingTest, TestSetLabel) {
    Room* room = new Room("RoomA", "A1", 10, "Main Campus", "Building 1");
    year_month_day date = year{2026}/5/22;

    Meeting* meeting = new Meeting("Weekly meeting", "M1", *room, date);

    meeting->setLabel("Project meeting");

    string result = meeting->getLabel();
    string expected = "Project meeting";

    ASSERT_EQ(expected, result);
}

TEST(MeetingTest, TestSetIdentifier) {
    Room* room = new Room("RoomA", "A1", 10, "Main Campus", "Building 1");
    year_month_day date = year{2026}/5/22;

    Meeting* meeting = new Meeting("Weekly meeting", "M1", *room, date);

    meeting->setIdentifier("M2");

    string result = meeting->getIdentifier();
    string expected = "M2";

    ASSERT_EQ(expected, result);
}

// =========================================================================
// CONTRACT TESTEN (PRECONDITIES & EXPECT_DEATH)
// =========================================================================

// Test 1: Constructor mag geen leeg label accepteren
TEST(MeetingContractTest, InvalidConstructorLabel) {
    Room room("RoomA", "A1", 10, "Main Campus", "Building 1");
    year_month_day date = year{2026}/5/22;

    EXPECT_DEATH({
        Meeting meeting("", "M1", room, date);
    }, "Label van een meeting mag niet leeg zijn");
}

// Test 2: setOccupancy mag niet negatief zijn
TEST(MeetingContractTest, NegativeOccupancy) {
    Room room("RoomA", "A1", 10, "Main Campus", "Building 1");
    year_month_day date = year{2026}/5/22;
    Meeting meeting("Weekly meeting", "M1", room, date);

    EXPECT_DEATH({
        meeting.setOccupancy(-5.0);
    }, "Bezetting mag niet negatief zijn");
}

// Test 3: Bezetting mag de capaciteit van de kamer niet overschrijden
TEST(MeetingContractTest, OccupancyExceedsCapacity) {
    Room room("RoomA", "A1", 10, "Main Campus", "Building 1");
    year_month_day date = year{2026}/5/22;
    Meeting meeting("Weekly meeting", "M1", room, date);

    EXPECT_DEATH({
        meeting.setOccupancy(15.0);
    }, "Bezetting mag de capaciteit van de kamer niet overschrijden");
}

// Test 4: Veranderen naar een te kleine kamer mag niet
TEST(MeetingContractTest, ChangeToTooSmallRoom) {
    Room bigRoom("Big Room", "A1", 50, "Main Campus", "Building 1");
    Room smallRoom("Small Room", "B2", 10, "Main Campus", "Building 1");
    year_month_day date = year{2026}/5/22;

    Meeting meeting("Big Conference", "M1", bigRoom, date);
    meeting.setOccupancy(30.0); // Past in de grote kamer


    EXPECT_DEATH({
        meeting.setRoom(smallRoom);
    }, "Nieuwe kamer is te klein voor de huidige bezetting");
}