#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include "Doc.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QString path = "C:/Users/ADMIN/Desktop/QT/beginWithJson1/data.json";
    QString path1 = "C:/Users/ADMIN/Desktop/QT/beginWithJson1/data1.json";
    Doc doc;
    doc.Read(path);
    doc.Write(path1);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
