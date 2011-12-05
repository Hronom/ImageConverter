#ifndef ABOUTMYPROGRAM_H
#define ABOUTMYPROGRAM_H

#include <QDialog>
#include "NewVersionChecker.h"

namespace Ui {
class AboutMyProgram;
}

class AboutMyProgram : public QDialog
{
    Q_OBJECT
private:
    Ui::AboutMyProgram *mUI;

    NewVersionChecker *mNewVersionChecker;

public:
    AboutMyProgram(QWidget *xParent = 0);
    ~AboutMyProgram();

private slots:
    void versionChecked(QString xCurrentVersion, QString xDownloadLink);
    void versionNotChecked(QString xError);
    void on_checkVersionButton_clicked();
};

#endif // ABOUTMYPROGRAM_H
