#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("qstudiomdl");
    QCoreApplication::setOrganizationName("arbtttrn6");
    QLocale systemLocale = QLocale::system();
    QTranslator translator;
    QString translationFileName = QCoreApplication::applicationName() + "_" + systemLocale.name() + ".qm";
    if (QFile::exists(translationFileName)) {
        translator.load(translationFileName);
        a.installTranslator(&translator);
    } else {
        translator.load(QCoreApplication::applicationName() + "_eo.qm");
        a.installTranslator(&translator);
    }

    MainWindow w;
    w.show();
    return a.exec();
}
