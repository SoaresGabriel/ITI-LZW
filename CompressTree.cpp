#include "CompressTree.h"

CompressTree::CompressTree(unsigned long sizeLimit) : SIZE_LIMIT(sizeLimit) {

    root = new Node(0, 0);

    // insert the firsts elements to the dictionary
    for(size = 0; size < 256; size++) {
        root->insertChild(new Node(size, static_cast<int>(size)));
    }

    root->insertChild(new Node(size, EOF));
    size++;

    bitsForIndex = 9;
    nextBitIncrease = 512;
}

Node *CompressTree::newNodeChild(Node *parent, int byte) {
    parent->insertChild(new Node(size, byte));
    size++;

    if(size > nextBitIncrease) {
        bitsForIndex++;
        nextBitIncrease <<= 1u; // * 2
    }
}
