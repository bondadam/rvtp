/*!
  \file rvsphere.cpp
  \brief Définition de la classe RVSphere.
  \author  Leo Donati
  \date    22/01/2021
  \version 21.1

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/

#include "rvsphere.h"

RVSphere::RVSphere(double r)
    :RVSurface(), m_texture2()
{
    m_radius = r;
    m_minS = 0;
    m_maxS = 2 * M_PI;
    m_minT = - M_PI_2;
    m_maxT = + M_PI_2;
    m_FSFileName = ":/shaders/FS_earth_texture.fsh";
}

RVSphere::~RVSphere()
{
    if (m_texture2) {
        m_texture2->destroy();
        delete m_texture2;
    }
}

void RVSphere::draw()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (m_wireFrame)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (m_culling)
        glEnable(GL_CULL_FACE);
    else
         glDisable(GL_CULL_FACE);


    if (m_texture) {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE0);
        glActiveTexture(GL_TEXTURE0);
        m_texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
        //Liaison de la texture
        m_texture->bind(GL_TEXTURE0);
    }

    if (m_texture2) {
        glEnable(GL_TEXTURE1);
        glActiveTexture(GL_TEXTURE1);
        m_texture2->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        m_texture2->setMagnificationFilter(QOpenGLTexture::Linear);
        //Liaison de la texture
        m_texture2->bind(GL_TEXTURE1);
    }

    m_program.bind();
    m_vao.bind();

    m_time += 0.05f;
    QMatrix4x4 matrix;
    matrix = m_camera->projectionMatrix() * m_camera->viewMatrix() * this->modelMatrix();
    m_program.setUniformValue("u_ModelViewProjectionMatrix", matrix);
    m_program.setUniformValue("u_opacity", m_opacity);
    m_program.setUniformValue("u_daytime", m_time);
    m_program.setUniformValue("u_color", m_globalColor);
    m_program.setUniformValue("texture0", 0);
    m_program.setUniformValue("texture1", 1);

    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, nullptr);

    m_vao.release();
    m_program.release();

    if (m_texture2) {
        m_texture2->release();
        glDisable(GL_TEXTURE1);
    }

    if (m_texture) {
        m_texture->release();
        glActiveTexture(GL_TEXTURE0);
        glDisable(GL_TEXTURE0);
        glDisable(GL_TEXTURE_2D);
    }
}

float RVSphere::x(double s, double t)
{
    return float(m_radius*qCos(t)*qCos(s)) ;
}

float RVSphere::y(double s, double t)
{
    return float(m_radius*qSin(t));
}

float RVSphere::z(double s, double t)
{
    return float(m_radius* qCos(t)*qSin(s));
}

double RVSphere::radius() const
{
    return m_radius;
}

void RVSphere::setRadius(double radius)
{
    m_radius = radius;
}

void RVSphere::setTexture2(QString filename)
{
    if (m_texture2) {
        m_texture2->destroy();
        delete m_texture2;
    }
    m_texture2 = new QOpenGLTexture(QImage(filename).mirrored(true));
}
