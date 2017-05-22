#include "scene.h"

Scene::Scene(Qt3DCore::QEntity *sceneRoot, QPushButton *AddElementBox, QCheckBox *START_BUTTON, QCheckBox *Preset1)
       : rootEntity(sceneRoot),
         AddElementBoxT(AddElementBox),
         START(START_BUTTON),
         Preset1T(Preset1)
{    
    //lineEditsT[0] = lineEdits[0];
    //lineEditsT[1] = lineEdits[1];
    //lineEditsT[2] = lineEdits[2];
//QString temp11 = lineEditsListT.at(0);
    //(&lineEditsT)->text().isEmpty();

    //(**lineEdits).setText("4");

}

Scene::~Scene(){
    if(V_Fireworks.size() > 0){
        for(list<Firework*>::iterator iter=V_Fireworks.begin(); iter != V_Fireworks.end(); iter++){
            delete (*iter);
            iter = V_Fireworks.erase(iter);
            qDebug() << V_Fireworks.size();
        }
    }
    delete AddElementBoxT;
    delete START;
}

void Scene::DefPosX(const QString &newValue){
    DefX = newValue;
}

void Scene::DefPosY(const QString &newValue){
    DefY = newValue;
}

void Scene::DefPosZ(const QString &newValue){
    DefZ = newValue;
}

void Scene::MaxParticles(const QString &newValue){
    maxP = newValue;
}

void Scene::AddFireworks(Qt3DCore::QEntity *rootEntity, int i){
    for(int j = 0; j < i; j++){
    V_Fireworks.push_back(new Firework(rootEntity, Preset1T));
    }
}

void Scene::AddBOOM(Qt3DCore::QEntity *rootEntity, QVector3D pos, int i){
    for(int j = 0; j < i; j++){
        V_Fireworks.push_back(new Firework(rootEntity, pos, Preset1T));
    }
}

void Scene::AddFirework(){
    if(maxP != NULL){
        if(V_Fireworks.size()*20 < maxP.toUInt()){
            AddFireworks(rootEntity, 1);}
    }
    else if(V_Fireworks.size()*20 < 900){
        AddFireworks(rootEntity, 1);}
}

void Scene::AddFireworkDefPos(){
    if(DefX != NULL && DefY != NULL && DefZ != NULL)
        if(V_Fireworks.size()*20 < 900){
            iter = 64;
            V_Fireworks.push_back(new Firework(rootEntity, QVector3D(DefX.toInt(), DefY.toInt(), DefZ.toInt()), Preset1T, false));}
}

void Scene::AUTO_MODE(){
  if(AddElementBoxT->text() == "ON"){
    AddElementBoxT->setStyleSheet("background-color: green");
    //if(V_Fireworks.size() < maxP.toInt()){
        AddFirework();
    //}
  }
  else{
      AddElementBoxT->setStyleSheet("background-color: red");
  }
}

void Scene::BOOM(Firework *i){
    if(V_Fireworks.size() > 0){
        if((i)->ReturnZeroVelocity() && (i)->CheckIfDead() == false){
            AddBOOM(rootEntity, (i)->ReturnPosition(), 20);
        }
        if((i)->ReturnZeroVelocity() && (i)->CheckIfDead() == true && Preset1T->checkState() == Qt::Checked && i->ReturnphaseB() == false){
            if(iter-- >= 0)
                AddBOOM(rootEntity, (i)->ReturnPosition(), 20);
            usleep(100);
        }
    }
}

void Scene::update(){
    if(START->checkState() == Qt::Checked){
        //qDebug() << (lineEditsT[0]);

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
