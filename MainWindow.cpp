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

MainWindow::MainWindow(QWidget *xParent) : QMainWindow(xParent), mUI(new Ui::MainWindow)
{
    mUI->setupUi(this);
    mUI->buttonBox->button(QDialogButtonBox::Apply)->setText(tr("Применить"));
    mUI->buttonBox->button(QDialogButtonBox::RestoreDefaults)->setText(tr("Восстановить значения по умолчанию"));
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

    mUI->Image->setPixmap(xPixmap);

    mDefaultImageWidth = mUI->Image->pixmap()->width();
    mDefaultImageHeight = mUI->Image->pixmap()->height();
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
        QRect xRectangle = QRect(0, 0, mUI->Width->value(), mUI->Height->value());

        QSvgGenerator xGenerator;
        xGenerator.setFileName(xSaveFilePath);
        xGenerator.setSize(xRectangle.size());
        xGenerator.setViewBox(xRectangle);

        QPainter xPainter;
        xPainter.begin(&xGenerator);
        xPainter.drawPixmap(xRectangle, *mUI->Image->pixmap());
        xPainter.end();
    }
    else
        mUI->Image->pixmap()->save(xSaveFilePath);
}

void MainWindow::on_actionAbout_Program_triggered()
{
    QString xString;
    xString.append("<p><b>Image Converter 0.0.1</b></p>");

    xString.append("<p>");
    xString.append(tr("Сайт программы:"));
    xString.append(" <a href='http://hronom.github.com/ImageConverter/'>http://hronom.github.com/ImageConverter</a>");
    xString.append("</p>");

    xString.append("<p>");
    xString.append(tr("Автор:"));
    xString.append(" Hronom");
    xString.append("</p>");

    xString.append("<p> Email: <a href='mailto:hronom@gmail.com'>hronom@gmail.com</a></p>");
    xString.append("<p> Blog: <a href='http://hronom.blogspot.com/'>http://hronom.blogspot.com</a></p>");

    QMessageBox::about(this, tr("О программе"), xString);
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    qApp->aboutQt();
}

void MainWindow::on_Width_valueChanged(int xValue)
{
    if(mUI->Proportion->checkState() == Qt::Checked && mUI->Width->hasFocus() == true && mUI->Image->pixmap() != NULL)
    {
        int xDifWH;
        xDifWH = mUI->Image->pixmap()->width() - mUI->Image->pixmap()->height();
        mUI->Height->setValue(mUI->Width->value() - xDifWH);
    }
}

void MainWindow::on_Height_valueChanged(int xValue)
{
    if(mUI->Proportion->checkState() == Qt::Checked && mUI->Height->hasFocus() == true && mUI->Image->pixmap() != NULL)
    {
        int xDifWH;
        xDifWH = mUI->Image->pixmap()->width() - mUI->Image->pixmap()->height();
        mUI->Width->setValue(xDifWH + mUI->Height->value());
    }
}

void MainWindow::on_buttonBox_clicked(QAbstractButton *button)
{
    if(mUI->Image->pixmap() != NULL)
    {
        if(mUI->buttonBox->standardButton(button) == QDialogButtonBox::Apply)
        {
            mUI->Image->setPixmap(mUI->Image->pixmap()->scaled(mUI->Width->value(), mUI->Height->value()));
        }
        if(mUI->buttonBox->standardButton(button) == QDialogButtonBox::RestoreDefaults)
        {
            mUI->Width->setValue(mDefaultImageWidth);
            mUI->Height->setValue(mDefaultImageHeight);
            mUI->Proportion->setChecked(false);
            mUI->Image->setPixmap(mUI->Image->pixmap()->scaled(mDefaultImageWidth, mDefaultImageHeight));
        }
    }
}
