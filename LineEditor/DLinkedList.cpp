/* Author: Gregory E. Hatt
 */

#include "DLinkedList.h"

// constructor
DLinkedList::DLinkedList()
{
  // sentinals
  header = new DNode();
  trailer = new DNode();
  
  // have them point at one another;
  header->next = trailer;
  trailer->prev = header;
  
  numElements = 0;
  
}

// destructor
DLinkedList::~DLinkedList()
{
  // keep calling the remove on the front
  // until the head is pointing at the trailer
  while(!empty()) 
    removeFront();
  
  delete header;
  delete trailer;
}

// empty()
// ======================================
// Check to see if any elements remain.
// ======================================
bool DLinkedList::empty() const
{
  // if head is pointing at trailer then
  // no elements remain
  return (header->next == trailer);
}

// front()
// ======================================
// get front element in list
// ======================================
const Elem& DLinkedList::front()
{
  // return front of list
  return header->next->elem;

}

// back()
// ======================================
// Returns the last item in the list
// ======================================
const Elem& DLinkedList::back()
{
  return trailer->prev->elem;
}

// getAt()
// ======================================
// Returns the elment at a specific index.
// ======================================
const Elem& DLinkedList::getAt(int index)
{

  // TODO Handle invalid indexes
  // TODO Throw an exception
  
  if(index < 0 || index >= numElements)
    throw IndexOutOfBounds();
  
  DNode * curNode = header;
    
  for(int i = 0; i < index + 1; i++){
    curNode = curNode->next;
  }
  
  return curNode->elem;
    
}


// addBack()
// ======================================
// Adds an element to the back of the list
// ======================================
void DLinkedList::addBack(const Elem& e)
{

  add(trailer, e); // will add a new element before node v
                   // which will always be trailer
}

// addFront()
// ======================================
// Adds an element to the front of the list
// ======================================
void DLinkedList::addFront(const Elem& e)
{
  add(header->next, e); // on first run it will add to pos ahead of trailer
			// afterwards it will place a new node in front of
			// the head
}

// addAt()
// ======================================
// Adds an element at a specific index
// ======================================
void DLinkedList::addAt(const Elem& element, int i)
{
  
  // Goal, insert a new node at a certain position
  // Basically we will traverse the nodes until our
  // index is at a given position and then use our
  // helper method to insert the node that element.
  
  if(i >= numElements || i < 0){
    if(i != 0)
    throw IndexOutOfBounds();
  }
  
  DNode * inNode = header->next; // first node
  
  // traverse the nodes i amount of times
  for(int n = 0; n < i; n++)
  inNode = inNode->next;
  
  // use our helper method to add the node
  add(inNode, element);
  
}

// removeAt()
// ======================================
// Removes an element at a specific index
// ======================================
void DLinkedList::remove(int index)
{
  // Goal, insert a new node at a certain position
  // Basically we will traverse the nodes until our
  // index is at a given position and then use our
  // helper method to insert the node that element.
  
	if (index >= numElements || index < 0)
    throw IndexOutOfBounds();
  
  
  DNode * inNode = header->next; // first node
  
  // traverse the nodes i amount of times
  for (int nodeCount = 0; nodeCount < index; nodeCount++)
  inNode = inNode->next;
  
  // use our helper method to add the node
  remove(inNode);
  
}

// remove(beg, end)
// ======================================
// Removes all from beggining to end
// ======================================
void DLinkedList::remove(int begIndex, int endIndex)
{
	if ((begIndex < 0 || begIndex > numElements - 1) || (begIndex > endIndex || endIndex > numElements - 1))
    throw IndexOutOfBounds();
 
	for (int i = begIndex; i <= endIndex; i++)
		remove(begIndex);
}


// add()
// ======================================
// Helper method which expands the list by 
// adding a new node in front of node sourceNode
// ======================================
void DLinkedList::add(DNode* sourceNode, const Elem element)
{ 
  numElements++;	// increment element count
  DNode * nodeToAdd = new DNode;   // create new node
  nodeToAdd->elem = element; // assign the value
  
  nodeToAdd->next = sourceNode; // have new nodes next point to list node
  nodeToAdd->prev = sourceNode->prev; // have the new nodes prev point to list node's prev
  sourceNode->prev->next = nodeToAdd; // have the node before v point to u
  sourceNode->prev = nodeToAdd; // have the node ahead of v's previous point to u
}


// remvoveFront()
// ======================================
// Removes the front element if there is 
// a front element to remove
// ======================================
void DLinkedList::removeFront()
{
  if(header->next == trailer)
    throw IndexOutOfBounds("Exception: No front element.");
    
  remove(header->next);
}

void DLinkedList::removeBack()
{
    if(trailer->prev != header) {
        remove(trailer->prev);
    }
}

// remvoeSpecifiedNode()
// ======================================
// Removes the front element if there is 
// a front element to remove
// ======================================
void DLinkedList::remove(DNode* nodeToRemove)
{

  numElements--;

  // hold both ends
  DNode * prevTemp = nodeToRemove->prev;
  DNode * nextemp = nodeToRemove->next;
  
  // tie them
  nextemp->prev = prevTemp;
  prevTemp->next = nextemp;
  
  // Remove the old node
  delete nodeToRemove;
  
}

// Returns an ostream loaded with the to string method.
ostream& operator << (ostream& output,  DLinkedList& list)
{
	char ch; // for some reason it would not run without this
	
	for(int i = 0; i < list.size(); i++)
	 output << "#" << i << "# " << list.getAt(i) << std::endl;
	
	return output;
};

