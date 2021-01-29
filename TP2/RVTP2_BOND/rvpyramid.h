#ifndef RVPYRAMID_H
#define RVPYRAMID_H

/*!
    \file rvpyramid.h
    \brief Déclaration de la classe RVPyramid.
    \author  Leo Donati
    \date    12/01/2021
    \version 21.1

    Cours de Réalité Virtuelle
    Polytech'Nice Sophia

    Pour faire un exemple de classe quihérite de RVBody

    Tutoriel n°2
  */

#include "rvbody.h"

/*!
 * \class RVPyramid.
 * \brief Un exemple de classe qui hérite de RVBody.
 *
 * Pas très intéressante (4 sommets). Utilisée dans le Tuto n°2
 * Donne un exemple de comment on crée des classes filles de RVBody
*/
class RVPyramid : public RVBody
{
public:
    RVPyramid();                    //!<    Constructeur

    void draw() override;           //!<    Lance le rendu

protected:
    void initializeBuffer() override;   //!<    Prépare les buffers
    void initializeVAO() override;      //!<    Lie le buffer avec les attributs du shader
};

#endif // RVPYRAMID_H
