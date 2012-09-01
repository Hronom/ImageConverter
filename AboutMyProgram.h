#ifndef ABOUTMYPROGRAM_H
#define ABOUTMYPROGRAM_H

#include <QDialog>
#include "VersionChecker.h"

namespace Ui {
class AboutMyProgram;
}

class AboutMyProgram : public QDialog
{
    Q_OBJECT
private:
    Ui::AboutMyProgram *mUI;

    VersionChecker *mVersionChecker;

public:
    AboutMyProgram(QWidget *xParent = 0);
    ~AboutMyProgram();

private slots:
    void newVersionAvailable(int xMajorVer, int xMinorVer, int xRevisVer, const QString &xDownloadLink);
    void newVersionNotAvailable();
    void errorHappened(QString xError);
    void on_checkVersionButton_clicked();
};

#endif // ABOUTMYPROGRAM_H
