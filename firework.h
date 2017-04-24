#ifndef FIREWORK_H
#define FIREWORK_H

#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>

#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongAlphaMaterial>

#include <QMouseEvent>

#include <QtCore/QObject>
#include <QTimer>

#include <QDebug>

#include <QThread>

#include "window.h"

#include <random>

class Firework : public QObject{
    Q_OBJECT

public:
    Firework(Qt3DCore::QEntity *rootEntity);
    Firework(Qt3DCore::QEntity *rootEntity, QVector3D posboomed);
    ~Firework();
    void destroy();
    void SetAndAdd();
    bool CheckIfDead();
    QVector3D ReturnPosition();
    void ApplyForce();
    int ReturnLifespan();
    bool ReturnZeroVelocity();
    bool CanIDelete();
    bool CanIDeleteRoot();
    void trail();
    float map(int lifespan_t);

public slots:
    void move();
    void update();
    void updateBOOM();

private:
    Qt3DCore::QEntity *m_rootEntity = new Qt3DCore::QEntity();
    Qt3DCore::QEntity *m_sphereEntity = new Qt3DCore::QEntity(m_rootEntity);

    Qt3DCore::QTransform *sphereTransform = new Qt3DCore::QTransform();
    Qt3DExtras::QSphereMesh *sphereMesh = new Qt3DExtras::QSphereMesh();
    Qt3DExtras::QPhongAlphaMaterial *sphereMaterial = new Qt3DExtras::QPhongAlphaMaterial();

    static void usleep(unsigned long usecs){QThread::usleep(usecs);}

    float x;
    float y = 0.0f;
    float z;
    QVector3D pos;
    QVector3D velocity;
    QVector3D acceleration;
    QVector3D gravity;
    bool boomed;
    int lifespan;
    bool YOUCANDELETE = false;
    bool YOUCANDELETEROOT = false;

    int h_color;
    int s_color;
    int v_color;
    int a_color;

    std::random_device rd;     // only used once to initialise (seed) engine

};

#endif // FIREWORK_H
