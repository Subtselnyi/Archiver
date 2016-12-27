#include "dearchivedialog.h"
#include "ui_dearchivedialog.h"
#include <QPushButton>
#include <QFileDialog>
#include <QCompleter>
#include <QListView>
#include <QDebug>
#include <QMessageBox>
#include <QTreeView>
#include <QFileSystemModel>


DeArchiveDialog::DeArchiveDialog(string file,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeArchiveDialog)
{
    ui->setupUi(this);
    this->file = file;
    QCompleter *cmpt;
    QFileSystemModel *model = new QFileSystemModel(this);
    cmpt = new QCompleter(model,this);
    model->setRootPath(QDir::rootPath());
    ui->DeArchiveLineEdit->setCompleter(cmpt);
}

DeArchiveDialog::~DeArchiveDialog()
{
    delete ui;
}

void DeArchiveDialog::on_DeArchiveSearchButton_clicked()
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

    ui->DeArchiveLineEdit->setText(fileName);

}

void DeArchiveDialog::on_DeArchiveOkButton_clicked()
{
    //emit FilePathDeArchive(ui->DeArchiveLineEdit->text());
   /* ProgressBarDialog *wnd5 = new ProgressBarDialog(this);
    wnd5->show();*/
    /*for(int i=0; i<90;i++){
    wnd5->on_progressBar_valueChanged(i);
    }*/
    if (ui->DeArchiveLineEdit->text()!=""){
        SParch * arch = new SParch();


        std::string strFilesLocation = ui->DeArchiveLineEdit->text().toUtf8().constData();

        std::istringstream iss(strFilesLocation);
        std::string token;
        std::string newStrFilesLocation;
        while (std::getline(iss, token, '/'))
        {
            newStrFilesLocation+=token +"\\";
        }
        strFilesLocation=newStrFilesLocation;

        std::istringstream iss1(file);
        std::string newStrFile;
        while (std::getline(iss1, token, '/'))
        {
            newStrFile+=token +"\\";
        }
        file=newStrFile.substr(0,newStrFile.length()-1);

        QString strfilesmt = QString::fromStdString(file);
        qInfo()<<"file to dearchive"<<strfilesmt;

        QString strfileloc = QString::fromStdString(strFilesLocation);
        qInfo()<<"PAth for dearchivation"<<strfileloc;

        arch->Decompression(file, strFilesLocation);
        compress = arch->compress;
        close();


    }
    else
    {
        QMessageBox Msgbox;
        Msgbox.setText("Please enter folder path");
        Msgbox.exec();
    }

}

void DeArchiveDialog::on_DeArchiveCancelButton_clicked()
{
    close();
}
