#ifndef ARCHIVEDIALOG_H
#define ARCHIVEDIALOG_H

#include <QDialog>

#include "bhuffman.h"

namespace Ui {
class ArchiveDialog;
}

class ArchiveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ArchiveDialog(QString,QWidget *parent = 0);
    ~ArchiveDialog();
    QString allPathes;
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
