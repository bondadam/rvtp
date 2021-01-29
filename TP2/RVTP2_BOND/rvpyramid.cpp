/*!
  \file rvpyramid.cpp
  \brief Définition de la classe RVPyramid.
  \author  Leo Donati
  \date    12/01/2021
  \version 21.1

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia

  Tutoriel n°2
*/
#include "rvpyramid.h"

RVPyramid::RVPyramid()
    :RVBody()
{
    //Je définis ici les shaders à utiliser dans RVPyraid
    m_VSFileName = ":/shaders/VS_simple.vsh";
    m_FSFileName = ":/shaders/FS_simple.fsh";
}

void RVPyramid::draw()
{
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    m_program.bind();
    m_vao.bind();

    //Définition de la variable uniforme
    QMatrix4x4 matrix;
    matrix = m_camera->projectionMatrix() * m_camera->viewMatrix() * this->modelMatrix();
    m_program.setUniformValue("u_ModelViewProjectionMatrix", matrix);

    //Commande de rendu (indexé)
    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, nullptr);

    m_vao.release();
    m_program.release();
}

void RVPyramid::initializeBuffer()
{
    //Définition de 4 points
    QVector3D A(0, 0, 1);
    QVector3D B(0.85f, 0, -0.5f);
    QVector3D C(-0.85f, 0, -0.5f);
    QVector3D D(0, 1, 0);

    //Définition de 4 couleurs
    QVector3D rouge(1, 0, 0);
    QVector3D vert(0, 1, 0);
    QVector3D bleu(0, 0, 1);
    QVector3D blanc(1, 1, 1);

    //Initialisation du Vertex Buffer Object ---------------------------------
    //On prépare le tableau des données
    QVector3D vertexData[] = {
        A, B, C, D,
        rouge, vert, bleu, blanc
    };

    //Lien du VBO avec le contexte de rendu OpenG
    m_vbo.bind();
    //Allocation des données dans le VBO
    m_vbo.allocate(vertexData, sizeof (vertexData));
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //Libération du VBO
    m_vbo.release();


    //Initialisation de l'Index Buffer Object -------------------------------
    uint indexData[] = {
        0, 1, 3,
        0, 3, 2,
        0, 2, 1,
        1, 2, 3
    };

    //Lien du VBO avec le contexte de rendu OpenG
    m_ibo.bind();
    //Allocation des données dans le VBO
    m_ibo.allocate(indexData, sizeof (indexData));
    m_ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //Libération du VBO
    m_ibo.release();

    m_numVertices = 4;
    m_numTriangles = 4;
    m_numIndices = 12;
}

void RVPyramid::initializeVAO()
{
    //Initialisation du Vertex Array Object
    m_program.bind();
    m_vao.bind();
    m_vbo.bind();
    m_ibo.bind();

    //Définition des attributs
    m_program.setAttributeBuffer("rv_Position", GL_FLOAT, 0, 3);
    m_program.enableAttributeArray("rv_Position");

    m_program.setAttributeBuffer("rv_Color", GL_FLOAT, sizeof(QVector3D)*4, 3);
    m_program.enableAttributeArray("rv_Color");

    //Libération
    m_vao.release();
    m_program.release();
}
