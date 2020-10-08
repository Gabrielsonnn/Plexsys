//Developer: Gabriel Johnson
//Created for PLEXSYS

#include "ioControl.h"
#include "MathTree.h"
#include "MathFormat.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//main entry point for application
int main() {

	//instantiate class to handle io operations
	ioControl IO;

	//instantiate class to error check and format math input
	MathFormat MF;

	//instantiate class to calculate math
	MathTree<double> MT;

	//declares string pointer to hold input of math equation
	string mathInput;

	//variable to hold error code output
	int correct = 1;

	//variable to hold location of error if there is one
	int charLocation = 0;

	//variable to output value from calculation
	double output = 0;

	//continue running program until closed
	while(1) {

		//uses io class to get input from user and stores it in math input
		IO.Inputstr(&mathInput, "Please input the math eqution to be solved?\n");

		//check if user wants to exit while loop
		if (mathInput == "quit" || mathInput == "exit")
			break;

		//removes all spaces and verifies no spaces between numbers
		correct = MF.removeSpaces(&mathInput, &charLocation);
		
		//if correct is still 1, then check for more errors
		if (correct == 1) {
			correct = MF.errorCheck(mathInput, &charLocation);
		}

		//verify no errors still occured
		if (correct == 1) {

			//variable to hold parenthesized result
			string parInput = "";

			//if passed all error checking parenthesize math input
			if (correct == 1) {

				//parenthesize input following order of operation
				parInput = MF.parenthesize(mathInput);

				//calculate math equation using a tree
				output = MT.calculate(parInput);
			}

			//prints output in a clean manner
			cout << endl << left << "Formatted Input: " << parInput << endl;
			cout << left << "SOLUTION: " << setprecision(5) << output << endl << endl;
		}

		//handles all errors
		else {
			switch (correct) {
			case -1:
				IO.printError("Not all characters within the input are valid.", charLocation, mathInput);
				break;
			case -2:
				IO.printError("Not all braces have matching closing or opening braces, or there are empty braces.", charLocation, mathInput);
				break;
			case -3:
				IO.printError("Not all operation have either a number or brace on both sides.", charLocation, mathInput);
				break;
			case -4:
				IO.printError("There is an empty space between two numbers.", charLocation, mathInput);
				break;
			}
		}

		//clears all values in MathTree in preperation for next calculation
		MT.clear();
	}
}