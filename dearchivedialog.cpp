#include "dearchivedialog.h"
#include "ui_dearchivedialog.h"
#include <QPushButton>
#include <QFileDialog>
#include <QCompleter>
#include <QListView>
#include <QTreeView>
#include <QFileSystemModel>
#include "progressbardialog.h"

DeArchiveDialog::DeArchiveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeArchiveDialog)
{
    ui->setupUi(this);
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
    emit FilePathDeArchive(ui->DeArchiveLineEdit->text());
    ProgressBarDialog *wnd5 = new ProgressBarDialog(this);
    wnd5->show();
    for(int i=0; i<90;i++){
    wnd5->on_progressBar_valueChanged(i);
    }
    close();
}

void DeArchiveDialog::on_DeArchiveCancelButton_clicked()
{
    close();
}
