//
// Created by danie on 2/26/2026.
//

#ifndef TICTACTOE10_PARTICIPATION_H
#define TICTACTOE10_PARTICIPATION_H
#include <string>
using namespace std;

class Participation {
private:
    string user;
    string meetingIdentifiers;

public:
    //CONSTRUCTOR//
    Participation(string u, string m): user(u), meetingIdentifiers(m){}

    //GETTERS//
    string getUser() const {return user;}
    string getMeeting() const {return meetingIdentifiers;}

    //SETTERS//
    void setUser(string u) {this->user = u;}
    void setMeeting(string m) {this->meetingIdentifiers = m;}

};


#endif //TICTACTOE10_PARTICIPATION_H
#include "Participation.h"