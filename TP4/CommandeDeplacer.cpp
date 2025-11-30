#include "CommandeDeplacer.h"

CommandeDeplacer::CommandeDeplacer(vector<Point>& points, int id, int nouveauX, int nouveauY)
    : m_points(points),
    m_id(id),
    m_nouveauX(nouveauX),
    m_nouveauY(nouveauY),
    m_premiereExecution(true)
{
};

void CommandeDeplacer::execute()
{
    if (m_id < 0 || m_id >= (int)m_points.size()) return;

    if (m_premiereExecution)
    {
        m_ancienX = m_points[m_id].x;
        m_ancienY = m_points[m_id].y;
    }
    
    m_points[m_id].x = m_nouveauX;
    m_points[m_id].y = m_nouveauY;
}

void CommandeDeplacer::cancel()
{
    if (m_id < 0 || m_id >= (int)m_points.size()) {
        return;
    }

    m_points[m_id].x = m_ancienX;
    m_points[m_id].y = m_ancienY;

}