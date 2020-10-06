#ifndef BINARYTREE_H
#define BINARYTREE_H

#include<iostream>

using namespace std;

template<class T>
class BTNode {
public://declares variables for Binary Tree Node
	T el;//value in node
	BTNode<T> *left = nullptr;//ptr to left node
	BTNode<T> *right = nullptr;//ptr to right node

	BTNode() {//sets both nodes to 0 if no values passed
		left = nullptr;
		right = nullptr;
	}

	BTNode(const T& e, BTNode<T> *l = nullptr, BTNode<T> *r = nullptr) {//sets nodes and el to values passed
		el = e;
		left = l;
		right = r;
	}
};

template<class T>
class BinaryTree {
private:
	BTNode<T> *root;

public:
	BinaryTree() {
		root = nullptr;
	}

	~BinaryTree() {
		clear();
	}

	void clear() {//clears tree starting at root
		clear(root);
		root = nullptr;
	}
	void clear(BTNode<T> *n);//clears tree starting at a node

	void insertNode(const T&);//inserts an element into the tree

	bool searchNode(const T& el) {//searches tree starting at the root
		return searchNode(el, root);
	}
	bool searchNode(const T&, BTNode<T> *n);//searches tree for a element starting at a node

	void preorderPrint() {//prints tree starting at root
		preorderPrint(root);
	}
	void preorderPrint(BTNode<T> *n);//prints tree using an itertive preorder starting at a node
};

#include "BinaryTree.cpp"

#endif // !BINARYTREE_H