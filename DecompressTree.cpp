#include <stdexcept>
#include "DecompressTree.h"

int DNode::getFirstByte() {
    if(parent == nullptr) {
        return byte;
    } else {
        return parent->getFirstByte();
    }
}

void DNode::writeStringIn(std::ofstream& file) {
    if(parent != nullptr) parent->writeStringIn(file);
    file.put(static_cast<char>(byte));
}

DecompressTree::DecompressTree(unsigned long sizeLimit) : SIZE_LIMIT(sizeLimit) {
    for(size = 0; size < 256; size++) {
        dictionary.push_back(new DNode(nullptr, static_cast<int>(size)));
    }

    bitsForIndex = 8;
    nextBitIncrease = 1u << bitsForIndex;

}

DNode *DecompressTree::newChildNode(unsigned long parent) {
    if(size < SIZE_LIMIT) {
        auto node = new DNode(dictionary[parent]);

        dictionary.push_back(node);
        size++;

        if(size > nextBitIncrease) {
            bitsForIndex++;
            nextBitIncrease <<= 1u; // * 2
        }

        return node;
    } else {
        return nullptr;
    }

}

DNode *DecompressTree::operator[](size_t index) {
    return dictionary[index];
}
