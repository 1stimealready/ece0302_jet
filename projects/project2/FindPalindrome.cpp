#include <string>
#include <vector>
#include <iostream>
#include "FindPalindrome.hpp"

using namespace std;

//------------------- HELPER FUNCTIONS -----------------------------------------

// non-class helper functions go here, should be declared as "static" so that
// their scope is limited

// helper function to convert string to lower case
static void convertToLowerCase(string & value)
{
	for (int i=0; i<value.size(); i++) {
		value[i] = tolower(value[i]);
	}
}

//------------------- PRIVATE CLASS METHODS ------------------------------------

// private recursive function. Must use this signature!
void FindPalindrome::recursiveFindPalindromes(vector<string>
        candidateStringVector, vector<string> currentStringVector)
{	

	//Check cutTest2
	if (cutTest2(candidateStringVector, currentStringVector) == false) {

		return;

	}

	string stringToTest = "";

	if (currentStringVector.size() == 2) { //If there are only two elements left in currentStringVector, we must swap them instead of iterating further

		//Check if current arrangement is a palindrome before and after each swap operation
		stringToTest = "";
		for (size_t i = 0; i < candidateStringVector.size(); i++) { stringToTest += candidateStringVector[i]; } //Loop through candidateVector and add values to a new empty string that can be passed to isPalindrome()
		stringToTest = stringToTest + currentStringVector[0] + currentStringVector[1];

		if (isPalindrome(stringToTest)) {
			numPalindromes++;

			//Update palindrome vector with new palindrome
			std::vector<string> tempVector(candidateStringVector);
			tempVector.push_back(currentStringVector[0]);
			tempVector.push_back(currentStringVector[1]);
			palindromeVector.push_back(tempVector);
		} 

		//Swap elements in currentStringVector
		currentStringVector.push_back(currentStringVector.front());
		currentStringVector.erase(currentStringVector.begin());

		//Palindrome checking code again
		stringToTest = "";
		for (size_t i = 0; i < candidateStringVector.size(); i++) { stringToTest += candidateStringVector[i]; }
		stringToTest = stringToTest + currentStringVector[0] + currentStringVector[1];
		if (isPalindrome(stringToTest)) {
			numPalindromes++;
			std::vector<string> tempVector(candidateStringVector);
			tempVector.push_back(currentStringVector[0]);
			tempVector.push_back(currentStringVector[1]);
			palindromeVector.push_back(tempVector);
		} 

	} else if (currentStringVector.size() != 1) {

		//Otherwise we change the elements of currentString Vector by moving elements to candidate vector one at a time
		for (size_t i = 0; i < currentStringVector.size(); i++) {

			//Move the ith element of current vector into candidate vector
			candidateStringVector.push_back(currentStringVector[i]);
			currentStringVector.erase(currentStringVector.begin() + i);

			//Call recursive function again with the now smaller currentVector
			recursiveFindPalindromes(candidateStringVector, currentStringVector);

			//Move vector pushed into candidate vector back into current vector, so we can iterate on the next permutation
			currentStringVector.insert(currentStringVector.begin() + i, candidateStringVector.back());
			candidateStringVector.pop_back();


		}

	} else {


		//Edge case where there is only 1 element in currentStringVector
		if (isPalindrome(currentStringVector[0])) {

			numPalindromes = 1;

		}

	}



	return; 
	
}


// private function to determine if a string is a palindrome (given, you
// may change this if you want)
bool FindPalindrome::isPalindrome(string currentString) const
{
	locale loc;
	// make sure that the string is lower case...
	convertToLowerCase(currentString);
	// see if the characters are symmetric...
	int stringLength = currentString.size();
	for (int i=0; i<stringLength/2; i++) {
		if (currentString[i] != currentString[stringLength - i - 1]) {
			return false;
		}
	}
	return true;
}

//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome()
{
	//Don't need to clear vectors since the objects are already constructed in the header
	numPalindromes = 0;


}

FindPalindrome::~FindPalindrome()
{

	//No dynamic memory (outside of the vectors) we need to deallocate

}

int FindPalindrome::number() const
{

	return numPalindromes;
}

void FindPalindrome::clear()
{

	numPalindromes = 0;
	wordArray.clear();
	palindromeVector.clear();


}

bool FindPalindrome::cutTest1(const vector<string> & stringVector)
{

	int charArray[26] = { 0 };
	char tempChar = 0;

	for (size_t i = 0; i < stringVector.size(); i++) {

		for (size_t j = 0; j < stringVector[i].length(); j++) { //This loop structure will go char by char through stringVector

				tempChar = tolower(stringVector[i][j]);

				// subtracting 0x61 means that [a...z] = [0...25]
				//We then add 1 to the corresponding element of the charArray, or set to 0 if it is already 1
				//Downside of this approach is that it only works with an ASCII encoding scheme
				//For this assignment we were never told to make our program work multi-lingually, so should be okay
				charArray[tempChar - 0x61] = (charArray[tempChar - 0x61] + 1) % 2; 

		}

	}

	for (size_t i = 1; i < 26; i++) {

		charArray[0] = charArray[0] + charArray[i]; //Add all elements of charArray into charArray[0]

	}

	return (charArray[0] <= 1); //1 or less means that there is 1 or 0 odd occurances of a letter
}

bool FindPalindrome::cutTest2(const vector<string> & stringVector1,
                              const vector<string> & stringVector2)
{
	
	string string1, string2, shorterString, longerString = "";
	size_t numMatches = 0;

	for (size_t i = 0; i < stringVector1.size(); i++) { //Combine string vector into 1 string

		string1 = string1 + stringVector1[i];

	}

	for (size_t i = 0; i < stringVector2.size(); i++) { //Combine string vector into 1 string

		string2 = string2 + stringVector2[i];

	}


	//Since cutTest2 iterates from the perspective of the shorter string, its helpful to determine a shorter and longer string
	if (string1.length() <= string2.length()) { 

		shorterString = string1;
		longerString = string2;

	} else {

		shorterString = string2;
		longerString = string1;

	}

	//Make both strings lowercase for comparison sake
	convertToLowerCase(shorterString);
	convertToLowerCase(longerString);

	//Check if there is a match for each characer in shorterString in longerString
	for (size_t i = 0; i < shorterString.length(); i++) {

		for (size_t j = 0; j < longerString.length(); j++) {

			if (shorterString[i] == longerString[j]) {

				numMatches++;
				break;

			}


		}

	}

	//if numMatches is equal to the number of characters in shorterString, we've found a match for every character
	return (shorterString.length() == numMatches);

}

bool FindPalindrome::add(const string & value)
{

	locale loc;

	vector<string> tempArray(wordArray);

	//Convert each element of tempArray to lowercase for comparison sake
	for (size_t i = 0; i < tempArray.size(); i++) {

		convertToLowerCase(tempArray[i]);

	}

	//check that each element of value is a character of the alphabet
	for (size_t i = 0; i < value.length(); i++) {

		if (isalpha(value[i]) == false) { return false; }

	}

	string valueToAdd = "";

	//lowercase version of the string to add 
	for (size_t i = 0; i < value.size(); i ++) {

		valueToAdd += tolower(value[i]);

	}

	//Now that we have lowercase versions of both, we can compare them
	for (size_t i = 0; i < wordArray.size(); i++) {

		if (tempArray[i] == valueToAdd) {

			return false;

		}

	}

	//Pushback value
	wordArray.push_back(value);


	//Reset palindrome stats so we can run recursiveFindPalindrome fresh
	numPalindromes = 0;
	palindromeVector.clear();

	//If we past cutTest1 we can then run recursiveFindPalindromes
	if (cutTest1(wordArray) == true) {

		vector<string> canidateStringArray;
		recursiveFindPalindromes(canidateStringArray, wordArray);

	}

	return true;
}

bool FindPalindrome::add(const vector<string> & stringVector)
{
	//lowercase version of wordArray for comparison sake
	vector<string> tempArray(wordArray);

	for (size_t i = 0; i < tempArray.size(); i++) {

		convertToLowerCase(tempArray[i]);

	}

	//For each element in stringArray, we check if it is a letter, and then we convert to lowercase and add to a temporary string
	for (size_t i = 0; i < stringVector.size(); i++) {

		string valueToAdd = "";

		for (size_t j = 0; j < stringVector[i].length(); j++) {

			if (isalpha(stringVector[i][j]) == false) { return false; }

			valueToAdd += tolower(stringVector[i][j]);

		}

	


		tempArray.push_back(valueToAdd); //Add lowercase value

	}


	//We now iterate through each pair of values in our lowercase array, starting with the first two elements, then progressing pair by pair
	for (size_t i = 0; i < tempArray.size() - 1; i++) {

		for (size_t j = i + 1; j < tempArray.size(); j++) {

			if (tempArray[i] == tempArray[j]) {

				return false;

			}

		}

	}

	//Assuming we have avoided all of the previous checks, we are now safe to add stringVector to wordArray
	for (size_t i = 0; i < stringVector.size(); i++) {

		wordArray.push_back(stringVector[i]);

	}

	//Clear palindrome information
	numPalindromes = 0;
	palindromeVector.clear();

	//Redo palindrome information from a fresh state
	if (cutTest1(wordArray)) {

		vector<string> canidateStringArray;
		recursiveFindPalindromes(canidateStringArray, wordArray);

	}

	return true;
	
}

vector< vector<string> > FindPalindrome::toVector() const
{
	return palindromeVector;
}

