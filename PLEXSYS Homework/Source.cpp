#include "ioControl.h"
#include "BinaryTree.h"
#include "MathFormat.h"
#include <iostream>
#include <string>

using namespace std;

/*TODO:
-secondary way of multiplication?? 2(4+5)
-dealing with floats

 */

//main entry point for application
int main() {

	//instantiate custom class to handle io operations
	ioControl IO;
	MathFormat MF;

	//declares string pointer to hold input of math equation
	string mathInput;

	//uses io class to get input from user and stores it in math input
	IO.Inputstr(&mathInput, "Please input the math eqution you would like solved?\n");

	bool correct = MF.errorCheck(mathInput);

	/*BinaryTree<int> bt;

	bt.insertNode(5);
	bt.insertNode(0);

	bt.preorderPrint();*/


	cout << "Ouput: " << correct;
}