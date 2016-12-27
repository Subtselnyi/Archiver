#include "addfiledialog.h"
#include "ui_addfiledialog.h"
#include <QPushButton>
#include <QFileDialog>
#include <QCompleter>
#include <QFileSystemModel>
#include <QMessageBox>

AddFileDialog::AddFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFileDialog)
{
    ui->setupUi(this);
    QCompleter *cmpt;
    QFileSystemModel *model = new QFileSystemModel(this);
    cmpt = new QCompleter(model,this);
    model->setRootPath(QDir::rootPath());
    ui->AddFileLineEdit->setCompleter(cmpt);
    connect(ui->AddFileOkButton,SIGNAL(clicked()),SLOT(okClicked()));
    connect(ui->AddFileCancelButton,SIGNAL(clicked()),SLOT(close()));
}

void AddFileDialog::okClicked()
{
    if (ui->AddFileLineEdit->text()!=""){
    std::string fileTry = ui->AddFileLineEdit->text().toUtf8().constData();
    FILE *f = fopen(fileTry.c_str(),"rb");
    if(f){
    emit FilePath(ui->AddFileLineEdit->text());
    close();
    }
    else{
        QMessageBox Msgbox;
        Msgbox.setText("Enter the valid file");
        Msgbox.exec();
    }
    fclose(f);
    }
    else
    {
        QMessageBox Msgbox;
        Msgbox.setText("Please enter file path");
        Msgbox.exec();
    }
}

AddFileDialog::~AddFileDialog()
{
    delete ui;
}

void AddFileDialog::on_AddFileSearchButton_clicked()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(
                this,
                tr("Add File (SP-Archiver)"),
                QDir::currentPath(),
                "All files (*.*)"
                );
    QString fileName;
    if( !fileNames.isEmpty() )
    {
        for (int i =0;i<fileNames.count();i++){
           fileName+=fileNames.at(i);
        }

    }
    ui->AddFileLineEdit->setText(fileName);

}
