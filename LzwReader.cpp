#include "LzwReader.h"

LzwReader::LzwReader(string fileName) :
        buffer(0), bitCount(0), file(fileName, ifstream::binary) {

    if(!file.good()) {
        cout << "Error opening the file!" << endl;
        exit(1);
    }

    file.read((char*) &dictionarySizeLimit, sizeof(unsigned long));
}

bool LzwReader::getBit() {
    if(bitCount == 0) {
        buffer = (unsigned char) file.get();
        bitCount = 7;
    } else {
        bitCount--;
    }

    return (bool) ((buffer >> bitCount) & 1u);
}

unsigned long LzwReader::getIndex(unsigned int bits) {
    unsigned long index = 0;

    for(int i = 0; i < bits; i++) {
        index = (index << 1u) | getBit();
    }

    return index;
}

void LzwReader::close() {
    file.close();
}
