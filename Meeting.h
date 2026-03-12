#include <chrono>
#include <string>

#include "Room.h"



#include <chrono>
#include <string>
using namespace std;


#ifndef TICTACTOE10_MEETING_H
#define TICTACTOE10_MEETING_H


class Meeting {
private:
    string label;
    string identifier;
    string room;
    chrono::year_month_day date;

public:
    //CONSTRUCTOR//
    Meeting(string l, string i, string r, std::chrono::year_month_day d):label(l), identifier(i),room(r), date(d){}

    //GETTERS//
    string getLabel() const {return label;}
    string getIdentifier() const {return identifier;}
    string getRoom() const {return room;}
    chrono::year_month_day getDate() const {return date;}

    //SETTERS//
    void setLabel(string l) {this->label = l;}
    void setIdentifier(string i) {this->identifier = i;}
    void setRoom(string r) {this->room = r;}
    void setDate(chrono::year_month_day d) {this->date = d;}
};


#endif //TICTACTOE10_MEETING_H
#include "Meeting.h"