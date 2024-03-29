#include "linked_list.hpp"
#include "sorted_linked_list.hpp"
#include <stdexcept>

template <typename T>
SortedLinkedList<T>::SortedLinkedList(): LinkedList<T>()
{

}

template <typename T>
SortedLinkedList<T>::SortedLinkedList(LinkedList<T> unsorted_list) 
{
  //Sort unstorted list
  LinkedList<T> sorted = LinkedList<T>::sort(unsorted_list); 

  LinkedList<T>::swap(sorted);

}

template <typename T>
SortedLinkedList<T>::SortedLinkedList(const SortedLinkedList<T> & x):
  LinkedList<T>(x)
{
  
  LinkedList<T>::operator=(x);

}

template <typename T>
SortedLinkedList<T>& SortedLinkedList<T>::operator=(SortedLinkedList<T> x)
{
  LinkedList<T>::operator=(x);
  return *this;
}

template <typename T>
SortedLinkedList<T>::~SortedLinkedList()
{
  // base destructor gets called automatically

}

template <typename T>
bool SortedLinkedList<T>::isEmpty() const noexcept
{
  return LinkedList<T>::isEmpty();
}

template <typename T>
std::size_t SortedLinkedList<T>::getLength() const noexcept
{
  return LinkedList<T>::getLength();
}

template <typename T>
void SortedLinkedList<T>::insert(const T& item)
{

  bool endOfList = true;

  for (size_t i = 0; i < getLength(); i++) {

    if (item <= getEntry(i)) {

      LinkedList<T>::insert(i, item);

      endOfList = false;

      break;

    }


  }

  if (endOfList) {

    LinkedList<T>::insert(getLength(), item);

  }

}

template <typename T>
void SortedLinkedList<T>::remove(const T& item)
{
  if(isEmpty()) throw std::range_error("empty list in remove");
  
  // TODO
  for (size_t i = 0; i < LinkedList<T>::getLength(); i++) {

    if (getEntry(i) == item) {

      LinkedList<T>::remove(i);

    }

  }

}

template <typename T>
void SortedLinkedList<T>::removeAt(std::size_t position)
{
  if(isEmpty()) throw std::range_error("empty list in remove");
  
  // TODO
  LinkedList<T>::remove(position);

}

template <typename T>
void SortedLinkedList<T>::clear()
{
  LinkedList<T>::clear();
}

template <typename T>
T SortedLinkedList<T>::getEntry(std::size_t position) const
{
  return LinkedList<T>::getEntry(position);
}

template <typename T>
long int SortedLinkedList<T>::getPosition(const T& item)
{
  // TODO
  if (getLength() == 0) {

    return -1;

  }

  size_t middle = getLength() / 2;
  size_t low = 0;
  size_t high = getLength() - 1;


  while (item != getEntry(middle)) {

    if (low == high) {

      return -1;

    }

    if (item > getEntry(middle)) {

      low = middle + 1;
      middle = (low + high) / 2;

    } else {

      high = middle - 1;
      middle = (low + high) / 2;

    }

  }

  return middle;



}

