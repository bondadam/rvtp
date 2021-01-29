/*!
  \file rvbody.cpp
  \brief Définition de la classe RVBody.
  \author  Leo Donati
  \date    22/01/2021
  \version 21.1


  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/
#include "rvbody.h"

RVBody::RVBody()
    :QOpenGLFunctions(),
      m_vao(), m_program(),
      m_position(), m_orientation()
{
    m_vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_ibo = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

    m_vbo.create();
    m_ibo.create();
    m_vao.create();
    m_program.create();

    //Valeurs par défaut des attributs de la classe
    m_numVertices = 0;
    m_numTriangles = 0;
    m_numIndices = 0;
    m_opacity = 1;
    m_wireFrame = false;
    m_culling = true;
    m_scale = 1;
    m_globalColor = QColor(255, 255, 255);

    //shaders très simples par défaut
    m_VSFileName = ":/shaders/VS_simpler.vsh";
    m_FSFileName = ":/shaders/FS_simple.fsh";
}

RVBody::~RVBody()
{
    if (m_program.hasOpenGLShaderPrograms())
        m_program.removeAllShaders();
    m_vao.destroy();
    m_ibo.destroy();
    m_vbo.destroy();
}

void RVBody::initialize()
{
    initializeShader();
    initializeBuffer();
    initializeVAO();
}

QMatrix4x4 RVBody::modelMatrix()
{
    QMatrix4x4 model;
    model.translate(m_position);
    model.rotate(m_orientation);
    model.scale(m_scale);
    return model;
}

void RVBody::initializeShader()
{
    initializeOpenGLFunctions();

    if (m_program.hasOpenGLShaderPrograms())
        m_program.removeAllShaders();
    bool resultat;

    //Vertex Shader
    resultat = m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, m_VSFileName);
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Vertex shader");
        msg.setText(m_program.log());
        msg.exec();
        exit(EXIT_FAILURE);
    }

    //Fragment Shader
    resultat = m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, m_FSFileName);
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

    //Libération
    m_program.release();
}

void RVBody::initializeVAO()
{
    //Initialisation du VAO
    m_vao.bind();
    m_vbo.bind();
    m_ibo.bind();

    //Définition du seul attribut position (la couleur est uniforme avec le VS_simpler)
    m_program.setAttributeBuffer("rv_Position", GL_FLOAT, 0, 3);
    m_program.enableAttributeArray("rv_Position");

    //Libération
    m_vao.release();
    m_program.release();
}

void RVBody::rotate(float angle, QVector3D axis)
{
    m_orientation =  QQuaternion::fromAxisAndAngle(axis, angle) * m_orientation ;
}

void RVBody::translate(QVector3D position)
{
    m_position += position;
}

void RVBody::setOrientation(float yaw, float pitch, float roll)
{
    m_orientation = QQuaternion::fromEulerAngles(pitch, yaw, roll);
}

//-------------------------- Accesseurs et Mutateurs ---------------------------
//

float RVBody::opacity() const
{
    return m_opacity;
}

void RVBody::setOpacity(float opacity)
{
    m_opacity = opacity;
}

bool RVBody::wireFrame() const
{
    return m_wireFrame;
}

void RVBody::setWireFrame(bool wireFrame)
{
    m_wireFrame = wireFrame;
}

float RVBody::scale() const
{
    return m_scale;
}

void RVBody::setScale(float scale)
{
    m_scale = scale;
}

bool RVBody::culling() const
{
    return m_culling;
}

void RVBody::setCulling(bool culling)
{
    m_culling = culling;
}

QColor RVBody::globalColor() const
{
    return m_globalColor;
}

void RVBody::setGlobalColor(const QColor &globalColor)
{
    m_globalColor = globalColor;
}

int RVBody::numVertices() const
{
    return m_numVertices;
}

int RVBody::numTriangles() const
{
    return m_numTriangles;
}

int RVBody::numIndices() const
{
    return m_numIndices;
}

void RVBody::setFS(const QString &FSFileName)
{
    m_FSFileName = FSFileName;
}

void RVBody::setVS(const QString &VSFileName)
{
    m_VSFileName = VSFileName;
}

RVCamera *RVBody::camera() const
{
    return m_camera;
}

void RVBody::setCamera(RVCamera *camera)
{
    m_camera = camera;
}

QVector3D RVBody::position() const
{
    return m_position;
}

void RVBody::setPosition(const QVector3D &position)
{
    m_position = position;
}


QQuaternion RVBody::orientation() const
{
    return m_orientation;
}

void RVBody::setOrientation(const QQuaternion &orientation)
{
    m_orientation = orientation;
}
//------------------------------------------------------------------------------
