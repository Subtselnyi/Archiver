#pragma once
#include <iostream>
#include <queue>
#include <map>
#include <iterator>     // ostream_iterator
#include <algorithm>    // copy
#include <string.h>     // strtok
#include "progressbardialog.h"


using namespace std;


typedef vector<bool> BinarySymbolCode;
typedef map<unsigned char, BinarySymbolCode> SymbolCodeMap;
typedef map<BinarySymbolCode, unsigned char> CodeSymbolMap;

const int UniqueSymbols = 256; // for char
class BasicNode;
const int MAX_META_H = 10; // order


class BHuffman
{
    public:
        BHuffman();
        virtual ~BHuffman();

        BasicNode* BuildTree(int frequencies[]);
        void GenerateCodes(const BasicNode*, const BinarySymbolCode&, SymbolCodeMap&); // обхід дерева + запис в map
        string GetHuffmanTable(SymbolCodeMap&);
        string Compression(string,int&);
        void Decompression(string, string,double);
        char findCodeInCodesMap(const BinarySymbolCode&, SymbolCodeMap&);

        ProgressBarDialog *wnd5;
        int progressCount=0;
};

class BasicNode {
    public:
        int freq;
        BasicNode();
        BasicNode(int f) { freq = f;}
        virtual ~BasicNode() {};
};


class ParentNode : public BasicNode {
    public:
       BasicNode* left;
       BasicNode* right;

       ParentNode(BasicNode* l, BasicNode* r) : BasicNode(l->freq + r->freq), left(l), right(r) {}
       ~ParentNode() {
            delete left;
            delete right;
       }
};


class LeafNode : public BasicNode {
    public:
        const unsigned char c;
        LeafNode(int f, char c) : BasicNode(f), c(c) {}
};


class NodeComp {
    bool rev;
public:
    NodeComp(const bool& revpar = false) { rev = revpar;}
    bool operator()(const BasicNode* l, const BasicNode* r) {
        if (rev) {
            return l->freq < r->freq;
        }
        else
            return l->freq > r->freq;
    }
};
