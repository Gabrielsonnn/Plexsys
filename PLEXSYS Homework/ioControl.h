#ifndef IOCONTROL_H
#define IOCONTROL_H

#include<string>

using namespace std;

class ioControl {//A class for handling output and input from a command line
public:
	ioControl();
	~ioControl();

	//template <class O> 
	void Output(string out, string extra = "");
	void newLine(int in = 1);
	void Pause();
	//template <typename I> I Input(I in, string lineOut = "");
	void Input(int *in, string lineOut = "");
	void Input(double *in, string lineOut = "");
	void Input(char *in, string lineOut = "");
	void Inputstr(string *in, string lineOut = "");
	void InputCheck(string *input, string question, string chk1 = "", string chk2 = "", string chk3 = "", string errorMessage = "\nError: please enter correct value\n\n");
	void InputCheck(int *input, string question, int greaterThan = -999, int lessThan = -999, string errorMessage = "\nError: please enter correct value\n\n");
};

#include "ioControl.cpp"

#endif // !IOCONTROL_H
