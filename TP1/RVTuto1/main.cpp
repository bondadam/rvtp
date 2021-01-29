/*!
  \file main.cpp
  \brief Tutoriel n°1
  \author  Leo Donati
  \date    12/01/2021
  \version 21.1

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/
#include "rvwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RVWidget w;
    w.setWindowTitle("Réalité Virtuelle: Tuto1");
    w.show();
    return a.exec();
}
