#pragma once
#include <iostream>
#include <string>
#include <vector>


using namespace std;


class Archiver
{
    const int MAX_META = 3; // order
    vector<string> files;

    public:
        Archiver();
        virtual ~Archiver();

    string getFilesMetaData(vector<string> const& filesName);
    void Compression(vector<string> const& filesName, string archName);
    vector<string> Decompression(string, string);
    int archFileSiz;
    void getFilesName();
    string validateMeta(string);
};

