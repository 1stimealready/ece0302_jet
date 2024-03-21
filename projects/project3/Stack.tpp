//  Adapated from Frank M. Carrano and Timothy M. Henry.

/** ADT Stack implementation.
    @file Stack.cpp */

#include <iostream>
#include <cstddef>
#include "Stack.hpp"
#include "Node.hpp"

// TODO: Implement the constructor here
template<class ItemType>
Stack<ItemType>::Stack() 
{
	//Initialize headPtr to nullptr
	headPtr = nullptr;

	//int currentSize is 0
	currentSize = 0;

}  // end default constructor

// TODO: Implement the destructor here
template<class ItemType>
Stack<ItemType>::~Stack()
{

	clear(); //clear function does same job as destructor


}  // end destructor

// TODO: Implement the isEmpty method here
template<class ItemType>
bool Stack<ItemType>::isEmpty() const
{
	return (currentSize == 0);
}  // end isEmpty

// TODO: Implement the size method here
template<class ItemType>
int Stack<ItemType>::size() const
{
	return currentSize;
}  // end size

// TODO: Implement the push method here
template<class ItemType>
bool Stack<ItemType>::push(const ItemType& newItem)
{
	Node<ItemType> *nodeToAdd = new Node<ItemType>(newItem);

	nodeToAdd->setNext(headPtr);

	headPtr = nodeToAdd;

	currentSize++;

	return true;

}  // end push

// TODO: Implement the peek method here
template<class ItemType>
ItemType Stack<ItemType>::peek() const
{
	//Check if stack is empty
	if (currentSize == 0) { throw std::logic_error("Tried to peek at an empty stack"); }

	return headPtr->getItem();
}  // end peek

// TODO: Implement the pop method here
template<class ItemType>
bool Stack<ItemType>::pop() 
{
	//Check if stack is empty
	if (currentSize == 0) { return false; }

	Node<ItemType> *itemToPop = headPtr; //Create temp variable to delete top item

	headPtr = headPtr->getNext(); //Set headPtr to next item

	delete itemToPop; //Delete item to pop

	currentSize--;

	return true;


}  // end pop

// TODO: Implement the clear method here
template<class ItemType>
void Stack<ItemType>::clear()
{

	Node<ItemType> *nextPtr;

	while (headPtr != nullptr) { //Loops through stack until all elements are deleted

		nextPtr = headPtr->getNext();

		delete headPtr;

		headPtr = nextPtr;

	}

	currentSize = 0;

}  

