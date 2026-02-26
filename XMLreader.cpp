#include "XMLreader.h"
#include "MeetingPlanner.h"

#include <iostream>
#include "tinyxml_2_6_2/tinyxml.h"

bool XMLreader::readFile(const std::string& filename,
                         MeetingPlanner& planner) {

    TiXmlDocument doc(filename.c_str());

    if (!doc.LoadFile()) {
        std::cerr << doc.ErrorDesc() << std::endl;
        return false;
    }

    TiXmlElement* root = doc.FirstChildElement("SYSTEM");
    if (!root) {
        std::cerr << "Geen SYSTEM element gevonden" << std::endl;
        return false;
    }

    /* =====================
       ROOMS lezen
       ===================== */
    for (TiXmlElement* roomElem = root->FirstChildElement("ROOM");
         roomElem != nullptr;
         roomElem = roomElem->NextSiblingElement("ROOM")) {

        const char* name = roomElem->FirstChildElement("NAME") ?
                           roomElem->FirstChildElement("NAME")->GetText() : nullptr;
        const char* id = roomElem->FirstChildElement("IDENTIFIER") ?
                         roomElem->FirstChildElement("IDENTIFIER")->GetText() : nullptr;
        const char* cap = roomElem->FirstChildElement("CAPACITY") ?
                          roomElem->FirstChildElement("CAPACITY")->GetText() : nullptr;

        if (!name || !id || !cap) {
            errors.push_back("ROOM met ontbrekende velden");
            continue;
        }

        int capacity = std::stoi(cap);
        if (capacity <= 0) {
            errors.push_back("ROOM " + std::string(id) + " heeft ongeldige capaciteit");
            continue;
        }

        planner.addRoom(name, id, capacity);
    }

    /* =====================
       MEETINGS lezen
       ===================== */
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

        if (!label || !id || !room || !date) {
            errors.push_back("MEETING met ontbrekende velden");
            continue;
        }

        planner.addMeeting(label, id, room, date);
    }

    /* =====================
       PARTICIPATIONS lezen
       ===================== */
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