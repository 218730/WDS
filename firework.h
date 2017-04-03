#ifndef FIREWORK_H
#define FIREWORK_H



#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>

#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>

#include <QMouseEvent>

#include <QtCore/QObject>
#include <QTimer>

#include <QDebug>

#include "window.h"

#include <random>

class Firework : public QObject{
    Q_OBJECT

public:
    explicit Firework(Qt3DCore::QEntity *rootEntity);
    Firework(Qt3DCore::QEntity *rootEntity, QVector3D posboomed);
    ~Firework();
    void destroy();
    void SetAndAdd();
    void mousePressEvent(QMouseEvent *e);
    bool CheckIfDead();
    QVector3D ReturnPosition();
    void ApplyForce();
    int ReturnLifespan();

protected:
    //void timerEvent(QTimerEvent *e) override;

public slots:
    void moveY();
    void update();
    void moveOnSphere();
    void updateBOOM();

private:
    Qt3DCore::QEntity *m_rootEntity;
    Qt3DCore::QEntity *m_sphereEntity;

    Qt3DCore::QTransform *sphereTransform = new Qt3DCore::QTransform();
    Qt3DExtras::QSphereMesh *sphereMesh = new Qt3DExtras::QSphereMesh();
    Qt3DExtras::QPhongMaterial *sphereMaterial = new Qt3DExtras::QPhongMaterial();

    float x;
    float y = 0.0f;
    float z;
    //int speed = 2;
    QVector3D pos;
    QVector3D velocity;
    QVector3D acceleration;
    QVector3D gravity;
    bool boomed;
    int lifespan;

    std::random_device rd;     // only used once to initialise (seed) engine

};

#endif // FIREWORK_H
