#include "addfiledialog.h"
#include "ui_addfiledialog.h"
#include <QPushButton>
#include <QFileDialog>

AddFileDialog::AddFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFileDialog)
{
    ui->setupUi(this);
    connect(ui->AddFileOkButton,SIGNAL(clicked()),SLOT(okClicked()));
    connect(ui->AddFileCancelButton,SIGNAL(clicked()),SLOT(close()));
}

void AddFileDialog::okClicked()
{
    emit FilePath(ui->AddFileLineEdit->text());
    close();
}

AddFileDialog::~AddFileDialog()
{
    delete ui;
}

void AddFileDialog::on_AddFileSearchButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Add File (SP-Archiver)"),
                "C://",
                "All files (*.*)"
                );
    ui->AddFileLineEdit->setText(fileName);

}