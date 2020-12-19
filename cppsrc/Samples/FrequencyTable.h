#include <string>
#include<iostream>
using namespace std;

class FrequencyTable{

  private:

    unsigned int Freq_arr[256]={};//frequency table array for 256 choices
    unsigned int numOfChar; //number of characters

  public:

    //Description: Defaulr constructor.
    FrequencyTable();

    //Description:  return number of char in source file.
    unsigned int getCharSize()const;

    //Description: this function returns the frequency of character i at position arr[i];
    int getFrequency(unsigned int atPos);


    //Description: This function reads file from aFile and build the frequency talbe
    bool setFrequency(string aFile);

};
