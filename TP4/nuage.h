#pragma once
#include <vector>
#include <string>
#include "affichage.h"

class Nuage {
public:
    char texture;
    std::vector<int> ids;  // IDs des points du nuage

    Nuage(char t) : texture(t) {}
};
