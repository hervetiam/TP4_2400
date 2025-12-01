#pragma once
#include <vector>
#include <string>
#include "ElementAbs.h"
#include <algorithm>


class Nuage : public ElementAbs {
public:
    char texture;
    std::vector<int> ids;  
    std::vector<char> nuagesEnfants;
    Nuage(char t) : texture(t) {}


    std::vector<int> obtenirIdsPoints() const override {
        return ids; 
    }

    char obtenirTexture() const override {
        return texture;
    }

    bool estComposite() const override {
        return true; 
    }

    
    void ajouterElement(const ElementAbs* element) {
        std::vector<int> nouveauxIds = element->obtenirIdsPoints();
        for (int id : nouveauxIds) {
            
            if (std::find(ids.begin(), ids.end(), id) == ids.end()) {
                ids.push_back(id);
            }
        }

        
        if (element->estComposite()) {
            nuagesEnfants.push_back(element->obtenirTexture());
        }
    }

};
