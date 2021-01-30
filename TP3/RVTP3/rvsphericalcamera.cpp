#include "rvsphericalcamera.h"
#include "QtMath"

RVSphericalCamera::RVSphericalCamera()
{
    m_rho = 10;
    m_phi = 0;
    m_theta = 0;
    this->update_position();
}

void RVSphericalCamera::update_position(){
    float x = m_target.x() + m_rho * qCos(m_phi) * qCos(m_theta);
    float y = m_target.y() + m_rho * qSin(m_phi);
    float z = m_target.z() + m_rho * qCos(m_phi) * qSin(m_theta);
    m_position = QVector3D(x, y, z);
}

float RVSphericalCamera::phi(){
    return m_phi;
}
float RVSphericalCamera::theta(){
    return m_theta;
}
float RVSphericalCamera::rho(){
    return m_rho;
}
void RVSphericalCamera::setPhi(float new_phi){
    if (new_phi > - M_PI_2 && new_phi < M_PI_2){
        m_phi = new_phi;
        update_position();
    }
}
void RVSphericalCamera::setTheta(float new_theta){
    m_theta = new_theta;
    update_position();
}
void RVSphericalCamera::setRho(float new_rho){
    if (new_rho > 0){
        m_rho = new_rho;
        update_position();
    }
}
