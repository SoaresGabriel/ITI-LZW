#include <iostream>
#include <fstream>
#include <map>
#include "LzwWriter.h"
#include "CompressTree.h"
#include "LzwReader.h"
#include "DecompressTree.h"

using namespace std;

void compress(const string &filename, unsigned int powerMaxSize);
void decompress(const string &filename);

int main(int argc, char** argv) {

    clock_t initialTime = clock(), finalTime;

    if ((argc < 3 || argc > 4) || (argv[1][1] != 'c' && argv[1][1] != 'd') || (argc == 4 && argv[1][1] != 'c') || (argc == 3 && argv[1][1] != 'd')) {
        cout << "Arguments: [-c p |-d] file" << endl;
        exit(1);
    } else if (argv[1][1] == 'c') {

        // get the power of 2 of the size limit of dictionary
        unsigned int p = static_cast<unsigned int>(stoi(argv[2]));
        if(p < 9 || p > sizeof(unsigned long) * 8 - 1) {
            cout << "Invalid 'p', must be in (8," << sizeof(unsigned long) * 8 << ")" << endl;
            exit(1);
        }

        string filename(argv[3]);

        compress(filename, p);

        if(argv[1][2] == 'd') {
            decompress(filename + ".LZW");
        }

    } else if (argv[1][1] == 'd') {
        decompress(argv[2]);
    }

    finalTime = clock();
    long executionTime = ((finalTime - initialTime) / (CLOCKS_PER_SEC / 1000));
    cout << "t: " << executionTime << " ms" << endl;

    return 0;
}

void compress(const string &filename, unsigned int powerMaxSize) {

    unsigned long maxDictionarySize = (1ul << powerMaxSize);

    CompressTree compressTree(maxDictionarySize);

    ifstream inFile(filename, ifstream::binary);
    if(!inFile.good()) {
        cout << "Failed to open the file!" << endl;
        exit(1);
    }

    LzwWriter writer(filename + ".LZW", powerMaxSize);

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

    string outFilename(filename);
    outFilename.insert(outFilename.find_first_of('.'), "0"); // put '0' before first '.'
    outFilename = outFilename.substr(0, outFilename.find_last_of('.')); // remove '.LZW'

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