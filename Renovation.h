//
// Created by mohammed on 4/22/26.
//

#ifndef PSF_RENOVATION_H
#define PSF_RENOVATION_H
#include <chrono>


class Renovation {
    std::string roomId;
    std::chrono::year_month_day start;
    std::chrono::year_month_day end;

public:
    Renovation(const std::string& roomId,
               std::chrono::year_month_day start,
               std::chrono::year_month_day end);

    std::string getRoomId() const;
    std::chrono::year_month_day getStart() const;
    std::chrono::year_month_day getEnd() const;
};



#endif //PSF_RENOVATION_H
