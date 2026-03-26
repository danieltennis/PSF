#ifndef TICTACTOE10_ROOM_H
#define TICTACTOE10_ROOM_H

#include <string>
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
        : name(n), identifier(i), capacity(c), campus(cam), building(bld) {}

    string getName() const { return name; }
    string getIdentifier() const { return identifier; }
    int getCapacity() const { return capacity; }
    string getCampus() const { return campus; }
    string getBuilding() const { return building; }

    void setName(string na) { name = na; }
    void setIdentifier(string id) { identifier = id; }
    void setCapacity(int ca) { capacity = ca; }
    void setCampus(string cam) { campus = cam; }
    void setBuilding(string bld) { building = bld; }
};

bool isValid(Room& room);
void checkName(Room& room);
void checkIdentifier(Room& room);
void checkCapacity(Room& room);
void checkCampus(Room& room);
void checkBuilding(Room& room);

#endif