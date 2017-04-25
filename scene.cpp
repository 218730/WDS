#include "scene.h"

Scene::Scene(Qt3DCore::QEntity *sceneRoot, QPushButton *AddElementBox, QCheckBox *START_BUTTON)
       : rootEntity(sceneRoot),
         AddElementBoxT(AddElementBox),
         START(START_BUTTON)
{

}

Scene::~Scene(){
    if(V_Fireworks.size() > 0){
        for(list<Firework*>::iterator iter=V_Fireworks.begin(); iter != V_Fireworks.end(); iter++){
            delete (*iter);
            iter = V_Fireworks.erase(iter);
            qDebug() << V_Fireworks.size();
        }
    }
}

void Scene::AddFireworks(Qt3DCore::QEntity *rootEntity, int i){
    for(int j = 0; j < i; j++){
    V_Fireworks.push_back(new Firework(rootEntity));
    }
}

void Scene::AddBOOM(Qt3DCore::QEntity *rootEntity, QVector3D pos, int i){
    for(int j = 0; j < i; j++){
        V_Fireworks.push_back(new Firework(rootEntity, pos));
    }
}

void Scene::AddFirework(){
    if(V_Fireworks.size()*25 < 900)
    AddFireworks(rootEntity, 1);
}

void Scene::AUTO_MODE(){
  if(AddElementBoxT->text() == "AUTO_MODE IS ON"){
    if(V_Fireworks.size() < 900){
        AddFirework();
    }
  }
}

void Scene::BOOM(Firework *i){
    if(V_Fireworks.size() > 0)
        if((i)->ReturnZeroVelocity() && (i)->CheckIfDead() == false){
            AddBOOM(rootEntity, (i)->ReturnPosition(), 20);
        }
}

void Scene::update(){
    if(START->checkState() == Qt::Checked){
        AUTO_MODE();

        if(V_Fireworks.size() > 0){
            for(list<Firework*>::iterator iter=V_Fireworks.begin(); iter != V_Fireworks.end(); iter++){
                (*iter)->update();
                BOOM(*iter);

                if(((*iter)->ReturnZeroVelocity() && !(*iter)->CheckIfDead() && (*iter)->CanIDeleteRoot()) ||
                    ((*iter)->ReturnLifespan() <= 0 && (*iter)->CanIDelete())){
                    delete (*iter);
                    iter = V_Fireworks.erase(iter);
                    qDebug() << V_Fireworks.size();
                }
            }
        }
    }
}
