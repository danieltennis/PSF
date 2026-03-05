//
// Created by danie on 2/26/2026.
//

#include "MeetingPlanner.h"

#include "Room.h"

void MeetingPlanner::addRoom(const string &name, const string &id, int capacity) {
    Room r;
    r.name = name;
    r.id = id;
    r.capacity = capacity;
}
