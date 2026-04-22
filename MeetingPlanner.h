#ifndef PSF_MEETINGPLANNER_H
#define PSF_MEETINGPLANNER_H

#include <string>
#include <vector>
#include "Room.h"
#include "Meeting.h"
#include "Participation.h"
#include "Campus.h"
#include "Building.h"
#include "Renovation.h"

class MeetingPlanner {
private:
   std::vector<Room> rooms;
   std::vector<Meeting> meetings;
   std::vector<Participation> participations;
   std::vector<Campus> campuses;
   std::vector<Building> buildings;
   std::vector<Renovation> renovations;

public:

   void addRoom(const std::string& name, const std::string& id, int capacity,
      const std::string& campusId, const std::string& buildingId);
   Room findRoom(const std::string &id) const;


   void addCampus(const std::string& name, const std::string& id);
   Campus findCampus(const std::string& id) const;


   void addBuilding(const std::string& name, const std::string& id, const std::string& campusId);
   Building findBuilding(const std::string& id) const;


   void addMeeting(const std::string &label, const std::string &id, Room room, const std::string &dateStr);
   void addParticipation(const std::string &meetingId, const std::string &user);
   bool isConsistent() const;


   void addRenovation(const std::string& roomId,
                      const std::string& start,
                      const std::string& end);

   void printAll() const;
   void Write_Output(const std::string &filename) const;
};

#endif //PSF_MEETINGPLANNER_H