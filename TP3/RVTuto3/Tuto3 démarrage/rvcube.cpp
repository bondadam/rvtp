/*!
  \file rvcube.cpp
  \brief Définition de la classe RVCube.
  \author  Leo Donati
  \date    22/01/2021
  \version 21.1


  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/

#include "rvcube.h"

RVCube::RVCube()
    :RVBody()
{
    m_VSFileName = ":/shaders/VS_simple.vsh";
}

void RVCube::draw()
{
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
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

    m_program.bind();
    m_vao.bind();

    QMatrix4x4 matrix;
    matrix = m_camera->projectionMatrix() * m_camera->viewMatrix() * this->modelMatrix();
    m_program.setUniformValue("u_ModelViewProjectionMatrix", matrix);
    m_program.setUniformValue("u_color", m_globalColor);
    m_program.setUniformValue("u_opacity", m_opacity);

    for (int i = 0; i<6; i++)
        glDrawArrays(GL_TRIANGLE_FAN, 4*i, 4);

    m_vao.release();
    m_program.release();
}

void RVCube::initializeBuffer()
{
    //Definitions des 8 sommets du cube
    QVector3D A(0, 0, 1);
    QVector3D B(1, 0, 1);
    QVector3D C(1, 1, 1);
    QVector3D D(0, 1, 1);
    QVector3D E(0, 0, 0);
    QVector3D F(1, 0, 0);
    QVector3D G(1, 1, 0);
    QVector3D H(0, 1, 0);

    //Définitions des 6 couleurs primaires
    QVector3D rouge(1, 0, 0);
    QVector3D vert(0, 1, 0);
    QVector3D bleu(0, 0, 1);
    QVector3D cyan(0, 1, 1);
    QVector3D magenta(1, 0, 1);
    QVector3D jaune(1, 1, 0);

    //On prépare le tableau des données
    QVector3D vertexData[] = {
        A, B, C, D, //face avant
        H, G, F, E, //face arriere
        A, D, H, E, //face gauche
        B, F, G, C, //face droite
        D, C, G, H, //face dessus
        A, E, F, B, //face dessous
        rouge, rouge, rouge, rouge,
        cyan, cyan, cyan, cyan,
        vert, vert, vert, vert,
        magenta, magenta, magenta, magenta,
        bleu, bleu, bleu, bleu,
        jaune, jaune, jaune, jaune
    };

    //Lien du VBO avec le contexte de rendu OpenG
    m_vbo.bind();
    //Allocation des données dans le VBO
    m_vbo.allocate(vertexData, sizeof (vertexData));
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //Libération du VBO
    m_vbo.release();

    m_numVertices = 24;
    m_numTriangles = 12;
}

QMatrix4x4 RVCube::modelMatrix()
{
    QMatrix4x4 model;
    model.translate(-0.5f, -0.5f, -0.5f);
    return RVBody::modelMatrix() * model;
}

void RVCube::initializeVAO()
{
    //Initialisation du VAO
    m_vao.bind();
    m_vbo.bind();

    //Définition des attributs
    m_program.setAttributeBuffer("rv_Position", GL_FLOAT, 0, 3);
    m_program.enableAttributeArray("rv_Position");

    m_program.setAttributeBuffer("rv_Color", GL_FLOAT, int(sizeof(QVector3D))*m_numVertices, 3);
    m_program.enableAttributeArray("rv_Color");

    //Libération
    m_vao.release();
    m_program.release();
}

