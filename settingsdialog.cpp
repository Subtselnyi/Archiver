#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(const int rules,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    if (rules>=100)
    ui->SettingsMusicCheckBox->setChecked(true);
    if (rules%100>=10)
    ui->SettingsVideoCheckBox->setChecked(true);
   // if (rules%2!=0)
    //ui->SettingsPasswordCheckBox->setChecked(true);
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
    /*if (ui->SettingsPasswordCheckBox->isChecked())
    {
        code+=1;
    }*/
    emit CheckBoxes(code);
    close();
}

void SettingsDialog::on_SettingsCancelButton_clicked()
{
    close();
}
