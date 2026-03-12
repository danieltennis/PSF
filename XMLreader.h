#ifndef PSF_XMLREADER_H
#define PSF_XMLREADER_H

#include <string>
#include <vector>

class MeetingPlanner;

class XMLreader {
public:

    bool readFile(const std::string& filename, MeetingPlanner& planner);


private:
    std::vector<std::string> errors;

    void printErrors() const;
};

#endif // PSF_XMLREADER_H