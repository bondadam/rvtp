#ifndef RVSPHERE_H
#define RVSPHERE_H

/*!
  \file rvsphere.h
  \brief Déclaration de la classe RVSphere.
  \author  Leo Donati
  \date    22/01/2021
  \version 21.1

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia

  Utilise RVsurface avec l'équation paramétrée utilisant les coordonnées sphériques
*/

#include "rvsurface.h"

class RVSphere : public RVSurface
{
public:
    RVSphere(double radius = 1.0);
    ~RVSphere() override;
    void draw() override;

    double radius() const;
    void setRadius(double radius);

    void setTexture2(QString filename);

protected:
    float x(double s, double t) override;
    float y(double s, double t) override;
    float z(double s, double t) override;

    double m_radius;
    QOpenGLTexture *m_texture2;
};

#endif // RVSPHERE_H
