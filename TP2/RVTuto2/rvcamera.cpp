#include "rvcamera.h"

RVCamera::RVCamera()
{
    m_position = QVector3D(0, 0, 0);
    m_target = QVector3D(0, 0, -1);
    m_up = QVector3D(0, 1, 0);
    m_fov  = 40;
    m_aspect = 1.33f;
    m_zMax = 100;
    m_zMin  = 0.1f;
}

QMatrix4x4 RVCamera::viewMatrix()
{
    QMatrix4x4 view;
    view.lookAt(m_position, m_target, m_up);
    return view;
}

QMatrix4x4 RVCamera::projectionMatrix()
{
    QMatrix4x4 proj;
    proj.perspective(m_fov, m_aspect, m_zMin, m_zMax);
    return proj;
}
