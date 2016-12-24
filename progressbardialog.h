#ifndef PROGRESSBARDIALOG_H
#define PROGRESSBARDIALOG_H

#include <QDialog>

namespace Ui {
class ProgressBarDialog;
}

class ProgressBarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressBarDialog(QWidget *parent = 0);
    ~ProgressBarDialog();

public slots:


    void on_progressBar_valueChanged(int value);

private:
    Ui::ProgressBarDialog *ui;
};

#endif // PROGRESSBARDIALOG_H
