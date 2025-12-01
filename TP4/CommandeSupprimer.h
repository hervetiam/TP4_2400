#ifndef COMMANDESUPPRIMER_H
#define COMMANDESUPPRIMER_H
#include "commandeAbs.h"
#include "nuage.h"
#include <vector>

using namespace std;

class CommandeSupprimer : public  CommandeAbs
{
private:
	vector<Point>& m_points;
	int m_id;
	Point m_pointSauvegarde;
	int  m_positionOriginale;

public:

	CommandeSupprimer(vector<Point>& points, int id);
	virtual ~CommandeSupprimer() = default;
	void execute() override;
	void cancel() override;
	
};
#endif