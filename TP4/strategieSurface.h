#pragma once
#include <vector>
#include "affichage.h"
#include "surface.h"
#include "nuage.h"

class StrategieSurface {
public:
    virtual ~StrategieSurface() {}

    virtual void creerSurfaces(const std::vector<Point>& points,
                               const std::vector<Nuage>& nuages,
                               std::vector<Surface>& surfaces) = 0;
};