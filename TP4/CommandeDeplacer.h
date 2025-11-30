#ifndef COMMANDEDEPLACER_H
#define COMMANDEDEPLACER_H
#include "commandeAbs.h"
#include "nuage.h"
#include <vector>

using namespace std;

class CommandeDeplacer : public CommandeAbs
{
private:
	vector<Point>& m_points;
	int m_id;
	int m_ancienX, m_ancienY; //position pour undo
	int m_nouveauX, m_nouveauY; //position pour execute
	bool m_premiereExecution;
public:

	CommandeDeplacer(vector<Point>& points , int id , int nouveauX , int nouveauY);

	virtual ~CommandeDeplacer() = default;
	void execute() override;
	void cancel() override;
};
#endif