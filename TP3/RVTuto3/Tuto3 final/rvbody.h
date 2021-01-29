#ifndef RVBODY_H
#define RVBODY_H

/*!
  \file rvbody.h
  \brief Déclaration de la classe RVBody.
  \author  Leo Donati
  \date    22/01/2021
  \version 21.1

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/

#include <QMessageBox>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QVector3D>
#include <QMatrix4x4>
#include <QColor>
#include <QOpenGLTexture>

#include "rvcamera.h"

/*!
 * \class   RVBody.
 * \brief   Classe abstraite, base de tous les objets OpenGL.
 * \details La classe RVBody est une classe abstraite qui représente un objet OpenGL avec :
 * - un vertex buffer
 * - un vertex array object
 * - des programmes de shader (stockés dans des fichiers en ressource)
 * Cet objet a une position dans la scène donnée par un vecteur position et un quaternion orientation.
 * Ensemble ils définissent la matrice model
 *
 * Toute classe fille doit obligatoirement implémenter ;
 * - void initializeBuffer()
 * - void initializeVAO()
 * - void draw()
 *
 * La version 2 intègre la possibilité d'avoir des coordonnées textures dans le VBO.
 * On définit ainsi un struct RVVertex qui encapsule position et coordonnée texture
 * AInsi qu'une variable membre de type QOpenGLTexture avex son accesseur.
 *
*/
class RVBody : public QOpenGLFunctions
{
public:
    /*!
     * \brief Constructeur
     *
     * Constructeur de la classe RVBody.
     * Doit appeler la méthode initialize
     */
    RVBody();

    /*!
     * \brief Destructeur
     *
     * Déstructeur de la classe RVBody
     */
    virtual ~RVBody();

    /*!
     * \brief The RVVertex struct
     *
     * Structure utilisée pour replir le VBO:
     * - position est un QVector3D
     * - texCoord est un QVector2D
     */
    struct RVVertex {
        QVector3D position;         //!< position du sommet
        QVector2D texCoord;         //!< coordonnées texture

        RVVertex(QVector3D pos = QVector3D(), QVector2D tex = QVector2D())
        {
            position = pos;
            texCoord = tex;
        }
    };

    /*!
     * \brief méthode virtuelle pure à surcharger qui lance le rendu de l'objet.
     *
     * Doit obligatoirement :
     * - lier le shader.
     * - lier le vao.
     * - renseigner les variables uniformes des shaders (en utilisant éventuellement la cmaera).
     * - lancer la commande de rendu glDrawArray ou glDrawElement.
     */
    virtual void draw() = 0;

    /*!
     * \brief méhode qui initialise l'objet 3D en appellant :
     * - initializeShader
     * - initializeBuffer
     * - initializeVAO
     * Normalement doit être appelée manuellement après la construction de l'objet et après
     * avoir informé tous les paramètres
     */
    void initialize();

    /*!
     * \brief renvoie la matrice Model qui permet de passer du repère du modèle vers le repère de la scène.
     *
     * Utilise les variables position et orientation.
     * \return un QMatrix4x4.
     */
    virtual QMatrix4x4 modelMatrix();

    /*!
     * \brief méthode virtuelle pure à surcharger qui initialise les buffers.
     *
     * Doit obligatoirement remplir le vertex buffer.
     */
    virtual void initializeBuffer() = 0;

    /*!
    * \brief Utilise les programmes de shader vs et fs (en ressource) pour initialiser le
    *  programme de shader.
    *
    * Utilise les fichiers dontles noms sont stockés dans les varaibles membres
    * - m_VSFileName pour le vertex shader
    * - m_FSFileName pour le fragment shader
    * Génère des messages d'erreur et interromp la compilation si les fichiers ne sont pas trouvés ou si leur compilation échoue.
    *
    */
    void initializeShader();

    /*!
     * \brief Méthode virtuelle ; fait le lien entre le vertex Buffer et le shader.
     *
     * Doit être appelée après avoir défini le vertex shader et après avoir compilés les programmes de shader.
     * C'est ici que les variables de type "attribute" des shaders sont liés aux zones du vertex buffer.
     * Normalement c'est la méthode publique initialize() qui se charge des trois étapes. Elle même peut être
     * appelée dans le constructeur de la classe fille.
     * Par défaut cette méthode lie seulement l'attribut "rv_Position" à la position 0 du VB.
     * Si cela convient on n'a pas besoin de re-implémenter cette méthode (si en revanche il y a des couleurs ou
     * des coordonnées textures dans le VB il faut la re-écrire.
     */
    virtual void initializeVAO();

    /*!
     * \brief setTexture définit la texture à coller sur l'objet
     * \param textureFilename est un QString
     */
    void setTexture(QString textureFilename, bool mirrored = true);

public:  // accesseurs et mutateurs
    /*!
     * \brief : instance de RVCamera utilisée par l'objet.
     * \return un pointeur sur l'instance de RVCamera utilisée par l'objet.
     */
    RVCamera *camera() const;

    /*!
     * \brief : permet de modifier la RVCamera utilisée par l'objet.
     * \param camera    : pointeur sur l'instance de RVCamera que doit utiliser l'objet pour le rendu.
     */
    void setCamera(RVCamera *camera);

    /*!
     * \brief : position du centre de gravité de l'objet.
     * \return un vecteur qui donne les coordonnées du centre de gravité de l'objet.
     */
    QVector3D position() const;

    /*!
     * \brief : pour placer le centre de gravité de l'objet à un endroit précis.
     * \param QVector3D représentant, dans le repère de la scène, les coordonnées du centre de gravité de l'objet.
     */
    void setPosition(const QVector3D &position);

    /*!
     * \brief : pour déplacer l'objet d'un vecteur donné
     * \param position est un QVector3D qui est ajouté à la position courante pour donner la nouvelle position.
     */
    void translate(QVector3D position);

    /*!
     * \brief : renvoie le quaternion unitaire qui donne l'orientation de l'objet.
     * \return QQuaternion unitaire utilisé pour représenter l'orientation de l'objet dans l'espace
     */
    QQuaternion orientation() const;

    /*!
     * \brief : pour fixer l'orientation de l'objet.
     * \param un QQuaternion unitaire qui représente la rotation autour de son centre de gravité.
     */
    void setOrientation(const QQuaternion &orientation);

    /*!
     * \brief : pour modifier l'orientation de l'objet en lui appliquant une rotation qui s'ajoute à la rotation existante.
     * \param angle     angle de la rotation.
     * \param axis      vecteru unitaire qui représente l'axe de la rotation.
     */
    void rotate(float angle, QVector3D axis);

    /*!
     * \brief : pour fixer l'orientation de l'objet en lui passant des angles d'Euler
     * \param yaw       lacet : changement de cap = rotation autour de l'axe vertical (y)
     * \param pitch     tangage : rotation autour de l'axe transversal (x)
     * \param roll      roulis : rotation autour de l'axe longitudinal (z)
     */
    void setOrientation(float yaw, float pitch, float roll);

    float opacity() const;
    void setOpacity(float opacity);

    bool wireFrame() const;
    void setWireFrame(bool wireFrame);

    float scale() const;
    void setScale(float scale);

    bool culling() const;
    void setCulling(bool culling);

    QColor globalColor() const;
    void setGlobalColor(const QColor &globalColor);

    /*!
     * \brief donne le nombre de sommets du maillage
     * \return nombre de sommets
     */
    int numVertices() const;

    /*!
     * \brief donne le nombre de triangles du maillage
     * \return nombre de triangles
     */
    int numTriangles() const;

    /*!
     * \brief donne le nombre d'indices du maillage
     * \return nombre d'indices (0 si il n'y a pas de ibo)
     */
    int numIndices() const;

    void setVS(const QString &VSFileName);
    void setFS(const QString &FSFileName);

protected:
    QString m_VSFileName;               //!< : nom du fichier qui contient le vertex shader
    QString m_FSFileName;               //!< : nom du fichier qui contient le fragment shader
    QOpenGLBuffer m_vbo;                //!< : vertex buffer qui stocke les sommets du maillage
    QOpenGLBuffer m_ibo;                //!< : index buffer (optionnel) qui stocke les index à utiliser pour le rendu
    QOpenGLVertexArrayObject m_vao;     //!< : vertex array object (obligatoire)
    QOpenGLShaderProgram m_program;     //!< : shader program (obligatoire)

    QVector3D m_position;               //!< : position de l'objet dans la scène
    QQuaternion m_orientation;          //!< : attitude de l'objet dans la scène

    int m_numVertices;                  //!< : nombre de sommets de l'objet (lecture seule)
    int m_numTriangles;                 //!< : nombre de triangles de l'objet (lecture seule)
    int m_numIndices;                   //!< : nombre d'index (0 si on n'utilise pas l'ibo)

    float m_opacity;                    //!< : valeur de l'opacité (1 par défaut)
    bool m_wireFrame;                   //!< : indique si le rendu se fait en mode filaire (false par défaut)
    bool m_culling;                     //!< : indique si le backface culling est activé (true par défaut)
    float m_scale;                      //!< : facteur de grossissement à appliquer à l'objet (1 par défaut)
    QColor m_globalColor;               //!< : couleur globale de l'objet

    RVCamera *m_camera;                 //!< : pointeur sur la caméra utilisée pour le rendu.
    QOpenGLTexture *m_texture;          //!< : pointeur sur la texture OpenGL
};

#endif // RVBODY_H
