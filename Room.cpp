//
// Created by danie on 2/26/2026.
//

#include <string>
#include <iostream>
#include "Room.h"
using namespace std;


void checkName(Room& room)
{
   if (room.getName().empty())
   {
      cout << "De kamer heeft geen naam!" << endl;
   }
}

void checkIdentifier(Room& room)
{
   if (room.getIdentifier().empty())
   {
      cout << "De kamer heeft geen identifier!" << endl;
   }
}

void checkCapacity(Room& room)
{
   if (room.getCapacity() <= 0)
   {
      cout << "De kamer heeft geen capaciteit!" << endl;
   }
}

//Algemene checker voor alles in 1 keer//
bool isValid(Room& room)
{
   return !room.getName().empty() && !room.getIdentifier().empty() && room.getCapacity() > 0;
}