#ifndef LZW_COMPRESSTREE_H
#define LZW_COMPRESSTREE_H

#include <map>

class Node {
    friend class CompressTree;
public:

    unsigned long index;
    int byte;

    Node* getChild(int c) {
        return childs[c];
    }

private:

    void insertChild(Node* child) {
        childs[child->byte] = child;
    }

    Node(unsigned long index, int byte) : index(index), byte(byte) {}
    std::map<int, Node*> childs;
};

class CompressTree {
public:
    Node* root;

    unsigned int bitsForIndex;

    explicit CompressTree(unsigned long sizeLimit);

    Node* newNodeChild(Node* parent, int byte);

private:
    unsigned long SIZE_LIMIT;
    unsigned long size;
    unsigned long nextBitIncrease;
};


#endif //LZW_COMPRESSTREE_H
