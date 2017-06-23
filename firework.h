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

#include <random>
#include <math.h>

#include <QtOpenGL/QGLWidget>

#include <QtWidgets/QCheckBox>

#include <QGeometryRenderer>

/**
 * \brief Klasa Firework
 *
 * Klasa definiująca fajerwerki pojawiające się na scenie.
 *
 * \version alfa
 */
class Firework{

public:
    /**
     * \brief Konstruktor pojedynczego fajerwerka wystrzeliwanego w górę.
     *
     * \param rootEntity Przestrzeń w której zostaje stworzony obiekt
     * \param Preset1 Włącza predefiniowane zachowania obiektu
     */
    Firework(Qt3DCore::QEntity *rootEntity, QCheckBox *Preset1, QCheckBox *Preset2);
    /**
     * \brief Konstruktor fajerwerka z predefiniowaną pozycją przez użytkownika.
     *
     * \param rootEntity Przestrzeń w której zostaje stworzony obiekt
     * \param position Pozycja(x,y,z) w której ma się pojawić obiekt na scenie
     * \param Preset1 Włącza predefiniowane zachowania obiektu
     * \param boomed_t Okresla czy ma to być fajerwerk przed lub po wybuchu
     */
    Firework(Qt3DCore::QEntity *rootEntity, QVector3D position, QCheckBox *Preset1, QCheckBox *Preset2, bool boomed_t);
    /**
     * \brief Konstruktor "odłamków" po wybuchu fajerwerka.
     *
     * \param rootEntity Przestrzeń w której zostaje stworzony obiekt
     * \param posboomed Pozycja w którym fajerwerk wybuchł
     * \param Preset1 Włącza predefiniowane zachowania obiektu
     */
    Firework(Qt3DCore::QEntity *rootEntity, QVector3D posboomed, QCheckBox *Preset1, QCheckBox *Preset2);
    /**
     * \brief Dekonstruktor.
     */
    ~Firework();
    /**
     * \brief Usuwa poszczególne komponenty składające się na fajerwerk.
     */
    void destroy();
    /**
     * \brief Ustawia komponenty składające się na fajerwerk i odłamki.
     *
     * \param rootEntity Przestrzeń w której zostaje stworzony obiekt
     */
    void SetAndAdd(Qt3DCore::QEntity *rootEntity);
    /**
     * \brief Sprawdza czy nastąpił wybuch fajerwerka.
     *
     * \return Tak/Nie
     */
    bool CheckIfDead();
    /**
     * \brief Zwraca pozycję fajerwerka.
     *
     * \return Pozycja
     */
    QVector3D ReturnPosition();
    /**
     * \brief Nadaje przyspieszenie fajerwerkom.
     */
    void ApplyForce();
    /**
     * \brief Zwraca czas życia odłamków po wybuchu.
     *
     * \return Zwraca czas życia odłamków po wybuchu.
     */
    int ReturnLifespan();
    /**
     * \brief Sprawdza czy prędkość fajerwerka osiągnęła 0.
     *
     * \return Tak/Nie.
     */
    bool ReturnZeroVelocity();
    /**
     * \brief Tag oznaczający możliwość usunięcia odłamków ze sceny.
     *
     * \return Tak/Nie
     */
    bool CanIDelete();
    /**
     * \brief Tag oznaczający możliwość usunięcia fajerwerka ze sceny.
     *
     * \return Tak/Nie
     */
    bool CanIDeleteRoot();
    /**
     * \brief Zamiana zakresu 0-255 na 0-1.
     *
     * \return Liczba typu float z zakresu 0-1.
     */
    float map(int lifespan_t);
    /**
     * \brief Ciąg zadań do zrealizowania przez odłamki po aktywowaniu predefiniowanych zachowań nr 1.
     */
    void Preset1();
    /**
     * \brief Określa sposób poruszania sie przez odłamki po aktywowaniu predefiniowanych zachowań nr 1.
     */
    void moveP1a();
    /**
     * \brief Tag oznaczający, iż włączone predefiniowane zachowania mają dwie fazy(kolejny wybuch).
     *
     * \return Tak/Nie
     */
    bool ReturnphaseB();
    /**
     * \brief Określa normalny sposób poruszania się fajerwerków.
     *
     */
    void move();
    /**
     * \brief Wywołuje wszystkie konieczne metody konieczne do symulacji fajerwerków.
     *
     */
    void update();
    /**
     * \brief Określa normalny sposób poruszania się odłamków po wybuchu.
     *
     */
    void updateBOOM();
    /**
     * \brief Określa sposób poruszania się fajerwerków po aktywowaniu predefiniowanych zachowań  nr 2.
     *
     */
    void moveP2();

private:
    Qt3DCore::QEntity *m_sphereEntity;
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
    bool phaseB = true;

    //Kolor fajerwerkow
    int h_color;
    int s_color;
    int v_color;
    int a_color;

    std::random_device rd;     // only used once to initialise (seed) engine

    QCheckBox *temp_preset1;
    QCheckBox *temp_preset2;

};

#endif // FIREWORK_H
