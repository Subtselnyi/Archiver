#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(const int rules,QWidget *parent = 0);
    ~SettingsDialog();
    int code=0;

private slots:
    void on_SettingsOkButton_clicked();

    void on_SettingsCancelButton_clicked();
signals:
    void CheckBoxes(const int code);

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
