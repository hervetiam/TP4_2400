#pragma once
#include <vector>
#include <iostream>
#include "affichage.h"
#include "surface.h"

class AffichageOrthese {                                                                                       
public:
    virtual ~AffichageOrthese() {}

    void afficher(const std::vector<Point>& points,
                  const std::vector<Surface>& surfaces)
    {

        std::vector<std::vector<char>> grille(HAUTEUR,
                                              std::vector<char>(LARGEUR, ' '));

        for (const auto& s : surfaces) {
            // Trouver les points par ID, pas par indice
            const Point* p1 = nullptr;
            const Point* p2 = nullptr;
            
            for (const auto& p : points) {
                if (p.id == s.id1) p1 = &p;
                if (p.id == s.id2) p2 = &p;
            }
            
            if (p1 && p2) {
                tracerLigne(grille, p1->x, p1->y, p2->x, p2->y, s.texture);
            }
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