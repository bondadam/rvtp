#ifndef RVTORUS_H
#define RVTORUS_H

/*!
  \file rvtorus.h
  \brief Déclaration de la classe RVTorus
  \author  Leo Donati
  \date    22/01/2021
  \version 21.1

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia

  Utilise la classe RVSurface avec une représentation paramètrique du tore
*/

#include "rvsurface.h"

class RVTorus : public RVSurface
{
public:
    RVTorus(double smallRadius = 1.0, double bigRadius = 4.0);

    double bigRadius() const;
    void setBigRadius(double bigRadius);

    double smallRadius() const;
    void setSmallRadius(double smallRadius);

protected:
    float x(double s, double t) override;
    float y(double s, double t) override;
    float z(double s, double t) override;

    double m_bigRadius;
    double m_smallRadius;
};

#endif // RVTORUS_H
