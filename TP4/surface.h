#pragma once

class Surface {
public:
    int id1;      // ID du premier point
    int id2;      // ID du deuxième point
    char texture; 
    
    Surface(int id1, int id2, char t) : id1(id1), id2(id2), texture(t) {}
};