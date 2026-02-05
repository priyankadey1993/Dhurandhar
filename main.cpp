#include <QGuiApplication>
#include <QQmlApplicationEngine>
 #include <QQmlContext>
#include<GameController.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    GameController gameController;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("gameController", &gameController);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); },
                     Qt::QueuedConnection);
    engine.loadFromModule("dhurandhar", "Main");
   // engine.load(QUrl(QStringLiteral("Main.qml")));
    return app.exec();
}
