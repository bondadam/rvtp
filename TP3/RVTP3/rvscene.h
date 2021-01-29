#ifndef RVSCENE_H
#define RVSCENE_H

#include <QList<RVBody*>>

class RVScene : public QList<RVBody*>
{
public:
    RVScene();
};

#endif // RVSCENE_H
