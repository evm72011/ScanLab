#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include "backend.h"

int main(int argc, char* argv[])
{
    QQuickStyle::setStyle("Basic");
    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/icons/app.svg"));

    QQmlApplicationEngine engine;

    Backend backend;
    engine.rootContext()->setContextProperty("backend", &backend);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("ScanLab", "Main");

    return app.exec();
}
