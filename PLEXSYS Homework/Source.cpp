#include "ioControl.h"
#include "BinaryTree.h"
#include "MathFormat.h"
#include <iostream>
#include <string>

using namespace std;

/*TODO:
-secondary way of multiplication?? 2(4+5)
-dealing with floats
-specific char for where error occured.
-check if linked list has data leak
 */

//main entry point for application
int main() {

	//instantiate class to handle io operations
	ioControl IO;

	//instantiate class to error check and format math input
	MathFormat MF;

	//declares string pointer to hold input of math equation
	string mathInput;
	while(1) {
		//uses io class to get input from user and stores it in math input
		IO.Inputstr(&mathInput, "Please input the math eqution you would like solved?\n");

		int correct;

		if (!MF.removeSpaces(&mathInput)) {
			correct = -4; 
		}
		else {
			correct = MF.errorCheck(mathInput);
		}

		string parInput = "";

		//if passed all error checking parenthesize math input
		if (correct == 1) {
			parInput = MF.parenthesize(mathInput);
		}

		cout << "Input: " << parInput << endl;
		cout << "Ouput: " << correct << endl;
	}
}