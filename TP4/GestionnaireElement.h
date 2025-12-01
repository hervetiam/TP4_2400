#ifndef GESTIONNAIREELEMENT_H
#define GESTIONNAIREELEMENT_H

#include "affichage.h"
#include "nuage.h"
#include <vector>
#include <iostream>

using namespace std;

class GestionnaireElements {
private:
    vector<Point>& m_points;
    vector<Nuage>& m_nuages;
    vector<char>& m_texturesNuages;
    int& m_prochainNuage;

public:
    GestionnaireElements(vector<Point>& points, 
                        vector<Nuage>& nuages,
                        vector<char>& texturesNuages,
                        int& prochainNuage);

    void fusionnerPoints();
    void afficherListe() const;
};

#endif