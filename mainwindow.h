#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
     void  dragEnterEvent(QDragEnterEvent * event);
     void  dragLeaveEvent(QDragLeaveEvent * event);
     void  dragMoveEvent(QDragMoveEvent * event);
     void  dropEvent(QDropEvent * event);

private slots:
    void on_actionAdd_file_triggered();
    void AddFile(const QString &filePath);
    void SettingsCheckBoxes(const int code);
    void on_actionDelete_file_triggered();

    void on_actionDelete_All_triggered();

    void on_actionSettings_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
