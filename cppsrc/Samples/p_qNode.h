#pragma once
#include <cstdio>  // Needed for NULL
using namespace std;

template <class T>
class p_qNode {

public:

  T data;
  p_qNode<T>* next;

  //Description: create a node with next node = NULL
  p_qNode();

  // parametarized constructors

  //Description:set data to aData and next node = NULL
  p_qNode(T aData);

  //Description:set data to aData and next node = next
  p_qNode(T aData, p_qNode<T>* next);
}; // Node

//Description: create a node with next node = NULL
template <class T>
p_qNode<T>::p_qNode():next(NULL){
}

//Description:set data to aData and next node = NULL
template <class T>
p_qNode<T>::p_qNode(T aData ):data(aData),next(NULL){

}
//Description:set data to aData and next node = next
template <class T>
p_qNode<T>::p_qNode(T aData, p_qNode<T>* next):data(aData),next(next){

}
