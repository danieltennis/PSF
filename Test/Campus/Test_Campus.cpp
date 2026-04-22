//
// Created by mohammed on 3/26/26.
//

//
// Created by danie on 3/26/2026.
//

#include <gtest/gtest.h>
#include "../../Campus.h"

using namespace std;

TEST(CampusTest, TestConstructorAndGetters) {
    Campus c("Main Campus", "C1");

    ASSERT_EQ(c.getName(), "Main Campus");
    ASSERT_EQ(c.getIdentifier(), "C1");
}

TEST(CampusTest, TestSetName) {
    Campus c;
    c.setName("Science Campus");
    ASSERT_EQ(c.getName(), "Science Campus");
}

TEST(CampusTest, TestSetIdentifier) {
    Campus c;
    c.setIdentifier("C2");
    ASSERT_EQ(c.getIdentifier(), "C2");
}

TEST(CampusTest, TestDefaultConstructor) {
    Campus c;
    ASSERT_EQ(c.getName(), "");
    ASSERT_EQ(c.getIdentifier(), "");
}