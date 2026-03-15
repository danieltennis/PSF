#include <gtest/gtest.h>
#include "../Room.h"

// isValid moet TRUE zijn voor correcte room
TEST(RoomTest, ValidRoom)
{
    Room room("Room A", "A1", 10);

    EXPECT_TRUE(isValid(room));
}

// lege naam moet FALSE geven
TEST(RoomTest, EmptyName)
{
    Room room("", "A1", 10);

    EXPECT_FALSE(isValid(room));
}

// lege identifier moet FALSE geven
TEST(RoomTest, EmptyIdentifier)
{
    Room room("Room A", "", 10);

    EXPECT_FALSE(isValid(room));
}

// capaciteit <= 0 moet FALSE geven
TEST(RoomTest, InvalidCapacity)
{
    Room room("Room A", "A1", 0);

    EXPECT_FALSE(isValid(room));
}

// negatieve capaciteit
TEST(RoomTest, NegativeCapacity)
{
    Room room("Room A", "A1", -5);

    EXPECT_FALSE(isValid(room));
}