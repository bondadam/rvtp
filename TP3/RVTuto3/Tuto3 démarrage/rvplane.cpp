/*!
  \file rvplane.cpp
  \brief Définition de la classe RVPlane.
  \author  Leo Donati
  \date    22/01/2021
  \version 21.1


  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/

#include "rvplane.h"

RVPlane::RVPlane(float lenght, float width)
    :RVBody()
{
    m_FSFileName = ":/shaders/FS_plan.fsh";
    m_length = lenght;
    m_width = width;
}

void RVPlane::draw()
{
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (m_wireFrame) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDisable(GL_CULL_FACE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_CULL_FACE);
    }

    m_program.bind();
    m_vao.bind();

    QMatrix4x4 matrix;
    matrix = m_camera->projectionMatrix() * m_camera->viewMatrix() * this->modelMatrix();
    m_program.setUniformValue("u_ModelViewProjectionMatrix", matrix);
    m_program.setUniformValue("u_opacity", m_opacity);
    m_program.setUniformValue("u_color", m_globalColor);

    glDrawArrays(GL_TRIANGLE_FAN, 0, m_numVertices);

    m_vao.release();
    m_program.release();

}

void RVPlane::initializeBuffer()
{
    QVector3D A(-m_length/2, 0, m_width/2);
    QVector3D B(m_length/2, 0, m_width/2);
    QVector3D C(m_length/2, 0, -m_width/2);
    QVector3D D(-m_length/2, 0, -m_width/2);

    QVector3D vertexData[] = {
        A, B, C, D
    };

    //Initialisation et remplissage du Vertex Buffer Object
    m_vbo.bind();
    m_vbo.allocate(vertexData, sizeof (vertexData));
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vbo.release();

    m_numVertices = 4;
    m_numTriangles = 2;
}

