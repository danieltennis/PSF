
//
// Created by danie on 2/26/2026.
//

#include "MeetingPlanner.h"

std::vector<Campus> campuses;
std::vector<Building> buildings;
#include <iostream>
#include <fstream>
#include "Room.h"
#include "gtest/gtest.h"
using namespace std;






void MeetingPlanner::addRoom(const std::string& name,const std::string& id,int capacity,const std::string& campusId,
    const std::string& buildingId)
{
    Room r(name, id, capacity, campusId, buildingId);
    rooms.push_back(r);
}


Room MeetingPlanner::findRoom(const std::string& id) {
    for (const auto& r : rooms) {
        if (r.getIdentifier() == id) {
            return r;
        }
    }
    return Room("Onbekend", id, 0, "UnknownCampus", "UnknownBuilding");
}


void MeetingPlanner::addCampus(const std::string& name, const std::string& id) {
    campuses.emplace_back(name, id);
}

void MeetingPlanner::addBuilding(const std::string& name, const std::string& id, const std::string& campusId) {
    buildings.emplace_back(name, id, campusId);
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

bool MeetingPlanner::isConsistent() const
{
    for (const Meeting& m : meetings)
    {
        int participantCount = 0;

        // tel aantal participations voor deze meeting
        for (const Participation& p : participations)
        {
            if (p.getMeetingIdentifier() == m.getIdentifier())
            {
                participantCount++;
            }
        }

        // check capaciteit
        if (participantCount > m.getRoom().getCapacity())
        {
            return false;
        }
    }

    return true;
}

void MeetingPlanner::printAll() const {
    cout << "=== CAMPUSSEN ===" << endl;
    if (campuses.empty()) {
        cout << "Geen campussen geregistreerd." << endl;
    } else {
        for (const auto& c : campuses) {
            cout << "- " << c.getName() << " (" << c.getIdentifier() << ")" << endl;
        }
    }

    cout << "\n=== GEBBOUWEN ===" << endl;
    if (buildings.empty()) {
        cout << "Geen gebouwen geregistreerd." << endl;
    } else {
        for (const auto& b : buildings) {
            cout << "- " << b.getName()
                 << " (" << b.getIdentifier() << ")"
                 << ", Campus: " << b.getCampusIdentifier() << endl;
        }
    }

    cout << "\n=== KAMERS ===" << endl;
    if (rooms.empty()) {
        cout << "Geen kamers geregistreerd." << endl;
    } else {
        for (const auto& r : rooms) {
            cout << "- " << r.getName()
                 << " (ID: " << r.getIdentifier()
                 << ", Capaciteit: " << r.getCapacity()
                 << ", Gebouw: " << r.getBuilding()
                 << ", Campus: " << r.getCampus() << ")" << endl;
        }
    }

    cout << "\n=== MEETINGS ===" << endl;
    if (meetings.empty()) {
        cout << "Geen meetings gevonden." << endl;
    } else {
        for (const auto& m : meetings) {
            auto d = m.getDate();
            cout << "- " << m.getLabel() << " [" << m.getIdentifier() << "]" << endl;
            cout << "  Locatie: " << m.getRoom().getName()
                 << " (" << m.getRoom().getIdentifier() << ")"
                 << ", Gebouw: " << m.getRoom().getBuilding()
                 << ", Campus: " << m.getRoom().getCampus() << endl;
            cout << "  Datum: " << (int)d.year() << "-" << (unsigned)d.month() << "-" << (unsigned)d.day() << endl;

            cout << "  Deelnemers: ";
            bool first = true;
            for (const auto& p : participations) {
                if (p.getMeetingIdentifier() == m.getIdentifier()) {
                    if (!first) cout << ", ";
                    cout << p.getUser();
                    first = false;
                }
            }
            if (first) cout << "Geen deelnemers geregistreerd.";
            cout << "\n  -----------------------" << endl;
        }
    }
}
