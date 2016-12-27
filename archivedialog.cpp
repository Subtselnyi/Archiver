#include "archivedialog.h"
#include "ui_archivedialog.h"
#include <QPushButton>
#include <QFileDialog>
#include <QCompleter>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QDebug>

ArchiveDialog::ArchiveDialog(vector <string> allPathes,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArchiveDialog)
{
    ui->setupUi(this);
    this->allPathes = allPathes;
    QCompleter *cmpt;
    QFileSystemModel *model = new QFileSystemModel(this);
    cmpt = new QCompleter(model,this);
    model->setRootPath(QDir::rootPath());
    ui->ArchiveLineEdit->setCompleter(cmpt);
    QRegExp exp("[a-zA-Z0-9_-]{1,20}");
    ui->NameArchiveLineEdit->setValidator(new QRegExpValidator(exp,this));

}

ArchiveDialog::~ArchiveDialog()
{
    delete ui;
}

void ArchiveDialog::on_ArchiveSearchButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly);
    QString fileName = dialog.getExistingDirectory(
                this,
                tr("File Path (SP-Archiver)"),
                QDir::currentPath(),
                QFileDialog::DontResolveSymlinks
                );
    ui->ArchiveLineEdit->setText(fileName);
}

void ArchiveDialog::on_ArchiveOkButton_clicked()
{
    //emit FilePathArchive(ui->ArchiveLineEdit->text());
    QString arhivePath = ui->ArchiveLineEdit->text();
    QString arhiveName = ui->NameArchiveLineEdit->text();
    arhiveName+=".sp";
    bool flag=false;
    SParch * arch = new SParch();

    std::string strArchivePath = arhivePath.toUtf8().constData();
    std::string strArchiveName = arhiveName.toUtf8().constData();

        std::istringstream iss(strArchivePath);
        std::string token;
        std::string newStrArhcivePath;
        while (std::getline(iss, token, '/'))
        {
            newStrArhcivePath+=token +"\\";
        }
        newStrArhcivePath+=strArchiveName;


       for(int i=0; i<allPathes.size();i++)
       {
           std::istringstream iss(allPathes[i]);
           std::string token;
           std::string newAllPathesTemp;
           while (std::getline(iss, token, '/'))
           {
               newAllPathesTemp+=token +"\\";
           }
           newAllPathesTemp=newAllPathesTemp.substr(0,newAllPathesTemp.length()-1);
           allPathes[i]=newAllPathesTemp;

       }
       QString strvectors = QString::fromStdString(allPathes[0]);
       qInfo()<<strvectors;


    arch->Compression(allPathes, newStrArhcivePath);

   // flag =   hf->Compression(Pathes,where);

     close();
     QMessageBox Msgbox;
            Msgbox.setText("Files succesfully archived");
            Msgbox.exec();

}

void ArchiveDialog::on_ArchiveCancelButton_clicked()
{
    close();
}
