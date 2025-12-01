#pragma once
#include <string>
#include <vector>
#include "ElementAbs.h"  

using namespace std;

const int LARGEUR = 30;
const int HAUTEUR = 20;

class Point : public ElementAbs  {
    public:
        int id;       
        int x, y;    
        std::string textures;
    
        Point(int id = 0, int x = 0, int y = 0)
        : id(id), x(x), y(y), textures("") {}
    
        std::vector<int> obtenirIdsPoints() const override {
            return { id }; 
        }

        char obtenirTexture() const override {
            return textures.empty() ? ' ' : textures[0];
        }

        bool estComposite() const override {
            return false; 
        }
};
    


std::vector<Point> creerPoints(const std::string& ligne);
void tracerLigne(std::vector<std::vector<char>>& grille, int x0, int y0, int x1, int y1, char texture);
void imprimerGrille(const std::vector<Point>& points);