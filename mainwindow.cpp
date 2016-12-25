#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include "addfiledialog.h"
#include "settingsdialog.h"
#include "archivedialog.h"
#include "dearchivedialog.h"
#include <QWidget>
#include <QDebug>
#include <QDragEnterEvent>
#include <QMimeData>

#include "writeread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAdd_file_triggered()
{
    AddFileDialog *wnd1 = new AddFileDialog(this);
    wnd1->show();

    connect(wnd1,SIGNAL(FilePath(QString)),this,SLOT(AddFile(QString)));



}

void MainWindow::AddFile(const QString &filePath)
{
    ui->listWidget->addItem(filePath);
}



void MainWindow::on_actionDelete_file_triggered()
{
    delete ui->listWidget->currentItem();
}

void  MainWindow::dragEnterEvent(QDragEnterEvent * event)
{
    event->accept();
}

void  MainWindow::dragLeaveEvent(QDragLeaveEvent * event)
{
    event->accept();
}

void  MainWindow::dragMoveEvent(QDragMoveEvent * event)
{
    event->accept();
}

void  MainWindow::dropEvent(QDropEvent * event)
{
    QString numArch;
    QList<QUrl> urls;
    QList<QUrl>::Iterator i;
    urls = event->mimeData()->urls();
    for(i=urls.begin(); i!=urls.end(); ++i)
    {
        numArch = i->path();
        ui->listWidget->addItem(numArch);
    }

}

void MainWindow::on_actionDelete_All_triggered()
{
    ui->listWidget->clear();
}

void MainWindow::on_actionSettings_triggered()
{
    SettingsDialog *wnd2 = new SettingsDialog(setted,this);
    wnd2->show();

    connect(wnd2,SIGNAL(CheckBoxes(int)),this,SLOT(SettingsCheckBoxes(int)));

}

void MainWindow::SettingsCheckBoxes(const int code)
{
    setted = code;
    QString s = QString::number(code);
     ui->listWidget->addItem(s);
}


void MainWindow::on_ArchiveButton_clicked()
{
    QString str = "";
    for(int i = 0; i < ui->listWidget->count(); ++i)
    {
        QListWidgetItem* item = ui->listWidget->item(i);
        str+=item->text();
    }
    ArchiveDialog *wnd3 = new ArchiveDialog(str,this);
    wnd3->show();

    connect(wnd3,SIGNAL(FilePathArchive(QString)),this,SLOT(GetPathArchive(QString)));

}

void MainWindow::GetPathArchive(const QString &filePath)
{
    ui->listWidget->addItem(filePath);
}

void MainWindow::on_DeArchiveButton_clicked()
{
    DeArchiveDialog *wnd4 = new DeArchiveDialog(this);
    wnd4->show();

    connect(wnd4,SIGNAL(FilePathDeArchive(QString)),this,SLOT(GetPathDeArchive(QString)));
}

void MainWindow::GetPathDeArchive(const QString &filePath)
{
    ui->listWidget->addItem(filePath);
}
