//Developer: Gabriel Johnson

#ifndef MATHFORMAT_H
#define MATHFORMAT_H

#include <string>
#include <iostream>
#include <math.h>
#include "LinkedList.h"

using namespace std;

//A class to handle various error checking and formating of inputted math operations
class MathFormat {
public:
	//constructor
	MathFormat();

	//destructor
	~MathFormat();

	//function to check string for any math errors
	int errorCheck(string, int*);

	//function to remove all spaces from string, and returns wether valid or not.
	int removeSpaces(string*, int*);

	//function to correctly add parenthesis to a math forumla in order to forgoe order of operation
	string parenthesize(string);

private:
	//strings that contain commonly used characters to search against
	string listOfNumbers = "0123456789";
	string listOfValidOperations = "^*/%+-";
	string leftParenthesis = "([{";
	string rightParenthesis = "}])";
	string listOfParenthesis = leftParenthesis + rightParenthesis;
	string listOfNumbersParenthesis = listOfNumbers + listOfParenthesis;
	string listOfOperationNumbers = listOfNumbers + listOfValidOperations;
	string listOfOperationsParenthesis = listOfValidOperations + listOfParenthesis;
	string listOfValidCharacters = listOfValidOperations + listOfParenthesis + listOfNumbers + ". ";

	//function to determine if there is a specified char within a string
	bool charInString(char, string);

	//functions used by errorCheck to check for various errors
	//used to make sure all characters within equation are valid
	bool validCharacters(string, int*);
	//used to verify all parenthesis have a matching parenthesis
	bool matchingParenthesis(string, int*);
	//used to make sure all operations are used validly
	bool validOperations(string, int*);

	//function for finding end of a left parenthesis
	int findEndParenthesisLeft(int, string);
	//function for finding end of a right parenthesis
	int findEndParenthesisRight(int, string);
};

#endif // !MATHFORMAT_H
