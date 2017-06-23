#include <QGuiApplication>

#include "firework.h"
#include "scene.h"
#include "canvas.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Canvas *canvas = new Canvas();
    canvas->Create();

    return app.exec();

}
