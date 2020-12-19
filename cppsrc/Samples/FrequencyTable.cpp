 #include"FrequencyTable.h"
 #include<fstream>
 #include<iostream>

//Description: Defaulr constructor.
FrequencyTable::FrequencyTable():numOfChar(0){

}
//Description: this function returns the frequency of character i at position arr[i];
int FrequencyTable::getFrequency(unsigned int pos){

 return Freq_arr[pos];

}

//Description:  return number of char in source file.
unsigned int FrequencyTable::getCharSize()const{

  return numOfChar;

}
//Description: This function reads file from aFile and build the frequency talbe
bool FrequencyTable::setFrequency(string aFile){
  fstream inFile;
  char c;
  unsigned char buffer;

  inFile.open(aFile, istream::in|ios::binary);

  // get length of file:
    inFile.seekg (0, inFile.end);
    int length = inFile.tellg();
    inFile.seekg (0, inFile.beg);

  if(inFile.fail()){
    return false;
  }

  int i = 0;
  while(i<length){
    inFile.read(&c,1);
    buffer =c;
    i++;
    Freq_arr[buffer]++;
    numOfChar++;
  }

  inFile.close();
  return true;
}
