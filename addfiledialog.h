#ifndef ADDFILEDIALOG_H
#define ADDFILEDIALOG_H

#include <QDialog>

namespace Ui {
class AddFileDialog;
}

class AddFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddFileDialog(QWidget *parent = 0);
    ~AddFileDialog();

private:
    Ui::AddFileDialog *ui;
signals:
    void FilePath(const QString &atr);
private slots:
    void okClicked();
    void on_AddFileSearchButton_clicked();
};

#endif // ADDFILEDIALOG_H
