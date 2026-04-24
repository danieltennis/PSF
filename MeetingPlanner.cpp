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
    return {"Unknown", id, 0, "UnknownCampus", "UnknownBuilding"};
}

void MeetingPlanner::addCampus(const string &name, const string &id) {
    campuses.emplace_back(name, id);
}

Campus MeetingPlanner::findCampus(const string &id) const {
    for (const auto& c : campuses)
        if (c.getIdentifier() == id)
            return c;
    return {"Unknown", "Unknown"};
}

void MeetingPlanner::addBuilding(const string &name, const string &id, const string &campusId) {
    buildings.emplace_back(name, id, campusId);
}

Building MeetingPlanner::findBuilding(const string &id) const {
    for (const auto& b : buildings)
        if (b.getIdentifier() == id)
            return b;
    return {"Unknown", "Unknown", "UnknownCampus"};
}

#include <stdexcept>

void MeetingPlanner::addMeeting(const std::string &label,const std::string &id,const Room& room,const std::string &dateStr,bool catering,bool online)
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


    if (!online) {
        for (const auto& ren : renovations) {
            if (room.getIdentifier() == ren.getRoomId()) {
                if (date >= ren.getStart() && date <= ren.getEnd()) {
                    throw std::invalid_argument("Room is under renovation on this date");
                }
            }
        }
    }

    if (online && catering) {
        throw std::invalid_argument("Online meeting can not have catering");
    }

    meetings.emplace_back(label, id, room, date, catering,online);

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

        if (!m.isOnline()) {
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

int MeetingPlanner::getCO2ForCampus(const std::string& campusId) const {
    for (const auto& c : caterings) {
        if (c.getCampusId() == campusId) {
            return c.getCO2();
        }
    }
    return 0;
}

void MeetingPlanner::Write_Output(const string &filename) const {
    ofstream out(filename);
    if (!out) {
        cerr << "Kan output bestand niet openen\n";
        return;
    }

    out << "## ==== [SYSTEM STATUS] ==== ##" << endl;
    writeAll(out);
}

void MeetingPlanner::printAll() const {
    writeAll(std::cout);
}

void MeetingPlanner::processMeetings() const {

    for (size_t i = 0; i < meetings.size(); i++) {

        const Meeting& current = meetings[i];
        bool conflict = false;

        for (size_t j = 0; j < meetings.size(); j++) {

            if (i == j) continue;

            const Meeting& other = meetings[j];

            if (!current.isOnline() && !other.isOnline()) {
                if (current.getRoom().getIdentifier() == other.getRoom().getIdentifier() &&
                    current.getDate() == other.getDate()) {
                    conflict = true;
                    break;
                    }
            }
        }

        if (conflict) {
            std::cout << "Error: Meeting " << current.getIdentifier()
                      << " kan niet doorgaan (room bezet)" << std::endl;
        } else {
            std::cout << "Meeting " << current.getIdentifier()
                      << " heeft plaatsgevonden." << std::endl;
        }
    }
}

void MeetingPlanner::writeAll(std::ostream& out) const {
    out << "=== CAMPUSSEN ===" << endl;
    if (campuses.empty()) out << "Geen campussen geregistreerd." << endl;
    else for (const auto& c : campuses)
        out << "- " << c.getName() << " (" << c.getIdentifier() << ")" << endl;

    out << "\n=== GEBBOUWEN ===" << endl;
    if (buildings.empty()) out << "Geen gebouwen geregistreerd." << endl;
    else for (const auto& b : buildings)
        out << "- " << b.getName()
            << " (" << b.getIdentifier() << ")"
            << ", Campus: " << b.getCampusIdentifier() << endl;

    out << "\n=== KAMERS ===" << endl;
    if (rooms.empty()) out << "Geen kamers geregistreerd." << endl;
    else for (const auto& r : rooms)
        out << "- " << r.getName()
            << " (ID: " << r.getIdentifier()
            << ", Capaciteit: " << r.getCapacity()
            << ", Gebouw: " << r.getBuilding()
            << ", Campus: " << r.getCampus() << ")" << endl;

    out << "\n=== MEETINGS ===" << endl;
    if (meetings.empty()) out << "Geen meetings gevonden." << endl;
    else for (const auto& m : meetings) {
        auto d = m.getDate();

        out << "- " << m.getLabel() << " [" << m.getIdentifier() << "]" << endl;
        out << "  Locatie: " << m.getRoom().getName()
            << " (" << m.getRoom().getIdentifier() << ")"
            << ", Gebouw: " << m.getRoom().getBuilding()
            << ", Campus: " << m.getRoom().getCampus() << endl;

        out << "  Datum: " << (int)d.year() << "-"
            << (unsigned)d.month() << "-"
            << (unsigned)d.day() << endl;

        out << "  Catering: " << (m.hasCatering() ? "Ja" : "Nee") << endl;

        int co2 = getCO2ForCampus(m.getRoom().getCampus());
        out << "  CO2 catering: " << (m.hasCatering() ? co2 : 0) << " kg" << endl;

        out << "  Deelnemers: ";

        bool first = true;
        for (const auto& p : participations)
            if (p.getMeetingIdentifier() == m.getIdentifier()) {
                if (!first) out << ", ";
                out << p.getUser();
                first = false;
            }

        if (first) out << "Geen deelnemers geregistreerd.";
        out << "\n  -----------------------" << endl;
    }

    int totalCO2 = 0;
    for (const auto& m : meetings)
        if (m.hasCatering())
            totalCO2 += getCO2ForCampus(m.getRoom().getCampus());

    out << "\n--== CO2 summary ==--" << endl;
    out << "Total CO2 emitted: " << totalCO2 << " kg" << endl;
}