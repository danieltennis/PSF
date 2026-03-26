#ifndef CAMPUS_H
#define CAMPUS_H

#include <string>


class Campus {
private:
    std::string name;
    std::string identifier;

public:
    Campus(const std::string& name,
           const std::string& identifier);

    std::string getName() const;
    std::string getIdentifier() const;
};

#endif