#ifndef CAMPUS_H
#define CAMPUS_H

#include <string>

class Campus {
private:
    std::string name;
    std::string identifier;

public:
    Campus(); // default constructor
    Campus(const std::string& name, const std::string& identifier);

    std::string getName() const;
    std::string getIdentifier() const;

    void setName(const std::string& n);
    void setIdentifier(const std::string& id);
};

#endif