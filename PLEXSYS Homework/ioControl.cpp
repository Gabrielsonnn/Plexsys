//Developer: Gabriel Johnson

#pragma once
#include<iomanip>
#include<iostream>
#include<string>

#include "ioControl.h"

using namespace std;

//constructor
ioControl::ioControl() {
}

//destructor
ioControl::~ioControl() {
}


//to output a string
void ioControl::Output(string out, string extra) {
	cout << out << extra;
}


//pauses program
void ioControl::Pause() {
	string garbage;
	cout << "Press ENTER to continue. . .";
	getchar();
}

//outputs \n
void ioControl::newLine(int in) {
	for (int i = 0; i < in; i++)
		cout << endl;
}


void ioControl::Input(int *in, string lineOut) {
	cout << lineOut;//outputs prompt
	cin >> *in;//inputs variable
	cin.ignore();//removes \n
}

void ioControl::Input(double *in, string lineOut) {
	cout << lineOut;//outputs prompt
	cin >> *in;//inputs variable
	cin.ignore();//removes \n
}

void ioControl::Input(char *in, string lineOut) {
	cout << lineOut;//outputs prompt
	cin >> *in;//inputs variable
	cin.ignore();//removes \n
}

void ioControl::Inputstr(string *in, string lineOut) {
	cout << lineOut;//outputs prompt
	getline(cin, *in);//inputs variable
}



void ioControl::InputCheck(string *input, string question, string chk1, string chk2, string chk3, string errorMessage) {
	bool cont = false;
	while (cont == false) {
		Inputstr(input, question);//gets input
		bool c1 = false;//bools for individual checks
		bool c2 = false;
		bool c3 = false;
		bool noC = true;

		if (chk1 != "") {
			noC = false;
			if (*input == chk1)
				c1 = true;//sets true if check is correct
		}

		if (chk2 != "") {
			noC = false;
			if (*input == chk2)
				c2 = true;//sets true if check is correct
		}

		if (chk3 != "") {
			noC = false;
			if (*input == chk3)
				c3 = true;//sets true if check is correct
		}

		if (noC == true || (noC == false && (c1 || c2 || c3)))//set continue to true if all checks are correcct
			cont = true;

		if (cont == false)//if not outputs error msg
			Output(errorMessage);
	}
}

void ioControl::InputCheck(int *input, string question, int greaterThan, int lessThan, string errorMessage) {//test for wether an input is both greater than or less than value
	bool cont = false;
	while (cont == false) {//only continues if input is valid
		Input(input, question);//gets input
		bool greater = true;//bools for greater than and less than
		bool less = true;

		if (greaterThan != -999) {//checks greater than if value inputted
			greater = false;
			if (*input >= greaterThan)
				greater = true;
		}

		if (lessThan != -999) {//checks less than if value inputted
			less = false;
			if (*input <= lessThan)
				less = true;
		}

		if (greater && less)//continues if both greater and less than are true
			cont = true;

		if (cont == false)
			Output(errorMessage);//outputs error message
	}
}

//function for printing out errors messsages, and specifying where the error occured.
void ioControl::printError(string error, int charLocation, string mathInput) {
	
	//print out error message
	cout << endl << "ERROR: " << error << endl;

	//print out input
	cout << mathInput << endl;

	//print out where occured
	for (int i = 0; i <= charLocation; i++) {
		
		//if error occured print out carrot
		if (i == charLocation) {
			cout << '^';
		}
		//if error didn't occur yet, print an empty space
		else {
			cout << ' ';
		}
	}

	//add two new lines
	cout << endl << endl;
}
