#pragma once
#include "affichageOrthese.h"

//commande o2

class AffichageParID : public AffichageOrthese {
protected:
    void remplirPoints(std::vector<std::vector<char>>& grille,
                       const std::vector<Point>& points) override
    {
        for (auto& p : points) {
            if (p.x >= 0 && p.x < LARGEUR && p.y >= 0 && p.y < HAUTEUR)
                grille[p.y][p.x] = '0' + (p.id % 10);
        }
    }
};
