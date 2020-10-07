#include "MathFormat.h"

MathFormat::MathFormat()
{
}

MathFormat::~MathFormat()
{
}


//checks math input for any and all errors with the input
int MathFormat::errorCheck(string mathInput)
{
	//checks that all characters are valid within the string
	if (validCharacters(mathInput) == false) {
		return -1;
	}

	//verifies that all parenthesis have matching parenthesis
	if (matchingParenthesis(mathInput) == false) {
		return -2;
	}

	//checks that all operations have number or parenthesis on either side
	if (validOperations(mathInput) == false) {
		return -3;
	}

	//secondary way of multiplication?? 2(4+5)

	//if passed all tests return true
	return 1;
}

//function to verify all characters within string are valid
bool MathFormat::validCharacters(string mathInput) {

	//boolean to keep track if input character matches one character from list of valid characters
	bool match = false;

	//compares each character in input string to list of valid characters
	for (int i = 0; i < mathInput.length(); i++) {
		
		//assume match is false
		match = charInString(mathInput[i], listOfValidCharacters);

		//if no match found return false, else check next char
		if (match == false)
			return false;
	}

	//if made through for loop return true;
	return true;
}

//determines if all parenthesis are matching
bool MathFormat::matchingParenthesis(string mathInput) {
	
	//instantiates doubly linked list
	DoublyLinkedList<char> DL;
	
	//declares chars to hold values
	char ch, chTmp;

	//declares bool for flaggin if error or not
	bool error = false;

	for(int i = 0; i < mathInput.length(); i++) {

		//gets next char from string
		ch = mathInput[i];

		if (ch == '(' || ch == '[' || ch == '{') {
			//adds to stack parenthesis to stack
			DL.addTail(ch);
		}
		else if (ch == ')' || ch == ']' || ch == '}') {
			//removes parenthesis from stack to verify correct order
			//if stack is not empty continue
			if (!DL.isEmpty()) {

				//pops from stack
				chTmp = DL.deleteTail();

				//assumes error
				error = true;

				//ch should be the other matching parenthesis to chTmp
				switch (chTmp) {
				case '(':
					if (ch == ')')
						error = false;//no error
					break;

				case '[':
					if (ch == ']')
						error = false;//no errror
					break;

				case '{':
					if (ch == '}')
						error = false;//no error
					break;
				}
				//if char popped of stack isnt reverse of ch than errror
				if (error == true)
					return false;//returns error (Mismatched braces)
			}
			else {//else stack is empty
				return false;//returns error (Mismatched braces)
			}
		}
		else;//do nothing for other characters
	}
	//if stack is empty after end of string return success
	if (DL.isEmpty())
		return true;
	else
		//otherwise returns error (Mismatched braces)
		return false;
}

//determines if a the string has valid usage of operations within it. eg 4+4 not 4++4
bool MathFormat::validOperations(string mathInput) {

	//loop through string to find all operations
	for (int i = 0; i < mathInput.length(); i++) {

		//if character matches valid operation, check to make sure operation is used correctly
		if (charInString(mathInput[i], listOfValidOperations)) {

			//check to make sure operation is not at start or end of math input
			if (i == 0 || i == (mathInput.length() - 1)) {
				//if it is return false
				return false;
			}

			//check left and right of operation to verify that it is used properly e.g 2+2
			else {

				//flag variables
				bool leftValue = false;
				bool rightValue = false;

				//first check left
				int left = i - 1;
				while (left >= 0) {
					if (charInString(mathInput[left], listOfNumbers + rightParenthesis)) {
						leftValue = true;
						break;
					}

					if (charInString(mathInput[left], listOfValidOperations + leftParenthesis)) {
						return false;
					}

					left--;
				}

				//then check right
				int right = i + 1;
				while (right <= mathInput.length()) {
					if (charInString(mathInput[right], listOfNumbers + leftParenthesis)) {
						rightValue = true;
						break;
					}

					if (charInString(mathInput[right], listOfValidOperations + rightParenthesis)) {
						return false;
					}

					right++;
				}
				
				//if right or left value are still false, then no number or parentheses was ever hit
				if (rightValue == false || leftValue == false) {
					return false;
				}
			}
		}
	}
	//if it made it through for loop, the string is valid, return true
	return true;
}

//function that removes all unneccesary spaces within a function and returns false if there is a space inbetween two numbers.
bool MathFormat::removeSpaces(string *mathInput) {

	//iterate through math input to find all spaces
	for (int i = 0; i < mathInput->length(); i++) {

		//if character matches a space
		if ((*mathInput)[i] == ' ') {

			//check to make sure space is not at start or end of math input
			if (i == 0 || i == (mathInput->length() - 1)) {
				//if it is move to next character
				mathInput->erase(mathInput->begin() + i);
				i--;
				continue;
			}
			//check left and right of operation to verify that there is not a 4_4.
			else {
				//flag variables
				bool numberLeft = false;
				bool numberRight = false;

				//first check left
				int left = i - 1;
				while (left >= 0) {

					//if char to left is number, then number left
					if (charInString((*mathInput)[left], listOfNumbers)) {
						numberLeft = true;
						break;
					}

					//if char to left is not number, then not number left
					else if (charInString((*mathInput)[left], listOfOperationsParenthesis)) {
						numberLeft = false;
						break;
					}
					//else move to next char and recheck
					else {
						left--;
					}
				}

				//only check right if number to left of space
				if (numberLeft == true) {

					//then check right
					int right = i + 1;
					while (right <= mathInput->length()) {
						//if char to right is number, then number right
						if (charInString((*mathInput)[right], listOfNumbers)) {
							numberRight = true;
							break;
						}

						//if char to right is not number, then not number right
						else if (charInString((*mathInput)[right], listOfOperationsParenthesis)) {
							numberRight = false;
							break;
						}
						//else move to next char and recheck
						else {
							right++;
						}
					}

					//if number right aswell, then there is a number to left and right of space, thus invalid syntax
					if (numberRight == true) {
						//return false
						return false;
					}
				}
				//if not both number left and right then space is okay to be removed
				//remove space
				mathInput->erase(mathInput->begin() + i);
				i--;
				continue;
			}
		}
		else {
			//do nothing
		}
	}
	//if made it through for loop, string is valid and has no #_#
	return true;
}

//function to test wethere there is a specific char within a string
bool MathFormat::charInString(char inchar, string instring) {

	//iterate through all chars in string
	for (int i = 0; i < instring.length(); i++) {
		//check all chars agains in char
		if (inchar == instring[i]) {
			//if found return true
			return true;
		}
	}

	//if not found return false
	return false;
}

string MathFormat::parenthesize(string)
{
	return string();
}
