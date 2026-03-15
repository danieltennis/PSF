//
// Created by danie on 3/15/2026.
//
#include <gtest/gtest.h>
#include "../Participation.h"

using namespace std;

TEST(ParticipationTest, TestGetUser)
{
    Participation* p = new Participation("Peter Selie", "M1");

    string result = p->getUser();
    string expected = "Peter Selie";

    ASSERT_EQ(expected, result);
}

TEST(ParticipationTest, TestGetMeetingIdentifier)
{
    Participation* p = new Participation("Peter Selie", "M1");

    string result = p->getMeetingIdentifier();
    string expected = "M1";

    ASSERT_EQ(expected, result);
}

TEST(ParticipationTest, TestSetUser)
{
    Participation* p = new Participation("Peter Selie", "M1");

    p->setUser("John Doe");

    string result = p->getUser();
    string expected = "John Doe";

    ASSERT_EQ(expected, result);
}

TEST(ParticipationTest, TestSetMeeting)
{
    Participation* p = new Participation("Peter Selie", "M1");

    p->setMeeting("M2");

    string result = p->getMeetingIdentifier();
    string expected = "M2";

    ASSERT_EQ(expected, result);
}
