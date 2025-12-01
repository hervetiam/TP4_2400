#include "CommandeSupprimer.h"
#include <algorithm>

CommandeSupprimer::CommandeSupprimer(std::vector<Point>& points,
                                     std::vector<Nuage>& nuages,
                                     int id)
    : m_points(points), m_nuages(nuages), m_id(id)
{
}

void CommandeSupprimer::execute()
{
    if (m_id < 0 || m_id >= (int)m_points.size()) return;

    m_pointSauvegarde = m_points[m_id];
    m_positionOriginale = m_id;

    m_nuagesSauvegarde.clear();
    for (auto& n : m_nuages)
        m_nuagesSauvegarde.push_back(n.ids);

    m_points.erase(m_points.begin() + m_id);

    for (int i = 0; i < (int)m_points.size(); i++)
        m_points[i].id = i;

    for (auto& n : m_nuages) {
        for (auto& pointId : n.ids) {
            if (pointId > m_id) {
                pointId--; 
            }
        }
   
        n.ids.erase(
            std::remove(n.ids.begin(), n.ids.end(), m_id),
            n.ids.end()
        );
    }
}

void CommandeSupprimer::cancel()
{
    
    m_points.insert(m_points.begin() + m_positionOriginale, m_pointSauvegarde);

    
    for (int i = 0; i < (int)m_points.size(); i++)
        m_points[i].id = i;

    
    for (int i = 0; i < (int)m_nuages.size(); i++)
        m_nuages[i].ids = m_nuagesSauvegarde[i];
}