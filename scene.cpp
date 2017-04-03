#include "scene.h"

Scene::Scene(){

    //AddFireworks(rootEntity, 5);
}

Scene::~Scene(){
    if(V_Fireworks.size() > 0){
        for(int i = 0; i < V_BoomedFireworks.size(); i++){
            delete V_Fireworks[i];}
            V_Fireworks.pop_front();
    }
    //delete V_Fireworks;

    if(V_BoomedFireworks.size() > 0){
        for(int i = 0; i < V_BoomedFireworks.size(); i++){
            delete V_BoomedFireworks[i];}
            V_BoomedFireworks.pop_front();
    }
    //delete V_BoomedFireworks;
    //for(int i = 0; i<V_Fireworks.size(); i++)
    //V_Fireworks.erase(i);
}

void Scene::AddFireworks(Qt3DCore::QEntity *rootEntity, int i){
    for(int j = 0; j < i; j++){
    //fire = new Firework(rootEntity);
    V_Fireworks.push_back(new Firework(rootEntity));
    qDebug() << V_Fireworks.size();

    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(20);
    }
}

void Scene::AddBOOM(Qt3DCore::QEntity *rootEntity, QVector3D pos, int i){
    for(int j = 0; j < i; j++){
    //fire = new Firework(rootEntity, pos);
    V_BoomedFireworks.push_back(new Firework(rootEntity, pos));
    qDebug() << V_BoomedFireworks.size();
    }
}

void Scene::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_A){
        //fire = new Firework(rootEntity, sphereMesh, sphereMaterial);
        qDebug() << "vdsfds";
    }
}

void Scene::AddFirework(){
    AddFireworks(rootEntity, 1);
    //AddElement->setText("Added.");
}

void Scene::BOOM(){
    //if(fire->CheckIfDead() == true){
//for(int i = 0; i < V_Fireworks.size(); i++)
    if(V_Fireworks.size() > 0)
       // if(V_Fireworks[0]->destroy()){

    if(V_Fireworks[0]->CheckIfDead()){
        AddBOOM(rootEntity, V_Fireworks[0]->ReturnPosition(), 20);
        qDebug() << V_Fireworks[0]->ReturnPosition();
        qDebug() << "DEAD.";

            //if(V_Fireworks.size() > 0){
            delete V_Fireworks[0];
            V_Fireworks.pop_front();
    }
            //}
    //}
}

void Scene::update(){
    BOOM();
    //for(int i = V_BoomedFireworks.size()-1; i>= 0; i--)
    if(V_BoomedFireworks.size() > 0)
    if (V_BoomedFireworks[V_BoomedFireworks.size()-1]->ReturnLifespan() <= 0){
        delete V_BoomedFireworks[V_BoomedFireworks.size()-1];
        V_BoomedFireworks.pop_back();
    }

}



void Scene::CreateWindow(){

    view->defaultFrameGraph()->setClearColor(QColor(Qt::black));
    QWidget *container = QWidget::createWindowContainer(view);
    QSize screenSize = view->screen()->size();
    container->setMinimumSize(QSize(200, 100));
    container->setMaximumSize(screenSize);

    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setAlignment(Qt::AlignTop);
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);

    widget->setWindowTitle(QStringLiteral("Fireworks"));

    Qt3DInput::QInputAspect *input = new Qt3DInput::QInputAspect;
    view->registerAspect(input);

    // Root entity
    rootEntity = new Qt3DCore::QEntity();

    // Camera
    Qt3DRender::QCamera *cameraEntity = view->camera();

    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 300.0f);
    cameraEntity->setPosition(QVector3D(0, 0, 20.0f));
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));

    /*Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("red");
    light->setIntensity(4);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(cameraEntity->position());
    lightEntity->addComponent(lightTransform);*/

    // For camera controls
    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(rootEntity);
    camController->setCamera(cameraEntity);

    // Fireworks
    Scene *modifier = new Scene();
    modifier->AddFireworks(rootEntity, 0);

    // Set root object of the scene
    view->setRootEntity(rootEntity);

    // Create control widgets
    //QCommandLinkButton *info = new QCommandLinkButton();
    QLabel *label;
    //QString buffer1;
    //buffer1 = V_Fireworks.size();
    //QByteArray ba = buffer1.toLatin1();
    char* buffer = ":(";

    //sprintf(buffer, "Liczba: %d", V_Fireworks.size());
    //buffer = V_Fireworks.size();
    //sprintf(buffer,"Liczba fajerwerków: %d", V_Fireworks.size());
    label = new QLabel(buffer);
    label->setText(buffer);
    qDebug() << V_Fireworks.size();
    //qDebug() << buffer;
    //info->setText(QStringLiteral(buffer));
    //info->setDescription(QString::fromLatin1("Qt3D provides several ready-made meshes, like torus, cylinder, cone, cube, plane and sphere."));
    //info->setIconSize(QSize(0,0));

   /* QCheckBox *sphereCB = new QCheckBox(widget);
    sphereCB->setChecked(true);
    sphereCB->setText(QStringLiteral("Sphere"));*/
    AddElement = new QPushButton("Add New Element");

    //hLayout->addWidget(modifier);

    vLayout->addWidget(label);
    vLayout->addWidget(AddElement);

    connect(AddElement, SIGNAL(clicked()), this, SLOT(AddFirework()));

//SIGNAL(clicked()), qApp,
    //sphereCB->setChecked(true);

    // Show window
    widget->show();
    widget->resize(1200, 800);

}
