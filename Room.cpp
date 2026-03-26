#include <iostream>
#include "Room.h"
using namespace std;

void checkName(Room& room) {
   if (room.getName().empty()) {
      cout << "De kamer heeft geen naam!" << endl;
   }
}

void checkIdentifier(Room& room) {
   if (room.getIdentifier().empty()) {
      cout << "De kamer heeft geen identifier!" << endl;
   }
}

void checkCapacity(Room& room) {
   if (room.getCapacity() <= 0) {
      cout << "De kamer heeft geen capaciteit!" << endl;
   }
}

void checkCampus(Room& room) {
   if (room.getCampus().empty()) {
      cout << "De kamer heeft geen campus!" << endl;
   }
}

void checkBuilding(Room& room) {
   if (room.getBuilding().empty()) {
      cout << "De kamer heeft geen gebouw!" << endl;
   }
}

bool isValid(Room& room) {
   return !room.getName().empty() &&
          !room.getIdentifier().empty() &&
          room.getCapacity() > 0 &&
          !room.getCampus().empty() &&
          !room.getBuilding().empty();
}