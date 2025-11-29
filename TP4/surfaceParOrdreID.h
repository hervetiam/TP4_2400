#pragma once
#include "strategieSurface.h"

// commande c1

class StrategieParOrdreID : public StrategieSurface {
public:
   void creerSurfaces(const std::vector<Point>& points,
                   std::vector<std::pair<int,int>>& surfaces) override
{
    surfaces.clear();
    if (points.size() < 2) return;

    for (int i = 0; i < (int)points.size() - 1; i++) {
        surfaces.push_back({ points[i].id, points[i+1].id });
    }

    surfaces.push_back({ points.back().id, points.front().id });
}

};
