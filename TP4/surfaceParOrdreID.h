#pragma once
#include "strategieSurface.h"

// commande c1

class StrategieParOrdreID : public StrategieSurface {
public:
    void creerSurfaces(const std::vector<Point>& points,
                      const std::vector<Nuage>& nuages,
                      std::vector<Surface>& surfaces) override
    {
        surfaces.clear();
        
        for (const auto& nuage : nuages) {
            // Extraire les points du nuage selon leurs IDs
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
            
            for (int i = 0; i < (int)pointsDuNuage.size() - 1; i++) {
                surfaces.push_back(Surface(pointsDuNuage[i].id, 
                                          pointsDuNuage[i+1].id, 
                                          nuage.texture));
            }
            

            surfaces.push_back(Surface(pointsDuNuage.back().id, 
                                      pointsDuNuage.front().id, 
                                      nuage.texture));
        }
    }
};