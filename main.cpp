#include <QtGui/QApplication>
#include <QTextCodec>
#include <QLocale>
#include <QTranslator>
#include "MainWindow.h"
#include <GlobalDefinitions.h>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));//установка нужной кодировки
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));//установка нужной кодировки
    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));//установка нужной кодировки для Tr

    QApplication xApp(argc, argv);
    xApp.setApplicationName(program_name);
    xApp.setApplicationVersion(QString::number(MajorVer)+"."+QString::number(MinorVer)+"."+QString::number(RevisVer));
    QApplication::addLibraryPath(QApplication::applicationDirPath() + "/plugins");

    QString xLocale = QLocale::system().name();
    QTranslator xTranslator;
    xTranslator.load(QString("ImageConverter_") + xLocale);
    xApp.installTranslator(&xTranslator);

    MainWindow xMainWindow;
    xMainWindow.show();

    return xApp.exec();
}
