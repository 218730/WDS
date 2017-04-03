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
#include <QtCore/QObject>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>
#include "firework.h"

using namespace std;

class Scene : public QObject{
    Q_OBJECT


    //void mousePressEvent(QMouseEvent *event) override;

public:
    void CreateWindow();
    ///WINDOW ^^

    void AddFireworks(Qt3DCore::QEntity *rootEntity, int i);
    ~Scene();
    Scene();
    void    keyPressEvent(QKeyEvent *e);
    void BOOM();
    void AddBOOM(Qt3DCore::QEntity *rootEntity, QVector3D pos, int i);

public slots:
    void AddFirework();
    void update();

private:
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    QPushButton *AddElement;
    Qt3DCore::QEntity *rootEntity;

    QVector<Firework*> V_Fireworks;
    QVector<Firework*> V_BoomedFireworks;

    Firework *fire;
};

#endif // SCENE_H
