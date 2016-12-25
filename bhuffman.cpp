#include "bhuffman.h"

#include <QDebug>
#include "progressbardialog.h"
BHuffman::BHuffman() {

}

BHuffman::~BHuffman() {

}

void outputBinarySymbolCode(BinarySymbolCode code);

bool BHuffman::Compression(string bFileName,string where) {
    QString str = QString::fromStdString(bFileName);
    qInfo()<<"FILES"<<str;
    ProgressBarDialog *wnd5 = new ProgressBarDialog();
    wnd5->show();
    wnd5->on_progressBar_valueChanged(0);
    qInfo() << "Compression";
    char byte[1];

    FILE *bf ;
    bf= fopen("G:\\Qt\\projects\\Archiver\\extra.txt", "r"); // open basic file


    if(!bf) {
        qInfo()<<"Problem bf";
        cout << "Error opening file!";
        return false;
    }


    fseek(bf, 0, SEEK_END);
    int bFileSize = ftell(bf); // count byte from begin

    fseek(bf, 0, SEEK_SET); // begin of file

    unsigned char* data = new unsigned char[bFileSize];
    int index = 0;
    while(!feof(bf)) {
        if( fread(byte, 1, 1, bf) ) {
            data[index] = byte[0];
            index++;
        }
    }

    cout <<"Initial Length: " << index << endl;
    qInfo() << "Initial Length:"<< index;
    int frequencies[UniqueSymbols] = {0};
    const unsigned char* ptr = data;

    int i = 0;
    while (i < bFileSize) {
        frequencies[(int)ptr[i]] += 1;
        i++;
    }

    i = 0;

    /*for (; i < 256; i++) {
        cout << i << " " << frequencies[i] << endl;
    }*/

    qInfo() << "New steps";
    BasicNode* root = BuildTree(frequencies);
    qInfo() << "some New steps";
    SymbolCodeMap codes;
    GenerateCodes(root, BinarySymbolCode(), codes);
    delete root;


    string huffmanTable = GetHuffmanTable(codes);
    cout << huffmanTable << endl << endl << endl;
    string nameFile = "G:\\Qt\\projects\\Archiver\\huffmanCom.bin";

    FILE* f = fopen( (nameFile).c_str(), "wb"); // create new File
    qInfo() << "NewFile crreated:";
    cout << "Compresed: " << huffmanTable.length() << endl; // 2869
    qInfo() << "Compresed: " << huffmanTable.length();
    const char* hfm_cstr = huffmanTable.c_str();
    for (int i = 0; i < huffmanTable.length(); i++) {
        byte[0] = hfm_cstr[i];
        fwrite(byte, 1, 1, f);
    }
    //cout << "Compresed: " << i << endl;
    wnd5->on_progressBar_valueChanged(50);
    byte[0] = 0;
    int count_ = 0;
    for (int i = 0; i < bFileSize; i++) {
        vector<bool> code = codes[data[i]];
        for (int n = 0; n < code.size(); n++) {
            byte[0] = byte[0] | code[n] << (7 - count_);
            count_++;
            if (count_ == 8) {
                fwrite(byte, 1, 1, f);
                byte[0] = 0;
                count_ = 0;
            }
        }
    }

    fwrite(byte, 1, 1, f);
    qInfo() << "Compressionbefore end";
    fclose(f);
    qInfo() << "Compression end";
     wnd5->on_progressBar_valueChanged(100);
    return true;
}

void BHuffman::Decompression(string cFileName, string dFileName) {
    FILE* cf = fopen( (cFileName).c_str(), "rb"); // open compressed file
    FILE* df = fopen( (dFileName).c_str(), "wb"); // create decompress file

    fseek(cf, 0, SEEK_END);
    int cFileSize = ftell(cf); // count byte from begin

    fseek(cf, 0, SEEK_SET); // begin of file

    cout << "Size of compressed file: " << cFileSize << endl;
    int numberOfBR = 0; // number of bytes read

    char byte[1];

    char strSizeMeta[MAX_META_H];
    fread(strSizeMeta, 1, MAX_META_H, cf);
    numberOfBR += MAX_META_H;
    int sizeMeta = atoi(strSizeMeta);

    //cout <<"Size Meta: " << sizeMeta << endl;
    char *metaData = new char[sizeMeta];
    //const char* hfm_cstr = huffmanTable.c_str();
    for (int i = 0; i < sizeMeta; i++) {
        fread(byte, 1, 1, cf);
        metaData[i] = byte[0];
    }
    numberOfBR += sizeMeta;

    /*cout << "Meta: " << metaData << endl;
    for (int i = 0; i < sizeMeta; i++) {
        cout << metaData[i];
    }
    cout << endl;
    cout << "Length : "<< strlen(metaData) << endl;
    */

    vector<unsigned char*> tokens; // "symbol symbol_code"

    int metaEnd = sizeMeta;
    for (int i = sizeMeta; i >= 0; i--) {
        if (metaData[i] == '|' && metaData[i - 1] != '|') {
            unsigned char *str = new unsigned char[metaEnd - i];
            for (int j = i + 1; j < metaEnd; j++) {
                str[j - i - 1] = metaData[j];
                if (j + 1 == metaEnd) {
                    str[j - i] = '\0';
                }
            }
            metaEnd = i;
            //cout << (int) str[0] << " " <<  str << endl;
            tokens.push_back(str);
        }
        else if(metaData[i] == '|' && metaData[i - 1] == '|') {
            i = i - 1;
            unsigned char *str = new unsigned char[metaEnd - i];
            for (int j = i + 1; j < metaEnd; j++) {
                str[j - i - 1] = metaData[j];
                if (j + 1 == metaEnd) {
                    str[j - i] = '\0';
                }
            }
            metaEnd = i;
            cout << (int) str[0] << " " <<  str << endl;
            tokens.push_back(str);
        }

    }


    //create SymbolCodeMap ([symbol] = [binary_code])
    SymbolCodeMap codes;
    cout << tokens.size() << endl;

    for (int i = 0; i < tokens.size(); i++) {
        unsigned char symbol = tokens[i][0];
        BinarySymbolCode code;

        int n = 2;
        while(tokens[i][n] != '\0') {
            if (tokens[i][n] == '1') {
                code.push_back(true);
            }
            else if (tokens[i][n] == '0') {
                code.push_back(false);
            }
            n++;
        }
        codes[symbol] = code;
    }

    // Checking truth
   /* for (int i = 0; i < sizeMeta; i++) {
        if (metaData[i] == '|') {
            unsigned char s = metaData[i + 1];
            if(i + 1 == sizeMeta) break;
            int j = i + 1;
            while(metaData[j] != '|' && j != sizeMeta){
                j++;
            }
            int c_i = 0;
            for(int o = i + 3; o < j; o++) {
                bool b = codes[s][c_i++];
                if (!(b && metaData[o] == '1' || !b && metaData[o] == '0')) {
                    cout <<"Error: " << (int)s << " " << s << " " << o << " "<< j <<  endl;
                }
            }
            cout << "Check: " << (int)s  << s << endl;
        }
    }

    cout << sizeMeta; */


    //read 1 bite from file and find out in map
    char buffer[1]; int count_ = 0;
    byte[0] = fgetc(cf);
    byte[0] = fgetc(cf);
    numberOfBR += 2;

    BinarySymbolCode code;

    while(!feof(cf)) {

        bool b = byte[0] & (1 << (7 - count_) );

        if (b) {
            code.push_back(1);
        }
        else {
            code.push_back(0);
        }
        //cout << b;
        for (SymbolCodeMap::const_iterator it = codes.begin(); it != codes.end(); ++it) {
            if (code == it->second) {
                fputc(it->first, df);
                code.clear();
                if (numberOfBR == cFileSize) {
                    // Close files & end work
                    fclose(cf);
                    fclose(df);
                    return;
                }
            }
        }

        count_++;
        if (count_ == 8) {
            count_ = 0;
            byte[0] = fgetc(cf);
            numberOfBR++;
        }
    }

    //fputc('\n', df);
    //fputc('\0', df);

    /*while(count_ < 8) {

        bool b = byte[0] & (1 << (7 - count_) );

        if (b) {
            code.push_back(1);
        }
        else {
            code.push_back(0);
        }
        //cout << b;
        for (SymbolCodeMap::const_iterator it = codes.begin(); it != codes.end(); ++it) {
            if (code == it->second) {
                amount++;
                fputc(it->first, df);
                code.clear();
                break;
            }
        }

        count_++;
    }*/



    //cout << endl << code.size() << endl << count_ << endl  << numberOfBR;
    //fclose(cf);
    //fclose(df);
}

char BHuffman::findCodeInCodesMap(const BinarySymbolCode& code, SymbolCodeMap& codes) {
    return 0;
}


BasicNode* BHuffman::BuildTree(int frequencies[]) {
    priority_queue<BasicNode*, vector<BasicNode*>, NodeComp> trees;

    for (int i = 0; i < UniqueSymbols; ++i) {
        if(frequencies[i] != 0) {
            trees.push(new LeafNode(frequencies[i], (char)i));
        }
    }
    //cout << "Size " << trees.size() << endl;

    while (trees.size() > 1) {
        BasicNode* childR = trees.top();
        trees.pop();

        BasicNode* childL = trees.top();
        trees.pop();

        BasicNode* parent = new ParentNode(childR, childL);
        trees.push(parent);

    }

    return trees.top();
}


void BHuffman::GenerateCodes(const BasicNode* node, const BinarySymbolCode& bsc, SymbolCodeMap& scm) {
    if (const LeafNode* lf = dynamic_cast<const LeafNode*>(node)) { // РїРµСЂРµРІС–СЂРєР° С‡Рё РІСѓР·РѕР» С” РµРєР·РµРјРїР»СЏСЂРѕРј LeafNode
        scm[lf->c] = bsc;
    }
    else if (const ParentNode* pn = dynamic_cast<const ParentNode*>(node)) {
        BinarySymbolCode leftPrefix = bsc;
        leftPrefix.push_back(false);
        GenerateCodes(pn->left, leftPrefix, scm);

        BinarySymbolCode rightPrefix = bsc;
        rightPrefix.push_back(true);
        GenerateCodes(pn->right, rightPrefix, scm);
    }
}


string BHuffman::GetHuffmanTable(SymbolCodeMap& scm) {
    string huffmanTable = "";
    for (SymbolCodeMap::const_iterator it = scm.begin(); it != scm.end(); ++it) {
        huffmanTable += it->first + '\0';
        huffmanTable += " ";

        string code = "";

        for (int i = 0; i < it->second.size(); i++) {
            code += it->second[i] ? "1" : "0";
        }
        huffmanTable += code + "|";
        cout << (int) it->first << " " << it->first << " " << code << endl;
    }
    // add string length meta data on begin
    string strTableSize = to_string( huffmanTable.length() );

    while(strTableSize.length() < MAX_META_H) {
        strTableSize = "0" + strTableSize;
    }

    return strTableSize + "|" + huffmanTable;
}


void outputBinarySymbolCode(BinarySymbolCode code) {
    cout << "Code: ";
    for (int i  = 0; i < code.size(); i++) {
        cout << code[i];
    }
    cout << endl;
}


