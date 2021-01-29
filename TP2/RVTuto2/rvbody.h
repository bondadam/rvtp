#ifndef RVBODY_H
#define RVBODY_H

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <rvcamera.h>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QMessageBox>

class RVBody : public QOpenGLFunctions
{
public:
    RVBody();
    virtual ~RVBody();

    virtual void draw() = 0;
    virtual QMatrix4x4 modelMatrix();

    void initialize();
    void initializeShader();
    virtual void initializeBuffer() = 0;
    virtual void initializeVAO() = 0;

    void rotate();
    void translate();

    // accesseurs et mutateurs .....

protected:
    QString m_VSFileName;               //! : nom du fichier qui contient le vertex shader
    QString m_FSFileName;               //! : nom du fichier qui contient le fragment shader
    QOpenGLBuffer m_vbo;                //! : vertex buffer qui stocke les sommets du maillage
    QOpenGLBuffer m_ibo;                //! : index buffer (optionnel) qui stocke les index à utiliser pour le rendu
    QOpenGLVertexArrayObject m_vao;     //! : vertex array object (obligatoire)
    QOpenGLShaderProgram m_program;     //! : shader program (obligatoire)

    QVector3D m_position;               //! : position de l'objet dans la scène
    QQuaternion m_orientation;          //! : attitude de l'objet dans la scène

    int m_numVertices;                  //! : nombre de sommets de l'objet (lecture seule)
    int m_numTriangles;                 //! : nombre de triangles de l'objet (lecture seule)
    int m_numIndices;                   //! : nombre d'index (0 si on n'utilise pas l'ibo)

    RVCamera *m_camera;                 //! : pointeur sur la caméra utilisée pour le rendu.
};

#endif // RVBODY_H
