//
// Created by gabriel on 17/04/18.
//

#ifndef LZW_BITWRITER_H
#define LZW_BITWRITER_H

#include <iostream>
#include <fstream>

using namespace std;

class BitWriter {
private:
    unsigned char buffer;
    unsigned short bitCount;
    ofstream file;
public:
    explicit BitWriter(const string& fileName);

    void writeBit(bool bit);

    void writeIndex(unsigned long index, unsigned int bits);

    void close();
};

#endif //LZW_BITWRITER_H
