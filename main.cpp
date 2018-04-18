#include <iostream>
#include <fstream>
#include <map>
#include "LzwWriter.h"
#include "CompressTree.h"
#include "LzwReader.h"
#include "DecompressTree.h"

using namespace std;

void compress(const string &filename, unsigned long maxDictionarySize);
void decompress(const string &filename);

int main() {

    clock_t initialTime = clock(), finalTime;

    string filename = "teste.txt";
    unsigned long maxDictionarySize = 999999;

    //compress(filename, maxDictionarySize);
    decompress("teste2.txt.LZW");

    finalTime = clock();
    long executionTime = ((finalTime - initialTime) / (CLOCKS_PER_SEC / 1000));
    cout << "t: " << executionTime << " ms" << endl;

    return 0;
}

void compress(const string &filename, unsigned long maxDictionarySize) {
    CompressTree compressTree(maxDictionarySize);

    ifstream inFile(filename, ifstream::binary);
    LzwWriter writer(filename + ".LZW", maxDictionarySize);

    if(!inFile.good()) {
        cout << "Failed to open the file!" << endl;
    }

    CNode* current = compressTree.root;
    int symbol;
    while((symbol = inFile.get()) != EOF) {
        CNode* child = current->getChild(static_cast<unsigned char>(symbol));
        if(child == nullptr) { // nó atual não tem esse byte, então deve comprimi-lo, e inseri-lo
            writer.writeIndex(current->index, compressTree.bitsForIndex);
            compressTree.newNodeChild(current, symbol);
            inFile.unget(); // retorna ultimo byte lido, para fazer o matching
            current = compressTree.root;
        } else {
            current = child;
        }
    }

    if(current != compressTree.root) {
        writer.writeIndex(current->index, compressTree.bitsForIndex);
    }

    writer.writeIndex(compressTree.root->getChild(EOF)->index, compressTree.bitsForIndex);

    inFile.close();
    writer.close();
}

void decompress(const string &filename) {
    if(filename.size() <= 4 || filename.substr(filename.find_last_of('.')) != ".LZW") {
        cout << "Invalid compressed file! (not .LZW)!" << endl;
        exit(1);
    }

    string outFilename = filename.substr(0, filename.find_last_of('.'));

    LzwReader reader(filename);
    DecompressTree decompressTree(reader.maxDictionarySize);
    ofstream outfile(outFilename, ofstream::binary);

    DNode* lastNode = nullptr;
    while(true) {
        unsigned long index = reader.readIndex(decompressTree.bitsForIndex);

        DNode* node = decompressTree[index];

        if(node->byte == EOF) {
            break;
        }

        if(lastNode != nullptr) {
            lastNode->byte = node->getFirstByte();
        }

        node->writeStringIn(outfile);

        lastNode = decompressTree.newChildNode(index);
    }

    outfile.close();
    reader.close();
}