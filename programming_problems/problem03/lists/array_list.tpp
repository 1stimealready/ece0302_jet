#include "array_list.hpp"

template <typename T>
ArrayList<T>::ArrayList() {

  listArray = new T[0];

  listSize = 0;

}

template <typename T>
ArrayList<T>::~ArrayList() {

  delete [] listArray;

}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList& rhs){

  listSize = rhs.listSize;

  listArray = new T[listSize];

  for (int i = 0; i < listSize; i++) {

    listArray[i] = rhs.listArray[i];

  }
  
}

template <typename T>
ArrayList<T>& ArrayList<T>::operator=(ArrayList rhs){

  swap(rhs);

  return *this;
}

template <typename T>
void ArrayList<T>::swap(ArrayList& rhs) {

  std::swap(listArray, rhs.listArray);

  std::swap(listSize, rhs.listSize);

}

template <typename T>
bool ArrayList<T>::isEmpty() const noexcept {

  return (listSize == 0);
}

template <typename T>
std::size_t ArrayList<T>::getLength() const noexcept {

  return listSize;

}

template <typename T>
bool ArrayList<T>::insert(std::size_t position, const T& item){

  if (position > listSize ||  position < 0) { return false; } //Template for checking whether or not a new element can be added to list

  T *tempArray = new T[listSize + 1];

  for (size_t i = 0; i < position; i++) { //Load values up until position into new temp array

    tempArray[i] = listArray[i]; 

  }


  tempArray[position] = item; //Load item into position


  for (size_t i = position + 1; i < listSize + 1; i++) { //Load all values past position into tempArray

    tempArray[i] = listArray[i - 1];

  }

  delete [] listArray;

  listArray = tempArray;

  listSize++;

  return true;

}

template <typename T>
bool ArrayList<T>::remove(std::size_t position){
  
  if (listSize == 0 || position < 0 || position >= listSize ) { return false; } //Error checking

  T *tempArray = new T[listSize - 1];

  for (size_t i = 0; i < position; i++) { //Load values up to position

    tempArray[i] = listArray[i];

  }

  //Skip loading position

  for (size_t i = position + 1; i < listSize; i++) { //Load all values past position

    tempArray[i - 1] =  listArray[i];

  }


  delete [] listArray;

  listArray = tempArray;

  listSize--;

  return true;

}

template <typename T>
void ArrayList<T>::clear() {

  delete [] listArray;

  listArray = new T[0];

  listSize = 0;

}

template <typename T>
T ArrayList<T>::getEntry(std::size_t position) const {

  if (position >= listSize || position < 0) { return T(); }


  return listArray[position];


}

template <typename T>
void ArrayList<T>::setEntry(std::size_t position, const T& newValue) {

  if (position >= listSize || position < 0) { return; }

  listArray[position] = newValue;

}
