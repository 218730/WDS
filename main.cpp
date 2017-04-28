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

#include <QDialog>
#include <QtWidgets>

#include "firework.h"
#include "window.h"
#include "scene.h"

#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QNormalDiffuseSpecularMapMaterial>
#include <Qt3DRender/QTextureImage>

#include <QtOpenGL/QGLWidget>

/*
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcameralens.h>


#include <Qt3DExtras/qtorusmesh.h>
#include <Qt3DRender/qmesh.h>
#include <Qt3DRender/qtechnique.h>
#include <Qt3DRender/qmaterial.h>
#include <Qt3DRender/qeffect.h>
#include <Qt3DRender/qtexture.h>
#include <Qt3DRender/qrenderpass.h>
#include <Qt3DRender/qsceneloader.h>
#include <Qt3DRender/qpointlight.h>

#include <Qt3DCore/qaspectengine.h>

#include <Qt3DRender/qrenderaspect.h>
*/

/*
TODO:

- Sprawdz czy inne losowanie liczb zmniejsza zużycie procesora
- Rozwaz czy wprowadzenie listy na rootFireworks to zly pomysl - 1->0-20 - 2->21-41
    - dwie petle?
    - (i*20-29) - (i*20)

- sleep przy dodawaniu
-
*/

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

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    Qt3DExtras::Qt3DWindow view;



    QColor b_color(0,0,0,60);
    b_color.setAlpha(60);

    view.defaultFrameGraph()->setClearColor(b_color);

    //QWidget *container = QGLWidget::createWindowContainer(&view);
    //container->createWindowContainer(&view);

    /*QOpenGLWidget *container = new QOpenGLWidget();
    container->createWindowContainer(&view);*/

    QWidget *container = QWidget::createWindowContainer(&view);
    container->setAttribute(Qt::WA_TranslucentBackground, true);
    container->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );
    container->setWindowOpacity(0.5);

    QSize screenSize = view.screen()->size();
    container->setMinimumSize(QSize(200, 100));
    container->setMaximumSize(screenSize);
    //container->setStyleSheet("background:transparent");

    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setAlignment(Qt::AlignTop);
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);

    widget->setWindowTitle(QStringLiteral("Fireworks v.0.47"));

    Qt3DInput::QInputAspect *input = new Qt3DInput::QInputAspect;
    view.registerAspect(input);

    // Root entity
    static Qt3DCore::QEntity *sceneRoot;
    sceneRoot = new Qt3DCore::QEntity();

    // Camera
    Qt3DRender::QCamera *cameraEntity = view.camera();

    cameraEntity->lens()->setPerspectiveProjection(60.0f, 16.0f/9.0f, 0.1f, 500.0f);
    cameraEntity->setPosition(QVector3D(0, 0, 20.0f));
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setViewCenter(QVector3D(0, 90, 0));

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(sceneRoot);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(0.5);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(cameraEntity->position());
    lightEntity->addComponent(lightTransform);

    // For camera controls
    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(sceneRoot);
    camController->setCamera(cameraEntity);

    // Set root object of the scene
    view.setRootEntity(sceneRoot);

    // Create control widgets
    QGroupBox *gridGroupBoxAutoMode;
    gridGroupBoxAutoMode = new QGroupBox("AUTO_MODE:");
    QGridLayout *AutoModeLayout = new QGridLayout;
    QLabel *AMlabels[1];
    QLineEdit *AMlineEdits[1];
    AMlabels[0] = new QLabel("max. particles on the scene: ");
    AMlineEdits[0] = new QLineEdit();

    QPushButton *AddElementBox;
    AddElementBox = new QPushButton();
    AutoModeLayout->addWidget(AMlabels[0]);
    AutoModeLayout->addWidget(AMlineEdits[0]);
    AutoModeLayout->addWidget(AddElementBox);

    gridGroupBoxAutoMode->setLayout(AutoModeLayout);

    QStateMachine machine;

    QState *off = new QState();
        off->assignProperty(AddElementBox, "text", "OFF");
        off->setObjectName("off");

    QState *on = new QState();
        on->setObjectName("on");
        on->assignProperty(AddElementBox, "text", "ON");

     off->addTransition(AddElementBox, SIGNAL(clicked()), on);
     on->addTransition(AddElementBox, SIGNAL(clicked()), off);

     machine.addState(off);
     machine.addState(on);

     machine.setInitialState(off);
     machine.start();



    QLabel *label;
    string buffer_string = "Fireworks Symulator";
    const char* buffer = buffer_string.c_str();
    label = new QLabel(buffer);
    label->setText(buffer);
    label->setAlignment(Qt::AlignCenter);

    QCheckBox *START_BUTTON;
    START_BUTTON = new QCheckBox("APPLY TIME");
    START_BUTTON->setStyleSheet("margin-left:50%; margin-right:50%;");

    QPushButton *AddElementRandPos;
    AddElementRandPos = new QPushButton("Add new element - random pos.");

    QPushButton *AddElementDefPos;
    AddElementDefPos = new QPushButton("Add new element");

    QGroupBox *gridGroupBoxPresets;
    gridGroupBoxPresets = new QGroupBox("Presets:");
    QGridLayout *PresetsLayout = new QGridLayout;
    QCheckBox *Preset1 = new QCheckBox("Preset 1");
    QCheckBox *Preset2 = new QCheckBox("Preset 2");
    QCheckBox *Preset3 = new QCheckBox("Preset 3");
    PresetsLayout->addWidget(Preset1);
    PresetsLayout->addWidget(Preset2);
    PresetsLayout->addWidget(Preset3);
    gridGroupBoxPresets->setLayout(PresetsLayout);

    QGroupBox *gridGroupBox;
    gridGroupBox = new QGroupBox(("Define your position:"));
    QGridLayout *layout = new QGridLayout;
    QLabel *labels[3];
        labels[0] = new QLabel("x");
        labels[1] = new QLabel("y");
        labels[2] = new QLabel("z");
    QLineEdit *lineEdits[3];
    for (int i = 0; i < 3; ++i) {
        lineEdits[i] = new QLineEdit;
        layout->addWidget(labels[i], i + 1, 0);
        layout->addWidget(lineEdits[i], i + 1, 1);
    }
    //layout->setColumnStretch(1, 10);
    //layout->setColumnStretch(2, 20);
    layout->addWidget(AddElementDefPos);
    gridGroupBox->setLayout(layout);

    vLayout->addWidget(label);
    vLayout->addWidget(START_BUTTON);
    vLayout->addWidget(AddElementRandPos);
    vLayout->addWidget(gridGroupBoxAutoMode);
    vLayout->addWidget(gridGroupBox);
    vLayout->addWidget(gridGroupBoxPresets);

/*
    Qt3DExtras::QPlaneMesh *planeEntity = new Qt3DExtras::QPlaneMesh(sceneRoot);
    planeEntity->setHeight(100.0f);
    planeEntity->setWidth(100.0f);
    planeEntity->setMeshResolution(QSize(20, 20));

    Qt3DExtras::QNormalDiffuseSpecularMapMaterial *normalDiffuseSpecularMapMaterial = new Qt3DExtras::QNormalDiffuseSpecularMapMaterial();
    normalDiffuseSpecularMapMaterial->setTextureScale(10.0f);
    normalDiffuseSpecularMapMaterial->setShininess(80.0f);
    normalDiffuseSpecularMapMaterial->setAmbient(QColor::fromRgbF(0.2f, 0.2f, 0.2f, 1.0f));

    Qt3DRender::QTextureImage *diffuseImage = new Qt3DRender::QTextureImage();
    diffuseImage->setSource(QUrl(QStringLiteral("/home/psiejka/Qt/Examples/Qt-5.8/qt3d/exampleresources/assets/textures/pattern_09/diffuse.webp")));
    normalDiffuseSpecularMapMaterial->diffuse()->addTextureImage(diffuseImage);

    Qt3DRender::QTextureImage *specularImage = new Qt3DRender::QTextureImage();
    specularImage->setSource(QUrl(QStringLiteral("/home/psiejka/Qt/Examples/Qt-5.8/qt3d/exampleresources/assets/textures/pattern_09/specular.webp")));
    normalDiffuseSpecularMapMaterial->specular()->addTextureImage(specularImage);

    Qt3DRender::QTextureImage *normalImage = new Qt3DRender::QTextureImage();
    normalImage->setSource(QUrl((QStringLiteral("/home/psiejka/Qt/Examples/Qt-5.8/qt3d/exampleresources/assets/textures/pattern_09/normal.webp"))));
    normalDiffuseSpecularMapMaterial->normal()->addTextureImage(normalImage);

    //planeEntity->addComponent(normalDiffuseSpecularMapMaterial);
    sceneRoot->addComponent(normalDiffuseSpecularMapMaterial);

*/



    Scene *window = new Scene(sceneRoot, AddElementBox, START_BUTTON);

    QObject::connect(AddElementRandPos, SIGNAL(clicked()), window, SLOT(AddFirework()));

    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), window, SLOT(update()));
    timer->start(1000 / 33);

    // Show window

    widget->show();
    widget->resize(1200, 600);

    return app.exec();

}
