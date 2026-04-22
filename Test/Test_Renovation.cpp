//
// Created by mohammed on 4/22/26.
//

#include <gtest/gtest.h>
#include "../Renovation.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

TEST(RenovationTest, TestGetRoomId)
{
    Renovation* r = new Renovation("A101", year{2026}/4/22, year{2026}/5/1);

    string result = r->getRoomId();
    string expected = "A101";

    ASSERT_EQ(expected, result);
}

TEST(RenovationTest, TestGetStartDate)
{
    Renovation* r = new Renovation("A101", year{2026}/4/22, year{2026}/5/1);

    year_month_day result = r->getStart();
    year_month_day expected = year{2026}/4/22;

    ASSERT_EQ(expected, result);
}

TEST(RenovationTest, TestGetEndDate)
{
    Renovation* r = new Renovation("A101", year{2026}/4/22, year{2026}/5/1);

    year_month_day result = r->getEnd();
    year_month_day expected = year{2026}/5/1;

    ASSERT_EQ(expected, result);
}

TEST(RenovationTest, TestSameStartAndEndDate)
{
    Renovation* r = new Renovation("A101", year{2026}/4/22, year{2026}/4/22);

    ASSERT_EQ(r->getStart(), r->getEnd());
}