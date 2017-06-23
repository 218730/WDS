#ifndef CANVAS_H
#define CANVAS_H

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

#include <QDialog>
#include <QtWidgets>

#include "scene.h"

#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QNormalDiffuseSpecularMapMaterial>
#include <Qt3DRender/QTextureImage>

#include <QtOpenGL/QGLWidget>

#include <Qt3DExtras/QPhongMaterial>


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


/**
 * \brief Klasa Canvas
 *
 * Klasa definiująca scenę dla fajerwerków oraz panelu użytkownika.
 *
 * \version beta
 */
class Canvas : public QOpenGLWidget, protected QOpenGLFunctions{
//class Canvas{
private:
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    QWidget *container = QWidget::createWindowContainer(view);  //
    int value = 50;
    //QWidget *container = QGLWidget::createWindowContainer(view);
    //QOpenGLWidget *container = new QOpenGLWidget();
    QSize screenSize;

    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();

    Qt3DInput::QInputAspect *input = new Qt3DInput::QInputAspect;

    Qt3DCore::QEntity *sceneRoot = new Qt3DCore::QEntity();
    Qt3DRender::QCamera *cameraEntity = view->camera();

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(sceneRoot);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);

    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(sceneRoot);

    QGroupBox *gridGroupBoxAutoMode = new QGroupBox("AUTO_MODE:");
    QGridLayout *AutoModeLayout = new QGridLayout;
    QLabel *AMlabels[1];
    QLineEdit *AMlineEdits[1];

    QPushButton *AddElementBox = new QPushButton();

    QStateMachine* machine = new QStateMachine();

public:
    /**
     * Konstruktor.
     */
    Canvas();
    /**
     * Dekonstruktor.
     */
    ~Canvas();
    /**
     * Metoda tworząca okno programu wraz z panelem użytkownika.
     */
    void Create();
};

#endif // CANVAS_H
