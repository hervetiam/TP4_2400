#ifndef ELEMENTABS_H
#define ELEMENTABS_H

#include <vector>

class ElementAbs {
public:
    ElementAbs() = default;
    virtual ~ElementAbs() = default;

   
    virtual std::vector<int> obtenirIdsPoints() const = 0;

   
    virtual char obtenirTexture() const = 0;

    
    virtual bool estComposite() const = 0;
};

#endif