/*!
  \file rvcube.cpp
  \brief Définition de la classe RVCube.
  \author  Leo Donati
  \date    22/01/2021
  \version 21.1

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/

#include "rvdice.h"

RVDice::RVDice()
    :RVBody()
{
    m_VSFileName = ":/shaders/VS_cube_texture.vsh";
    m_FSFileName = ":/shaders/FS_simple_texture.fsh";
}


void RVDice::draw()
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

void RVDice::initializeBuffer()
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
    QVector3D SW3(0, 0.75, 0);
    QVector3D SE3(0.25, 0.75, 0);
    QVector3D NE3(0.25, 1, 0);
    QVector3D NW3(0, 1, 0);

    QVector3D SW1(0, 0.5, 0);
    QVector3D SE1(0.25, 0.5, 0);
    QVector3D NE1(0.25, 0.75, 0);
    QVector3D NW1(0, 0.75, 0);

    QVector3D SW5(0.25, 0.5, 0);
    QVector3D SE5(0.5, 0.5, 0);
    QVector3D NE5(0.5, 0.75, 0);
    QVector3D NW5(0.25, 0.75, 0);

    QVector3D SW6(0.5, 0.5, 0);
    QVector3D SE6(0.75, 0.5, 0);
    QVector3D NE6(0.75, 0.75, 0);
    QVector3D NW6(0.5, 0.75, 0);

    QVector3D SW2(0.75, 0.5, 0);
    QVector3D SE2(1, 0.5, 0);
    QVector3D NE2(1, 0.75, 0);
    QVector3D NW2(0.75, 0.75, 0);

    QVector3D SW4(0, 0.25, 0);
    QVector3D SE4(0.25, 0.25, 0);
    QVector3D NE4(0.25, 0.5, 0);
    QVector3D NW4(0, 0.5, 0);



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
        SW1, SE1, NE1, NW1,
        NE2, NW2, SW2, SE2,
        SE3, NE3, NW3, SW3,
        SW4, SE4, NE4, NW4,
        SW5, SE5, NE5, NW5,
        SW6, SE6, NE6, NW6,
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

QMatrix4x4 RVDice::modelMatrix()
{
    QMatrix4x4 model;
    model.translate(-0.5f, -0.5f, -0.5f);
    return RVBody::modelMatrix() * model;
}

void RVDice::initializeVAO()
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

