;//
// Created by danie on 2/26/2026.
//

#ifndef TICTACTOE10_ROOM_H
#define TICTACTOE10_ROOM_H

#include <string>
using namespace std;

class Room
{
public:
    string name;
    string identifier;
    int capacity;

    Room() = default;
    //CONSTRUCTOR//
    Room(string n, string i, int c): name(n), identifier(i), capacity(c) {}

    //GETTERS//
    string getName() const {return name;}
    string getIdentifier() const {return identifier;}
    int getCapacity() const {return capacity;}

    //SETTERS//
    //gaan we dit niet moeten gebruiken om een kamer aan te maken aan de hand van de xml parser?//
    void setName(string na) {this->name = na;}
    void setIdentifier(string id) {this->identifier = id;}
    void setCapacity(int ca) {this->capacity = ca;}
};
bool isValid(Room& room);
void checkName(Room& room);
void checkIdentifier(Room& room);
void checkCapacity(Room& room);


#endif //TICTACTOE10_ROOM_H