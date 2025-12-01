#ifndef NUAGE_H
#define NUAGE_H

#include <vector>
#include "ElementAbs.h"

class Nuage : public ElementAbs {
public:
    int id;
    char texture;
    std::vector<int> ids;
    std::vector<int> enfantsIDs;

    Nuage(char t, int idNuage) : id(idNuage), texture(t) {}

    std::vector<int> obtenirIdsPoints() const override {
        return ids;
    }

    char obtenirTexture() const override {
        return texture;
    }

    bool estComposite() const override {
        return true;
    }
};

#endif
