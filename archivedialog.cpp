#include "archivedialog.h"
#include "ui_archivedialog.h"
#include <QPushButton>
#include <QFileDialog>
#include <QCompleter>
#include <QFileSystemModel>
#include <QMessageBox>
#include "progressbardialog.h"

ArchiveDialog::ArchiveDialog(QString allPathes,QWidget *parent) :
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

    bool flag=false;
    BHuffman * hf = new BHuffman();
    std::string Pathes = allPathes.toUtf8().constData();
    std::string where = ui->ArchiveLineEdit->text().toUtf8().constData();

    flag =   hf->Compression(Pathes,where);

    if (flag){
        close();
        QMessageBox Msgbox;
            Msgbox.setText("Files succesfully archived");
            Msgbox.exec();
    }

}

void ArchiveDialog::on_ArchiveCancelButton_clicked()
{
    close();
}
