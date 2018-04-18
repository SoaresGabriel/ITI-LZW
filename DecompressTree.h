#ifndef LZW_DECOMPRESSTREE_H
#define LZW_DECOMPRESSTREE_H

#include <vector>
#include <fstream>

struct DNode {

    DNode* parent;
    int byte;

    DNode(DNode* parent, int byte) : parent(parent), byte(byte) {}
    explicit DNode(DNode* parent) : parent(parent), byte(-2) {}

    int getFirstByte();
    void writeStringIn(std::ofstream& file);
};

class DecompressTree {
private:

    unsigned long size;
    unsigned long SIZE_LIMIT;
    unsigned long nextBitIncrease;
public:

    std::vector<DNode *> dictionary;
    explicit DecompressTree(unsigned long sizeLimit);

    unsigned int bitsForIndex;

    DNode* newChildNode(unsigned long parent);

    DNode* operator[](size_t index);

};


#endif //LZW_DECOMPRESSTREE_H
