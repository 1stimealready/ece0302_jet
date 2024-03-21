// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
    @file XMLParser.cpp */

#include <string>
#include <assert.h>
#include "XMLParser.hpp"

// TODO: Implement the constructor here
XMLParser::XMLParser()
{

	parseStack = new Stack<std::string>();
	elementNameBag = new Bag<std::string>();


}  // end default constructor

// TODO: Implement the destructor here
XMLParser::~XMLParser()
{

	delete parseStack;
	delete elementNameBag;

}  // end destructor

// TODO: Implement the tokenizeInputString method
bool XMLParser::tokenizeInputString(const std::string &inputString)
{

	char currentChar;
	TokenStruct currentItem;

	//Clear previous input
	tokenizedInputVector.clear();

	//This approach uses a number of tags to determine the state of the current progam:
	bool inTag = false, pastTag = false, inText = false;

	for (size_t i = 0; i < inputString.size(); i++) {

		currentChar = inputString[i];


		//Every time we encount " we can swap whether or not we are in a text segment
		if (currentChar == '\"') {

			inText = !inText; //If we are inside a tag's data we ignore certain special characters

		}



		if (currentChar == '<') {

			if (currentItem.tokenType == CONTENT && !currentItem.tokenString.empty()) { //If we reach the start of a tag and we are currently in content, we push content and start new token

				//We also must cleanse the current entry of any whitespace after the last character, and before first character
				while (isspace(currentItem.tokenString.back())) {

					currentItem.tokenString.pop_back();

				}

				while (isspace(currentItem.tokenString.front())) {

					currentItem.tokenString.erase(0, 1);

				}

				if(currentItem.tokenString.size() == 0) { //If there is "content" that is all whitespace we ignore it

					currentItem = TokenStruct();

				} else {

					tokenizedInputVector.push_back(currentItem);
					currentItem = TokenStruct();

				}

			} else if (inTag) {//Error checking; If we encounter a '<' while we are currently processing a tag, the XML is invalid

				tokenizedInputVector.clear();

				return false;

			}

			inTag = true;
			pastTag = false;

			i++;
			if (i != inputString.length()) { //Make sure we aren't reading a value outside of our list

				currentChar = inputString[i]; //iterate to next char to check tag type

			} else {

				tokenizedInputVector.clear();

				return false;
				
			}


			if (currentChar == '?') {

				currentItem.tokenType = DECLARATION;

				i++;
				if (i != inputString.length()) { //Make sure we aren't reading past the end of our string

				currentChar = inputString[i];

				} else {

					tokenizedInputVector.clear();

					return false;
				
				} //Iterate past declaration character if encountered

			} else if (currentChar == '/') {

				currentItem.tokenType = END_TAG; //'/' character after < means we are working with an end tag

				i++;
				if (i != inputString.length()) { //Ensure we are still within the string

				currentChar = inputString[i];  

				} else {

					tokenizedInputVector.clear();

					return false;
				
				}

			} else if (isalpha(currentChar) || currentChar == '_') { //Tags must start with either an underscore or a letter

				currentItem.tokenType = START_TAG;

			} else { //If not, we can't tokenize

				tokenizedInputVector.clear();

				return false;

			}

		} else if (currentChar == '>') { //Push back tag we've just read

			if (!inTag) { //If we encounter '>' while we aren't in a tag, the string is invalid

				tokenizedInputVector.clear();

				return false;

			}

			inTag = false;
			tokenizedInputVector.push_back(currentItem);

			currentItem = TokenStruct();	

			continue;

		}
		
		//Logic for tags that has signifiers before '>', right at the end
		//In either case this means we push the tag we have
		//Also only check this if we are not currently in content
		if ((currentChar == '/' || currentChar == '?') && currentItem.tokenType != CONTENT && !inText) {

			i++;
			if (i != inputString.length()) {

				currentChar = inputString[i]; //Ensure we are not iterating past end of string

			} else {

				tokenizedInputVector.clear();

				return false;
				
			} //iterate to see if '/' or '?' is followed by '>'

			if (currentChar == '>') {

				//If the system thinks we are in a start tag at this point, it means it did not encounter any signifiers at the start of the tag
				//Given this is the case, it means we must be in an empty tag
				//If tokenType is already a declaration, we can just push to the stack
				if (currentItem.tokenType == START_TAG) {
					
					currentItem.tokenType = EMPTY_TAG;

				} else if (currentItem.tokenType != DECLARATION) { //If we are not in a start tag, then we have reached an escape character too early and inputString is not valid XML

					tokenizedInputVector.clear();

					return false;

				}

				inTag = false;

				tokenizedInputVector.push_back(currentItem);

				currentItem = TokenStruct();

				continue;

			} else if (inTag){ //If our special character is not succeeded by '>' We are not in a valid tag

				tokenizedInputVector.clear();

				return false;


			}


		}

		//If we are not in a tag at this point we can assume we are looking at content
		if (inTag == false && currentItem.tokenType != CONTENT) {

			currentItem.tokenType = CONTENT;
			pastTag = true;

		}

	//pastTag is for all cases EXCEPT declarations and content
	//Encountering a whitespace while we are not in a declaration tag means we can safely continue through the loop until we reach '>'
		if (currentItem.tokenType != DECLARATION && pastTag == false) { 

			if (isspace(currentChar)) {

				pastTag = true;

			} else {

				currentItem.tokenString += currentChar;

			}

		} else if (currentItem.tokenType == DECLARATION) {

			currentItem.tokenString += currentChar;

		}

		//If in content, push current char

		if (currentItem.tokenType == CONTENT) {

			currentItem.tokenString += currentChar;

		}

	}

	//If we reach the end of our string and we still have content loaded, we add it to tokenizedVector
	if (currentItem.tokenType == CONTENT) { 
		while (isspace(currentItem.tokenString.back())) {

			currentItem.tokenString.pop_back();

		}

		while (isspace(currentItem.tokenString.front())) {

			currentItem.tokenString.erase(0, 1);

		}

		if(currentItem.tokenString.size() != 0) { //If the content is not whitespace we can add it to tokenVector

			tokenizedInputVector.push_back(currentItem);
			currentItem = TokenStruct();

		}

	}

	if (tokenizedInputVector.size() == 0) {

		return false;

	}

	return true;
}  // end

// TODO: Implement the parseTokenizedInput method here
bool XMLParser::parseTokenizedInput()
{
	//Ensure element bag and stack are empty before we parse a new statement
	elementNameBag->clear();
	parseStack->clear();

	//Make sure we are not parsing an empty string
	if (tokenizedInputVector.size() == 0) {

		return false;

	}

	bool encountedStartTag = false; //We only expect to see tags that are not declarations or start tags once we have encountered our first start tag

	for (size_t i = 0; i < tokenizedInputVector.size(); i++) {

		//If we run into an invalid tag too early, return false
		if (!encountedStartTag && !(tokenizedInputVector[i].tokenType == DECLARATION || tokenizedInputVector[i].tokenType == START_TAG)) {

			return false;

		}

		if (tokenizedInputVector[i].tokenType == START_TAG) {

			(*parseStack).push(tokenizedInputVector[i].tokenString);
			encountedStartTag = true;

		} else if (tokenizedInputVector[i].tokenType == END_TAG) {

			if (parseStack->isEmpty()) { //If we would ever peek at an empty stack, exit instead

				return false;

			}

			if (tokenizedInputVector[i].tokenString == (*parseStack).peek()) {

				(*elementNameBag).add((*parseStack).peek());
				(*parseStack).pop();


				//If we clear the stack and we are not at the end of the loop, the XML is not valid
				if (parseStack->size() == 0 && i != tokenizedInputVector.size() - 1) {

					return false;

				}

			} else {

				return false;
				
			}

		}

	}

	if ((*parseStack).size() != 0) {

		parseStack->clear(); //Clear parsestack so we are not messing up next XML parse
		return false;

	}



	return true;
}

// TODO: Implement the clear method here
void XMLParser::clear()
{

	tokenizedInputVector.clear();
	parseStack->clear();
	elementNameBag->clear();

}

vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

// TODO: Implement the containsElementName method
bool XMLParser::containsElementName(const std::string &inputString) const
{
	if (elementNameBag->size() == 0) {

		throw(std::logic_error("Input has not been tokenized or is empty."));

	}


	return elementNameBag->contains(inputString);
}

// TODO: Implement the frequencyElementName method
int XMLParser::frequencyElementName(const std::string &inputString) const
{

	if (elementNameBag->size() == 0) {

		throw(std::logic_error("Input has not been tokenized or is empty."));

	}
	
	return elementNameBag->getFrequencyOf(inputString);
}

