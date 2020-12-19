#include "BitStream.h"
#include <string>
#include<cstddef>

//Description: Paramaterized constructor and takes filename as input.
BitStream::BitStream(const std::string& aFile):fileName(aFile),charSize(0),buffer('\0'),bufferCounter(0){

}

//Description: open file in writing Mode. If the file exist then append in that filename
bool BitStream::OpenToWrite(){
  file.open(fileName,ios::out|ios::app|ios::binary);
  bufferCounter = 0;
  charSize = 0;
  return file.is_open();
}

bool BitStream::OpenToWriteFirst(int n,int m, const std::string& str){

  file.open(fileName,ios::out|ios::binary);
  bufferCounter = 0;
  string str1 = to_string(n);
  string str2 = to_string(m);
  cout<<m;
  file<<"*"<< endl;
  file<<str<<endl;
  file<<str1<< endl;
  file<<str2<< endl;
  charSize = (str1.size()+str2.size()+str.size()+5)*8;
  // charSize = (str1.size()+1)*8;

  return file.is_open();
}

//Description: write bits into a file using a character buffer.
void BitStream::writeBits(unsigned char bit){

  charSize++;
  bufferCounter++;

  //write bits into buffer
  if (bit==1){
    buffer|= (128>>(bufferCounter-1));
  }

  //if buffer is full then write it into file
  if(bufferCounter==8){
    file.put(buffer);
    buffer='\0';
    bufferCounter=0;
  }
}

//Description: This function writes bits in bytes.
void BitStream::writeBytes(unsigned char aChar){

    for( int i = 7; i >=0;i--){
      unsigned char aBit = (int(aChar)>>i) & 1;
      this->writeBits(aBit);
    }
}

//Description: This function flushes bits left in buffer by padding zeros.
//Post:        buffer is zero.
void BitStream::flushWrite(){
  if(bufferCounter){
    file.put(buffer);
  }
  charSize+=bufferCounter;
  bufferCounter=0;
  buffer = '\0';
}

//Description: open file in reading mode if successful then return true otherwise false.
bool BitStream::OpenToRead(){
  file.open(fileName,ios::in|ios::binary);
  bufferCounter = 0;

  if(!file.is_open()){
    return false;
  }

  return file.is_open();
}

bool BitStream::OpenToReadFirst(int* a, int* b, string* str){
  file.open(fileName,ios::in|ios::binary);
  bufferCounter = 0;
  string tmp;
  if(!file.is_open()){
    return false;
  }
  getline(file, tmp);
  if (tmp != "*"){
    return false;
  }
  string tmp2;
  string str1, str2;
  getline(file, *str);
  getline(file, str1);
  getline(file, str2);
  *a = stoi(str1);
  *b = stoi(str2);
  return true;
}

//Description: This function read bits from file and return bits.
unsigned char BitStream::readBits(){
  unsigned char c = 2;

  //if there is not bits in buffer then read a byte
  if(bufferCounter==0){

    if(!file.eof()){
      buffer=file.get();
      c = (((buffer >> 7) & 1));
      bufferCounter = 7;

    }
  //if there are bits then process those bits.
  }else{
    c = ((buffer >> (bufferCounter-1)) & 1);
    bufferCounter--;
  }

  return c;
}

//Description: This function read file in Bytes and return as unsigned char.
unsigned char BitStream::readBytes(){

  unsigned char c='\0';
  if(!file.eof()){

    for(int i = 7 ; i >=0;i--){
      c |= (this->readBits()<<i);
    }
  }
  return c;
}

//Description: Flush the buffer and after reading is done.
void BitStream::flushRead(){
  bufferCounter = 0;
}

//Description: return true if file is open false otherwise
bool BitStream::isOpen()const{
  return file.is_open();
}

//Description: close the file.
void BitStream::closeFile(){
  file.close();
}

//Description: Get the number of bits written in file when writing to a file.
int BitStream::getCharSize(){
  return charSize;
}
