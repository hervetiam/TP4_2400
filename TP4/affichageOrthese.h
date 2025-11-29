#pragma once
#include <vector>
#include <iostream>
#include "affichage.h"

class AffichageOrthese {                                                                                       
public:
    virtual ~AffichageOrthese() {}

    void afficher(const std::vector<Point>& points,
                  const std::vector<std::pair<int,int>>& surfaces)
    {

        std::vector<std::vector<char>> grille(HAUTEUR,
                                              std::vector<char>(LARGEUR, ' '));

        for (auto& s : surfaces) {
            const Point& p1 = points[s.first];
            const Point& p2 = points[s.second];
            tracerLigne(grille, p1.x, p1.y, p2.x, p2.y);
        }

        remplirPoints(grille, points);

        for (int y = HAUTEUR - 1; y >= 0; --y) {
            for (int x = 0; x < LARGEUR; ++x)
                std::cout << grille[y][x];
            std::cout << '\n';
        }
    }

protected:

    virtual void remplirPoints(std::vector<std::vector<char>>& grille,
                               const std::vector<Point>& points) = 0;
};
