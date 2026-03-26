#ifndef BUILDING_H
#define BUILDING_H

#include <string>
using namespace std;

class Building {
private:
    string name;
    string identifier;
    string campusIdentifier;

public:
    Building() = default;
    Building(const string& n, const string& id, const string& campus)
        : name(n), identifier(id), campusIdentifier(campus) {}

    string getName() const { return name; }
    string getIdentifier() const { return identifier; }
    string getCampusIdentifier() const { return campusIdentifier; }

    void setName(const string& n) { name = n; }
    void setIdentifier(const string& id) { identifier = id; }
    void setCampusIdentifier(const string& campus) { campusIdentifier = campus; }
};

#endif