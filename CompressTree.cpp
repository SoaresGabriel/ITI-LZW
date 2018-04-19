#include "CompressTree.h"

CompressTree::CompressTree(unsigned long sizeLimit) : SIZE_LIMIT(sizeLimit) {

    root = new CNode(0, 0);

    // insert the firsts elements to the dictionary
    for(size = 0; size < 256; size++) {
        root->insertChild(new CNode(size, static_cast<int>(size)));
    }

    root->insertChild(new CNode(size, EOF));
    size++;

    bitsForIndex = 9;
    nextBitIncrease = 1u << bitsForIndex;
}

void CompressTree::newNodeChild(CNode *parent, int byte) {
    if(size < SIZE_LIMIT) {
        parent->insertChild(new CNode(size, byte));
        size++;

        if(size > nextBitIncrease) {
            bitsForIndex++;
            nextBitIncrease <<= 1u; // * 2
        }
    }
}
