//
// Created by danie on 2/26/2026.
//

#include "MeetingPlanner.h"

#include <iostream>
#include <fstream>
#include "Room.h"
#include "gtest/gtest.h"
using namespace std;




void MeetingPlanner::addRoom(const string &name, const string &id, int capacity) {

    Room r(name, id, capacity);
    rooms.push_back(r);
}


Room MeetingPlanner::findRoom(const string& id) {
    for (const auto& r : rooms) {
        if (r.getIdentifier() == id) {
            return r;
        }
    }
    return Room("Onbekend", id, 0);
}

void MeetingPlanner::Write_Output(const string &filename) const {
    ofstream out(filename);

    if (!out) {
        cerr<<"kan output bestand niet openen\n";
    }

    out<<"Past meetings:\n";
    for (const Meeting& m : meetings) {
        if (m.isPast()) {
            out<<"- "<<m.getRoom().getName();




        }
    }

}


void MeetingPlanner::addMeeting(const string &label, const string &id, Room room, const string &dateStr) {
    int y, m, d;
    char dash;
    stringstream ss(dateStr);
    ss >> y >> dash >> m >> dash >> d;

    chrono::year_month_day date{chrono::year{y}, chrono::month{(unsigned)m}, chrono::day{(unsigned)d}};

    meetings.emplace_back(label, id, room, date);
}

void MeetingPlanner::addParticipation(const string &meetingId, const string &user) {
    participations.emplace_back(user, meetingId);
}

bool MeetingPlanner::isConsistent() const {
    return true; // Placeholder so the program can run
}

void MeetingPlanner::printAll() const {
    cout << "=== KAMERS ===" << endl;
    if (rooms.empty()) {
        cout << "Geen kamers geregistreerd." << endl;
    } else {
        for (const auto& r : rooms) {
            cout << "- " << r.getName()
                 << " (ID: " << r.getIdentifier()
                 << ", Capaciteit: " << r.getCapacity() << ")" << endl;
        }
    }

    cout << "\n=== MEETINGS ===" << endl;
    if (meetings.empty()) {
        cout << "Geen meetings gevonden." << endl;
    } else {
        for (const auto& m : meetings) {
            auto d = m.getDate();

            cout << "- " << m.getLabel() << " [" << m.getIdentifier() << "]" << endl;
            cout << "  Locatie:    " << m.getRoom().getName() << " (" << m.getRoom().getIdentifier() << ")" << endl;
            cout << "  Datum:      " << (int)d.year() << "-"
                                     << (unsigned)d.month() << "-"
                                     << (unsigned)d.day() << endl;

            cout << "  Deelnemers: ";
            bool first = true;
            for (const auto& p : participations) {
                // We koppelen de deelname aan de meeting via het Identifier
                if (p.getMeetingIdentifier() == m.getIdentifier()) {
                    if (!first) cout << ", ";
                    cout << p.getUser();
                    first = false;
                }
            }

            if (first) {
                cout << "Geen deelnemers geregistreerd.";
            }

            cout << "\n  -----------------------" << endl;
        }
    }
}







