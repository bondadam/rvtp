/*!
  \file rvwidget.cpp
  \brief Définition de la classe RVWidget.
  \author  Leo Donati
  \date    22/01/2021
  \version 21.1

  Tutoriel n°3

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/
#include "rvwidget.h"

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
    makeCurrent();
    delete m_camera;
    delete m_body;
    delete m_plane;
    delete m_world;
    delete m_timer;
    delete m_dice;
    delete m_scene;
}

void RVWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.0f, 0.566f, 0.867f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    float scale = float(this->width())/this->height();

    m_camera = new RVSphericalCamera();
    m_camera->setAspect(scale);
    m_camera->setIsOrthogonal(false);
    //m_camera->setPosition(QVector3D(0, 10, 20));
    m_camera->setTarget(QVector3D(0, 0, 0));
    m_camera->setZMin(1);
    m_camera->setRho(20);

    m_body = new RVTexCube();
    m_body->setCamera(m_camera);
    m_body->setPosition(QVector3D(0, 3, 0));
    m_body->setTexture(":/textures/polytech_logo.jpg", false);
    m_body->setScale(3);
    m_body->initialize();

    m_dice = new RVDice();
    m_dice->setCamera(m_camera);
    m_dice->setPosition(QVector3D(0, 0, 0));
    m_dice->setTexture(":/textures/dice_texture.jpg", false);
    m_dice->setScale(3);
    m_dice->initialize();

    m_plane = new RVPlane();
    m_plane->setScale(3);
    m_plane->setGlobalColor(QColor(0, 220, 0));
    m_plane->setCamera(m_camera);
    m_plane->setTexture(":/textures/wood.png");
    m_plane->initialize();

    m_world = new RVSphere(5.0);
    m_world->setCamera(m_camera);
    m_world->setPosition(QVector3D(0, 3, 20));
    m_world->setTexture(":/textures/2k_earth_daymap.jpg");
    m_world->initialize();
    dynamic_cast<RVSphere*>(m_world)->setTexture2(":/textures/2k_earth_nightmap.jpg");

    m_torus = new RVTorus(1.0, 8.0);
    m_torus->setCamera(m_camera);
    m_torus->setPosition(QVector3D(0, 3, 20));

    m_torus->setFS(":/shaders/FS_texture_damier.fsh");
    m_torus->initialize();

    m_skybox = new RVSkyBox();
    m_skybox->setCamera(m_camera);
    m_skybox->setPosition(QVector3D(0, 0, 0));
    m_skybox->setCulling(false);
    m_skybox->setScale(50);
    m_skybox->setCubeTexture(":/textures/negx.jpg", ":/textures/posx.jpg", ":/textures/posz.jpg", ":/textures/negz.jpg", ":/textures/posy.jpg", ":/textures/negy.jpg");
    m_skybox->initialize();


    m_scene = new RVScene();
    m_scene->append(m_body);
    m_scene->append(m_dice);
    m_scene->append(m_plane);
    m_scene->append(m_world);
    m_scene->append(m_torus);
    m_scene->append(m_skybox);
    m_scene->setCamera(m_camera);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start(10);
}

void RVWidget::switchSkybox(int new_index){
    this->makeCurrent();
    m_skybox->setCubeTexture(":/textures/" + skybox_prefixes[new_index] + "negx.jpg",
                             ":/textures/" + skybox_prefixes[new_index] + "posx.jpg",
                             ":/textures/" + skybox_prefixes[new_index] + "posz.jpg",
                             ":/textures/" + skybox_prefixes[new_index] + "negz.jpg",
                             ":/textures/" + skybox_prefixes[new_index] + "posy.jpg",
                             ":/textures/" + skybox_prefixes[new_index] + "negy.jpg");
    m_skybox->initialize();
}

void RVWidget::addBody(RVBody *obj){
    this->makeCurrent();
    obj->initialize();
    obj->setCamera(m_camera);
    m_scene->append(obj);
}

void RVWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_scene->draw();
}

void RVWidget::resizeGL(int w, int h)
{
    float aspect = float(w)/h;
    m_camera->setAspect(aspect);

    //transformation de viewport
    glViewport(0, 0, w, h);
}

void RVWidget::update()
{
    if (m_animation) {
        m_scene->rotate(m_angularVelocityY, QVector3D(0, 1, 0));
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
    m_camera->setFov(newFov);
    this->update();
}

void RVWidget::changeOpacity(int newOpacity)
{
    //m_body->setOpacity(newOpacity * 0.01f);
    //m_scene->first()->setOpacity(newOpacity * 0.01f);
    //m_world->setOpacity(newOpacity * 0.01f);
    foreach (RVBody* body, m_scene->toList()) {
           body->setOpacity(newOpacity * 0.01f);
    }
}

void RVWidget::changeWireFrame(bool b)
{
    m_world->setWireFrame(b);
    m_body->setWireFrame(b);
    m_dice->setWireFrame(b);
}

void RVWidget::changeCulling(bool b)
{
    foreach (RVBody* body, m_scene->toList()) {
           body->setCulling(b);
    }
}

void RVWidget::changeScale(int s)
{
    m_world->setScale(s*0.01f);
    m_body->setScale(s*0.01f);
    m_dice->setScale(s*0.01f);
}

void RVWidget::changeSaturation(int s)
{
    foreach (RVBody* body, m_scene->toList()) {
           body->setGlobalColor(QColor(s, s, s));
    }
}

void RVWidget::changeCameraType(bool b)
{
    m_camera->setIsOrthogonal(!b);
    m_scene->setCamera(m_camera);
}

void RVWidget::mousePressEvent(QMouseEvent *event)
{
    m_oldPos = event->pos();
}

void RVWidget::mouseMoveEvent(QMouseEvent *event)
{
    /*
    float dx = float(event->position().x() - m_oldPos.x()) / width();
    float dy = float(event->position().y() - m_oldPos.y()) / height();
    float angleX = 180 * dy;
    float angleY = 180 * dx;
    m_scene->rotate(angleX, QVector3D(1, 0, 0));
    m_scene->rotate(angleY, QVector3D(0, 1, 0));
    m_oldPos = event->pos();*/

    float dx = float(event->position().x() - m_oldPos.x()) / width();
    float dy = float(event->position().y() - m_oldPos.y()) / height();
    m_camera->setPhi(m_camera->phi() + dy);
    m_camera->setTheta(m_camera->theta() + dx);
    m_oldPos = event->pos();

    QOpenGLWidget::update();
}

void RVWidget::wheelEvent(QWheelEvent *event){
    /* Ce code marche mais en fait c'est bien plus simple de
     * simplement se servir de rho...
    float dz = event->angleDelta().y()/8;
    float step = 0.01f;
    float diff_x = m_camera->target().x() - m_camera->position().x();
    float diff_y = m_camera->target().y() - m_camera->position().y();
    float diff_z = m_camera->target().z() - m_camera->position().z();
    QVector3D old_position = m_camera->position();
    QVector3D new_position;
    new_position.setX(old_position.x() + (step * diff_x * dz));
    new_position.setY(old_position.y() + (step * diff_y * dz));
    new_position.setZ(old_position.z() + (step * diff_z * dz));
    m_camera->setPosition(new_position);
    QOpenGLWidget::update();
    */
    float dz = -event->angleDelta().y()/8;
    float step = 0.1f;
    m_camera->setRho(m_camera->rho() + step*dz);
    QOpenGLWidget::update();
}

void RVWidget::keyPressEvent(QKeyEvent *event)
{
    QVector3D camPos = m_camera->position();
    float deltaX = 0.2f;
    float deltaY = 0.2f;
    switch (event->key())
    {
    case Qt::Key_Left:
        camPos.setX(camPos.x() - deltaX);
        break;
    case Qt::Key_Right:
        camPos.setX(camPos.x() + deltaX);
        break;
    case Qt::Key_Up:
        camPos.setY(camPos.y() + deltaY);
        break;
    case Qt::Key_Down:
        camPos.setY(camPos.y() - deltaY);
        break;
    }
    m_camera->setPosition(camPos);
}

