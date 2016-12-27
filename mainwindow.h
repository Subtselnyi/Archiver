#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once
#include <QWidget>
#include <QMainWindow>
#include <vector>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int setted=0;
    double comress;


protected:
     void  dragEnterEvent(QDragEnterEvent * event);
     void  dragLeaveEvent(QDragLeaveEvent * event);
     void  dragMoveEvent(QDragMoveEvent * event);
     void  dropEvent(QDropEvent * event);

private slots:
    void on_actionAdd_file_triggered();
    void AddFile(const QString &filePath);
    void GetPathArchive(const QString &filePath);
    void GetPathDeArchive(const QString &filePath);
    void SettingsCheckBoxes(const int code);
    void on_actionDelete_file_triggered();

    void on_actionDelete_All_triggered();

    void on_actionSettings_triggered();

    void on_pushButton_clicked();

    void on_ArchiveButton_clicked();

    void on_DeArchiveButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
