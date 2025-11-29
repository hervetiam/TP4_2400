#pragma once
#include "strategieSurface.h"
#include <cmath>

 //commande c2
class StrategieParDistanceMin : public StrategieSurface {
public:

    double distanceMin(const Point& a, const Point& b)
    {
        int dx = a.x - b.x;
        int dy = a.y - b.y;
        return dx*dx + dy*dy;
    }

    void creerSurfaces(const std::vector<Point>& points,
                       std::vector<std::pair<int,int>>& surfaces) override
    {
        surfaces.clear();
        if (points.size() < 2) return;

        std::vector<bool> visite(points.size(), false);
        int courant = 0;
        visite[courant] = true;

        int first = 0;          // point de départ
        int last  = 0;          // point suivant

        for (int k = 0; k < (int)points.size() - 1; k++) {

            int prochain = -1;
            double meilleure = 0;

            for (int i = 0; i < (int)points.size(); i++) {
                if (visite[i]) continue;

                double d = distanceMin(points[courant], points[i]);

                if (prochain == -1 || d < meilleure) {
                    prochain = i;
                    meilleure = d;
                }
            }

            surfaces.push_back({points[courant].id, points[prochain].id});

            visite[prochain] = true;
            courant = prochain;
            last = prochain;
        }

        surfaces.push_back({points[last].id, points[first].id});
    }
};
