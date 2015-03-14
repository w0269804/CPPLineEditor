#ifndef DNODE_H
#define DNODE_H

#include <string>
using std::string;

//typedef string Elem;
typedef string Elem;

class DNode
{

private:
  Elem elem;
  DNode * prev;
  DNode * next;

  friend class DLinkedList;

};

#endif // DNODE_H
