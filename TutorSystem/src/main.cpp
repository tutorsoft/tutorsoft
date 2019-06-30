#pragma execution_character_set("utf-8")
#include "mainwidget.h"
#include <QApplication>

#include <QDesktopWidget>
#include <QTextCodec>
#include <QProcess>
#include <QFontDatabase>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QIcon>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    a.setWindowIcon(QIcon(":/main.ico"));

    QString qssFile = ":/qss/lightgray.css";
    QFile file(qssFile);

    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
    MainWidget w;
    w.show();
    return a.exec();
}
