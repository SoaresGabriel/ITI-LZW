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

    unsigned long maxDictionarySize;

    explicit LzwReader(string filename);

    unsigned long readIndex(unsigned int bits);

    bool good();

    void close();
};


#endif //LZW_LZWREADER_H
