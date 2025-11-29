#pragma once
#include "affichageOrthese.h"

// commande o1

class AffichageParTexture : public AffichageOrthese {
protected:
    void remplirPoints(std::vector<std::vector<char>>& grille,
                       const std::vector<Point>& points) override
    {
        for (const auto& p : points) {

            // Si le point n'a aucune texture on met un '.'
            if (p.textures.empty()) {
                if (p.x >= 0 && p.x < LARGEUR &&
                    p.y >= 0 && p.y < HAUTEUR)
                {
                    grille[p.y][p.x] = '.';
                }
            }
            else {
                // On affiche toutes les textures du point
                int x = p.x;
                for (size_t i = 0; i < p.textures.size() && x + (int)i < LARGEUR; ++i) {
                    if (p.y >= 0 && p.y < HAUTEUR)
                        grille[p.y][x + (int)i] = p.textures[i];
                }
            }
        }
    }
};
