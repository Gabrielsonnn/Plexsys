//Developer: Gabriel Johnson

#ifndef MATHTREE_H
#define MATHTREE_H

#include<iostream>
#include<string>

using namespace std;

template<class T>
class MNode {
public://declares variables for Math Tree Node
	T el;//value in node
	char middle = ' ';//char variable that will hold operation

	MNode<T>* left = nullptr;//ptr to left node
	MNode<T>* right = nullptr;//ptr to right node

	//flags to determine if the left right and operation nodes are filled
	//1: node has value assinged, 0: node has no value assinged (null), -1: node has not value, but an operation lives above it.
	int leftFilled = 0;
	int middleFilled = 0;
	int rightFilled = 0;

	//sets both nodes to nullptr if no values passed
	MNode() {
		left = nullptr;
		right = nullptr;
	}

	//sets nodes and el to values passed
	MNode(const T& e, MNode<T>* l = nullptr, MNode<T>* r = nullptr) {
		el = e;
		left = l;
		right = r;
	}
};

template<class T>
class MathTree {
private:
	//variable to hold root node
	MNode<T>* root;

	//variables to hold lists of chars to compare against
	string listOfNumbers = "0123456789";
	string listOfOperations = "^*/%+-";
	string leftParenthesis = "([{";
	string rightParenthesis = "}])";
	string listOfParenthesis = leftParenthesis + rightParenthesis;

	//determines if a specific char is in a specified string
	bool charInString(char, string);

	//imports math equation into tree
	int buildTree(int, string, MNode<T>* n);

	//steps through tree and determines value
	double calculateNodes(MNode<T>* n);

public:
	//constructor
	MathTree() {
		root = new MNode<T>(-1);
	}

	//destructor
	~MathTree() {
		clear();
	}

	//functions for clearing tree.
	void clear() {//clears tree starting at root
		clear(root);
		root = new MNode<T>(-1);
	}
	void clear(MNode<T>* n);//clears tree starting at a node

	//calculates math equation and returns the answer as a double
	double calculate(string);

};

#include "MathTree.cpp"

#endif // !MATHTREE_H