#ifndef LZW_COMPRESSTREE_H
#define LZW_COMPRESSTREE_H

#include <map>

class CNode {
    friend class CompressTree;
public:

    unsigned long index;
    int byte;

    CNode* getChild(int c) {
        return childs[c];
    }

private:

    void insertChild(CNode* child) {
        childs[child->byte] = child;
    }

    CNode(unsigned long index, int byte) : index(index), byte(byte) {}
    std::map<int, CNode*> childs;
};

class CompressTree {
public:
    CNode* root;

    unsigned int bitsForIndex;

    explicit CompressTree(unsigned long sizeLimit);

    CNode* newNodeChild(CNode* parent, int byte);

private:
    unsigned long SIZE_LIMIT;
    unsigned long size;
    unsigned long nextBitIncrease;
};


#endif //LZW_COMPRESSTREE_H
