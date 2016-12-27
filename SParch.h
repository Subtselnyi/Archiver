#pragma once
#include "Archiver.h"
#include "BHuffman.h"


class SParch // main class
{

    public:
        SParch();
        virtual ~SParch();
        void Compression(vector<string> files, string pathArch);
        void Decompression(string cFilePath, string dFilePath);
        void DeleteFiles(vector<string> files);
        int fileSize=0;
        double compress;
    private:
        Archiver* ar;
        BHuffman* bH;
};
