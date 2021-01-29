/*!
  \file main.cpp
  \brief Tutoriel n°3
  \author  Leo Donati
  \date    22/01/2021
  \version 21.1

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Réalité Virtuelle: Tuto 3");
    w.show();
    return a.exec();
}
