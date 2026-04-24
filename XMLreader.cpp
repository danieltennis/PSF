#include "XMLreader.h"
#include "MeetingPlanner.h"
#include "tinyxml_2_6_2/tinyxml.h"

#include <iostream>
#include <string>

bool XMLreader::readFile(const std::string& filename, MeetingPlanner& planner) {
    TiXmlDocument doc(filename.c_str());

    if (!doc.LoadFile()) {
        std::cerr << "Kon bestand niet openen: " << filename << " (" << doc.ErrorDesc() << ")" << std::endl;
        return false;
    }

    TiXmlElement* root = doc.FirstChildElement("SYSTEM");
    if (!root) {
        std::cerr << "Geen SYSTEM element gevonden in XML." << std::endl;
        return false;
    }

    for (TiXmlElement* campusElem = root->FirstChildElement("CAMPUS");
         campusElem != nullptr;
         campusElem = campusElem->NextSiblingElement("CAMPUS")) {

        const char* name = campusElem->FirstChildElement("NAME") ?
                           campusElem->FirstChildElement("NAME")->GetText() : nullptr;
        const char* id = campusElem->FirstChildElement("IDENTIFIER") ?
                         campusElem->FirstChildElement("IDENTIFIER")->GetText() : nullptr;

        if (!name || !id) {
            errors.push_back("CAMPUS met ontbrekende velden");
            continue;
        }

        planner.addCampus(name, id);
    }

    for (TiXmlElement* buildingElem = root->FirstChildElement("BUILDING");
         buildingElem != nullptr;
         buildingElem = buildingElem->NextSiblingElement("BUILDING")) {

        const char* name = buildingElem->FirstChildElement("NAME") ?
                           buildingElem->FirstChildElement("NAME")->GetText() : nullptr;
        const char* id = buildingElem->FirstChildElement("IDENTIFIER") ?
                         buildingElem->FirstChildElement("IDENTIFIER")->GetText() : nullptr;
        const char* campus = buildingElem->FirstChildElement("CAMPUS") ?
                             buildingElem->FirstChildElement("CAMPUS")->GetText() : nullptr;

        if (!name || !id || !campus) {
            errors.push_back("BUILDING met ontbrekende velden");
            continue;
        }

        planner.addBuilding(name, id, campus);
    }

    for (TiXmlElement* roomElem = root->FirstChildElement("ROOM");
         roomElem != nullptr;
         roomElem = roomElem->NextSiblingElement("ROOM")) {

        const char* name = roomElem->FirstChildElement("NAME") ?
                           roomElem->FirstChildElement("NAME")->GetText() : nullptr;
        const char* id = roomElem->FirstChildElement("IDENTIFIER") ?
                         roomElem->FirstChildElement("IDENTIFIER")->GetText() : nullptr;
        const char* cap = roomElem->FirstChildElement("CAPACITY") ?
                          roomElem->FirstChildElement("CAPACITY")->GetText() : nullptr;
        const char* campus = roomElem->FirstChildElement("CAMPUS") ?
                             roomElem->FirstChildElement("CAMPUS")->GetText() : nullptr;
        const char* building = roomElem->FirstChildElement("BUILDING") ?
                               roomElem->FirstChildElement("BUILDING")->GetText() : nullptr;

        if (!name || !id || !cap || !campus || !building) {
            errors.push_back("ROOM met ontbrekende velden");
            continue;
        }

        int capacity = std::stoi(cap);
        if (capacity <= 0) {
            errors.push_back("ROOM " + std::string(id) + " heeft ongeldige capaciteit");
            continue;
        }

        planner.addRoom(name, id, capacity, campus, building);
    }

    for (TiXmlElement* renElem = root->FirstChildElement("RENOVATION");
     renElem != nullptr;
     renElem = renElem->NextSiblingElement("RENOVATION")) {

        const char* room = renElem->FirstChildElement("ROOM") ?
                           renElem->FirstChildElement("ROOM")->GetText() : nullptr;

        const char* start = renElem->FirstChildElement("START") ?
                            renElem->FirstChildElement("START")->GetText() : nullptr;

        const char* end = renElem->FirstChildElement("END") ?
                          renElem->FirstChildElement("END")->GetText() : nullptr;

        if (!room || !start || !end) {
            errors.push_back("RENOVATION met ontbrekende velden");
            continue;
        }

        planner.addRenovation(room, start, end);
     }

    for (TiXmlElement* catElem = root->FirstChildElement("CATERING");
     catElem != nullptr;
     catElem = catElem->NextSiblingElement("CATERING")) {

        const char* campus = catElem->FirstChildElement("CAMPUS") ?
                             catElem->FirstChildElement("CAMPUS")->GetText() : nullptr;

        const char* co2Str = catElem->FirstChildElement("CO2") ?
                             catElem->FirstChildElement("CO2")->GetText() : nullptr;

        if (!campus || !co2Str) {
            errors.emplace_back("CATERING met ontbrekende velden");
            continue;
        }

        int co2;
        try {
            co2 = std::stoi(co2Str);
        } catch (...) {
            errors.emplace_back("CATERING heeft ongeldige CO2 waarde");
            continue;
        }

        if (co2 <= 0) {
            errors.emplace_back("CATERING CO2 moet > 0 zijn");
            continue;
        }

        Campus c = planner.findCampus(campus);
        if (c.getIdentifier() == "Unknown") {
            errors.push_back("CATERING verwijst naar onbekende campus: " + std::string(campus));
            continue;
        }

        planner.addCatering(campus, co2);
     }

    for (TiXmlElement* meetElem = root->FirstChildElement("MEETING");
         meetElem != nullptr;
         meetElem = meetElem->NextSiblingElement("MEETING")) {

        const char* label = meetElem->FirstChildElement("LABEL") ?
                            meetElem->FirstChildElement("LABEL")->GetText() : nullptr;
        const char* id = meetElem->FirstChildElement("IDENTIFIER") ?
                         meetElem->FirstChildElement("IDENTIFIER")->GetText() : nullptr;
        const char* room = meetElem->FirstChildElement("ROOM") ?
                           meetElem->FirstChildElement("ROOM")->GetText() : nullptr;
        const char* date = meetElem->FirstChildElement("DATE") ?
                           meetElem->FirstChildElement("DATE")->GetText() : nullptr;
        const char* cateringStr = meetElem->FirstChildElement("CATERING") ?
                          meetElem->FirstChildElement("CATERING")->GetText() : "false";
        bool catering = std::string(cateringStr) == "TRUE";

        const char* onlineStr = meetElem->FirstChildElement("ONLINE") ?
            meetElem->FirstChildElement("ONLINE")->GetText() : "false";

        bool online = std::string(onlineStr) == "TRUE";


        if (!label || !id || !date) {
            errors.emplace_back("MEETING met ontbrekende velden");
            continue;
        }

        if (online && catering) {
            errors.emplace_back("MEETING " + std::string(id) + ": online meetings kunnen geen catering hebben");
            continue;
        }

        // dummy room
        Room actualRoom = {"Online", "ONLINE", 0, "NONE", "NONE"};
        if (!online) {
            if (!room) {
                errors.emplace_back("MEETING " + std::string(id) + ": ontbrekende room");
                continue;
            }
            actualRoom = planner.findRoom(room);

        }


        try {
            planner.addMeeting(label, id, actualRoom, date, catering,online);
        } catch (const std::exception& e) {
            errors.push_back("MEETING fout (" + std::string(id) + "): " + e.what());
        }

    }

    for (TiXmlElement* partElem = root->FirstChildElement("PARTICIPATION");
         partElem != nullptr;
         partElem = partElem->NextSiblingElement("PARTICIPATION")) {

        const char* meeting = partElem->FirstChildElement("MEETING") ?
                              partElem->FirstChildElement("MEETING")->GetText() : nullptr;
        const char* user = partElem->FirstChildElement("USER") ?
                           partElem->FirstChildElement("USER")->GetText() : nullptr;

        if (!meeting || !user) {
            errors.push_back("PARTICIPATION met ontbrekende velden");
            continue;
        }

        planner.addParticipation(meeting, user);
    }

    printErrors();



    if (!planner.isConsistent()) {
        std::cerr << "Systeem is inconsistent. Programma wordt gestopt." << std::endl;
        return false;
    }

    return true;
}

void XMLreader::printErrors() const {
    for (const auto& e : errors) {
        std::cerr << "Error: " << e << std::endl;
    }
}