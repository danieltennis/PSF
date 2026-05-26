#include <gtest/gtest.h>
#include "../Room.h"

// isValid moet TRUE zijn voor correcte room
TEST(RoomTest, ValidRoom)
{
    Room room("Room A", "A1", 10, "Main Campus", "Building 1");
    EXPECT_TRUE(isValid(room));
}

TEST(RoomTest, EmptyName)
{
    Room room("", "A1", 10, "Main Campus", "Building 1");
    EXPECT_FALSE(isValid(room));
}


// lege identifier moet FALSE geven
TEST(RoomTest, EmptyIdentifier)
{
    EXPECT_DEATH({
        Room room("Room A", "", 10, "Main Campus", "Building 1");
    }, "Kamer identifier mag niet leeg zijn");
}

// capaciteit <= 0 moet FALSE geven
TEST(RoomTest, InvalidCapacity)
{
    Room room("Room A", "A1", 0,"Main Campus","Building1");

    EXPECT_FALSE(isValid(room));
}

// negatieve capaciteit
TEST(RoomTest, NegativeCapacity)
{
    EXPECT_DEATH({
        Room room("Room A", "A1", -5, "Main Campus", "Building1");
    }, "Capaciteit van een kamer mag niet negatief zijn");
}