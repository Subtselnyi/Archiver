#ifndef DEARCHIVEDIALOG_H
#define DEARCHIVEDIALOG_H

#include <QDialog>

namespace Ui {
class DeArchiveDialog;
}

class DeArchiveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeArchiveDialog(QWidget *parent = 0);
    ~DeArchiveDialog();


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
