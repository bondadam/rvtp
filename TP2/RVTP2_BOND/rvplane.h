#ifndef RVPLANE_H
#define RVPLANE_H

#include "rvbody.h"

class RVPlane : public RVBody
{
public:
    RVPlane();
    RVPlane(float longueur, float largeur);
    void draw() override;

protected:
    void initializeBuffer() override;

    float m_longueur;
    float m_largeur;
};

#endif // RVPLANE_H
