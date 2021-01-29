/*!
  \file rvsurface.cpp
  \brief Définition de la classe RVSurface.
  \author  Leo Donati
  \date    22/01/2021
  \version 21.1

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/

#include "rvsurface.h"

RVSurface::RVSurface()
    :RVBody()
{
    m_minS = 0;
    m_maxS = 1;
    m_minT = 0;
    m_maxT = 1;
    m_numSegS = 25;
    m_numSegT = 25;
}

void RVSurface::draw()
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
        m_texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
        //Liaison de la texture
        m_texture->bind();
    }

    m_program.bind();
    m_vao.bind();

    QMatrix4x4 matrix;
    matrix = m_camera->projectionMatrix() * m_camera->viewMatrix() * this->modelMatrix();
    m_program.setUniformValue("u_ModelViewProjectionMatrix", matrix);
    m_program.setUniformValue("u_opacity", m_opacity);
    m_program.setUniformValue("u_color", m_globalColor);
    if (m_texture)
        m_program.setUniformValue("texture0", 0);

    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, nullptr);

    m_vao.release();
    m_program.release();

    if (m_texture) {
        m_texture->release();
        glDisable(GL_TEXTURE0);
        glDisable(GL_TEXTURE_2D);
    }
}

void RVSurface::initializeBuffer()
{
    m_numVertices = (m_numSegS + 1) * (m_numSegT + 1);
    m_numTriangles = 2 * m_numSegS * m_numSegT;
    m_numIndices = 3 * m_numTriangles;

    RVVertex * vertexData = new RVVertex [m_numVertices];
    uint* indexData = new uint[m_numIndices];
    double t = m_minT;
    double s = m_minS;
    double deltaT = (m_maxT - m_minT)/m_numSegT;
    double deltaS = (m_maxS - m_minS)/m_numSegS;
    uint cptPoint = 0;
    uint cptIndex = 0;
    for (int i = 0; i <= m_numSegT; i++, t += deltaT) {
        s = m_minS;
        for (int j = 0; j <= m_numSegS; j++, s += deltaS, cptPoint++) {
            vertexData[cptPoint].position = pos(s,t);
            vertexData[cptPoint].texCoord = QVector2D(j/float(m_numSegS),i/float(m_numSegT));
            if ((i < m_numSegT) && (j < m_numSegS)) {
                indexData[cptIndex++] = cptPoint;
                indexData[cptIndex++] = cptPoint + uint(m_numSegS) + 1;
                indexData[cptIndex++] = cptPoint + uint(m_numSegS) + 2;
                indexData[cptIndex++] = cptPoint;
                indexData[cptIndex++] = cptPoint + uint(m_numSegS) + 2;
                indexData[cptIndex++] = cptPoint + 1;
            }
        }
    }

    //Initialisation et remplissage du Vertex Buffer Object
    m_vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(vertexData, m_numVertices*int(sizeof (RVVertex)));
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vbo.release();

    //Initialisation et remplissage de l'Index Buffer Object
    m_ibo = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_ibo.create();
    m_ibo.bind();
    m_ibo.allocate(indexData, m_numIndices*int(sizeof (uint)));
    m_ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_ibo.release();
}


