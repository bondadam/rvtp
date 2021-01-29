/*!
  \file rvwidget.cpp
  \brief Définition de la classe RVWidget.
  \author  Leo Donati
  \date    12/01/2021
  \version 21.1

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia

  Tutoriel n°2
*/
#include "rvwidget.h"
#include <QtDebug>


RVWidget::RVWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLFunctions()
{
    m_angularVelocityX = 0;
    m_angularVelocityY = 3;
    m_angularVelocityZ = 0;
    m_timer = new QTimer(this);
    m_animation = false;

    grabKeyboard();
}

RVWidget::~RVWidget()
{
    delete m_timer;
    delete m_camera;
    delete m_body;
}

void RVWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.0f, 0.566f, 0.867f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glDisable(GL_CULL_FACE);


    for (int i = 0; i < 4; i++){
        RVCamera* new_camera = new RVCamera();
        new_camera->setPosition(QVector3D(0,10,20));
        new_camera->setTarget(QVector3D(0,0,0));
        new_camera->setZMin(10);
        m_cameras[i] = new_camera;
    }

    m_cameras[1]->setIsOrthogonal(true);
    m_cameras[2]->setIsOrthogonal(true);
    m_cameras[3]->setIsOrthogonal(true);

    m_cameras[1]->setPosition(QVector3D(30,0,0));
    m_cameras[2]->setPosition(QVector3D(0,0,30));
    m_cameras[3]->setPosition(QVector3D(0,30,0.01f));

    m_body = new RVCube();

    m_body->setCamera(m_cameras[0]);
    m_body->setPosition(QVector3D(0, 0, 0));
    m_body->initialize();

    m_plane = new RVPlane();
    m_plane->setCamera(m_cameras[0]);
    m_plane->setPosition(QVector3D(0, 0, 0));
    m_plane->setGlobalColor(QVector3D(0,1,0));
    m_plane->initialize();

    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start(10);
}

void RVWidget::keyPressEvent(QKeyEvent* event){
    for (int i = 0; i < 4; i++){
        QVector3D current_position = m_cameras[i]->position();
        if (event->key() == Qt::Key_Left){
            m_cameras[i]->setPosition(QVector3D(current_position.x()-1, current_position.y(), current_position.z()));
        } else if (event->key() == Qt::Key_Right){
            m_cameras[i]->setPosition(QVector3D(current_position.x()+1, current_position.y(), current_position.z()));
        } else if (event->key() == Qt::Key_Down){
             m_cameras[i]->setPosition(QVector3D(current_position.x(), current_position.y()-1, current_position.z()));
        } else if (event->key() == Qt::Key_Up){
            m_cameras[i]->setPosition(QVector3D(current_position.x(), current_position.y()+1, current_position.z()));
        }
    }
}

void RVWidget::changeOpacity(int new_opacity){
    //m_body->setOpacity(new_opacity*1.0f/100);
    m_plane->setOpacity(new_opacity*0.01f);
}

void RVWidget::changeScale(int new_scale){
    m_body->setScale(0.01f * new_scale);
}

void RVWidget::changeSaturation(int new_saturation){
    m_body->setGlobalColor(QVector3D(0.01f * new_saturation, 0.01f * new_saturation, 0.01f * new_saturation));
}


void RVWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            m_camera = m_cameras[i*2+j];
            m_plane->setCamera(m_camera);
            m_body->setCamera(m_camera);
            glViewport(i*(width()/2), j*(height()/2), width()/2, height()/2);
            //m_plane->draw();
            for (float i = -7.5f; i < 7.5f; i+= 1.5){
                for (float j = -7.5f; j < 7.5f; j+= 1.5){
                    m_body->setPosition(QVector3D(i,0,j));
                    m_body->draw();
                }
            }
            m_plane->draw();
        }
    }
}

void RVWidget::changeOrthogonal(bool new_value){
    m_cameras[0]->setIsOrthogonal(new_value);
}

void RVWidget::changeWireframe(bool new_value){
    m_body->setWireframe(new_value);
}

void RVWidget::changeCulling(bool new_value){
    m_body->setCulling(new_value);
}

void RVWidget::resizeGL(int w, int h)
{
    //Pour tenir compte du changement de format du widget
    float aspect = float(w)/h;
    for (int i = 0; i < 4; i++){
        m_cameras[i]->setAspect(aspect);
    }
    //transformation de viewport
    glViewport(0,0,w,h);
}

void RVWidget::update()
{
    if (m_animation) {
        float angularVelocity = 3.0f;
        m_body->rotate(angularVelocity, QVector3D(0, 1, 0));
    }
    QOpenGLWidget::update();
}

void RVWidget::startAnimation()
{
    m_animation = ! m_animation;
    this->update();
}

void RVWidget::changeFov(int newFov)
{
    for (int i = 0; i < 4; i++){
        m_cameras[i]->setFov(newFov);
    }
    this->update();
}

void RVWidget::mousePressEvent(QMouseEvent *event)
{
    m_oldPos = event->pos();
}

void RVWidget::mouseMoveEvent(QMouseEvent *event)
{
    float dx = float(event->position().x() - m_oldPos.x()) / width();
    float dy = float(event->position().y() - m_oldPos.y()) / height();
    float angleX = 180 * dy;
    float angleY = 180 * dx;
    m_body->rotate(angleX, QVector3D(1, 0, 0));
    m_body->rotate(angleY, QVector3D(0, 1, 0));
    m_oldPos = event->pos();

    QOpenGLWidget::update();
}

