#pragma once
#include <string>
#include <fstream>
#include<vector>
#include<iostream>
using namespace std;


class BitStream{

  private:
    fstream file;
    string fileName;
    int charSize;//char size in bits
    unsigned char buffer;//buffer to read and write bits
    int bufferCounter;//bits position bufferCounter

  public:

    //Description: Default cononstructor. Takes the name of file as input.
    BitStream(const std::string& aFile);

    //Description: open file in writing Mode. If the file exist then append in that filename
    bool OpenToWrite();
    bool OpenToWriteFirst(int a,int b,const std::string& str);

    //Description: write bits into a file using a character buffer.
    void writeBits(unsigned char bit);

    //Description: This function writes bits in bytes.
    void writeBytes(unsigned char aChar);

    //Description: This function flushes bits left in buffer by padding zeros.
    void flushWrite();

    //Description: open file in reading mode if successful then return true otherwise false.
    bool OpenToRead();
    bool OpenToReadFirst(int* a, int* b, string* str);

    //Description: This function read bits from file and return bits..
    unsigned char readBits();

    //Description: This function read file in Bytes and return as unsigned char.
    unsigned char readBytes();

    //Description: Flush the buffer and after reading is done.
    //post:        buffer is empty.
    void flushRead();

    //Description: close the file.
    void closeFile();
    //Description: write bits into inputFile destination
    bool isOpen()const;

    //Description: Get the number of bits written in file when writing to a file.
    int getCharSize();



};
