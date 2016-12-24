#include "archivedialog.h"
#include "ui_archivedialog.h"
#include <QPushButton>
#include <QFileDialog>
#include <QCompleter>
#include <QFileSystemModel>

ArchiveDialog::ArchiveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArchiveDialog)
{
    ui->setupUi(this);
    QCompleter *cmpt;
    QFileSystemModel *model = new QFileSystemModel(this);
    cmpt = new QCompleter(model,this);
    model->setRootPath(QDir::rootPath());
    ui->ArchiveLineEdit->setCompleter(cmpt);
}

ArchiveDialog::~ArchiveDialog()
{
    delete ui;
}

void ArchiveDialog::on_ArchiveSearchButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("File Path (SP-Archiver)"),
                "C://",
                "All files (*)"
                );
    ui->ArchiveLineEdit->setText(fileName);
}

void ArchiveDialog::on_ArchiveOkButton_clicked()
{
    emit FilePathArchive(ui->ArchiveLineEdit->text());
    close();
}

void ArchiveDialog::on_ArchiveCancelButton_clicked()
{
    close();
}