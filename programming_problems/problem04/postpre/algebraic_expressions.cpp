#include <string>
using std::string;

#include <iostream>

#include <cctype> // for isalpha

#include <stack>

#include <vector>

#include "algebraic_expressions.hpp"

bool isoperator(char ch) {
  return ((ch == '+') || (ch == '-') || (ch == '/') || (ch == '*'));
}

int endPost(string s, int last) {
  int first = 0;

  if ((first > last)) {
    return -1;
  }

  char ch = s[last];
  if (isalpha(ch)) {
    return last;
  } else {
    if (isoperator(ch)) {
      int lastEnd = endPost(s, last - 1);
      if (lastEnd > -1) {
        return endPost(s, lastEnd - 1);
      } else {
        return -1;
      }
    } else {
      return -1;
    }
  }
}

bool isPost(string s) {
  int firstChar = endPost(s, s.size() - 1);

  return (firstChar == 0);
}


//This version of convert works by splitting a large expression into smaller expressions, until we reach an expression of the form:
//AB* , at which point we can manually rearrange terms and put them back on the stack
//We also make use of a counter (numNonOperatorsNeeded), which allows us to divide a large expression into valid subexpressions
//by making sure that each operator has the correct number of operands.
//It iterates from the end of postfix, towards the start
void convert(string &postfix, string &prefix) {

 std::stack<string, std::vector<string> > tempStack;

  long long location = 0; //Location must be long long for signed behaviour

  size_t numNonOperatorsNeeded = 0;

  string stringToAdd = "";

  size_t infiniteLoopAvoider = 0;

  do {

    

    location = postfix.size() - 1; //Keeps track of our location within postfix
    stringToAdd = "";

    if (location == 2) { //Check if we are dealing with smallest unit of form: (AB*)

      stringToAdd += postfix[2];
      stringToAdd += postfix[0];
      stringToAdd += postfix[1];

      tempStack.push(stringToAdd);
      
    } else { //If we are not, we then loop iteratively through first the main problem, then each subproblem

        numNonOperatorsNeeded = 1; 

        if (isoperator(postfix[location])) { //Check for an outer operator that encloses other expressions

          stringToAdd = postfix[location];
          tempStack.push(stringToAdd);

          stringToAdd = "";

          location--;

        }

        for ( ; location >= 0; location--) { //loop through current part of main expression

          if (isoperator(postfix[location])) { 

            //Since each operator needs two operands, and also counts itself as an operand for a previous operator,
            //The net effect is that each successive operator adds an additional operand that is needed for a complete expression
            numNonOperatorsNeeded++;

          } else {

            numNonOperatorsNeeded--; //Non operators decrease this count by 1

          }

          //We keep track of a "stringToAdd" that holds the next value we plan to place onto the stack
          stringToAdd = postfix[location] + stringToAdd;

          if (numNonOperatorsNeeded == 0) { //If we have completed a valid expression, we need to place it on the stack
            //To keep the outermost operator on top of the stack, we actually insert terms below position 0
            //This means that when we go to pull a value from the stack, we get the outermost term first
            string topElement = tempStack.top();

            tempStack.pop();

            tempStack.push(stringToAdd);

            tempStack.push(topElement);

            stringToAdd = "";

            numNonOperatorsNeeded = 1;

          }

        }

  }

    //After we have looped through the entire array, we can update prefix with whatever the outermost value we have found is
    prefix += tempStack.top();

    if (tempStack.size() != 0)  { tempStack.pop(); }

    //We then set postfix to the next subset of the original postfix expression
    postfix = tempStack.top();

    if (tempStack.size() != 0)  { tempStack.pop(); }


    infiniteLoopAvoider++; //Just to make sure we are not somehow looping forever
  } while (postfix != "" && infiniteLoopAvoider < 100);

} 
