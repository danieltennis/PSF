
#ifndef TICTACTOE10_MEETING_H
#define TICTACTOE10_MEETING_H

#include <chrono>
#include <string>

#include "DesignByContract.h"
#include "Room.h"

class Meeting {
private:
    std::string label;
    std::string identifier;
    Room room;
    std::chrono::year_month_day date;
    bool catering;
    bool online;
    double occupancy = 0;


public:
    // CONSTRUCTOR
    Meeting(std::string l, std::string i, Room r, std::chrono::year_month_day d,bool c = false,bool online = false)
        : label(l), identifier(i), room(r), date(d),catering(c),online (online) {

        REQUIRE(!l.empty(), "Label van een meeting mag niet leeg zijn");
        REQUIRE(!i.empty(), "Identifier van een meeting mag niet leeg zijn");

        ENSURE(getLabel() == l, "Label is niet correct ingesteld");
        ENSURE(getIdentifier() == i, "Identifier is niet correct ingesteld");
    }

    // GETTERS
    std::string getLabel() const { return label; }
    std::string getIdentifier() const { return identifier; }
    Room getRoom() const { return room; }
    std::chrono::year_month_day getDate() const { return date; }
    bool hasCatering() const { return catering; }
    bool isOnline() const {return online;}
    int getOccupancy() const { return occupancy; }


    // SETTERS
    void setLabel(std::string l) {
        REQUIRE(!l.empty(), "Label mag niet leeg zijn");
        this->label = l;
        ENSURE(getLabel() == l, "Label is niet correct aangepast");
    }

    void setIdentifier(std::string i) {
        REQUIRE(!i.empty(), "Identifier mag niet leeg zijn");
        this->identifier = i;
        ENSURE(getIdentifier() == i, "Identifier is niet correct aangepast");
    }

    void setRoom(Room r) {
        // PRECONDITIE: Als er al een bezetting is ingevoerd, moet de nieuwe kamer groot genoeg zijn
        REQUIRE(this->occupancy <= r.getCapacity(), "Nieuwe kamer is te klein voor de huidige bezetting");

        this->room = r;
        ENSURE(getRoom().getIdentifier() == r.getIdentifier(), "Kamer is niet correct aangepast");
    }

    void setDate(std::chrono::year_month_day d) {
        this->date = d;
        ENSURE(getDate() == d, "Datum is niet correct aangepast");
    }

    void setCatering(bool c) {
        this->catering = c;
        ENSURE(hasCatering() == c, "Catering is niet correct aangepast");
    }

    void setOccupancy(double oc) {
        // PRECONDITIES: Bezetting mag niet negatief zijn en niet groter dan de zaalcapaciteit [cite: 100]
        REQUIRE(oc >= 0, "Bezetting mag niet negatief zijn");
        REQUIRE(oc <= room.getCapacity(), "Bezetting mag de capaciteit van de kamer niet overschrijden");

        this->occupancy = oc;

        // POSTCONDITIE [cite: 101]
        ENSURE(getOccupancy() == (int)oc, "Bezetting is niet correct aangepast");
    }

    bool isPast() const;
};

#endif // TICTACTOE10_MEETING_H
