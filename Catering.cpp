//
// Created by mohammed on 4/23/26.
//

#include "Catering.h"



Catering::Catering(const std::string& campusId, int co2)
    : campusId(campusId), co2(co2) {}

std::string Catering::getCampusId() const {
    return campusId;
}

int Catering::getCO2() const {
    return co2;
}