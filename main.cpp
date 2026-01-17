#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "control/episodescreencontrol.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<EpisodeScreenControl>("EpisodeScreenControl", 1, 0, "EpisodeScreenControl");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/rick-and-morty-ui/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
