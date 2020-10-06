#include "MathFormat.h"

MathFormat::MathFormat()
{
}

MathFormat::~MathFormat()
{
}

bool MathFormat::errorCheck(string mathInput)
{
	//check for valid characters all within string
	if (validCharacters(mathInput) == false) {
		return false;
	}


	//verify mathcing parenthesis

	//check for operation in between all numbers slash parenthesis
	//OR all operations have numbers on either side

	//secondary way of multiplication?? 2(4+5)

	return true;
}

//function to verify all characters within string are valid
bool MathFormat::validCharacters(string mathInput) {

	//boolean to keep track if input character matches one character from list of valid characters
	bool match = false;

	//compares each character in input string to list of valid characters
	for (int i = 0; i < mathInput.length(); i++) {
		
		//assume match is false
		match = false;
		for (int j = 0; j < listOfValidCharacters.length(); j++) {
		
			//if character mathces a character from valid charcters, set match to true 
			if (mathInput[i] == listOfValidCharacters[j])
				match = true;
		}

		//if no match found return false, else check next char
		if (match == false)
			return false;
	}

	//if made through for loop return true;
	return true;
}

string MathFormat::parenthesize(string)
{
	return string();
}
