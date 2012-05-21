#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QPainter>
#include <QPixmap>
#include <QFileDialog>
#include <QSvgGenerator>
#include <QMessageBox>
#include <QFileInfo>
#include <QFileIconProvider>
#include <QPushButton>
#include "AboutMyProgram.h"
#include <QGraphicsScene>
#include <qmath.h>
#include <QImage>

MainWindow::MainWindow(QWidget *xParent) : QMainWindow(xParent), mUI(new Ui::MainWindow)
{
    mUI->setupUi(this);
    mUI->buttonBox->button(QDialogButtonBox::Apply)->setText(tr("Применить"));
    mUI->buttonBox->button(QDialogButtonBox::RestoreDefaults)->setText(tr("Восстановить значения по умолчанию"));

    QGraphicsScene *xGraphicsScene;
    xGraphicsScene = new QGraphicsScene(this);
    mUI->graphicsView->setScene(xGraphicsScene);

    mGraphicsPixmapItem = xGraphicsScene->addPixmap(QPixmap(":/main/ImageConverter.png"));

    mDefaultImageWidth = mGraphicsPixmapItem->pixmap().width();
    mDefaultImageHeight = mGraphicsPixmapItem->pixmap().height();

    mDifferenceWidthHeight = mDefaultImageWidth - mDefaultImageHeight;

    mUI->Width->setValue(mDefaultImageWidth);
    mUI->Height->setValue(mDefaultImageHeight);
}

MainWindow::~MainWindow()
{
    delete mUI;
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString xOpenFilePath = QFileDialog::getOpenFileName(this,
                                                         tr("Открыть файл"),
                                                         qApp->applicationDirPath(),
                                                         tr("Все файлы") + " (*.*)");
    if (xOpenFilePath.isEmpty()) return;

    QPixmap xPixmap(xOpenFilePath);
    if(xPixmap.isNull() == true)
    {
        QFileIconProvider xFileIconProvider;
        QIcon xIcon;
        xIcon = xFileIconProvider.icon(xOpenFilePath);
        xPixmap = xIcon.pixmap(257);
    }

    mGraphicsPixmapItem->setPixmap(xPixmap);

    mDefaultImageWidth = mGraphicsPixmapItem->pixmap().width();
    mDefaultImageHeight = mGraphicsPixmapItem->pixmap().height();

    mDifferenceWidthHeight = mDefaultImageWidth - mDefaultImageHeight;

    mUI->Width->setValue(mDefaultImageWidth);
    mUI->Height->setValue(mDefaultImageHeight);
}

void MainWindow::on_actionSave_Image_triggered()
{
    QString xSaveFilePath = QFileDialog::getSaveFileName(this,
                                                         tr("Сохранить файл"),
                                                         qApp->applicationDirPath(),
                                                         "SVG (*.svg);;BMP (*.bmp);;JPG (*.jpg);;JPEG (*.jpeg);;PNG (*.png);;PPM (*.ppm);;TIFF (*.tiff);;XBM (*.xbm);;XPM (*.xpm)");

    if (xSaveFilePath.isEmpty()) return;

    QFileInfo xSaveFileInfo(xSaveFilePath);
    if(xSaveFileInfo.completeSuffix() == "svg")
    {
        QRect xRectangle = QRect(0, 0, mGraphicsPixmapItem->pixmap().width(), mGraphicsPixmapItem->pixmap().height());

        QSvgGenerator xGenerator;
        xGenerator.setFileName(xSaveFilePath);
        xGenerator.setSize(xRectangle.size());
        xGenerator.setViewBox(xRectangle);

        QPainter xPainter;
        xPainter.begin(&xGenerator);
        xPainter.drawPixmap(xRectangle, mGraphicsPixmapItem->pixmap());
        xPainter.end();
    }
    else
    {
        if(xSaveFileInfo.completeSuffix() == "png")
            mGraphicsPixmapItem->pixmap().save(xSaveFilePath);
        else
        {
            int xCurrentPixmapWidth = mGraphicsPixmapItem->pixmap().width();
            int xCurrentPixmapHeight = mGraphicsPixmapItem->pixmap().height();

            QRect xRectangle = QRect(0, 0, xCurrentPixmapWidth, xCurrentPixmapHeight);

            QPixmap xTempPixmap(xCurrentPixmapWidth, xCurrentPixmapHeight);
            xTempPixmap.fill(Qt::white);

            QPainter xPainter;
            xPainter.begin(&xTempPixmap);
            xPainter.drawPixmap(xRectangle, mGraphicsPixmapItem->pixmap());
            xPainter.end();

            xTempPixmap.save(xSaveFilePath);
        }
    }
}

void MainWindow::on_actionAbout_Program_triggered()
{
    AboutMyProgram *xAboutMyProgram;
    xAboutMyProgram = new AboutMyProgram(this);
    xAboutMyProgram->setAttribute(Qt::WA_DeleteOnClose, true);
    xAboutMyProgram->show();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    qApp->aboutQt();
}

void MainWindow::on_Width_valueChanged(int xValue)
{
    if(mUI->Proportion->checkState() == Qt::Checked && mUI->Width->hasFocus() == true)
        mUI->Height->setValue(xValue - mDifferenceWidthHeight);
}

void MainWindow::on_Height_valueChanged(int xValue)
{
    if(mUI->Proportion->checkState() == Qt::Checked && mUI->Height->hasFocus() == true)
        mUI->Width->setValue(xValue + mDifferenceWidthHeight);
}

void MainWindow::on_buttonBox_clicked(QAbstractButton *button)
{
    if(mUI->buttonBox->standardButton(button) == QDialogButtonBox::Apply)
    {
        mGraphicsPixmapItem->setPixmap(mGraphicsPixmapItem->pixmap().scaled(mUI->Width->value(), mUI->Height->value()));
        mDefaultImageWidth = mGraphicsPixmapItem->pixmap().width();
        mDefaultImageHeight = mGraphicsPixmapItem->pixmap().height();
        mDifferenceWidthHeight = mDefaultImageWidth - mDefaultImageHeight;
    }
    if(mUI->buttonBox->standardButton(button) == QDialogButtonBox::RestoreDefaults)
    {
        mUI->Width->setValue(mDefaultImageWidth);
        mUI->Height->setValue(mDefaultImageHeight);
        mUI->Proportion->setChecked(false);
    }
}

void MainWindow::on_Proportion_clicked()
{
    if(mUI->Proportion->checkState() == Qt::Checked)
    {
        mUI->Width->setValue(mDefaultImageWidth);
        mUI->Height->setValue(mDefaultImageHeight);
    }
}

void MainWindow::on_zoominButton_clicked()
{
    mUI->zoomSlider->setValue(mUI->zoomSlider->value()+1);
}

void MainWindow::on_zoomoutButton_clicked()
{
    mUI->zoomSlider->setValue(mUI->zoomSlider->value()-1);
}

void MainWindow::on_zoomSlider_valueChanged(int xValue)
{
    qreal xScale = qPow(qreal(2), (xValue - 250) / qreal(50));

    QMatrix xMatrix;
    xMatrix.scale(xScale, xScale);

    mUI->graphicsView->setMatrix(xMatrix);
}
