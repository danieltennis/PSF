#ifndef PSF_XMLREADER_H
#define PSF_XMLREADER_H

#include <string>
#include <vector>

// forward declaration
class MeetingPlanner;

class XMLreader {
public:
    // Leest het XML-bestand en vult de MeetingPlanner
    // return true = alles ok
    // return false = fatale fout (terminate)
    bool readFile(const std::string& filename, MeetingPlanner& planner);

private:
    // Verzamelt alle niet-fatale fouten tijdens het lezen
    std::vector<std::string> errors;

    void printErrors() const;
};

#endif // PSF_XMLREADER_H