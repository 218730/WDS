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

QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
QT_END_NAMESPACE

using namespace std;

class Scene : public QObject{
    Q_OBJECT

public:
    void AddFireworks(Qt3DCore::QEntity *rootEntity, int i);
    ~Scene();
    Scene(Qt3DCore::QEntity *sceneRoot, QPushButton *AddElementBox, QCheckBox *START_BUTTON);
    void BOOM(Firework *i);
    void AddBOOM(Qt3DCore::QEntity *rootEntity, QVector3D pos, int i);

    static void usleep(unsigned long usecs){QThread::usleep(usecs);}

public slots:
    void AddFirework();
    void AddFireworkDefPos();
    void update();
    void AUTO_MODE();
    void DefPosX(const QString &newValue);
    void DefPosY(const QString &newValue);
    void DefPosZ(const QString &newValue);


private:
    Qt3DCore::QEntity *rootEntity;
    QPushButton *AddElementBoxT;
    QCheckBox *START;
    //QList<QLineEdit*> *lineEditsListT;
    //lineEditsT[0] = new QLineEdit;
    //lineEditsT[1] = new QLineEdit;
    //lineEditsT[2] = new QLineEdit;
    list<Firework*> V_Fireworks;
    QString DefX;
    QString DefY;
    QString DefZ;
};

#endif // SCENE_H
