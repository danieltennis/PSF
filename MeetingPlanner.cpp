#include "MeetingPlanner.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

void MeetingPlanner::addRoom(const string& name, const string& id, int capacity,
                             const string& campusId, const string& buildingId)
{
    rooms.emplace_back(name, id, capacity, campusId, buildingId);
}

Room MeetingPlanner::findRoom(const string &id) const {
    for (const auto& r : rooms)
        if (r.getIdentifier() == id)
            return r;
    cerr << "Room niet gevonden: " << id << endl;
    return Room("Unknown", id, 0, "UnknownCampus", "UnknownBuilding");
}

void MeetingPlanner::addCampus(const string &name, const string &id) {
    campuses.emplace_back(name, id);
}

Campus MeetingPlanner::findCampus(const string &id) const {
    for (const auto& c : campuses)
        if (c.getIdentifier() == id)
            return c;
    return Campus("Unknown", "Unknown");
}

void MeetingPlanner::addBuilding(const string &name, const string &id, const string &campusId) {
    buildings.emplace_back(name, id, campusId);
}

Building MeetingPlanner::findBuilding(const string &id) const {
    for (const auto& b : buildings)
        if (b.getIdentifier() == id)
            return b;
    return Building("Unknown", "Unknown", "UnknownCampus");
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
    for (const auto& m : meetings) {
        int count = 0;
        for (const auto& p : participations)
            if (p.getMeetingIdentifier() == m.getIdentifier())
                count++;
        if (count > m.getRoom().getCapacity())
            return false;
    }
    return true;
}

void MeetingPlanner::Write_Output(const string &filename) const {
    ofstream out(filename);
    if (!out) { cerr << "Kan output bestand niet openen\n"; return; }

    out << "Past meetings:\n";
    for (const auto& m : meetings) {
        if (m.isPast())
            out << "- " << m.getRoom().getName() << endl;
    }
}

void MeetingPlanner::printAll() const {
    cout << "=== CAMPUSSEN ===" << endl;
    if (campuses.empty()) cout << "Geen campussen geregistreerd." << endl;
    else for (const auto& c : campuses)
        cout << "- " << c.getName() << " (" << c.getIdentifier() << ")" << endl;

    cout << "\n=== GEBBOUWEN ===" << endl;
    if (buildings.empty()) cout << "Geen gebouwen geregistreerd." << endl;
    else for (const auto& b : buildings)
        cout << "- " << b.getName()
             << " (" << b.getIdentifier() << ")"
             << ", Campus: " << b.getCampusIdentifier() << endl;

    cout << "\n=== KAMERS ===" << endl;
    if (rooms.empty()) cout << "Geen kamers geregistreerd." << endl;
    else for (const auto& r : rooms)
        cout << "- " << r.getName()
             << " (ID: " << r.getIdentifier()
             << ", Capaciteit: " << r.getCapacity()
             << ", Gebouw: " << r.getBuilding()
             << ", Campus: " << r.getCampus() << ")" << endl;

    cout << "\n=== MEETINGS ===" << endl;
    if (meetings.empty()) cout << "Geen meetings gevonden." << endl;
    else for (const auto& m : meetings) {
        auto d = m.getDate();
        cout << "- " << m.getLabel() << " [" << m.getIdentifier() << "]" << endl;
        cout << "  Locatie: " << m.getRoom().getName()
             << " (" << m.getRoom().getIdentifier() << ")"
             << ", Gebouw: " << m.getRoom().getBuilding()
             << ", Campus: " << m.getRoom().getCampus() << endl;
        cout << "  Datum: " << (int)d.year() << "-" << (unsigned)d.month() << "-" << (unsigned)d.day() << endl;

        cout << "  Deelnemers: ";
        bool first = true;
        for (const auto& p : participations)
            if (p.getMeetingIdentifier() == m.getIdentifier()) {
                if (!first) cout << ", ";
                cout << p.getUser();
                first = false;
            }
        if (first) cout << "Geen deelnemers geregistreerd.";
        cout << "\n  -----------------------" << endl;
    }
}