#include <QGuiApplication>

#include "firework.h"
#include "scene.h"
#include "canvas.h"

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



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Canvas *canvas = new Canvas();
    canvas->Create();

    return app.exec();

}
