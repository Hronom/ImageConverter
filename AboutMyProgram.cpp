#include "AboutMyProgram.h"
#include "ui_AboutMyProgram.h"
#include "GlobalDefinitions.h"

AboutMyProgram::AboutMyProgram(QWidget *xParent) : QDialog(xParent), mUI(new Ui::AboutMyProgram)
{
    mUI->setupUi(this);

    mUI->programName->setText(tr("��� ���������:") + " " + program_name);
    mUI->programVersion->setText(tr("������ ���������:") + " " + program_version);
    mUI->programSite->setText(tr("���� ���������:")+" <a href='http://hronom.github.com/ImageConverter/'>http://hronom.github.com/ImageConverter/</a>");

    mUI->programAuthor->setText(tr("�����:") + " Hronom");
    mUI->authorEmail->setText("Email: <a href='mailto:hronom@gmail.com'>hronom@gmail.com</a>");
    mUI->authorBlog->setText("Blog: <a href='http://hronom.blogspot.com/'>http://hronom.blogspot.com</a>");

    mNewVersionChecker = new NewVersionChecker(this);
    connect(mNewVersionChecker, SIGNAL(versionChecked(QString,QString)),this,SLOT(versionChecked(QString,QString)));
    connect(mNewVersionChecker, SIGNAL(versionNotChecked(QString)),this,SLOT(versionNotChecked(QString)));
}

AboutMyProgram::~AboutMyProgram()
{
    delete mUI;
}

void AboutMyProgram::versionChecked(QString xCurrentVersion, QString xDownloadLink)
{
    if(xCurrentVersion == program_version)
        mUI->actualVersion->setText(tr("� ��� ��������� ������ ���������"));
    else
    {
        QString xString;
        xString.append(tr("���������� ������:"));
        xString.append(" " + xCurrentVersion + " ");
        xString.append(" <a href='");
        xString.append(xDownloadLink);
        xString.append("'>");
        xString.append(tr("�������"));
        xString.append("</a>");

        mUI->actualVersion->setText(xString);
    }

    mUI->checkVersionButton->setDisabled(false);
}

void AboutMyProgram::versionNotChecked(QString xError)
{
    mUI->actualVersion->setText(tr("�� ������� ��������� ������� ����� ������ ���������.")+"<br>"+tr("������:")+" "+xError);
    mUI->checkVersionButton->setDisabled(false);
}

void AboutMyProgram::on_checkVersionButton_clicked()
{
    mUI->checkVersionButton->setDisabled(true);
    QString xLink = "https://github.com/downloads/Hronom/ImageConverter/currentVersion";
    mNewVersionChecker->checkVersion(xLink);
    mUI->actualVersion->setText(tr("�������� ������� ����� ������..."));
}
