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
#include <QDebug>
#include <string>


RVWidget::RVWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLFunctions()
{
    m_angleY = 0;
    m_angleX = 0;
    m_timer = new QTimer();
    m_fov = 45;
    animation_enabled = false;
    m_opacity = 100;
    filter_index = 0;
    m_strength = 0;
}

RVWidget::~RVWidget()
{
    m_vbo.destroy();
    m_vao.destroy();
}

void RVWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.0f, 0.566f, 0.867f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT, GL_FILL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    initializeBuffer();
    initializeShaders();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    //m_timer->start(50);
}

void RVWidget::filterStrengthChanged(int new_strength){
    m_strength = new_strength;
    QOpenGLWidget::update();
}

void RVWidget::filterChanged(int new_index){
    filter_index = new_index;
    QOpenGLWidget::update();
}

void RVWidget::changeOpacity(int new_opacity){
    m_opacity = new_opacity;
    QOpenGLWidget::update();
}

void RVWidget::changeFov(int new_fov){
    m_fov = new_fov;
    QOpenGLWidget::update();
}

void RVWidget::startAnimation(){
    animation_enabled = !animation_enabled;
    animation_enabled ? m_timer->start(24) : m_timer->stop();
}

void RVWidget::update(){
    m_angleY += 5;
    QOpenGLWidget::update();
}

void RVWidget::mousePressEvent(QMouseEvent* event){
    m_oldPos = event->position();
    QOpenGLWidget::update();
}

void RVWidget::mouseMoveEvent(QMouseEvent* event){
    QPointF newPos = event->position();
    float dx = (newPos.x() - m_oldPos.x())/width();
    float dy = (newPos.y() - m_oldPos.y())/height();
    m_angleX += dy*180;
    m_angleY += dx*180;
    m_oldPos = newPos;
    QOpenGLWidget::update();
}

void RVWidget::initializeBuffer()
{
    //Définition de 4 points
    QVector3D A(0, 0, 1);
    QVector3D B(1, 0, 1);
    QVector3D C(1, 1, 1);
    QVector3D D(0, 1, 1);
    QVector3D E(0, 0, 0);
    QVector3D F(1, 0, 0);
    QVector3D G(1, 1, 0);
    QVector3D H(0, 1, 0);

    //Définition de 4 couleurs
    QVector3D rouge(1, 0, 0);
    QVector3D jaune(1, 1, 0);
    QVector3D bleu(0, 0, 1);
    QVector3D cyan(0, 1, 1);
    QVector3D vert(0, 1, 0);
    QVector3D magenta(1, 0, 1);

    //On prépare le tableau des données
    QVector3D vertexData[] = {
        A, B, C, D,
        B, F, G, C,
        C, G, H, D,
        F, E, H, G,
        H, E, A, D,
        E, F, B, A,
        rouge, rouge, rouge, rouge,
        magenta, magenta, magenta, magenta,
        bleu, bleu, bleu, bleu,
        cyan, cyan, cyan, cyan,
        vert, vert, vert, vert,
        jaune, jaune, jaune, jaune
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

    m_program.setAttributeBuffer("rv_Color", GL_FLOAT, sizeof(QVector3D)*4*6, 3);
    m_program.enableAttributeArray("rv_Color");

    //Libération
    m_vao.release();
    m_program.release();
}

void RVWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



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
    proj.perspective(m_fov, width()*1.0f/height(), 0.1f, 100.0f);

    //Définiion de la matrice de vue
    view  = QMatrix4x4();

    //Définition de la matrice de placement
    model.translate(0, 0, -3);
    model.translate(0,0,-2);
    model.rotate(m_angleX, 1, 0, 0);
    model.rotate(m_angleY, 0, 1, 0);
    model.translate(-0.5,-0.5,-0.5);


    //Produit des trois matrices (dans ce sens!)
    matrix = proj * view * model;

    //On passe la matrice au vertex shader pour initialiser sa variable uniforme
    m_program.setUniformValue("u_ModelViewProjectionMatrix", matrix);
    m_program.setUniformValue("u_Opacity", (m_opacity*1.0f)/100);
    QVector3D filter_colors[] = {QVector3D(1,0,0), QVector3D(0,1,0), QVector3D(0,0,1)};
    m_program.setUniformValue("u_filter_color", filter_colors[filter_index]);
    m_program.setUniformValue("u_strength", (m_strength*1.0f)/100);
    m_program.setUniformValue("u_resolution", QVector2D(1.0f*width(), 1.0f*height()));

    m_vao.bind();
    //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    for(int i = 0; i < 6; i++){
         glDrawArrays(GL_TRIANGLE_FAN, (i*4), 4);
    }
    //glDrawArrays(GL_TRIANGLES, 0, 4);
    m_vao.release();
    m_program.release();

}

void RVWidget::resizeGL(int w, int h)
{
    //transformation de viewport
    glViewport(0, 0, w, h);
}




