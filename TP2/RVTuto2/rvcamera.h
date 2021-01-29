#ifndef RVCAMERA_H
#define RVCAMERA_H

#include <QMatrix4x4>
#include <QVector3D>

class RVCamera
{
public:
    RVCamera();
    virtual ~RVCamera();

    QMatrix4x4 viewMatrix();
    QMatrix4x4 projectionMatrix();

    QVector3D position() const;
    void setPosition(const QVector3D &position);

    QVector3D target() const;
    void setTarget(const QVector3D &target);

    QVector3D up() const;
    void setUp(const QVector3D &up);

    float fov() const;
    void setFov(float fov);
    float aspect() const;
    void setAspect(float aspect);
    float zMin() const;
    void setZMin(float zMin);
    float zMax() const;
    void setZMax(float zMax);
protected:
    QVector3D m_position;
    QVector3D m_target;
    QVector3D m_up;
    float m_fov;
    float m_aspect;
    float m_zMin;
    float m_zMax;
};

#endif // RVCAMERA_H
