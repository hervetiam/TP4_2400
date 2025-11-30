#include "affichage.h"
#include "nuage.h"
#include "surface.h"
#include "surfaceParOrdreID.h"
#include "surfaceParOrdreDistanceMinimale.h"
#include "affichageOrtheseParTexture.h"
#include "affichageOrtheseParID.h"
#include "CommandeDeplacer.h"
#include "CommandeFusionner.h"
#include "CommandeSupprimer.h"
#include "Invoker.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

void fusionnerPoints(vector<Point>& points,
                     vector<Nuage>& nuages,
                     vector<char>& texturesNuages,
                     int& prochainNuage)
{
    if (prochainNuage >= (int)texturesNuages.size()) {
        cout << "Plus de textures disponibles.\n";
        return;
    }

    char tex = texturesNuages[prochainNuage++];
    Nuage n(tex);

    cout << "IDs des points à fusionner dans un nuage (ex: 0 2 4): ";
    string ligne;
    getline(cin, ligne);
    istringstream iss(ligne);

    int id;
    while (iss >> id) {
        if (id < 0 || id >= (int)points.size()) continue;

        // On applique la texture au point
        points[id].textures.push_back(tex);

        // On enregistre l'ID dans le nuage
        n.ids.push_back(id);
    }

    nuages.push_back(n);
}



void supprimerPoint(vector<Point>& points)
{
    string ligne;
    int id;

    cout << "ID du point à supprimer: ";
    getline(cin, ligne);

    istringstream iss(ligne);
    if (!(iss >> id)) return;
    if (id < 0 || id >= (int)points.size()) return;

    points.erase(points.begin() + id);

    for (int i = 0; i < (int)points.size(); i++) {
        points[i].id = i;
    }

}


int main(int argc, char* argv[]) {
    string args;
    Invoker invoker;
    // On accepte des points en entrée.
    if (argc > 1) {
        ostringstream oss;
        for (int i = 1; i < argc; ++i) oss << argv[i] << " ";
        args = oss.str();
    } else {
        cout << "Entrez les points au format (x,y) :\n> ";
        getline(cin, args);
    }
    
    // Voici des fonctions utiles pour réaliser le TP. 
    // TODO: Il faudrait les placer dans des classes appropriées.
    vector<Point> pointsInitiaux = creerPoints(args);
    
    // Ce sont différentes textures possibles. Seules les 2 premières sont utilisées dans les scénarios du TP.
    vector<char> texturesNuages = {'o', '#', '$'};

    vector<Point> points = pointsInitiaux;
    vector<Nuage> nuages;
    
    int prochainNuage = 0;
    
    string cmd;
    
    AffichageOrthese* affichage = nullptr;

    StrategieSurface* strategie = nullptr;
    vector<Surface> surfaces;  // CHANGÉ: vector<Surface> au lieu de vector<pair<int,int>>

    // Menu
    while (true) {
        cout << "\nCommandes:\n"
                  << "a  - Afficher les points et les nuages\n"
                  << "o1 - Afficher l'orthèse avec les textures des points\n"
                  << "o2 - Afficher l'orthèse avec les IDs des points\n"
                  << "f  - Fusionner des points dans un nuage (et appliquer texture)\n"
                  << "d  - Deplacer un point (ID)\n"
                  << "s  - Supprimer un point (ID)\n"
                  << "u  - Annuler la dernière commande (undo)\n"
                  << "r  - Réappliquer la dernière commande annulée (redo)\n"
                  << "c1 - Créer les surfaces selon l'ordre des IDs\n"
                  << "c2 - Créer les surfaces selon la distance minimale\n"
                  << "q  - Quitter\n> ";
        getline(std::cin, cmd);

        if (cmd == "q") break;
        else if (cmd == "a") {
            cout << "Liste:\n";
            for (const auto& p : points) {
                cout << p.id << ": (" << p.x << "," << p.y
                     << ") textures:'" << p.textures << "'\n";
            }
        
            cout << "\n";
            for (const auto& n : nuages) {
                cout << "Nuage '" << n.texture << "' contient les points: ";
                for (size_t i = 0; i < n.ids.size(); ++i) {
                    cout << n.ids[i];
                    if (i + 1 < n.ids.size()) cout << ", ";
                }
                cout << "\n";
            }
        }
        
        else if (cmd == "o1") {
            affichage = new AffichageParTexture();
            affichage->afficher(points, surfaces);
            delete affichage;
        }
        
        else if (cmd == "o2") {
            affichage = new AffichageParID();
            affichage->afficher(points, surfaces);
            delete affichage;
        }
        else if (cmd == "f") {
            fusionnerPoints(points, nuages, texturesNuages, prochainNuage);
        }

        else if (cmd == "d") {
            string ligne;
            int id, x, y;

            cout << "ID du point à déplacer: ";
            getline(cin, ligne);
            {
                istringstream iss(ligne);
                if (!(iss >> id)) {
                    cout << "ID invalide.\n";
                    continue;  // Retour au menu
                }
            }

            if (id < 0 || id >= (int)points.size()) {
                cout << "ID hors limites.\n";
                continue;
            }

            cout << "Nouvelle position (x y): ";
            getline(cin, ligne);
            {
                istringstream iss(ligne);
                if (!(iss >> x >> y)) {
                    cout << "Position invalide.\n";
                    continue;
                }
            }


            CommandeAbs* cmd = new  CommandeDeplacer(points , id , x , y);
            invoker.execute(cmd);
        }

        else if (cmd == "u") {
            invoker.undo();
        }

        else if (cmd == "r") {
            invoker.redo();
        }
        
        else if (cmd == "c1") {
            strategie = new StrategieParOrdreID();
            strategie->creerSurfaces(points, nuages, surfaces);
            delete strategie;
        }
        
        else if (cmd == "c2") {
            strategie = new StrategieParDistanceMin();
            strategie->creerSurfaces(points, nuages, surfaces);
            delete strategie;
        }        
        else if (cmd == "s") {
            supprimerPoint(points);
        }

    }

    return 0;
}