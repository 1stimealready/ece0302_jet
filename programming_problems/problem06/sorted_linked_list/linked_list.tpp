#include "linked_list.hpp"
#include <stdexcept>

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
  
  Node<T> * currentPtr = headPtr;

  Node<T> * nextPtr = nullptr;

  for (int i = 0; i < length; i++) {

    nextPtr = currentPtr->getNext();

    delete currentPtr;

    currentPtr = nextPtr;

  }
  

}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& x)
{

  headPtr = nullptr;
  tailPtr = nullptr;
  length = 0;
  
  for (size_t i = 0; i < x.length; i++) {

    insert(i, x.getEntry(i));

  }


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

  /*
    Node<T> *currentPtr = headptr;

    size_t count = 0;

    while (currentPtr != nullptr) {

      currentPtr = currentPtr->getNext();
      count++;

      return count;

    }    

  */


}

template <typename T>
void LinkedList<T>::insert(std::size_t position, const T& item)
{
  //TODO

  if (position > length || position < 0) { throw std::range_error("Tried to insert an element outside of a linked list"); }
  Node<T> *newNode = new Node<T>(item);

  if (length == 0) { //Case if list is empty

    headPtr = newNode;
    tailPtr = newNode;

  } else if (position == 0) { //Case where we are inserting to beginning of list

    newNode->setNext(headPtr);
    headPtr = newNode;  

  } else if (position == length) { //Case inserting at end of list

    tailPtr->setNext(newNode);
    tailPtr = newNode;

  } else { //Case where position is inside of list

    Node<T> *currentPtr = headPtr;

    for (size_t i = 0; i < position - 1; i++) {

      currentPtr = currentPtr->getNext();

    }

    Node<T> *nextPtr = currentPtr->getNext();

    currentPtr->setNext(newNode);

    newNode->setNext(nextPtr);

  }

  length++;


}

template <typename T>
void LinkedList<T>::remove(std::size_t position)
{
  if (position < 0 || position >= length) { throw std::range_error("Tried to remove an element outside of a linked list"); }

  if (length == 1) { //Case where there is only one item in list

    delete headPtr;
    headPtr = nullptr;
    tailPtr = nullptr;

    length--;


  } else if (position == 0) { //Case where we are removing first item of list

    Node<T> *tempPtr = headPtr->getNext();
    delete headPtr;
    headPtr = tempPtr;

    length--;


  } else {

    Node<T> *tempPtr = headPtr; //Case where we are removing an item in the middle of the list

    for (int i = 0; i < position - 1; i++) {

      tempPtr = tempPtr->getNext();

    }

    if (tempPtr->getNext() == tailPtr) { //If we are removing the item before tailPtr, we need to set tailPtr

      delete tailPtr;
      tailPtr = tempPtr;

      length--;


    } else {

      Node<T> *nextPtr = tempPtr->getNext()->getNext(); //Otherwise we get the item after next, so we can link it back without the removed object

      delete tempPtr->getNext();

      tempPtr->setNext(nextPtr);

      length--;


    }

  }

}

template <typename T>
void LinkedList<T>::clear()
{
  //TODO
  Node<T> * currentPtr = headPtr;

  Node<T> * nextPtr = nullptr;

  for (int i = 0; i < length; i++) {

    nextPtr = currentPtr->getNext();

    delete currentPtr;

    currentPtr = nextPtr;

  }

  headPtr = nullptr;
  tailPtr = nullptr;
  length = 0;

}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  //TODO
  if (position < 0 || position >= length) { throw std::range_error("Tried to get an entry outside a list."); }

  Node<T> *currentPtr = headPtr;

  for (int i = 0; i < position; i++) {

    currentPtr = currentPtr->getNext();

  }

  return currentPtr->getItem();


}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
  if (position < 0 || position >= length) { throw std::range_error("Tried to set an entry outside a list."); }

  Node<T> *currentPtr = headPtr;

  for (int i = 0; i < position; i++) {

    currentPtr = currentPtr->getNext();

  }

  currentPtr->setItem(newValue);
}


template<typename T> 
LinkedList<T> LinkedList<T>::sort(LinkedList<T> list)
{

	//Base case if list is empty
	//If there is 1 or 0 items in a list, the list is already sorted and we can simply return up a level of recursion
	if (list.getLength() <= 1) {

		return list;

	}

	//Recursive Quick sort implementation
	T partition = list.getEntry(0); //Partion about first element;

	LinkedList<T> prePartition;
	LinkedList<T> postPartition;


	//This loop partitions the list
	//For each item in the list, we compare it against the partition
	//If it is greater, we put it into a new array that is above the partition
	//If it is less than, we put it into an array that is below the partition
	for (size_t i = 1; i < list.getLength(); i++) {

		T itemToPartition = list.getEntry(i); 

		if (itemToPartition >= partition) {

			postPartition.insert(0, itemToPartition);

		} else {

			prePartition.insert(0, itemToPartition);

		}

	}

	//We then sort the above and below lists in the same method
	prePartition = sort(prePartition);
	postPartition = sort(postPartition);

	//Finally, we clear list, and add all values from our smaller post and pre lists
	//The partition sits in between
	list.clear();

	for (size_t i = 0; i < prePartition.getLength(); i++) {

		list.insert(i, prePartition.getEntry(i));

	}

	list.insert(prePartition.getLength(), partition);

	size_t j = 0;

	for (size_t i = prePartition.getLength() + 1; i < postPartition.getLength() + prePartition.getLength() + 1; i++) {

		list.insert(i, postPartition.getEntry(j));
		j++;

	}

	return list;
}