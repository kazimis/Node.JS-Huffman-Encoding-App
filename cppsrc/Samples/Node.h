#pragma once
#include <cstdio>  // Needed for NULL
using namespace std;

template <class T>

class Node {
public:

  int Frequency;
  unsigned char aChar;
  Node<T>* left;
  Node<T>* right;

  //Default Constructor
  //Description: create a node with left and right child  = NULL, Frequency = 0 and aChar = is '\0'
  Node();
  //Description:parametarized constructor
  Node(int aFrequency, unsigned char aChar);


};
//Default Constructor
//Description: create a node with left and right child  = NULL, Frequency = 0 and aChar = is '\0'
template <class T>
Node<T>::Node():Frequency(0),aChar('\0'),left(NULL),right(NULL){

}
//Description:parametarized constructor
template <class T>
Node<T>::Node( int aFrequency, unsigned char aChar ):Frequency(aFrequency),aChar(aChar),left(NULL),right(NULL){

}
