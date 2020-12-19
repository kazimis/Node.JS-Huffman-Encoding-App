#pragma once
#include<iostream>
#include <cstdio>
#include"p_qNode.h"
using namespace std;
template <class T>

class PriorityQueue {

  private:

  // singly-linked list
  p_qNode<T>* head;
  int len;

  public:

  // Desc: Default Constructor. (O(1)). Intitialzes head to NULL and len to zero.
  PriorityQueue();

  // Desc: Destructor. (O(N))
  //Post: All allocated memory by the class is released.
  ~PriorityQueue();

  // Desc: Returns true if Priority Queue empty. (O(1))
  bool isEmpty() const;

  // Desc: Returns length of the Priority Queue. (O(1))
  int getLength() const;

  // Desc: Inserts x in sorted order. (O(N))
  void enqueue(T x);

  // Desc: Removes the element with "highest" priority. (O(1))
  void dequeue();

  // Desc: Returns the element with the "highest" priority. (O(1))
  T peek()const;

};

// Desc: Default Constructor. (O(1)). Intitialzes head to NULL and len to zero.
template <class T>
  PriorityQueue  <T>::PriorityQueue():head(NULL),len(0){
}

// Desc: Destructor. (O(N))
//Post: All allocated memory by the class is released. head is Null
template <class T>
PriorityQueue<T>::~PriorityQueue(){

  //traverse till the end of list
  while(head){
    p_qNode <T>* temp = head->next;
    delete head;
    head = temp;
  }

  head=NULL;
  len = 0;
}

// Desc: Returns true if Priority Queue empty. (O(1))
template <class T>
bool PriorityQueue<T>::isEmpty() const{

  return(head==NULL);

}

// Desc: Returns length of the Priority Queue. (O(1))
template <class T>
int PriorityQueue <T>::getLength() const{

  return len;
}
// Desc: Inserts x in sorted order. (O(N))
template <class T>
void PriorityQueue <T>::enqueue(T x){

  //if PriorityQueue is empty
  if(head == NULL){
    head = new p_qNode<T>(x, NULL);
  //if not empty
  }else{

    //node trackers
    p_qNode <T>* current = head;
    p_qNode <T>* prevNode = NULL;
    bool notFound = true;

    //traverse the list
    while(current && notFound){

      //if appropriate slot found for x
      if(x->Frequency < (current->data)->Frequency){
        //at the beginning
        if(current == head){
          head = new p_qNode<T>(x,current);
        //add in the middle
        }else{
          prevNode->next = new p_qNode <T> (x,current);
        }
        notFound =false;
      }

    prevNode = current;
    current=current->next;
    }

    //if the end of list is reached then add the end of list.
    if(notFound){
      prevNode->next = new p_qNode <T> (x, NULL);
    }
  }

  len++;
}

// Desc: Removes the element with "highest" priority. (O(1))
template <class T>
void PriorityQueue <T>::dequeue(){

  //trhow exception
  p_qNode <T> * temp = head->next;
  delete head;
  head = temp;
  len--;

}
// Desc: Returns the element with the "highest" priority. (O(1))
template <class T>
T PriorityQueue<T>::peek() const{

  return head->data;

}
