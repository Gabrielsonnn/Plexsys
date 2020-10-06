#ifndef MATHFORMAT_H
#define MATHFORMAT_H

#include <string>
#include <iostream>

using namespace std;

//A class to handle various error checking and formating of inputted math operations
class MathFormat {
public:
	MathFormat();
	~MathFormat();

	//function to check string for any math errors
	bool errorCheck(string);

	//function to correctly add parenthesis to a math forumla in order to forgoe oder of operation
	string parenthesize(string);

private:
	string listOfValidCharacters = "0123456789()[]{}*+-/. ";

	bool validCharacters(string);
};

#endif // !MATHFORMAT_H
