//
// Created by danie on 2/26/2026.
//

#include "MeetingPlanner.h"

#include <iostream>
#include <fstream>
#include "Room.h"
using namespace std;




void MeetingPlanner::addRoom(const string &name, const string &id, int capacity) {
    Room r;
    r.name = name;
    r.identifier = id;
    r.capacity = capacity;
}

void MeetingPlanner::Write_Output(const string &filename) const {
    ofstream out(filename);

    if (!out) {
        cerr<<"kan output bestand niet openen\n";
    }

    out<<"Past meetings:\n";
    for (const Meeting& m : meetings) {
        if (m.isPast()) {
            out<<"- "<<m.getRoom().getName()
               <<", "<<m.getFormattedDate<<"\n";




        }
    }

}





