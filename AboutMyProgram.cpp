#include "AboutMyProgram.h"
#include "ui_AboutMyProgram.h"
#include "GlobalDefinitions.h"

AboutMyProgram::AboutMyProgram(QWidget *xParent) : QDialog(xParent), mUI(new Ui::AboutMyProgram)
{
    mUI->setupUi(this);

    mUI->programName->setText(tr("Имя программы:") + " " + program_name);
    mUI->programVersion->setText(tr("Версия программы:") + " " + QString::number(MajorVer)+"."+QString::number(MinorVer)+"."+QString::number(RevisVer));
    mUI->programSite->setText(tr("Сайт программы:")+" <a href='http://hronom.github.com/ImageConverter/'>http://hronom.github.com/ImageConverter/</a>");

    mUI->programAuthor->setText(tr("Автор:") + " Hronom");
    mUI->authorEmail->setText("Email: <a href='mailto:hronom@gmail.com'>hronom@gmail.com</a>");
    mUI->authorBlog->setText("Blog: <a href='http://hronom.blogspot.com/'>http://hronom.blogspot.com</a>");

    mVersionChecker = new VersionChecker(MajorVer, MinorVer, RevisVer, "https://github.com/downloads/Hronom/ImageConverter/currentVersion", this);
    connect(mVersionChecker,
            SIGNAL(newVersionAvailable(int,int,int,QString)),
            this,
            SLOT(newVersionAvailable(int,int,int,QString)));
    connect(mVersionChecker,
            SIGNAL(newVersionNotAvailable()),
            this,
            SLOT(newVersionNotAvailable()));
    connect(mVersionChecker,
            SIGNAL(errorHappened(QString)),
            this,
            SLOT(errorHappened(QString)));
}

AboutMyProgram::~AboutMyProgram()
{
    delete mUI;
}

void AboutMyProgram::newVersionAvailable(int xMajorVer, int xMinorVer, int xRevisVer, const QString &xDownloadLink)
{
    QString xString;
    xString.append(tr("Актуальная версия: "));
    xString.append(QString::number(xMajorVer)+"."+QString::number(xMinorVer)+"."+QString::number(xRevisVer));
    xString.append(" <a href='");
    xString.append(xDownloadLink);
    xString.append("'>");
    xString.append(tr("скачать"));
    xString.append("</a>");

    mUI->actualVersion->setText(xString);
    mUI->checkVersionButton->setDisabled(false);
}

void AboutMyProgram::newVersionNotAvailable()
{
    mUI->actualVersion->setText(tr("У вас последняя версия программы"));
    mUI->checkVersionButton->setDisabled(false);
}

void AboutMyProgram::errorHappened(QString xError)
{
    mUI->actualVersion->setText(tr("Не удалось проверить наличие новой версии программы.")+"<br>"+tr("Ошибка:")+" "+xError);
    mUI->checkVersionButton->setDisabled(false);
}

void AboutMyProgram::on_checkVersionButton_clicked()
{
    mUI->checkVersionButton->setDisabled(true);
    mVersionChecker->checkVersion();
    mUI->actualVersion->setText(tr("Проверка наличия новой версии..."));
}
