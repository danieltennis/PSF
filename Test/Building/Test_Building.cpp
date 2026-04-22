//
// Created by mohammed on 3/26/26.
//

//
// Created by danie on 3/26/2026.
//

#include <gtest/gtest.h>
#include "../../Building.h"

using namespace std;

TEST(BuildingTest, TestConstructorAndGetters) {
    Building b("Main Building", "B1", "C1");

    ASSERT_EQ(b.getName(), "Main Building");
    ASSERT_EQ(b.getIdentifier(), "B1");
    ASSERT_EQ(b.getCampusIdentifier(), "C1");
}

TEST(BuildingTest, TestSetName) {
    Building b;
    b.setName("Science Building");
    ASSERT_EQ(b.getName(), "Science Building");
}

TEST(BuildingTest, TestSetIdentifier) {
    Building b;
    b.setIdentifier("B2");
    ASSERT_EQ(b.getIdentifier(), "B2");
}

TEST(BuildingTest, TestSetCampusIdentifier) {
    Building b;
    b.setCampusIdentifier("C2");
    ASSERT_EQ(b.getCampusIdentifier(), "C2");
}

TEST(BuildingTest, TestDefaultConstructor) {
    Building b;
    ASSERT_EQ(b.getName(), "");
    ASSERT_EQ(b.getIdentifier(), "");
    ASSERT_EQ(b.getCampusIdentifier(), "");
}