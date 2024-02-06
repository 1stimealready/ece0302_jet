#include "linked_list.hpp"

template <typename T>
LinkedList<T>::LinkedList()
{
  //initialize both points to null, no items in list
  headPtr = nullptr;
  tailPtr = nullptr;

  length = 0;


}

template <typename T>
LinkedList<T>::~LinkedList()
{
  //TODO
  
  Node<T> * currentPtr = headPtr;

  Node<T> * nextPtr = nullptr;

  while (currentPtr != nullptr) {

    nextPtr = currentPtr->getNext();
    delete currentPtr;
    currentPtr = nextPtr;

  }
  

}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& x)
{
  
  Node<T> * currentPtrInX = x.headPtr;

  Node<T> * currentPtrInThis = nullptr;

  if (currentPtrInX != nullptr && currentPtrInX->getNext() != nullptr) {
    
    Node<T> * prevPtrInThis = new Node<T>(currentPtrInX->getItem()); //Create a new pointer in this with no next value

    currentPtrInX = currentPtrInX->getNext(); //Progress to next pointer in X

    currentPtrInThis = new Node<T>(currentPtrInX->getItem()); //Set current pointer in this to new value of X

    prevPtrInThis->setNext(currentPtrInThis); //Link previous value in this to current value in this

    headPtr = prevPtrInThis;


    while(currentPtrInX->getNext() != nullptr) {

      currentPtrInX = currentPtrInX->getNext(); //Advance pointer in X to the next in sequence

      currentPtrInThis = new Node<T>(currentPtrInX->getItem()); //Create a new object for this with the value of the current item in X

      prevPtrInThis = prevPtrInThis->getNext(); //Advance previous member of this to the most recently created item

      prevPtrInThis->setNext(currentPtrInThis); //Link previous ptr in this with newly created object in this


    }
    

  } else if (currentPtrInX != nullptr) { //Logic for if there is only one item in the linked list

    currentPtrInThis = new Node<T>(currentPtrInX->getItem());

    headPtr = currentPtrInThis;

  }


  tailPtr = currentPtrInThis;

  length = x.length;



}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> x)
{
  //TODO
  swap(x);
  return *this;
}

template <typename T>
void LinkedList<T>::swap(LinkedList& x) 
{
  //TODO
  std::swap(headPtr, x.headPtr);
  std::swap(tailPtr, x.tailPtr);
  std::swap(length, x.length);


}

template <typename T>
bool LinkedList<T>::isEmpty() const noexcept
{
  //TODO
  return (length == 0);

}

template <typename T>
std::size_t LinkedList<T>::getLength() const noexcept
{

  return length;


}

template <typename T>
bool LinkedList<T>::insert(std::size_t position, const T& item)
{
  //TODO

  if (position > length || position < 0) { return false; }

  Node<T> *currentPtr = headPtr;

  size_t currentPos = 0;

  while (currentPtr != nullptr) {

    if (currentPos == position) {

      Node<T> * newNode = new Node<T>(item, currentPtr->getNext());

      currentPtr->setNext(newNode);

      length++;

      return true;

    }

    currentPos++;

    currentPtr = currentPtr->getNext();

  }

  return false;
  
}

template <typename T>
bool LinkedList<T>::remove(std::size_t position)
{
  if (position < 0 || position >= length) { return false; }

  if (length == 1) {

    delete headPtr;

    headPtr = nullptr;
    tailPtr = nullptr;

    length--;

    return true;

  }

  Node<T> * currentPtr = headPtr->getNext();
  Node<T> * prevPtr = headPtr;

  if (position == 0) {

    currentPtr =  headPtr->getNext();

    delete headPtr;

    headPtr = currentPtr;

    length--;

    return true;

  }



  size_t currentPos = 1;

  while (currentPtr != nullptr) {

    if (currentPos == position) {

      currentPtr = currentPtr->getNext();

      delete prevPtr->getNext();

      prevPtr->setNext(currentPtr);

      length--;

      return true;

    }

    

    currentPos++;
    currentPtr = currentPtr->getNext();

    

  }
  

  
  return false;

}

template <typename T>
void LinkedList<T>::clear()
{
  //TODO
  Node<T> * currentPtr = headPtr;

  Node<T> * nextPtr = nullptr;

  while (currentPtr != nullptr) {

    nextPtr = currentPtr->getNext();
    delete currentPtr;
    currentPtr = nextPtr;

  }

  headPtr = nullptr;
  tailPtr = nullptr;

}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  //TODO
  return T();
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
  //TODO
}
