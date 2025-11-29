#pragma once
#include <vector>
#include "affichage.h"

class StrategieSurface {
public:
    virtual ~StrategieSurface() {}

    virtual void creerSurfaces(const std::vector<Point>& points,
                               std::vector<std::pair<int,int>>& surfaces) = 0;
};