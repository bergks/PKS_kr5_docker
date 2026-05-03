#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "ArrayModel.h"
#include "SortingController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ArrayModel>("SortVisualizer", 1, 0, "ArrayModel");
    qmlRegisterType<SortingController>("SortVisualizer", 1, 0, "SortingController");

    ArrayModel arrayModel;
    SortingController controller(&arrayModel);
    controller.selectAlgorithm("Пузырёк");

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("arrayModel", &arrayModel);
    engine.rootContext()->setContextProperty("controller", &controller);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("sort_visualizer", "Main");

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
