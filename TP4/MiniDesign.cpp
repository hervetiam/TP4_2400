#include "affichage.h"
#include "nuage.h"
#include "surface.h"
#include "surfaceParOrdreID.h"
#include "surfaceParOrdreDistanceMinimale.h"
#include "affichageOrtheseParTexture.h"
#include "affichageOrtheseParID.h"
#include "CommandeDeplacer.h"
#include "CommandeSupprimer.h"
#include "Invoker.h"
#include "GestionnaireElement.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    string args;
    Invoker invoker;

    if (argc > 1) {
        ostringstream oss;
        for (int i = 1; i < argc; ++i) oss << argv[i] << " ";
        args = oss.str();
    } else {
        cout << "Entrez les points au format (x,y) :\n> ";
        getline(cin, args);
    }

    vector<Point> pointsInitiaux = creerPoints(args);

    vector<char> texturesNuages = {'o', '#', '$'};

    vector<Point> points = creerPoints(args); 
    vector<Nuage> nuages;

    int prochainNuage = 0;

    GestionnaireElements gestionnaire(points, nuages, texturesNuages, prochainNuage);

    string cmd;

    AffichageOrthese* affichage = nullptr;
    StrategieSurface* strategie = nullptr;

    vector<Surface> surfaces;

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
            gestionnaire.afficherListe();
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
            gestionnaire.fusionnerPoints();
        }

        else if (cmd == "d") {
            string ligne;
            int id, x, y;

            cout << "ID du point à déplacer: ";
            getline(cin, ligne);
            istringstream iss1(ligne);
            if (!(iss1 >> id) || id < 0 || id >= (int)points.size()) {
                cout << "ID invalide.\n";
                continue;
            }

            cout << "Nouvelle position (x y): ";
            getline(cin, ligne);
            istringstream iss2(ligne);
            if (!(iss2 >> x >> y)) {
                cout << "Position invalide.\n";
                continue;
            }

            invoker.execute(new CommandeDeplacer(points, id, x, y));

            if (strategie)
                strategie->creerSurfaces(points, nuages, surfaces);
        }

        else if (cmd == "u") {
            invoker.undo();
            if (strategie)
                strategie->creerSurfaces(points, nuages, surfaces);
        }

        else if (cmd == "r") {
            invoker.redo();
            if (strategie)
                strategie->creerSurfaces(points, nuages, surfaces);
        }

        else if (cmd == "s") {
            string ligne;
            int id;

            cout << "ID du point à supprimer: ";
            getline(cin, ligne);
            istringstream iss(ligne);

            if (!(iss >> id) || id < 0 || id >= (int)points.size()) {
                cout << "ID invalide.\n";
                continue;
            }

            invoker.execute(new CommandeSupprimer(points, nuages, id));

            if (strategie)
                strategie->creerSurfaces(points, nuages, surfaces);
        }

        else if (cmd == "c1") {
            delete strategie;  
            strategie = new StrategieParOrdreID();
            strategie->creerSurfaces(points, nuages, surfaces);
        }

        else if (cmd == "c2") {
            delete strategie;  
            strategie = new StrategieParDistanceMin();
            strategie->creerSurfaces(points, nuages, surfaces);
        }
        else {
            cout << "Commande inconnue.\n";
        }
    }

    delete strategie;
    
    return 0;
}