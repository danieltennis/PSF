#include "Campus.h"

Campus::Campus()
    : name(""), identifier("") {}

Campus::Campus(const std::string& name, const std::string& identifier)
    : name(name), identifier(identifier) {}

std::string Campus::getName() const { return name; }
std::string Campus::getIdentifier() const { return identifier; }

void Campus::setName(const std::string& n) { name = n; }
void Campus::setIdentifier(const std::string& id) { identifier = id; }