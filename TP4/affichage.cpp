#include "affichage.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>

void tracerLigne(vector<vector<char>>& grille, int x0, int y0, int x1, int y1, char texture) {

    int lignes = abs(y1 - y0);

    int dx = x1 - x0;
    int dy = y1 - y0;
    char c;

    // Si la ligne est horizontale 
    if (lignes == 0) {
        // On prend distance horizontale 
        lignes = abs(x1 - x0);
 
        if (texture == 'o') {
            c = '-'; 
        } else if (texture == '#') {
            c = '_'; 
        } else {
            c = '-'; 
        }

        for (int i = 0; i <= lignes; ++i) {
            int x = (x0 < x1) ? x0 + i : x0 - i;
            if (y1 >= 0 && y1 < HAUTEUR && x >= 0 && x < LARGEUR)
                grille[y1][x] = c;
        }
    } else {
       
        if (texture == 'o') {
            
            if (dx == 0) {
                c = '|';  
            } else {
                c = (dx * dy > 0) ? '/' : '\\';  
            }
        } else if (texture == '#') {
            
            c = (dx * dy > 0) ? '/' : '\\';
        } else {
            // Par défaut
            c = (dx * dy > 0) ? '/' : '\\';
        }

        for (int i = 0; i <= lignes; ++i) {
            double t = (double)i / lignes;
            // On fait une interpolation lineaire
            int x = round(x0 + t * (x1 - x0));
            int y = round(y0 + t * (y1 - y0));
            if (x >= 0 && x < LARGEUR && y >= 0 && y < HAUTEUR)
                grille[y][x] = c;
        }
    }
}


void imprimerGrille(const vector<Point>& points) {
    // On crée une grille.
    vector<vector<char>> grille(HAUTEUR, vector<char>(LARGEUR, ' '));

    // On trace une ligne entre le point 0 et 1.
    // TODO : Remplacer par un tracé selon la commande de l'utilisateur (c1 ou c2)
    if (points.size() >= 2) {
        tracerLigne(grille, points[0].x, points[0].y, points[1].x, points[1].y, 'o');
    }

    // On imprime la grille.
    for (int y = HAUTEUR - 1; y >= 0; --y) {
        for (int x = 0; x < LARGEUR; ++x)
            cout << grille[y][x];
        cout << '\n';
    }
}



vector<Point> creerPoints(const string& ligne) {
    vector<Point> points;
    // On crée un flux de lecture (istringstream) à partir de la chaîne ligne.
    istringstream iss(ligne);
    string token;
    int id = 0;
    // On lit chaque point de la ligne (séparé par des espaces).
    while (iss >> token) {
        // On vérifie que le point est entre parenthèses
        if (token.size() >= 3 && token.front() == '(' && token.back() == ')') {
            // On enlève les parenthèses au début et à la fin.
            token = token.substr(1, token.size() - 2);
            // On remplace la virgule par un espace.
            replace(token.begin(), token.end(), ',', ' ');
            // On crée un flux de lecture pour chaque point
            istringstream pair(token);
            int x, y;
            // On ajoute un point {x, y} au vecteur de points.
            if (pair >> x >> y) {
                points.emplace_back(id, x, y);
                id++;
            }
        }
    }
    return points;
}