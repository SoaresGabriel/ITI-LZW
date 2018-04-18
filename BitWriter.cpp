//
// Created by gabriel on 23/03/18.
//

#include "BitWriter.h"

BitWriter::BitWriter(const string &fileName) :
        file(fileName, ofstream::binary), buffer(0), bitCount(0) {

}

void BitWriter::writeBit(bool bit) {
    buffer = ((buffer << 1u) | bit);
    bitCount++;

    if(bitCount == 8){
        file.put(buffer);
        bitCount = 0;
    }
}

void BitWriter::writeIndex(unsigned long index, unsigned int bits) {
    for(int b = bits - 1; b >= 0; b--) {
        writeBit(((index >> b) & 1u) == 1u);
    }
}

void BitWriter::close() {
    if(bitCount > 0) {
        buffer = (buffer << 8u - bitCount);
        file.put(buffer);
    }
    file.close();
}
