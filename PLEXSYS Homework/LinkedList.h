//Developer: Gabriel Johnson

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

using namespace std;

template<class T>
class DLLNode {//the individual nodes within the linked list
public:
	T info;
	DLLNode *next, *prev;//declares next and previous which are pointers to other nodes

	DLLNode() {
		next = nullptr;//constructor for node sets next and prev to null
		prev = nullptr;
	}

	DLLNode(const T& el, DLLNode *n = nullptr, DLLNode *p = nullptr) {//constructor for node sets values to specified values
		info = el;
		next = n;
		prev = p;
	}
};

template<class T>
class DoublyLinkedList {//linked list class for contaning nodes
protected:
	DLLNode<T> *head, *tail, *current;//declares head and tail variables
	int length;

public:

	DoublyLinkedList() {//constructor for class
		head = nullptr;//sets head and tail to null
		tail = nullptr;
		current = nullptr;
		length = 0;
	}
	
	//destructor for deleting all nodes within the doubly linked list
	~DoublyLinkedList() {
		if (!this->isEmpty()) {
			while (head == nullptr) {
				deleteTail();
			}
		}
	}

	int getLength() { return length; }//gets length

	T getCurrent();//gets current value
	T getNthNode(int);//gets nth node
	int incCurrent();//increments current value
	int decCurrent();//decrements current value
	void addTail(const T&);//adds tail
	void deleteHead();//deletes head
	T deleteTail();//deletes tail
	int deleteNode(const T&);//finds and deletes node
	void sortList();//sorts nodes
	void swapData(DLLNode<T>*, DLLNode<T>*);//swaps two nodes data values
	int searchNode(const T& el);//search nodes and returns a 1 or a 0 if found
	DLLNode<T>* findNode(const T&);//searches for a node and return the node
	int isEmpty();//retruns 1 if empty and 0 if not
	void printAll();//prints all the data in the nodes

};

#include "LinkedList.cpp"
#endif // !LINKEDLIST_H