#ifndef RVCAMERA_H
#define RVCAMERA_H

/*!
  \file rvcamera.h
  \brief Déclaration de la classe RVCamera.
  \author  Leo Donati
  \date    22/01/2021
  \version 21.1


  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/

#include <QMatrix4x4>
#include <QVector3D>

/*!
 * \class RVCamera
 * \brief Classe qui représente l'observateur de la scène 3D
 * \details : cette classe encapsule en fait deux matrices :
 *  - la matrice view : qui permet de placer l'observateur et de préciser le point qui est visé
 *  - la matrice projection qui représente la projection de 2D vers 3D
 * \author  Leo Donati
 * \date    2019-2020
 * \version 1.1
*/
class RVCamera
{
public:
    /*!
     * \brief constructeur de la classe RVCamera
     *
     * Donne des valeurs par défaut aux variables membres :
     * - la caméra est en (0, 0, 0), regarde vers les z négatifs et le haut est (0, 1, 0)
     * - l'ouverture focale est de 40 degrés
     * - la projection est perspective
     * - l'aspect de l'image est 4/3
     * - la profondeur du volume de vue est [0.1 , 100]
     */
    RVCamera();

    /*!
     * \brief renvoie la matrice de vue.
     * \return une instance de QMatrix4x4 qui permet de passer du repère de la scène au repère de la vue.
     */
    QMatrix4x4 viewMatrix();

    /*!
     * \brief renvoie la matrice de projection
     * \return une instance de QMatric4x4 qui permet de passer du repère de vue au repère normalisé de projection
     */
    QMatrix4x4 projectionMatrix();

    /*!
     * \brief renvoie la position du point focal de la caméra.
     * \return position de la caméra.
     */
    QVector3D position() const;

    /*!
     * \brief fixe la position de la caméra.
     * \param position : la position de la caméra dans le repère de la scène.
     */
    void setPosition(const QVector3D &position);

    /*!
     * \brief renvoie la position du point au centre de l'objectif de la caméra.
     * \return position de la cible.
     */
    QVector3D target() const;

    /*!
     * \brief fixe la position de la cible.
     * \param target : la position de la cible dans le repère de la scène.
     */
    void setTarget(const QVector3D &target);

    /*!
     * \brief renvoie le vecteur qui donne la direction du "haut" dans l'image.
     * \return un QVector3D.
     */
    QVector3D up() const;

    /*!
     * \brief fixe la direction du "haut" dans l'image.
     * \param un QVector3D unitaire.
     */
    void setUp(const QVector3D &up);

    /*!
     * \brief renvoie la distance du plan de fenétrage avant
     * \return un réel positif
     */
    float zMin() const;

    /*!
     * \brief fixe la distance du plan de fenétrage avant
     * \param un réel positif
     */
    void setZMin(float zMin);

    /*!
     * \brief renvoie la distance du plan de fenétrage arrière
     * \return un réel positif
     */
    float zMax() const;

    /*!
     * \brief fixe la distance du plan de fenétrage arrière
     * \param un réel positif
     */
    void setZMax(float zMax);

    /*!
     * \brief renvoie l'ouverture focale de la caméra (en degrés) dans la direction verticale
     * \return un angle en degrés
     */
    float fov() const;

    /*!
     * \brief fixe l'ouverture focale de la caméra (en degrés) dans la direction verticale
     * \param un angle en degrés (entre 0° et 180° non compris)
     */
    void setFov(float fov);

    /*!
     * \brief renvoie le rapport largeur/hauteur de la pellicule de la caméra
     * \return un réel strictement positif (>1 pour une vue paysage, <1 pour une vue portrait)
     */
    float aspect() const;

    /*!
     * \brief fixe l'aspect de l'image (rapport largeur/hauteur)
     * \param un réel strictement positif qui correspond au rapport du widget utilisé pour le rendu
     */
    void setAspect(float aspect);

    /*!
     * \brief indique s'il s'agit d'une projection orthogonale (true) ou perspective (false)
     * \return un booléen
     */
    bool isOrthogonal() const;

    /*!
     * \brief permet de changer le type de projection utilisé par la caméra
     * \param true pour avoir une projection orthogonale, fase pour avoir une projection perspective
     */
    void setIsOrthogonal(bool isOrthogonal);

protected:
    QVector3D m_position;   //!< la position (centre focale) de la camera - (0, 0, 0) par défaut.
    QVector3D m_target;     //!< la position de la cible de la camera - (0, 0, -1) par défaut.
    QVector3D m_up;         //!< la direction "haut" dans l'image - (0, 1, 0) par défaut.
    float m_zMin;           //!< distance du plan de fenetrage avant (near clipping plane)
    float m_zMax;           //!< distance du plan de fenetrage arrière (far clipping plane)
    float m_fov;            //!< ouverture focale (en degrés) dans la direction verticale
    float m_aspect;          //!< format de l'image (rapport largeur/hauteur)
    bool m_isOrthogonal;     //!> indique si la projection est orthogonale ou perspective (false par défaut)
};

#endif // RVCAMERA_H
