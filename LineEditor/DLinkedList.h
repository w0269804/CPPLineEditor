#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include "DNode.h"
#include <iostream>
#include "IndexOutOfBounds.h"

using std::ostream; /* << operator */

typedef string Elem;

class DLinkedList
{
  
public:
  
  DLinkedList(); // constructor
  ~DLinkedList(); // destructor
  
  bool empty() const; // whether the list is empty
  const Elem & front (); // the front element
  const Elem & back(); // the back element
  
  void addFront(const Elem& element); // add to front of list
  void addBack(const Elem& element); // add to back of list
  void addAt(const Elem& element, int index); // add an item to the selected index
  
  void removeFront(); // remove front of list
  void removeBack(); // remove back of list
  void remove(int index); // remove at index
  void remove(int begIndex, int endIndex); // remove a subset
  const Elem & getAt(int index); // return element at index
  int size() { return numElements; }; // get size of list
  
  friend ostream& operator << (ostream& output, DLinkedList& list);
  
private:
  
  DNode * header = nullptr;
  DNode * trailer = nullptr;
  
  int numElements;
  
protected:
  
  void add(DNode * sourceNode, const Elem element);
  void remove(DNode *nodeToRemove);
  
};

#endif // DLINKEDLIST_H
