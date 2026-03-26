//
// Created by mohammed on 3/26/26.
//

#include "Campus.h"

Campus::Campus(const std::string& name,
               const std::string& identifier)
    : name(name), identifier(identifier) {}

std::string Campus::getName() const {
    return name;
}

std::string Campus::getIdentifier() const {
    return identifier;
}