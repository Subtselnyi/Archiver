#ifndef ARCHIVEDIALOG_H
#define ARCHIVEDIALOG_H
#pragma once
#include <QDialog>
#include <vector>
#include "SParch.h"
#include <string>
#include <sstream>

namespace Ui {
class ArchiveDialog;
}

class ArchiveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ArchiveDialog(vector<string>,QWidget *parent = 0);
    ~ArchiveDialog();
    vector <string> allPathes;
signals:
    void FilePathArchive(const QString &atr);

private slots:
    void on_ArchiveSearchButton_clicked();

    void on_ArchiveOkButton_clicked();

    void on_ArchiveCancelButton_clicked();

private:
    Ui::ArchiveDialog *ui;
};

#endif // ARCHIVEDIALOG_H
