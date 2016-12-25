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
    arhivePath += ui->NameArchiveLineEdit->text();
    arhivePath+=".sp";
    bool flag=false;
    BHuffman * hf = new BHuffman();
    std::string Pathes = allPathes.toUtf8().constData();
    std::string where = arhivePath.toUtf8().constData();

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
