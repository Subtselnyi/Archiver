#ifndef DEARCHIVEDIALOG_H
#define DEARCHIVEDIALOG_H
#pragma once
#include <QDialog>
#include <vector>
#include "SParch.h"
#include <string>
#include <sstream>

namespace Ui {
class DeArchiveDialog;
}

class DeArchiveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeArchiveDialog(string,QWidget *parent = 0);
    ~DeArchiveDialog();
     string file="";
     double compress;

signals:
    void FilePathDeArchive(const QString &atr);

private slots:
    void on_DeArchiveSearchButton_clicked();

    void on_DeArchiveOkButton_clicked();

    void on_DeArchiveCancelButton_clicked();

private:
    Ui::DeArchiveDialog *ui;
};

#endif // DEARCHIVEDIALOG_H
