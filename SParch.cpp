#include "SParch.h"
#include <vector>
#include <iostream>
#include <QDebug>
#include <QMessageBox>
using namespace std;

SParch::SParch() {
    ar = new Archiver();
    bH = new BHuffman();
}

SParch::~SParch() { }

void SParch::Compression(vector<string> files, string pathArch) {

    vector<string> compressedFiles;

    for (vector<string>::iterator it = files.begin(); it != files.end(); ++it) {
         compressedFiles.push_back(bH->Compression(*(it),fileSize));
    }
    ar->Compression(compressedFiles, pathArch);
    DeleteFiles(compressedFiles);
}

void SParch::DeleteFiles(vector<string> files) {
    for (vector<string>::iterator it = files.begin(); it != files.end(); ++it) {
        string fileName = *(it);
        remove(fileName.c_str());
    }
}

void SParch::Decompression(string cFilePath, string dFilePath) {
    vector<string> cFiles;
    QString strTest = QString::fromStdString(cFilePath);
    qInfo()<<"WE ARE"<<strTest;
    QString strTest1 = QString::fromStdString(dFilePath);
    qInfo()<<"WE ARE"<<strTest1;
    double progressStep=0;
    int progressCount=0;
    std::string fileTry = dFilePath + "file.txt";
    FILE *f = fopen(fileTry.c_str(),"w");
    if (!f)
    {
        QMessageBox Msgbox;
        Msgbox.setText("You Entered non valid Path.\n Please try again.");
        Msgbox.exec();
        return;
    }
    else{
    fclose(f);
    remove(fileTry.c_str());
    ProgressBarDialog *wnd5 = new ProgressBarDialog();
    wnd5->show();
    cFiles = ar->Decompression(cFilePath, dFilePath);
    for (vector<string>::iterator it = cFiles.begin(); it != cFiles.end(); ++it) {
        string filePath = *(it);
        cout << "Compressed files: " << endl;
        cout << filePath << endl;
        int l_pos = filePath.rfind("\\");
        int d_pos = filePath.rfind(".");
        string fileName = filePath.substr(l_pos + 1, (d_pos - l_pos - 1));
        string dFileName = dFilePath + fileName;
        cout << "Decompressed files: " << endl;
        cout << dFileName << endl;

        progressStep = 1/ar->archFileSiz;
        compress = fileSize/(ar->archFileSiz);
        //progressCount+=50;
        //wnd5->on_progressBar_valueChanged(progressCount);
        bH->Decompression(filePath, dFilePath + fileName,progressStep);
    }
    wnd5->close();
    DeleteFiles(cFiles);
    QMessageBox Msgbox;
           Msgbox.setText("Files succesfully dearchived");
           Msgbox.exec();
    }
}


