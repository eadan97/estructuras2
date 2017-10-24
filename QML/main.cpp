#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "backend.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<BackEnd>("progra2",1,0,"BackEnd");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/StartDialog.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
