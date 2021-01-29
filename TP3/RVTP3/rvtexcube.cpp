/*!
  \file rvcube.cpp
  \brief Définition de la classe RVCube.
  \author  Leo Donati
  \date    22/01/2021
  \version 21.1

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/

#include "rvtexcube.h"

RVTexCube::RVTexCube()
    :RVBody()
{
    m_VSFileName = ":/shaders/VS_cube_texture.vsh";
    m_FSFileName = ":/shaders/FS_cube_texture.fsh";
}


void RVTexCube::draw()
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
    m_program.setUniformValue("u_color", m_globalColor);
    m_program.setUniformValue("u_opacity", m_opacity);
    m_program.setUniformValue("texture0", 0);

    for (int i = 0; i<6; i++)
        glDrawArrays(GL_TRIANGLE_FAN, 4*i, 4);

    m_vao.release();
    m_program.release();

    if (m_texture) {
        m_texture->release();
        glDisable(GL_TEXTURE0);
        glDisable(GL_TEXTURE_2D);
    }
}

void RVTexCube::initializeBuffer()
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

    //Définitions des 4 coins de la texture
    QVector3D SW(0, 0, 0);
    QVector3D SE(1, 0, 0);
    QVector3D NE(1, 1, 0);
    QVector3D NW(0, 1, 0);

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
        jaune, jaune, jaune, jaune,
        SW, SE, NE, NW,
        NE, NW, SW, SE,
        SE, NE, NW, SW,
        SW, SE, NE, NW,
        SW, SE, NE, NW,
        SW, SE, NE, NW,
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

QMatrix4x4 RVTexCube::modelMatrix()
{
    QMatrix4x4 model;
    model.translate(-0.5f, -0.5f, -0.5f);
    return RVBody::modelMatrix() * model;
}

void RVTexCube::initializeVAO()
{
    //Initialisation du VAO
    m_vao.bind();
    m_vbo.bind();

    //Définition des attributs
    m_program.setAttributeBuffer("rv_Position", GL_FLOAT, 0, 3);
    m_program.enableAttributeArray("rv_Position");

    m_program.setAttributeBuffer("rv_Color", GL_FLOAT, sizeof(QVector3D)*24, 3);
    m_program.enableAttributeArray("rv_Color");

    m_program.setAttributeBuffer("rv_TexCoord", GL_FLOAT,  sizeof(QVector3D)*24*2, 3);
    m_program.enableAttributeArray("rv_TexCoord");

    //Libération
    m_vao.release();
    m_program.release();
}

