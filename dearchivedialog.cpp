#include "dearchivedialog.h"
#include "ui_dearchivedialog.h"
#include <QPushButton>
#include <QFileDialog>
#include <QCompleter>
#include <QFileSystemModel>

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
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("File Path (SP-Archiver)"),
                "C://",
                "All files (*)"
                );
    ui->DeArchiveLineEdit->setText(fileName);
}

void DeArchiveDialog::on_DeArchiveOkButton_clicked()
{
    emit FilePathDeArchive(ui->DeArchiveLineEdit->text());
    close();
}

void DeArchiveDialog::on_DeArchiveCancelButton_clicked()
{
    close();
}
