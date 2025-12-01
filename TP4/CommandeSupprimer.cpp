#include "CommandeSupprimer.h"

CommandeSupprimer::CommandeSupprimer(vector<Point>& points, int id) :
	m_points(points),
	m_id(id)
{
};

void CommandeSupprimer::execute()
{
    if (m_id < 0 || m_id >= (int)m_points.size()) return;

    m_pointSauvegarde = m_points[m_id];
    m_positionOriginale = m_id;


    m_points.erase(m_points.begin() + m_id);

    for (int i = 0; i < (int)m_points.size(); i++) {
        m_points[i].id = i;
    }
}


void CommandeSupprimer::cancel()
{
    m_points.insert(m_points.begin() + m_positionOriginale, m_pointSauvegarde);
    for (int i = 0; i < (int)m_points.size(); i++)
        m_points[i].id = i;
}



