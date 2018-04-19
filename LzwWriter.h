#ifndef LZW_LZWWRITER_H
#define LZW_LZWWRITER_H

#include <iostream>
#include <fstream>

using namespace std;

class LzwWriter {
private:
    ofstream file;
    unsigned char buffer;
    unsigned short bitCount;
public:
    LzwWriter(const string& fileName, int powerMaxSize);

    void writeBit(bool bit);

    void writeIndex(unsigned long index, unsigned int bits);

    void close();
};

#endif //LZW_LZWWRITER_H
