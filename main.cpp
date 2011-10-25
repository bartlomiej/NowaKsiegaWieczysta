#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    a.setApplicationName("Nowa Księga Wieczysta");
    a.setOrganizationName("Bartłomiej Cieślak");
    a.setOrganizationDomain("www.bartlomiej.cieslak.info.pl");
    a.setApplicationVersion("0.0.1");
    MainWindow w;
    w.show();

    return a.exec();
}
