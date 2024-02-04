#include "limited_size_bag.hpp"

template<typename T>
LimitedSizeBag<T>::LimitedSizeBag() {

  bagSize = 0;

}
  
template<typename T>
bool LimitedSizeBag<T>::add(const T& item)
{
  if (bagSize == maxsize) {
    
    return false;

  }

  bagArray[bagSize] = item;

  bagSize++;

  return true;

}

template<typename T>
bool LimitedSizeBag<T>::remove(const T& item)
{
  if (bagSize == 0) {

    return false;

  }

  size_t itemToRemove = 0;

  while ((bagArray[itemToRemove] != item) && itemToRemove < bagSize) {

    itemToRemove++;

  }

  if (itemToRemove < bagSize) {


    //Start at the item to remove, and overwrite it with the next value in line. 
    //This method will leave bagArray[bagSize] still assigned a value, but this shouldn't matter, since that's outside the scope of the new array
    //And that memory is reserved anyways
    for(size_t i = itemToRemove; i < bagSize - 1; i++) { 

      bagArray[i] = bagArray[i+1];

    }

    bagSize--;

    return true;

  } else {

    return false;

  }


}

template<typename T>
bool LimitedSizeBag<T>::isEmpty() const
{

  return (bagSize == 0);

}

template<typename T>
std::size_t LimitedSizeBag<T>::getCurrentSize() const
{
  return bagSize;
}

template<typename T>
bool LimitedSizeBag<T>::contains(const T& item) const
{  
  
  for (int i = 0; i < bagSize; i++) {

    if (bagArray[i] == item) {

      return true;

    }

  }

  return false;

}

template<typename T>
void LimitedSizeBag<T>::clear(){

  for(int i = 0; i < maxsize; i++) {

    bagArray[i] = NULL;

  }

  bagSize = 0;


}

template<typename T>
std::size_t LimitedSizeBag<T>::getFrequencyOf(const T & item) const
{
  
  size_t count = 0;

  for (int i = 0; i < bagSize; i++) {

    if (bagArray[i] == item) {

      count++;

    }

  }
  
  return count;

};
