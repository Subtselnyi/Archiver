#include "progressbardialog.h"
#include "ui_progressbardialog.h"

ProgressBarDialog::ProgressBarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressBarDialog)
{
    ui->setupUi(this);

}

ProgressBarDialog::~ProgressBarDialog()
{
    delete ui;
}



void ProgressBarDialog::on_progressBar_valueChanged(int value)
{

    ui->progressBar->setValue(value);
    if (value==100)
        close();
}
