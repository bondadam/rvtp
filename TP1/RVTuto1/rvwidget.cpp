/*!
  \file rvwidget.cpp
  \brief Définition de la classe RVWidget.
  \author  Leo Donati
  \date    12/01/2021
  \version 21.1

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia

  Tutoriel n°1
*/
#include "rvwidget.h"
#include <QMessageBox>

RVWidget::RVWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLFunctions()
{
}

RVWidget::~RVWidget()
{
    m_vbo.destroy();
    m_vao.destroy();
}

void RVWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    initializeBuffer();
    initializeShaders();
}

void RVWidget::initializeBuffer()
{
    //Définition de 4 points
    QVector3D A(-1, 0, 0);
    QVector3D B(+1, 0, 0);
    QVector3D C(+1, 1, 0);
    QVector3D D(-1, 1, -1);

    //Définition de 4 couleurs
    QVector3D rouge(1, 0, 0);
    QVector3D noir(0, 0, 0);
    QVector3D bleu(0, 0, 1);
    QVector3D blanc(1, 1, 1);

    //On prépare le tableau des données
    QVector3D vertexData[] = {
        A, B, C, D,
        rouge, noir, bleu, blanc
    };

    //Initialisation du Vertex Buffer Object
    m_vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    //Création du VBO
    m_vbo.create();
    //Lien du VBO avec le contexte de rendu OpenG
    m_vbo.bind();
    //Allocation des données dans le VBO
    m_vbo.allocate(vertexData, sizeof (vertexData));
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //Libération du VBO
    m_vbo.release();
}

void RVWidget::initializeShaders()
{
    bool resultat;
    m_program.create();
    m_program.bind();

    //Vertex Shader
    resultat = m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/VS_simple.vsh");
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Vertex shader");
        msg.setText(m_program.log());
        msg.exec();
        exit(EXIT_FAILURE);
    }

    //Fragment Shader
    resultat = m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/FS_simple.fsh");
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Fragment shader");
        msg.setText(m_program.log());
        msg.exec();
        exit(EXIT_FAILURE);
    }

    //Link
    resultat = m_program.link();
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Link du shader program");
        msg.setText(m_program.log());
        msg.exec();
        exit(EXIT_FAILURE);
    }

    //Initialisation du VAO
    m_vao.create();
    m_vao.bind();
    m_vbo.bind();

    //Définition des attributs
    m_program.setAttributeBuffer("rv_Position", GL_FLOAT, 0, 3);
    m_program.enableAttributeArray("rv_Position");

    m_program.setAttributeBuffer("rv_Color", GL_FLOAT, sizeof(QVector3D)*4, 3);
    m_program.enableAttributeArray("rv_Color");

    //Libération
    m_vao.release();
    m_program.release();
}

void RVWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    Lignes de code déplacées dans initializeGL()
//
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
//    //glDisable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
//    glFrontFace(GL_CCW);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    m_program.bind();

//    Lignes de code déplacées dans initializeShader() pour définir le VAO
//
//    m_vbo.bind()
//
//    m_program.setAttributeBuffer("rv_Position", GL_FLOAT, 0, 3);
//    m_program.enableAttributeArray("rv_Position");
//    m_program.setAttributeBuffer("rv_Color", GL_FLOAT, sizeof(QVector3D)*4, 3);
//    m_program.enableAttributeArray("rv_Color");

    QMatrix4x4 model, proj, view, matrix;

    //Définition de la matrice de projetcion
    proj.perspective(45, 1.33f, 0.1f, 100.0f);

    //Définiion de la matrice de vue
    view  = QMatrix4x4();

    //Définition de la matrice de placement
    model.translate(0, 0, -3);

    //Produit des trois matrices (dans ce sens!)
    matrix = proj * view * model;

    //On passe la matrice au vertex shader pour initialiser sa variable uniforme
    m_program.setUniformValue("u_ModelViewProjectionMatrix", matrix);

    m_vao.bind();
    //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    //glDrawArrays(GL_TRIANGLES, 0, 4);
    m_vao.release();
    m_program.release();

}

void RVWidget::resizeGL(int w, int h)
{
    //transformation de viewport
    glViewport(0, 0, w, h);
}




