#include "rvplane.h"

RVPlane::RVPlane(float longueur, float largeur):RVBody()
{

    //Je définis ici les shaders à utiliser dans RVPyraid
    m_VSFileName = ":/shaders/VS_simpler.vsh";
    m_FSFileName = ":/shaders/FS_plan.fsh";


    m_longueur = longueur;
    m_largeur = largeur;
}

RVPlane::RVPlane():RVBody()
{

    //Je définis ici les shaders à utiliser dans RVPyraid
    m_VSFileName = ":/shaders/VS_simpler.vsh";
    m_FSFileName = ":/shaders/FS_plan.fsh";


    m_longueur = 10.0f;
    m_largeur = 10.0;
}



void RVPlane::draw()
{
    glEnable(GL_DEPTH_TEST);
    if (this->culling()){
        glEnable(GL_CULL_FACE);
    } else {
        glDisable(GL_CULL_FACE);
    }
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, this->wireframe() ? GL_LINE : GL_FILL);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    m_program.bind();
    m_vao.bind();

    //Définition de la variable uniforme
    QMatrix4x4 matrix;
    matrix = m_camera->projectionMatrix() * m_camera->viewMatrix() * this->modelMatrix();
    m_program.setUniformValue("u_ModelViewProjectionMatrix", matrix);
    m_program.setUniformValue("u_opacity", this->opacity());
    m_program.setUniformValue("u_color", this->globalColor());

    //Commande de rendu (indexé)
    for(int i = 0; i < 6; i++){
         glDrawArrays(GL_TRIANGLE_FAN, (i*4), 4);
    };

    m_vao.release();
    m_program.release();
}


void RVPlane::initializeBuffer()
{
    //Définition de 4 points
    QVector3D A(-m_longueur/2, 0, -m_largeur/2);
    QVector3D B(-m_longueur/2, 0, m_largeur/2);
    QVector3D C(m_longueur/2, 0, m_largeur/2);
    QVector3D D(m_longueur/2, 0, -m_largeur/2);


    //On prépare le tableau des données
    QVector3D vertexData[] = {
        A, B, C, D
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


