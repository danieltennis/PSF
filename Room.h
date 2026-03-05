;//
// Created by danie on 2/26/2026.
//

#ifndef TICTACTOE10_ROOM_H
#define TICTACTOE10_ROOM_H
#include <string>
using namespace std;

class Room {
public:
    Room();
    string name;
    string id;
    int capacity;

     Room(const string& name,const string& id, int capacity);
     int getCapacity()const{return capacity;}

};


#endif //TICTACTOE10_ROOM_H