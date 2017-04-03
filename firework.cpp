#include "firework.h"

Firework::Firework(Qt3DCore::QEntity *rootEntity)
    : m_rootEntity(rootEntity)
{
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni; // guaranteed unbiased

    velocity = QVector3D(0, 10, 0);
    acceleration = QVector3D(0, 0, 0);
    gravity = QVector3D(0, -0.2, 0);

    //srand((unsigned)time(NULL));
    //x = random()%200-100;
    //z = random()%200-100;
    x = uni(rng)%200-100;
    z = uni(rng)%200-100;
    pos = QVector3D(x, -4.0f, z);

    SetAndAdd();

    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(20);
}

Firework::~Firework()
{
    //delete this;
}

Firework::Firework(Qt3DCore::QEntity *rootEntity, QVector3D posboomed) : m_rootEntity(rootEntity)
{
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni; // guaranteed unbiased

    //srand((unsigned)time(NULL));
    boomed = true;
    velocity = QVector3D(uni(rng)%1-0.5, uni(rng)%1-0.5, uni(rng)%1-0.5);
    velocity = velocity * QVector3D(uni(rng)%5+1,uni(rng)%5+1,uni(rng)%5+1);
    //velocity.setX(velocity.x() * ((uni(rng))%3));
    //velocity.setY(velocity.y() * ((uni(rng))%3));
    //velocity.setZ(velocity.z() * ((uni(rng))%3));
    acceleration = QVector3D(0, 0, 0);
    pos = posboomed;
    gravity = QVector3D(0, -0.2, 0);
    lifespan = 255;

    SetAndAdd();

    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(updateBOOM()));
    timer->start(20);
}

void Firework::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
    qDebug() << "Fdsfds";
    }
}

void Firework::moveY(){
// Jeżęli box == checked
    velocity = velocity + acceleration;
    pos = pos + velocity;
    acceleration = acceleration*0;

    sphereTransform->setTranslation(QVector3D(pos.x(), pos.y(), pos.z()));

}

void Firework::moveOnSphere(){
    //srand((unsigned)time(NULL));

    //if(boomed){
        velocity = velocity + acceleration;
        pos = pos + velocity;
        acceleration = acceleration*0;

        sphereTransform->setTranslation(QVector3D(pos.x(), pos.y(), pos.z()));
    //}

}

void Firework::destroy(){
    if(!boomed){
        //if(pos.y() >= y_temp){
        if(velocity.y() <= 0){
            //y = -5.0f;
            //pos = QVector3D(pos.x(), y_temp, pos.z());
            boomed = true;
            m_sphereEntity->removeComponent(sphereMaterial);
            m_sphereEntity->removeComponent(sphereTransform);
            m_sphereEntity->removeComponent(sphereMesh);

        }
    }
}

void Firework::update(){
    ApplyForce();
    moveY();
    destroy();
}

void Firework::updateBOOM(){
    //std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    //std::uniform_int_distribution<int> uni; // guaranteed unbiased

        velocity = velocity * QVector3D(0.90, 0.90, 0.90);
        //velocity = velocity + QVector3D(((uni(rng))%1-0.5), ((uni(rng))%1-0.5), ((uni(rng))%1-0.5));
        lifespan -= 6;
    if(lifespan <= 0) {
        lifespan = 0;
        sphereMaterial->setDiffuse(QColor(255,0,0,lifespan));
        m_sphereEntity->removeComponent(sphereMaterial);
        m_sphereEntity->removeComponent(sphereTransform);
        m_sphereEntity->removeComponent(sphereMesh);
    }
    ApplyForce();
    moveOnSphere();

}

void Firework::SetAndAdd(){
    sphereMesh->setRings(10);
    sphereMesh->setSlices(15);
    sphereMesh->setRadius(0.3);

    sphereMaterial->setDiffuse(QColor(random()%255,random()%255,random()%255));
    //sphereMaterial->setAmbient(QColor(255,0,0,0));
    //sphereMaterial->setShininess(5);

    sphereTransform->setScale3D(QVector3D(1.0f,1.0f,1.0f));
    sphereTransform->setTranslation(pos);

    m_sphereEntity = new Qt3DCore::QEntity(m_rootEntity);
    m_sphereEntity->addComponent(sphereMesh);
    m_sphereEntity->addComponent(sphereMaterial);
    m_sphereEntity->addComponent(sphereTransform);
}

bool Firework::CheckIfDead(){
    return boomed;
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
