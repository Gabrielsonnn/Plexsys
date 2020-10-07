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

//determines if all parenthesis are matching and that there are no empty braces
bool MathFormat::matchingParenthesis(string mathInput) {
	
	//instantiates doubly linked list
	DoublyLinkedList<char> DL;
	
	//declares chars to hold values
	char ch, chTmp;
	char chLast = ' ';

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

			//assume no error for empty brace check
			error = false;

			//switch statement to verify there are no empty braces
			switch (chLast) {
			case '(':
				if (ch == ')')
					error = true;//error, last char and current char are matching, thus empty braces
				break;

			case '[':
				if (ch == ']')
					error = true;//errror, last char and current char are matching, thus empty braces
				break;

			case '{':
				if (ch == '}')
					error = true;//error, last char and current char are matching, thus empty braces
				break;
			}

			if (error == true) {
				return false;//returns error (Empty Braces)
			}
		}
		else;//do nothing for other characters

		//set ch last to ch to maintain what the last char was to check for empty braces
		chLast = ch;
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


//adds parenthesis to all operations within math input based on order of operation.
string MathFormat::parenthesize(string mathInput)
{

	//go through list of operators, which is listed in order of operation
	for (int i = 0; i < listOfValidOperations.length(); i++) {

		//loop through math input searching for current math operation
		for (int j = 0; j < mathInput.length(); j++) {

			//if matching operation for current operator, add parenthesis
			if (listOfValidOperations[i] == mathInput[j]) {

				//first check left
				int left = j - 1;
				while (left >= 0) {
					
					//if next character is a number, add parenthesis to left
					if (charInString(mathInput[left], listOfNumbers)){
						
						//decrement left to check value next to found number
						left--;
						
						//keep checking left to see if number continues
						while (left >= 0) {

							//if next char is not in list of numbers or decimal, break
							if (!charInString(mathInput[left], listOfNumbers + ".")) {
								break;
							}

							//move to next char
							left--;
						}
						
						//increment to get back to actual end of number string
						left++;
						
						//add parenthesis to left of number
						mathInput.insert(mathInput.begin() + left, '(');

						//break
						break;
					}

					//if next character is a parenthesis, find end of parenthesis pair, and add parenthesis to left
					if (charInString(mathInput[left], rightParenthesis)) {

						//find and return index of where end of parenthesis is
						left = findEndParenthesisLeft(left, mathInput);

						//then add parenthesis to left of where end of parenthesis pair is
						mathInput.insert(mathInput.begin() + left, '(');

						//break
						break;
					}

					//decrement left to find number or parenthesis
					left--;
				}

				//then check right

				//add two to account for added left parenthesis
				int right = j + 2;
				while (right <= mathInput.length()) {

					//if next character is a number add parenthesis to right
					if (charInString(mathInput[right], listOfNumbers)) {

						//increment right to check value next to found number
						right++;

						//keep checking right to see if number continues
						while (right <= mathInput.length()) {

							//if next char is not in list of numbers or decimal, break
							if (!charInString(mathInput[right], listOfNumbers + ".")) {
								break;
							}

							//move to next char
							right++;
						}

						//increment to get back to actual end of number string
						right--;

						//add parenthesis to right of number
						mathInput.insert(mathInput.begin() + right + 1, ')');//adds to right + 1 to put brace on right side of char

						//break
						break;
					}

					//if next character is a parenthesis, find end of parenthesis pair, and add parenthesis to left
					if (charInString(mathInput[right], leftParenthesis)) {

						//find and return index of where end of parenthesis is
						right = findEndParenthesisRight(right, mathInput);

						//then add parenthesis to left of where end of parenthesis pair is
						mathInput.insert(mathInput.begin() + right + 1, ')');//adds to right + 1 to put brace on right side of char

						//break
						break;
					}

					//increment right to find number or parenthesis
					right++;
				}

				//at end increment j once, to account for added parenthesis on left side of index in string
				j++;
			}
		}
	}

	return mathInput;
}

//gets index of string for matching right parenthesis to left parenthesis
int MathFormat::findEndParenthesisLeft(int index, string input) {

	//move one to left, to move past right brace
	index--;

	//scan for end brace
	while (index >= 0) {

		//if left parenthesis is found return index
		if (charInString(input[index], leftParenthesis))
			return index;

		//if right parenthesis is found, find matching left parenthesis
		if (charInString(input[index], rightParenthesis))
			index = findEndParenthesisLeft(index, input);

		//do nothing for any other characters

		//decrement index and keep scanning
		index--;
	}

	//if finishes loop return index
	return index;
}

//gets index of string for matching left parenthesis to right parenthesis
int MathFormat::findEndParenthesisRight(int index, string input) {

	//move one to right, to move past left brace
	index++;

	//scan for end brace
	while (index <= input.length()) {

		//if right parenthesis is found return index
		if (charInString(input[index], rightParenthesis))
			return index;

		//if left parenthesis is found, find matching right parenthesis
		if (charInString(input[index], leftParenthesis))
			index = findEndParenthesisRight(index, input);

		//do nothing for any other characters

		//increment index and keep scanning
		index++;
	}

	//if finishes loop return index
	return index;
}
