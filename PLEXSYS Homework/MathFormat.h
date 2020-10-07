#ifndef MATHFORMAT_H
#define MATHFORMAT_H

#include <string>
#include <iostream>
#include "LinkedList.h"

using namespace std;

//A class to handle various error checking and formating of inputted math operations
class MathFormat {
public:
	MathFormat();
	~MathFormat();

	//function to check string for any math errors
	int errorCheck(string);

	//function to remove all spaces from string, and returns wether valid or not.
	bool removeSpaces(string*);

	//function to correctly add parenthesis to a math forumla in order to forgoe oder of operation
	string parenthesize(string);

private:
	
	
	string listOfNumbers = "0123456789";
	string listOfValidOperations = "+-*/^%";
	string leftParenthesis = "([{";
	string rightParenthesis = "}])";
	string listOfParenthesis = leftParenthesis + rightParenthesis;
	string listOfNumbersParenthesis = listOfNumbers + listOfParenthesis;
	string listOfOperationNumbers = listOfNumbers + listOfValidOperations;
	string listOfOperationsParenthesis = listOfValidOperations + listOfParenthesis;
	string listOfValidCharacters = listOfValidOperations + listOfParenthesis + listOfNumbers + ". ";

	bool charInString(char, string);

	bool validCharacters(string);
	bool matchingParenthesis(string);
	bool validOperations(string);
};

#endif // !MATHFORMAT_H
