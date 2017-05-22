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


/**
 * \brief Klasa Scene
 *
 * Klasa tworząca obiekty na przestrzeni tworzonej przez Canvas.
 *
 * \version alfa
 */
class Scene : public QObject{
    Q_OBJECT

public:
    /**
     * \brief Tworzy i fajerwerków na scenie w losowych miejscach.
     */
    void AddFireworks(Qt3DCore::QEntity *rootEntity, int i);
    /**
     * \brief Dekonstruktor usuwający tworzone obiekty.
     */
    ~Scene();
    /**
     * \brief Konstruktor przypisujący obiekty do ich tymczasowych zmiennych.
     *
     * \param sceneRoot Przestrzeń w której zostaje stworzony obiekt
     * \param AddElementBox Przycisk odpowiadający za tryb automatyczny
     * \param START_BUTTON Przycisk odpowiadający za aktywację pętli aktualizującej scenę.
     * \param Preset1 Przycisk włączający predefiniowane zachowania fajerwerków nr 1
     */
    Scene(Qt3DCore::QEntity *sceneRoot, QPushButton *AddElementBox, QCheckBox *START_BUTTON, QCheckBox *Preset1);
    /**
     * \brief Sprawdza czy można dodać wybuch.
     *
     * \param i iterator listy obiektów na scenie
     */
    void BOOM(Firework *i);
    /**
     * \brief Dodaje wybuch fajerwerków do sceny.
     */
    void AddBOOM(Qt3DCore::QEntity *rootEntity, QVector3D pos, int i);

public slots:
    /**
     * \brief Sprawdza czy można dodać fajerwerk na scenę i wywołuje metodę dodającą.
     */
    void AddFirework();
    /**
     * \brief Dodaje fajerwerk na zdefiniowaną pozycję.
     */
    void AddFireworkDefPos();
    /**
     * \brief Aktualizuje wszystkie obiekty znajdujące się na scenie.
     */
    void update();
    /**
     * \brief Utrzymuje stałą liczbę fajerwerków na scenie.
     */
    void AUTO_MODE();
    /**
     * \brief Slot odbierający liczbę wpisaną w polu wartości X dla pozycji fajerwerka.
     */
    void DefPosX(const QString &newValue);
    /**
     * \brief Slot odbierający liczbę wpisaną w polu wartości Y dla pozycji fajerwerka.
     */
    void DefPosY(const QString &newValue);
    /**
     * \brief Slot odbierający liczbę wpisaną w polu wartości Z dla pozycji fajerwerka.
     */
    void DefPosZ(const QString &newValue);
    /**
     * \brief Ustawia maksymalną liczbę obiektów znajdujących się na scenie.
     */
    void MaxParticles(const QString &newValue);

private:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}

    Qt3DCore::QEntity *rootEntity;
    QPushButton *AddElementBoxT;
    QCheckBox *START;
    QCheckBox *Preset1T;
    //QList<QLineEdit*> *lineEditsListT;
    //lineEditsT[0] = new QLineEdit;
    //lineEditsT[1] = new QLineEdit;
    //lineEditsT[2] = new QLineEdit;
    list<Firework*> V_Fireworks;
    QString DefX;
    QString DefY;
    QString DefZ;
    QString maxP;
    int iter = 0;
};

#endif // SCENE_H
