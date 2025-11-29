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
                       const std::vector<Nuage>& nuages,
                       std::vector<Surface>& surfaces) override
    {
        surfaces.clear();
        
        for (const auto& nuage : nuages) {
    
            std::vector<Point> pointsDuNuage;
            for (int id : nuage.ids) {
                for (const auto& p : points) {
                    if (p.id == id) {
                        pointsDuNuage.push_back(p);
                        break;
                    }
                }
            }
            
            if (pointsDuNuage.size() < 2) continue;

            std::vector<bool> visite(pointsDuNuage.size(), false);
            int courant = 0;
            visite[courant] = true;

            int first = 0;
            int last  = 0;

            for (int k = 0; k < (int)pointsDuNuage.size() - 1; k++) {

                int prochain = -1;
                double meilleure = 0;

                for (int i = 0; i < (int)pointsDuNuage.size(); i++) {
                    if (visite[i]) continue;

                    double d = distanceMin(pointsDuNuage[courant], pointsDuNuage[i]);

                    if (prochain == -1 || d < meilleure) {
                        prochain = i;
                        meilleure = d;
                    }
                }

                surfaces.push_back(Surface(pointsDuNuage[courant].id, 
                                          pointsDuNuage[prochain].id, 
                                          nuage.texture));

                visite[prochain] = true;
                courant = prochain;
                last = prochain;
            }

            surfaces.push_back(Surface(pointsDuNuage[last].id, 
                                      pointsDuNuage[first].id, 
                                      nuage.texture));
        }
    }
};