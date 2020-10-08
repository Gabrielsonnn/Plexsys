//Developer: Gabriel Johnson

#ifndef IOCONTROL_H
#define IOCONTROL_H

#include<string>

using namespace std;

class ioControl {//A class for handling output and input from a command line
public:
	//constructor
	ioControl();

	//destructor
	~ioControl();

	void Output(string out, string extra = "");//outputs a string and any extra string data provided
	void newLine(int in = 1);//creates x amount of new lines
	void Pause();//pauses a program

	//outputs a prompt and inputs a variable into various variable types
	void Input(int *in, string lineOut = "");//into int
	void Input(double *in, string lineOut = "");//into double
	void Input(char *in, string lineOut = "");//into char
	void Inputstr(string *in, string lineOut = "");//into string

	//outputs a question and checks the string input against 3 options
	void InputCheck(string *input, string question, string chk1 = "", string chk2 = "", string chk3 = "", string errorMessage = "\nError: please enter correct value\n\n");

	//outputs a question and checks the integer input is within a range
	void InputCheck(int *input, string question, int greaterThan = -999, int lessThan = -999, string errorMessage = "\nError: please enter correct value\n\n");

	//prints an error message, and where the error was located in the specifed string
	void printError(string error, int charLocation, string mathInput);
};

#include "ioControl.cpp"

#endif // !IOCONTROL_H
