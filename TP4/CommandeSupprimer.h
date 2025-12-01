#ifndef COMMANDESUPPRIMER_H
#define COMMANDESUPPRIMER_H
#include "commandeAbs.h"
#include "affichage.h"
#include "nuage.h"
#include <vector>

using namespace std;

class CommandeSupprimer : public CommandeAbs
{
private:
    vector<Point>& m_points;
    vector<Nuage>& m_nuages;       
    int m_id;
    Point m_pointSauvegarde;
    int  m_positionOriginale;

    vector<vector<int>> m_nuagesSauvegarde;  
public:
    CommandeSupprimer(vector<Point>& points,
                      vector<Nuage>& nuages,
                      int id);

    virtual ~CommandeSupprimer() = default;

    void execute() override;
    void cancel() override;
};

#endif
