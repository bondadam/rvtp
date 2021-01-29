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

    m_numVertices = 0;
    m_numTriangles = 0;
    m_numIndices = 0;

    m_VSFileName = "NO VS FILE";
    m_FSFileName = "NO FS FILE";
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
    initializeBuffer();		//à écrire dans la classe fille
    initializeVAO();    	//à écrire dans la classe fille
}



void RVBody::initializeShader()
{
    initializeOpenGLFunctions();

    if (m_program.hasOpenGLShaderPrograms())
        m_program.removeAllShaders();
    bool resultat;

    m_program.bind();
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
