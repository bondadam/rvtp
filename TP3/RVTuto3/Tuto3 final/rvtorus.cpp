/*!
  \file rvtorus.cpp
  \brief Définition de la classe RVTorus.
  \author  Leo Donati
  \date    22/01/2021
  \version 21.1

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/

#include "rvtorus.h"

RVTorus::RVTorus(double R1, double R2)
    :RVSurface()
{
    m_smallRadius = R1;
    m_bigRadius = R2;
    m_minS = - M_PI;
    m_maxS =  M_PI;
    m_minT = - M_PI;
    m_maxT =  M_PI;
}


float RVTorus::x(double s, double t)
{
    return float((m_bigRadius + m_smallRadius * qCos(t)) * qCos(s));
}

float RVTorus::y(double s, double t)
{
    return float(m_smallRadius * qSin(t));
}

float RVTorus::z(double s, double t)
{
    return float((m_bigRadius + m_smallRadius * qCos(t)) * qSin(s));
}

double RVTorus::bigRadius() const
{
    return m_bigRadius;
}

void RVTorus::setBigRadius(double bigRadius)
{
    m_bigRadius = bigRadius;
}

double RVTorus::smallRadius() const
{
    return m_smallRadius;
}

void RVTorus::setSmallRadius(double smallRadius)
{
    m_smallRadius = smallRadius;
}
