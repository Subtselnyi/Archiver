#ifndef BHUFFMAN_H
#define BHUFFMAN_H


#include <iostream>
#include <queue>
#include <map>
#include <iterator>     // ostream_iterator
#include <algorithm>    // copy
#include <string.h>     // strtok
#include <cstdio>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif

using namespace std;


typedef vector<bool> BinarySymbolCode;
typedef map<unsigned char, BinarySymbolCode> SymbolCodeMap;

const int UniqueSymbols = 256; // for char
class BasicNode;
const int MAX_META_H = 10; // order


class BHuffman
{
    public:
        BHuffman();
        virtual ~BHuffman();

        BasicNode* BuildTree(int frequencies[]);
        void GenerateCodes(const BasicNode*, const BinarySymbolCode&, SymbolCodeMap&); // РѕР±С…С–Рґ РґРµСЂРµРІР° + Р·Р°РїРёСЃ РІ map
        string GetHuffmanTable(SymbolCodeMap&);
        bool Compression(string,string);
        void Decompression(string, string);
        char findCodeInCodesMap(const BinarySymbolCode&, SymbolCodeMap&);
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
#ifdef __cplusplus
}
#endif



#endif // BHUFFMAN_H
