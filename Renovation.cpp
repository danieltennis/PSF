//
// Created by mohammed on 4/22/26.
//

#include "Renovation.h"


Renovation::Renovation(const std::string& roomId,
                       std::chrono::year_month_day start,
                       std::chrono::year_month_day end)
    : roomId(roomId), start(start), end(end) {}

std::string Renovation::getRoomId() const {
    return roomId;
}

std::chrono::year_month_day Renovation::getStart() const {
    return start;
}

std::chrono::year_month_day Renovation::getEnd() const {
    return end;
}