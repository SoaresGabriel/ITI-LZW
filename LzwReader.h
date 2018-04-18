#ifndef LZW_LZWREADER_H
#define LZW_LZWREADER_H

#include <fstream>
#include <iostream>

using namespace std;

class LzwReader {
private:
    unsigned char buffer;
    unsigned short bitCount;
    ifstream file;

    bool getBit();

public:

    unsigned long dictionarySizeLimit;

    explicit LzwReader(string filename);

    unsigned long getIndex(unsigned int bits);

    void close();
};


#endif //LZW_LZWREADER_H
