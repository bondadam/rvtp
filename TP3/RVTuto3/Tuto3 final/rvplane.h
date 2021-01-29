#ifndef RVPLANE_H
#define RVPLANE_H

/*!
  \file rvplane.h
  \brief Déclaration de la classe RVPlane.
  \author  Leo Donati
  \date    22/01/2021
  \version 21.1

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia

  Définit un plan par 4 points
*/

#include "rvbody.h"

/*!
 * \class RVPlane
 * \brief The RVPlane class représente un plan horizontal (au départ) défini par 4 points.
 *
 * Le plan par défaut est horizontal et centré en (0, 0, 0).
 * Il utilise une version simplifié du vertex shader (VS_simpler) dans le quel le VBO contient seulement
 * les coordonnées des points (ici 4 points) et pas leur couleur.
 * Utilise la couleur globale de RVBody
 * Est capable de gérer l'opacité
 */
class RVPlane : public RVBody
{
public:
    /*!
     * \brief constructeur de RVPlane
     * \param length : longueur du plan (mesurée le lond de l'axe x)
     * \param width : largeur du plan (mesurée le long de l'axe z)
     * Le centre du plan est en (0, 0, 0)
     */
    RVPlane(float length = 10.0f, float width = 10.0f);

    /*!
    * \brief dessine le plan en utilisant la couleur m_globalColor
    */
    void draw() override;

    /*!
     * \brief initialise le buffer de sommets avec 4 sommets
     */
    void initializeBuffer() override;

protected:
    float m_length;     //!< longueur du plan (le long de l'axe des x)
    float m_width;      //!< largeur du plan (le long de l'axe des z)
};

#endif // RVPLANE_H
