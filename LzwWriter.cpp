#include "LzwWriter.h"

LzwWriter::LzwWriter(const string &fileName, int powerMaxSize) :
        file(fileName, ofstream::binary), buffer(0), bitCount(0) {
    file.put(static_cast<char>(powerMaxSize));
}

void LzwWriter::writeBit(bool bit) {
    buffer = ((buffer << 1u) | bit);
    bitCount++;

    if(bitCount == 8){
        file.put(buffer);
        bitCount = 0;
    }
}

void LzwWriter::writeIndex(unsigned long index, unsigned int bits) {
    for(int b = bits - 1; b >= 0; b--) {
        writeBit(((index >> static_cast<unsigned int>(b)) & 1u) == 1u);
    }
}

void LzwWriter::close() {
    if(bitCount > 0) {
        buffer = (buffer << 8u - bitCount);
        file.put(buffer);
    }
    file.close();
}
