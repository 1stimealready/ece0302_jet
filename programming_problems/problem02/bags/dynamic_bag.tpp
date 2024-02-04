#include "dynamic_bag.hpp"

template<typename T>
DynamicBag<T>::DynamicBag() {

  bagArray = new T[0];
  bagSize = 0;

}
                

template<typename T>
DynamicBag<T>::DynamicBag(const DynamicBag<T>& x){

  bagArray = new T[x.getCurrentSize()];
  bagSize = x.getCurrentSize();

  for (size_t i = 0; i < x.getCurrentSize(); i++) {

    bagArray[i] = x.bagArray[i];

  }

}
    
template<typename T>
DynamicBag<T>::~DynamicBag(){

  delete [] bagArray;

}
  
template<typename T>
DynamicBag<T>& DynamicBag<T>::operator=(DynamicBag<T> x)
{ 

  swap(x);

  return *this;
}

template<typename T>
void DynamicBag<T>::swap(DynamicBag<T>& x){

  
  std::swap(bagArray, x.bagArray);
  std::swap(bagSize, x.bagSize);


}

template<typename T>
bool DynamicBag<T>::add(const T& item)
{

  if (false) { //TODO - situations where we can't add an item

    return false;

  } 


    T * tempBagArray = new T[bagSize + 1];

    for (size_t i = 0; i < bagSize; i++) {

      tempBagArray[i] = bagArray[i];

    }

    tempBagArray[bagSize] = item;

    delete[] bagArray;

    bagArray = tempBagArray;

    bagSize++;

    return true;

}

template<typename T>
bool DynamicBag<T>::remove(const T& item)
{
  
  if (bagSize == 0) {

    return false;

  }

  size_t curItem = 0;

  while ((bagArray[curItem] != item) && (curItem < bagSize)) { //Find index of item to remove, or curItem = bagSize

    curItem++;

  }

  if (curItem < bagSize) {

    T * tempBagArray = new T[bagSize - 1];

    for (size_t i = 0; i < bagSize; i++) {

      size_t indexToAdd = 0;

      if (i != curItem) { //indexToAdd increments along with i at all points except when i == curItem. This means that the new smaller array won't be accessed out of bounds

        tempBagArray[indexToAdd] = bagArray[i];

        indexToAdd++;

      }

    }

    delete [] bagArray;

    bagArray = tempBagArray;

    bagSize--;

    return true;

  } else {return false; }


  


}

template<typename T>
bool DynamicBag<T>::isEmpty() const
{

  if (bagSize == 0) {

    return true;

  }


  return false;
}

template<typename T>
std::size_t DynamicBag<T>::getCurrentSize() const
{
  
  return bagSize;

}

template<typename T>
bool DynamicBag<T>::contains(const T& item) const
{  
  
  for (size_t i = 0; i < bagSize; i++) {

    if (bagArray[i] == item) {

      return true;

    }

  }

  return false;

}

template<typename T>
void DynamicBag<T>::clear(){

  delete [] bagArray;

  bagArray = new T[0];

  bagSize = 0;


}

template<typename T>
std::size_t DynamicBag<T>::getFrequencyOf(const T & item) const
{
  size_t count = 0;

  for (size_t i = 0; i < bagSize; i++) {

    if (bagArray[i] == item) {

      count++;

    }

  }

  return count;


}
