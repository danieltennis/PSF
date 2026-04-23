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

#include <stdexcept>

void MeetingPlanner::addMeeting(const std::string &label,const std::string &id,Room room,const std::string &dateStr,bool catering)
{
    int y, m, d;
    char dash;
    std::stringstream ss(dateStr);
    ss >> y >> dash >> m >> dash >> d;

    std::chrono::year_month_day date{
        std::chrono::year{y},
        std::chrono::month{(unsigned)m},
        std::chrono::day{(unsigned)d}
    };


    for (const auto& ren : renovations) {
        if (room.getIdentifier() == ren.getRoomId()) {
            if (date >= ren.getStart() && date <= ren.getEnd()) {
                throw std::invalid_argument("Room is under renovation on this date");
            }
        }
    }

    meetings.emplace_back(label, id, room, date, catering);
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

        for (const auto& ren : renovations) {
            if (m.getRoom().getIdentifier() == ren.getRoomId()) {
                if (m.getDate() >= ren.getStart() && m.getDate() <= ren.getEnd()) {
                    return false;
                }
            }
        }
    }
    return true;
}

void MeetingPlanner::addRenovation(const string& roomId,const string& startStr,const string& endStr)
{
    int y1, m1, d1;
    int y2, m2, d2;
    char dash;

    stringstream ss1(startStr);
    ss1 >> y1 >> dash >> m1 >> dash >> d1;

    stringstream ss2(endStr);
    ss2 >> y2 >> dash >> m2 >> dash >> d2;

    chrono::year_month_day start{chrono::year{y1}, chrono::month{(unsigned)m1}, chrono::day{(unsigned)d1}};
    chrono::year_month_day end{chrono::year{y2}, chrono::month{(unsigned)m2}, chrono::day{(unsigned)d2}};

    renovations.emplace_back(roomId, start, end);
}

void MeetingPlanner::addCatering(const std::string& campusId, int co2) {
    caterings.emplace_back(campusId, co2);
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