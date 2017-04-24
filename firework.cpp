#include "firework.h"

Firework::Firework(Qt3DCore::QEntity *rootEntity)
         : m_rootEntity(rootEntity)
{
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni; // guaranteed unbiased

    boomed = false;
    velocity = QVector3D(0, 10, 0);
    acceleration = QVector3D(0, 0, 0);
    gravity = QVector3D(0, -0.2, 0);

    x = uni(rng)%400-200;
    z = uni(rng)%400-200;
    pos = QVector3D(x, -4.0f, z);

    SetAndAdd();
}

Firework::Firework(Qt3DCore::QEntity *rootEntity, QVector3D posboomed)
         : m_rootEntity(rootEntity)
{
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni; // guaranteed unbiased

    boomed = true;
    velocity = QVector3D(uni(rng)%2-1, uni(rng)%2-1, uni(rng)%2-1);
    velocity = velocity * QVector3D(uni(rng)%5+1,uni(rng)%5+1,uni(rng)%5+1);

    acceleration = QVector3D(0, 0, 0);
    pos = posboomed;
    gravity = QVector3D(0, -0.2, 0);
    lifespan = 255;

    SetAndAdd();
}

Firework::~Firework()
{
    //m_rootEntity = nullptr;
    delete sphereMaterial;
    delete sphereMesh;
    delete sphereTransform;
    delete m_sphereEntity;
    //delete m_rootEntity;     // - Czemu nie można usunąć?
}

void Firework::move(){
    velocity = velocity + acceleration;
    pos = pos + velocity;
    acceleration = acceleration*0;

    sphereTransform->setTranslation(QVector3D(pos.x(), pos.y(), pos.z()));
    //trail();
}

void Firework::destroy(){
    if(velocity.y() <= 0 && !boomed){
            m_sphereEntity->removeComponent(sphereMaterial);
            m_sphereEntity->removeComponent(sphereTransform);
            m_sphereEntity->removeComponent(sphereMesh);
            YOUCANDELETEROOT = true;
        }
}

void Firework::trail(){
    QVector3D pos_t;
    pos_t.setY(pos.y() - velocity.y());

    m_sphereEntity->addComponent(sphereMesh);
    m_sphereEntity->addComponent(sphereMaterial);

    sphereTransform->setScale3D(QVector3D(0.98, 0.98, 0.98));
    sphereTransform->setTranslation(QVector3D(pos.x(), pos_t.y(), pos.z()));
    m_sphereEntity->addComponent(sphereTransform);

}

void Firework::update(){
    if(!boomed){
        ApplyForce();
        move();
        destroy();
    }
    else if(boomed){
        updateBOOM();
    }
}

void Firework::updateBOOM(){
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni; // guaranteed unbiased

        velocity = velocity * QVector3D(0.90, 0.90, 0.90);
        sphereTransform->setScale3D(sphereTransform->scale3D() * QVector3D(0.98, 0.98, 0.98));

    ApplyForce();
    move();

    lifespan -= 5;
    if(lifespan <= 0){
        lifespan = 0;}

    sphereMaterial->setAlpha(map(lifespan)); // 0 - znika // 1 - pelna widocznosc ---------- RGBA 0 - transparent // 255 - pelna widocznosc

    if(lifespan <= 0){
        sphereTransform->setScale3D(QVector3D(0, 0, 0));

        m_sphereEntity->removeComponent(sphereMaterial);
        m_sphereEntity->removeComponent(sphereTransform);
        m_sphereEntity->removeComponent(sphereMesh);
        YOUCANDELETE = true;
    }
}

float Firework::map(int lifespan_t){
    double slope = 1.0 * (0 - 1) / (0 - 255);
    float output = 1 + slope * (lifespan_t - 255);

    return output;

}

void Firework::SetAndAdd(){
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni; // guaranteed unbiased
    //int xyz = random()%2;

    h_color = uni(rng)%255;
    s_color = uni(rng)%255;
    v_color = uni(rng)%255;
    a_color = 255;

    QColor p_color(h_color, s_color, v_color, a_color);

    sphereMesh->setRings(10);
    sphereMesh->setSlices(15);
    sphereMesh->setRadius(0.3);

    //sphereMaterial->setDiffuse(p_color.toHsv());
    sphereMaterial->setAmbient(p_color.toHsv());

    //sphereMaterial->setShininess(25);

    sphereTransform->setScale3D(QVector3D(2.0f,2.0f,2.0f));
    sphereTransform->setTranslation(pos);

    m_sphereEntity->addComponent(sphereMesh);
    m_sphereEntity->addComponent(sphereMaterial);
    m_sphereEntity->addComponent(sphereTransform);

}

bool Firework::CheckIfDead(){
    return boomed;
}

bool Firework::CanIDelete(){
    return YOUCANDELETE;
}

bool Firework::CanIDeleteRoot(){
    return YOUCANDELETEROOT;
}

QVector3D Firework::ReturnPosition(){
    return pos;
}

void Firework::ApplyForce(){
    acceleration = acceleration + gravity;
}

int Firework::ReturnLifespan(){
    return lifespan;
}

bool Firework::ReturnZeroVelocity(){
    if(velocity.y() <= 0)
        return true;
    else
        return false;
}
