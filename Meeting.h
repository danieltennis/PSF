#include <chrono>
#include <string>

#include "Room.h"



#ifndef TICTACTOE10_MEETING_H
#define TICTACTOE10_MEETING_H


class Meeting {
private:
    std::string label;
    std::string identifier;
    Room room;
    std::chrono::year_month_day date;

public:
    Meeting();




    std::string getLabel() const;
    std::string getIdentifier() const;
    Room getRoom() const;
    std::chrono::year_month_day getDate() const;



    void setLabel(const std::string& a);
    void setIdentifier(const std::string& t);

};


#endif //TICTACTOE10_MEETING_H