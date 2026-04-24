
#ifndef TICTACTOE10_MEETING_H
#define TICTACTOE10_MEETING_H

#include <chrono>
#include <string>
#include "Room.h"

class Meeting {
private:
    std::string label;
    std::string identifier;
    Room room;
    std::chrono::year_month_day date;
    bool catering;
    bool online;



public:
    // CONSTRUCTOR
    Meeting(std::string l, std::string i, Room r, std::chrono::year_month_day d,bool c = false,bool online = false)
        : label(l), identifier(i), room(r), date(d),catering(c),online (online) {}

    // GETTERS
    std::string getLabel() const { return label; }
    std::string getIdentifier() const { return identifier; }
    Room getRoom() const { return room; }
    std::chrono::year_month_day getDate() const { return date; }
    bool hasCatering() const { return catering; }
    bool isOnline() const {return online;}

    // SETTERS
    void setLabel(std::string l) { this->label = l; }
    void setIdentifier(std::string i) { this->identifier = i; }
    void setRoom(Room r) { this->room = r; }
    void setDate(std::chrono::year_month_day d) { this->date = d; }
    void setCatering(bool c) { this->catering = c; }

    bool isPast() const;
};

#endif // TICTACTOE10_MEETING_H
