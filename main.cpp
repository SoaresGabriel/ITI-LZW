#include <iostream>
#include <fstream>
#include <map>
#include "BitWriter.h"

using namespace std;

class Node {
public:
    Node(unsigned long index, int byte) : index(index), byte(byte) {}

    unsigned long index;
    int byte;

    void insertChild(Node* child) {
        childs[child->byte] = child;
    }

    Node* getChild(unsigned char c) {
        return childs[c];
    }

private:
    map<int, Node*> childs;
};

int main() {

    clock_t initialTime = clock(), finalTime;

    string fileName = "generated.fib26";

    auto root = new Node(0, 0);

    // insert the firsts elements to the dictionary
    for(int byte = 0; byte < 256; byte++) {
        root->insertChild(new Node(static_cast<unsigned long>(byte), byte));
    }

    unsigned long dictionarySize = 256;
    unsigned int indexBits = 8;
    unsigned long nextBitIncrease = 256;

    ifstream inFile(fileName, ifstream::binary);
    BitWriter writer(fileName + ".LZW");

    if(!inFile.good()) {
        cout << "Failed to open the file!" << endl;
    }

    Node* current = root;
    int symbol;
    while((symbol = inFile.get()) != EOF) {
        Node* child = current->getChild(static_cast<unsigned char>(symbol));
        if(child == nullptr) { // nó atual não tem esse byte, então deve comprimilo, e inserilo
            writer.writeIndex(current->index, indexBits);
            current->insertChild(new Node(dictionarySize, static_cast<unsigned char>(symbol)));
            inFile.unget(); // retorna ultimo byte lido, para fazer o matching
            current = root;
            dictionarySize++;
            if(dictionarySize > nextBitIncrease) {
                indexBits++;
                nextBitIncrease <<= 1; // duplica
            }
        } else {
            current = child;
        }
    }

    if(current != root) {
        writer.writeIndex(current->index, indexBits);
    }

    inFile.close();
    writer.close();

    finalTime = clock();
    long executionTime = ((finalTime - initialTime) / (CLOCKS_PER_SEC / 1000));
    cout << "t: " << executionTime << " ms" << endl;

    return 0;
}