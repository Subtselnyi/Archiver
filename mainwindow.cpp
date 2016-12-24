#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include "addfiledialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    ui->textBrowser->setText(filePath);
}
