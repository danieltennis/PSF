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

// etc.

// lege identifier moet FALSE geven
TEST(RoomTest, EmptyIdentifier)
{
    Room room("Room A", "", 10,"Main Campus", "Building 1");

    EXPECT_FALSE(isValid(room));
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
    Room room("Room A", "A1", -5,"Main Campus","Building1");

    EXPECT_FALSE(isValid(room));
}