#include <QtGui/QApplication>
#include <QTextCodec>
#include <QLocale>
#include <QTranslator>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));//установка нужной кодировки
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));//установка нужной кодировки
    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));//установка нужной кодировки для Tr

    QApplication xApp(argc, argv);
    xApp.setApplicationName("ImageConverter");
    xApp.setApplicationVersion("0.0.1");
    QApplication::addLibraryPath(QApplication::applicationDirPath() + "/plugins");

    QString xLocale = QLocale::system().name();
    QTranslator xTranslator;
    xTranslator.load(QString("ImageConverter_") + xLocale);
    xApp.installTranslator(&xTranslator);

    MainWindow xMainWindow;
    xMainWindow.show();

    return xApp.exec();
}
