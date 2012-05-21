#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GlobalDefinitions.h"
#include <QMainWindow>
#include <QAbstractButton>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *mUI;

    //QGraphicsScene *mGraphicsScene;
    QGraphicsPixmapItem *mGraphicsPixmapItem;

    int mDefaultImageWidth;
    int mDefaultImageHeight;
    int mDifferenceWidthHeight;

public:
    MainWindow(QWidget *xParent = 0);
    ~MainWindow();

private slots:
    void on_Height_valueChanged(int xValue);
    void on_Width_valueChanged(int xValue);
    void on_actionAbout_Qt_triggered();
    void on_actionAbout_Program_triggered();
    void on_actionSave_Image_triggered();
    void on_actionOpen_File_triggered();
    void on_buttonBox_clicked(QAbstractButton *button);
    void on_Proportion_clicked();
    void on_zoominButton_clicked();
    void on_zoomoutButton_clicked();
    void on_zoomSlider_valueChanged(int xValue);
};

#endif // MAINWINDOW_H
