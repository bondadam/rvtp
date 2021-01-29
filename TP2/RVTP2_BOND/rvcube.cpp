#include "rvcube.h"

RVCube::RVCube()
    :RVBody()
{
    //Je définis ici les shaders à utiliser dans RVPyraid
    m_VSFileName = ":/shaders/VS_simple.vsh";
    m_FSFileName = ":/shaders/FS_simple.fsh";

}

void RVCube::draw()
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

void RVCube::initializeBuffer()
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

QMatrix4x4 RVCube::modelMatrix()
{
    QMatrix4x4 model;
    model.translate(-0.5f, -0.5f, -0.5f);
    return RVBody::modelMatrix() * model;
}


void RVCube::initializeVAO(){
    //Initialisation du VAO
    m_program.bind();
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
