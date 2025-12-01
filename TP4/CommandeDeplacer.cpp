#include "CommandeDeplacer.h"

CommandeDeplacer::CommandeDeplacer(std::vector<Point>& points, int id, int nouveauX, int nouveauY)
    : m_points(points),
      m_id(id),
      m_nouveauX(nouveauX),
      m_nouveauY(nouveauY),
      m_premiereExecution(true)
{
}

void CommandeDeplacer::execute()
{
    Point* point = nullptr;
    for (auto& p : m_points) {
        if (p.id == m_id) {
            point = &p;
            break;
        }
    }
    
    if (!point) return;

    if (m_premiereExecution)
    {
        m_ancienX = point->x;
        m_ancienY = point->y;
        m_premiereExecution = false;
    }

    point->x = m_nouveauX;
    point->y = m_nouveauY;
}

void CommandeDeplacer::cancel()
{
   
    Point* point = nullptr;
    for (auto& p : m_points) {
        if (p.id == m_id) {
            point = &p;
            break;
        }
    }
    
    if (!point) return;

    point->x = m_ancienX;
    point->y = m_ancienY;
}
