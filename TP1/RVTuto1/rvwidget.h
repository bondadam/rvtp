#ifndef RVWIDGET_H
#define RVWIDGET_H
/*!
  \file rvwidget.h
  \brief Déclaration de la classe RVWidget (sans index buffer)
  \author  Leo Donati
  \date    12/01/2021
  \version 21.1

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia

  Tutoriel n°1
*/

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QVector3D>

/*!
 * \brief The RVWidget class est un widget ViewControlleur pour tous nos programmes.
 *
 * Hérite de QOpenGWidget qui s'occupe de préparer le contexte OpenGL
 * et de QOpenGLFunctions qui initialise toutes les fonctions OpenGL nécessaires.
 */
class RVWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    /*!
     * \brief Constructeur de RVWidget
     * \param parent = le widget dans lequel il apparait.
     *
     * Constructeur de la classe RVWidget. Initialise les paramètres.
     */
    RVWidget(QWidget *parent = nullptr);

    /*!
     * \brief Destructeur de RVWidget.
     * Responsable de libérer (avec delete) toute la mémoire allouée dynamiquement avec des new.
     */
    ~RVWidget() override;

    /*!
     * \brief méthode responsable de la préparation du contexte OpenGL.
     * Met en place la caméra, les objets, le timer
     */
    void initializeGL() override;

    /*!
     * \brief méthode responsable du rendu.
     * Efface le buffer d'image et appelle la méthode draw de chaque objet de la scène.
     */
    void paintGL() override;

    /*!
     * \brief initializeBuffer initialise le VertexBuffer
     * Est appelée par initializeGL()
     */
    void resizeGL(int w, int h) override;

protected:
    /*!
     * \brief initializeBuffer initialise le VertexBuffer
     * Est appelée par initializeGL()
     */
    void initializeBuffer();

    /*!
     * \brief initializeShaders compile les programmes de shader
     * Est appelée par initializeGL()
     * Initialise aussi le VAO
     */
    void initializeShaders();

protected:
    QOpenGLBuffer m_vbo;            //!<    vertex buffer object
    QOpenGLShaderProgram m_program; //!<    programmes de shader
    QOpenGLVertexArrayObject m_vao; //!<    vertex array object
};
#endif // RVWIDGET_H
