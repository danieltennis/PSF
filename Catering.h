//
// Created by mohammed on 4/23/26.
//

#ifndef PSF_CATERING_H
#define PSF_CATERING_H
#include <string>



class Catering {
private:
    std::string campusId;
    int co2;

public:
    Catering(const std::string& campusId, int co2);

    std::string getCampusId() const;
    int getCO2() const;
};



#endif //PSF_CATERING_H
