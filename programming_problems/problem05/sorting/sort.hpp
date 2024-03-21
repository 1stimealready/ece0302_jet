#ifndef _SORT_HPP
#define _SORT_HPP

#include "linked_list.hpp"
#include <iostream>

template<typename T> LinkedList<T> sort(LinkedList<T> list)
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

#endif
