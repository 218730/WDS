#ifndef SCENE_H
#define SCENE_H

#include <QGuiApplication>
#include <QtWidgets/QApplication>
#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qforwardrenderer.h>
#include <QtWidgets/QWidget>
#include <QtGui/QScreen>
#include <QtWidgets/QHBoxLayout>
#include <Qt3DInput/QInputAspect>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcamera.h>
#include <Qt3DCore/qtransform.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QCheckBox>

#include <Qt3DRender/qpointlight.h>


#include <QLabel>

#include <QVector>
#include <vector>
#include <deque>
#include <QtCore/QObject>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>
#include "firework.h"

#include <QThread>

using namespace std;

class Scene : public QObject{
    Q_OBJECT

public:
    void AddFireworks(Qt3DCore::QEntity *rootEntity, int i);
    ~Scene();
    Scene(Qt3DCore::QEntity *sceneRoot, QPushButton *AddElementBox, QCheckBox *START_BUTTON);
    void BOOM(Firework *i);
    void AddBOOM(Qt3DCore::QEntity *rootEntity, QVector3D pos, int i);


public slots:
    void AddFirework();
    void update();
    void AUTO_MODE();

private:
    Qt3DCore::QEntity *rootEntity;
    QPushButton *AddElementBoxT;
    QCheckBox *START;

    static void usleep(unsigned long usecs){QThread::usleep(usecs);}

    list<Firework*> V_Fireworks;

    Firework *fire;

};

#endif // SCENE_H
