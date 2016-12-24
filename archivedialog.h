#ifndef ARCHIVEDIALOG_H
#define ARCHIVEDIALOG_H

#include <QDialog>

namespace Ui {
class ArchiveDialog;
}

class ArchiveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ArchiveDialog(QWidget *parent = 0);
    ~ArchiveDialog();

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
