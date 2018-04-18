#ifndef LZW_LZWWRITER_H
#define LZW_LZWWRITER_H

#include <iostream>
#include <fstream>

using namespace std;

class LzwWriter {
private:
    unsigned char buffer;
    unsigned short bitCount;
    ofstream file;
public:
    explicit LzwWriter(const string& fileName);

    void writeBit(bool bit);

    void writeIndex(unsigned long index, unsigned int bits);

    void close();
};

#endif //LZW_LZWWRITER_H
