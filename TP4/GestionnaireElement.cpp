#include "GestionnaireElement.h"
#include <sstream>
#include <iostream>
#include "nuage.h"
using namespace std;

GestionnaireElements::GestionnaireElements(vector<Point>& points, 
                                           vector<Nuage>& nuages,
                                           vector<char>& texturesNuages,
                                           int& prochainNuage)
    : m_points(points), 
      m_nuages(nuages), 
      m_texturesNuages(texturesNuages),
      m_prochainNuage(prochainNuage)
{
}
void GestionnaireElements::fusionnerPoints()
{
    if (m_prochainNuage >= (int)m_texturesNuages.size()) return;

    char tex = m_texturesNuages[m_prochainNuage++];
    int idNuage = m_points.size() + m_nuages.size();
    Nuage nuage(tex, idNuage);

    string ligne;
    cout << "IDs des points à fusionner dans un nuage (ex: 0 2 4): ";
    getline(cin, ligne);
    istringstream iss(ligne);

    int id;
    while (iss >> id) {

        if (id >= 0 && id < (int)m_points.size()) {
            m_points[id].textures.push_back(tex);
            nuage.ids.push_back(id);
            continue;
        }

        int idPremierNuage = m_points.size();
        if (id >= idPremierNuage && id < idPremierNuage + (int)m_nuages.size()) {

            nuage.enfantsIDs.push_back(id);

            Nuage& enfant = m_nuages[id - idPremierNuage];
            for (int p : enfant.obtenirIdsPoints())
                m_points[p].textures.push_back(tex);

            continue;
        }
    }

    m_nuages.push_back(nuage);
}


void GestionnaireElements::afficherListe() const
{
    cout << "Liste:\n\n";

    for (const auto& p : m_points)
        cout << p.id << ": (" << p.x << "," << p.y << ") textures:'" << p.textures << "'\n";

    for (const auto& n : m_nuages) {
        cout << n.id << ": Nuage '" << n.texture << "' contient les points: ";

        for (int p : n.ids)
            cout << p << " ";

        for (int sub : n.enfantsIDs)
            cout << sub << " ";

        cout << "\n";
    }
}

