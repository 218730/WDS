#include "canvas.h"

Canvas::Canvas(){

}

Canvas::~Canvas(){
    delete view;
    delete container;
    delete widget;
    delete hLayout;
    delete vLayout;
    delete input;
    delete sceneRoot;
    delete cameraEntity;
    delete lightEntity;
    delete light;
    delete lightTransform;
    delete camController;
    delete gridGroupBoxAutoMode;
    delete AutoModeLayout;
    delete AMlabels[0];
    delete AMlineEdits[0];
    delete AddElementBox;
    delete machine;


}


void Canvas::Create(){

//Qt3DExtras::Qt3DWindow view;



QColor b_color(0,0,0,60);
b_color.setAlpha(60);

view->defaultFrameGraph()->setClearColor(b_color);

//Dla OPENGL
//container->createWindowContainer(view);

container->setAttribute(Qt::WA_TranslucentBackground, true);
container->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );
container->setWindowOpacity(0.5);

screenSize = view->screen()->size();
container->setMinimumSize(QSize(200, 100));
container->setMaximumSize(screenSize);
//container->setStyleSheet("background:transparent");


vLayout->setAlignment(Qt::AlignTop);
hLayout->addWidget(container, 1);
hLayout->addLayout(vLayout);

widget->setWindowTitle(QStringLiteral("Fireworks v.0.47"));

view->registerAspect(input);

// Camera

cameraEntity->lens()->setPerspectiveProjection(60.0f, 16.0f/9.0f, 0.1f, 500.0f);
cameraEntity->setPosition(QVector3D(0, 0, 20.0f));
cameraEntity->setUpVector(QVector3D(0, 1, 0));
cameraEntity->setViewCenter(QVector3D(0, 90, 0));


light->setColor("white");
light->setIntensity(0.5);
lightEntity->addComponent(light);
lightTransform->setTranslation(cameraEntity->position());
lightEntity->addComponent(lightTransform);

// For camera controls
camController->setCamera(cameraEntity);

// Set root object of the scene
view->setRootEntity(sceneRoot);

// Create control widgets

AMlabels[0] = new QLabel("max. particles on the scene: ");
AMlineEdits[0] = new QLineEdit();

AutoModeLayout->addWidget(AMlabels[0]);
AutoModeLayout->addWidget(AMlineEdits[0]);
AutoModeLayout->addWidget(AddElementBox);

gridGroupBoxAutoMode->setLayout(AutoModeLayout);

//Two Way Button

QState *off = new QState();
    off->assignProperty(AddElementBox, "text", "OFF");
    off->setObjectName("off");

QState *on = new QState();
    on->setObjectName("on");
    on->assignProperty(AddElementBox, "text", "ON");

 off->addTransition(AddElementBox, SIGNAL(clicked()), on);
 on->addTransition(AddElementBox, SIGNAL(clicked()), off);

 machine->addState(off);
 machine->addState(on);

 machine->setInitialState(off);
 machine->start();





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
layout->addWidget(AddElementDefPos);
gridGroupBox->setLayout(layout);

vLayout->addWidget(label);
vLayout->addWidget(START_BUTTON);
vLayout->addWidget(AddElementRandPos);
vLayout->addWidget(gridGroupBoxAutoMode);
vLayout->addWidget(gridGroupBox);
vLayout->addWidget(gridGroupBoxPresets);


//Podloze
Qt3DCore::QEntity *m_planeEntity;

Qt3DExtras::QPlaneMesh *planeMesh = new Qt3DExtras::QPlaneMesh(sceneRoot);
    planeMesh->setWidth(100);
    planeMesh->setHeight(100);

// Plane mesh transform
Qt3DCore::QTransform *planeTransform = new Qt3DCore::QTransform();
    planeTransform->setScale(2.0f);
    //planeTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 45.0f));
    planeTransform->setTranslation(QVector3D(0.0f, -4.5f, 0.0f));

Qt3DExtras::QPhongMaterial *planeMaterial = new Qt3DExtras::QPhongMaterial();
    planeMaterial->setDiffuse(QColor(0,255,0));
    planeMaterial->setAmbient(QColor(0,102,51));

// Plane
    m_planeEntity = new Qt3DCore::QEntity(sceneRoot);
    m_planeEntity->addComponent(planeMesh);
    m_planeEntity->addComponent(planeMaterial);
    m_planeEntity->addComponent(planeTransform);

/*
Qt3DExtras::QPlaneMesh *planeEntity = new Qt3DExtras::QPlaneMesh(sceneRoot);
planeEntity->setHeight(100.0f);
planeEntity->setWidth(100.0f);
planeEntity->setMeshResolution(QSize(20, 20));

Qt3DExtras::QNormalDiffuseSpecularMapMaterial *normalDiffuseSpecularMapMaterial = new Qt3DExtras::QNormalDiffuseSpecularMapMaterial();
normalDiffuseSpecularMapMaterial->setTextureScale(10.0f);
normalDiffuseSpecularMapMaterial->setShininess(80.0f);
normalDiffuseSpecularMapMaterial->setAmbient(QColor(51,20,29));*/
/*
Qt3DRender::QTextureImage *diffuseImage = new Qt3DRender::QTextureImage();
diffuseImage->setSource(QUrl(QStringLiteral("/home/psiejka/Qt/Examples/Qt-5.8/qt3d/exampleresources/assets/textures/pattern_09/diffuse.webp")));
normalDiffuseSpecularMapMaterial->diffuse()->addTextureImage(diffuseImage);

Qt3DRender::QTextureImage *specularImage = new Qt3DRender::QTextureImage();
specularImage->setSource(QUrl(QStringLiteral("/home/psiejka/Qt/Examples/Qt-5.8/qt3d/exampleresources/assets/textures/pattern_09/specular.webp")));
normalDiffuseSpecularMapMaterial->specular()->addTextureImage(specularImage);

Qt3DRender::QTextureImage *normalImage = new Qt3DRender::QTextureImage();
normalImage->setSource(QUrl((QStringLiteral("/home/psiejka/Qt/Examples/Qt-5.8/qt3d/exampleresources/assets/textures/pattern_09/normal.webp"))));
normalDiffuseSpecularMapMaterial->normal()->addTextureImage(normalImage);*/

//planeEntity->addComponent(normalDiffuseSpecularMapMaterial);
//sceneRoot->addComponent(normalDiffuseSpecularMapMaterial);



QList<QLineEdit*> lineEditsList;
lineEditsList.append(lineEdits[0]);
lineEditsList.append(lineEdits[1]);
lineEditsList.append(lineEdits[2]);

Scene *window = new Scene(sceneRoot, AddElementBox, START_BUTTON);

QObject::connect(AddElementRandPos, SIGNAL(clicked()), window, SLOT(AddFirework()));

QObject::connect(AddElementDefPos, SIGNAL(clicked()), window, SLOT(AddFireworkDefPos()));

QObject::connect(lineEdits[0], SIGNAL(textChanged(const QString &)), window, SLOT(DefPosX(const QString &)));
QObject::connect(lineEdits[1], SIGNAL(textChanged(const QString &)), window, SLOT(DefPosY(const QString &)));
QObject::connect(lineEdits[2], SIGNAL(textChanged(const QString &)), window, SLOT(DefPosZ(const QString &)));

QTimer *timer = new QTimer();
QObject::connect(timer, SIGNAL(timeout()), window, SLOT(update()));
timer->start(1000 / 33);

// Show window

widget->show();
widget->resize(1200, 600);
}
