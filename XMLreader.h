#ifndef PSF_XMLREADER_H
#define PSF_XMLREADER_H

#include <string>
#include <vector>

class XMLreader {
public:
    // Use Case 1.1: lezen van rooms, meetings en participations
    bool readFile(const std::string& filename);

private:
    // Hier verzamelen we alle foutmeldingen
    std::vector<std::string> errors;

    // (optioneel, maar handig)
    void printErrors() const;
};

#endif // PSF_XMLREADER_H