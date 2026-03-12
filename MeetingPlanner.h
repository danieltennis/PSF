//
// Created by danie on 2/26/2026.
//

#ifndef PSF_MEETINGPLANNER_H
#define PSF_MEETINGPLANNER_H
#include <string>
#include <vector>
#include "Room.h"
#include "Meeting.h"
#include "Participation.h"
#include <string>
using namespace std;

using namespace std;

class MeetingPlanner {
private:

   vector<Room> rooms;
   vector<Meeting> meetings;
   vector<Participation> participations;


public:
   void addRoom(const string& name,const string& id, int capacity);

   Room findRoom(const string &id);

   void addMeeting(const string& label, const string& id,Room room,const string& date);
   void addParticipation(const string& meeting, const string& user);
   bool isConsistent()const;

   void Write_Output(const string& filename)const;
   void printAll() const;



};


#endif //PSF_MEETINGPLANNER_H