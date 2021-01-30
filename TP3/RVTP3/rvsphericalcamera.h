#ifndef RVSPHERICALCAMERA_H
#define RVSPHERICALCAMERA_H

#include "rvcamera.h"

class RVSphericalCamera : public RVCamera
{
public:
    RVSphericalCamera();
    float phi();
    float theta();
    float rho();
    void setPhi(float new_phi);
    void setTheta(float new_theta);
    void setRho(float new_rho);

protected:
    float m_phi;
    float m_theta;
    float m_rho;
private:
    void update_position();
};

#endif // RVSPHERICALCAMERA_H
