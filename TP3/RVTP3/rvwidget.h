#ifndef RVWIDGET_H
#define RVWIDGET_H
/*!
  \file rvwidget.h
  \brief Déclaration de la classe RVWidget.
  \author  Leo Donati
  \date    22/01/2021
  \version 21.1

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia

  Session 3
*/

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <QTimer>
#include <QPoint>
#include <QMouseEvent>
#include <QKeyEvent>

#include "rvcamera.h"
#include "rvcube.h"
#include "rvtexcube.h"
#include "rvplane.h"
#include "rvsphere.h"
#include "rvtorus.h"
#include "rvdice.h"

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
     * \brief méthode responsable de la définition du viewport
     * \param w : largeur de la fenêtre
     * \param h : hauteur de la fenêtre
     */
    void resizeGL(int w, int h) override;

private slots:
    /*!
     * \brief slot associé au timer. Doit gérer la mise à our des objets puis appeler la méthode update
     * de la classe parent.
     */
    void update();

public slots:
    /*!
     * \brief slot associé au bouton animation de l'IHM. Active ou désacitive l'animation.
     */
    void startAnimation();

    /*!
     * \brief slot associé au QDial de l'IHM. Modifie l'angle de vue de la caméra.
     */
    void changeFov(int);

    /*!
     * \brief slot associé au slider qui contrôle l'opacité du l'bjet
     */
    void changeOpacity(int);

    void changeWireFrame(bool);
    void changeCulling(bool);
    void changeScale(int s);
    void changeSaturation(int s);
    void changeCameraType(bool b);

protected:
    /*!
     * \brief mousePressEvent
     * \param event : QMouseEvent qui donne accès aux informations sur l'événement
     * (typiquement ici la position où le clic a eu lieu) mais aussi sur quel bouton a été pressé).
     *
     * Surcharge de la méthode de QWidget qui est appelée lors d'un clic sur un des boutons de la souris.
     * On l'utilise pour mémoriser la position du curseur qui sera ensuite comparée à celle de mouseMoveEvent
     * qui gèrera le déplacement de l'objet.
     */
    void mousePressEvent(QMouseEvent* event) override;

    /*!
     * \brief mouseMoveEvent
     * \param event : QMouseEvent qui donne accès aux informations sur l'événement
     * (typiquement ici la position où le clic a eu lieu) mais aussi sur quel bouton a été pressé).
     *
     * On utilise la différence entre la position présente du curseur et la position ancienne pour calculer
     * deux angles de rotation de l'objet.
     */
    void mouseMoveEvent(QMouseEvent* event) override;

    void keyPressEvent(QKeyEvent* event) override;

protected:
    RVCamera *m_camera;         //!<    Pointeur sur la caméra à utiliser lors du rendu
    RVBody   *m_body;           //!<    Objet montré dans le widget
    RVBody   *m_plane;          //!<    Plan horizontal
    RVBody   *m_world;          //!<    Sphère terrestre
    RVBody   *m_torus;          //!<    Tore à carreaux
    RVBody   *m_dice;           //!<    Dé
    QTimer* m_timer;            //!<    Timer utilisé lors de l'animation
    float m_angularVelocityX;   //!<    Vitesse angulaire autour de l'axe x
    float m_angularVelocityY;   //!<    Vitesse angulaire autour de l'axe y
    float m_angularVelocityZ;   //!<    Vitesse angulaire autour de l'axe z
    QPoint m_oldPos;            //!<    Position du clic souris (utilisé dans mouseMove)
    bool m_animation;           //!<    Booléen qui dit si l'animation est activée ou pas
};
#endif // RVWIDGET_H
