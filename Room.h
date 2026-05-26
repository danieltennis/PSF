#ifndef TICTACTOE10_ROOM_H
#define TICTACTOE10_ROOM_H

#include <string>

#include "DesignByContract.h"
using namespace std;

class Room
{
public:
    string name;
    string identifier;
    int capacity;
    string campus;
    string building;

    Room() = default;
    Room(string n, string i, int c, string cam, string bld)
        : name(n), identifier(i), capacity(c), campus(cam), building(bld) {

        REQUIRE(c >= 0, "Capaciteit van een kamer mag niet negatief zijn");
        REQUIRE(!i.empty(), "Kamer identifier mag niet leeg zijn");

        ENSURE(getCapacity() == c, "Capaciteit is niet correct ingesteld");
        ENSURE(getIdentifier() == i, "Identifier is niet correct ingesteld");
    }

    string getName() const { return name; }
    string getIdentifier() const { return identifier; }
    int getCapacity() const { return capacity; }
    string getCampus() const { return campus; }
    string getBuilding() const { return building; }

    void setName(string na) {
        name = na;
        ENSURE(getName() == na, "Naam is niet correct aangepast");
    }
    void setIdentifier(string id) {
        REQUIRE(!id.empty(), "Identifier mag niet leeg zijn");
        identifier = id;
        ENSURE(getIdentifier() == id, "Identifier is niet correct aangepast");
    }
    void setCapacity(int ca) {
        REQUIRE(ca >= 0, "Capaciteit mag niet negatief zijn");

        capacity = ca;
        ENSURE(getCapacity() == ca, "Capaciteit is niet correct aangepast");
    }
    void setCampus(string cam) {
        campus = cam;
        ENSURE(getCampus() == cam, "Campus is niet correct aangepast");
    }
    void setBuilding(string bld) {
        building = bld;
        ENSURE(getBuilding() == bld, "Gebouw is niet correct aangepast");
    }
};

bool isValid(Room& room);
void checkName(Room& room);
void checkIdentifier(Room& room);
void checkCapacity(Room& room);
void checkCampus(Room& room);
void checkBuilding(Room& room);

#endif