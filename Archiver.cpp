#include "Archiver.h"

#include <stdio.h>
#include <string.h>
#include <QDebug>
#include <QMessageBox>

Archiver::Archiver() { }
Archiver::~Archiver() { }


void Archiver::Compression(vector<string> const& filesPath, string archName) {
    //cout << "aaaaaaa";
    string metaData = getFilesMetaData(filesPath);
    //cout << metaData;
    metaData = validateMeta(metaData);

    char byte[1];
    FILE* cf = fopen( (archName).c_str(), "wb"); // create new Arc File
    fputs(metaData.c_str(), cf); // writte meta in Arc


    for (int i = 0; i < filesPath.size(); i++) {
        FILE* f = fopen(filesPath[i].c_str(), "rb");
        if(!f){
            break;
        }
        while(!feof(f)) {
            if( fread(byte, 1, 1, f) ) {
                fwrite(byte, 1, 1, cf);
                //cout << byte[0];
            }
        }
        cout << filesPath[i]<<" Добавлен в архив."<<endl;
        fclose(f);
    }
    fclose(cf);
}




string Archiver::getFilesMetaData(vector<string> const& filesPath) {

    string filesMetaData = "";

    for(int i = 0; i < filesPath.size(); i++) {
        FILE *f = fopen( (filesPath[i]).c_str(), "rb"); // c_str - string to char *
        if(!f) {
            break;
            //
        }

        fseek(f, 0, SEEK_END);
        int fileSize = ftell(f); // count bite from begin

        string strFileSize = to_string(fileSize);
        int l_pos = filesPath[i].rfind("\\");
        string fileName = filesPath[i].substr(l_pos + 1, filesPath[i].length());
        //cout << "file_name : " << fileName << endl;

        filesMetaData += strFileSize + " " + fileName + "|";
        fclose(f);
    }
    return filesMetaData;
}


vector<string> Archiver::Decompression(string nameArcFile, string pathFile) {
    vector<string> cFiles;

    FILE *arch = fopen(nameArcFile.c_str(),"rb"); // open Arch File
    fseek(arch, 0, SEEK_END);
    int fileSize = ftell(arch);
    archFileSiz=fileSize;
    fseek(arch, 0, SEEK_SET);
    QString strTest = QString::fromStdString(nameArcFile);
    qInfo()<<"WE ARE in Archiver"<<strTest;
    QString strTest3 = QString::fromStdString(pathFile);
    qInfo()<<"WE ARE in Archiver"<<strTest3;
    if (!arch)
    {
        QString strTest1 = QString::fromStdString(nameArcFile);
        qInfo()<<"WE cant open"<<strTest1;
    }
    char strSizeMeta[MAX_META];
    fread(strSizeMeta, 1, MAX_META, arch);
    int sizeMeta = atoi(strSizeMeta);
    cout << "sizeMeta: " << sizeMeta << endl;

    qInfo()<<"Archiver1";

    char*metaData = new  char[sizeMeta];
    fread(metaData, 1, sizeMeta + 1, arch);
    /*for (int i = 0; i < sizeMeta; i++) {
        cout << metaData[i] << endl;
    }*/
    metaData[sizeMeta] = '\0';
    cout << "MetaData: " << metaData << endl << endl;

    //fread(metaData, 1, 1, arch);
    vector<string> tokens; // "file_name file_size"
    char *tok = strtok(metaData, "|");
    int toks = 0;

    while(tok) {
        if( !strlen(tok) ) break;
        tokens.push_back(tok);
        tok = strtok(NULL, "|");
        toks++;
    }

    char byte[1];

    for (int i = 0; i < tokens.size(); i++) {
        string fileName = tokens[i].substr(tokens[i].find(" ") + 1, tokens[i].length());
        int sizeFile = atoi( tokens[i].substr(0, tokens[i].find(" ")).c_str() );
        cout << pathFile << fileName << endl;
        FILE* f = fopen((pathFile + fileName).c_str(), "wb");
        if (!f)
        {
            QMessageBox Msgbox;
            Msgbox.setText("You entered not valid folder.\nTry again");
            Msgbox.exec();

        }
        else{


        if (!f)
        {
            qInfo()<<"WE cant open pathfile";
        }
        cFiles.push_back(pathFile + fileName);
        while(sizeFile--) {
            if( fread(byte, 1, 1, arch) ) {
                fwrite(byte, 1, 1, f);
            }
        }
        }
        fclose(f);
    }
    qInfo()<<"Archiverend";
    return cFiles;
}


string Archiver::validateMeta(string metaData) {
    int sizeMetaData = metaData.length();
    string strSizeMeta = to_string( metaData.length() );
    if(strSizeMeta.length() > MAX_META) {
        cout << "Error" << endl;
    }

    while(strSizeMeta.length() < MAX_META) {
        strSizeMeta = "0" + strSizeMeta;
    }
    cout << "W meta: " << metaData << endl;
    cout << "W meta size: " << strSizeMeta << endl;
    return strSizeMeta + "|" + metaData;
}


void Archiver::getFilesName() {
    for(vector<string>::const_iterator file = files.begin(); file != files.end(); ++file) {
        cout << *file << endl;
    }
}
