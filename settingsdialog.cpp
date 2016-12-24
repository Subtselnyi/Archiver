#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->SettingsMusicCheckBox->setChecked(true);
    ui->SettingsVideoCheckBox->setChecked(true);
    ui->SettingsPasswordCheckBox->setChecked(true);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_SettingsOkButton_clicked()
{
    code=0;
    if (ui->SettingsMusicCheckBox->isChecked())
    {
        code+=100;
    }
    if (ui->SettingsVideoCheckBox->isChecked())
    {
        code+=10;
    }
    if (ui->SettingsPasswordCheckBox->isChecked())
    {
        code+=1;
    }
    emit CheckBoxes(code);
    close();
}

void SettingsDialog::on_SettingsCancelButton_clicked()
{
    close();
}
