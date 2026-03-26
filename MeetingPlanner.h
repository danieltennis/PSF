
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
#include "Campus.h"
#include "Building.h"


extern std::vector<Campus> campuses;
extern std::vector<Building> buildings;
using namespace std;

using namespace std;

class MeetingPlanner {
private:

   vector<Room> rooms;
   vector<Meeting> meetings;
   vector<Participation> participations;


public:
   Room findRoom(const string &id);

   void addMeeting(const string& label, const string& id,Room room,const string& date);
   void addParticipation(const string& meeting, const string& user);
   bool isConsistent()const;

   void Write_Output(const string& filename)const;
   void printAll() const;


   void addCampus(const std::string& name, const std::string& id);
   void addBuilding(const std::string& name, const std::string& id, const std::string& campusId);
   void addRoom(const std::string& name, const std::string& id, int capacity, const std::string& campusId, const std::string& buildingId);



};


#endif //PSF_MEETINGPLANNER_H
