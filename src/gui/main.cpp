#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "../models/VisualizationModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Set application metadata
    app.setApplicationName("Algorithm Visualization Platform");
    app.setOrganizationName("AlgorithmViz");
    app.setOrganizationDomain("algorithviz.example.com");

    QQmlApplicationEngine engine;

    // Register C++ types
    qmlRegisterType<VisualizationModel>("AlgoViz", 1, 0, "VisualizationModel");

    const QUrl url(QStringLiteral("qrc:/qml/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
