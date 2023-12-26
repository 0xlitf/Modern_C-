#define USING_QTWIDGET

#ifdef USING_QTWIDGET

#include <QApplication>
#include <QDebug>
#include <QQmlContext>
#include <QSysInfo>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include <QWebEngineView>
#include <iostream>
#include <QStandardItemModel>
#include <QTreeView>
#include "tinyxml2.h"
#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MainWindow m;
    m.show();

    //    QWebEngineView view;
    //    view.setMinimumSize(1366, 900);

    //    auto settings = view.page()->settings();

    //    settings->setAttribute(QWebEngineSettings::ShowScrollBars, true);
    //    settings->setAttribute(QWebEngineSettings::WebGLEnabled, true);
    //    settings->setAttribute(QWebEngineSettings::ScrollAnimatorEnabled, true);

    //    view.load(QUrl("https://verytoolz.com/xml-parser.html"));

    //    QObject::connect(&view, &QWebEngineView::loadFinished, [&]() {
    //        qDebug() << "QWebEngineView::loadFinished";
    //    });

    //    view.show();

    return app.exec();
}

#else

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char* argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() {
            QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load("qrc:/qml/Main.qml");

    return app.exec();
}

#endif
