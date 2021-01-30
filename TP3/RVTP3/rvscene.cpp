#include "rvscene.h"

RVScene::RVScene()
{

}

void RVScene::setCamera(RVCamera* camera){
    m_camera = camera;
    foreach (RVBody* body, *this) {
           body->setCamera(m_camera);
    }
}
void RVScene::translate(QVector3D vec){
    foreach (RVBody* body, *this) {
           body->translate(vec);
    }

}
void RVScene::rotate(float angle, QVector3D axis){
    foreach (RVBody* body, *this) {
           body->rotate(angle, axis);
    }
}
void RVScene::draw(){
    foreach (RVBody* body, *this) {
           body->draw();
    }
}
