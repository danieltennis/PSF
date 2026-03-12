#include "Room.h"
#include "gtest/gtest.h"

TEST(RoomTest, StoresCapacityCorrectly) {
    // 1. Arrange
    Room myRoom("Auditoreum", "ROOM_001", 50);

    // 2. Act
    int currentCapacity = myRoom.getCapacity();

    // 3. Assert
    EXPECT_EQ(currentCapacity, 50);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}