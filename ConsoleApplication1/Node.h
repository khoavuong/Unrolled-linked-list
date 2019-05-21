/* Copyright (C) 2018
* Course: CO2003
* Author: Rang Nguyen
* Ho Chi Minh City University of Technology
*/

#pragma once
#include <iostream>
// Unrolled Linked List Node 

class Node {
private:
	int maxElements;
public:
	int numElements; // number of elements in this node, up to maxElements
	int* elements; // an array of numElements elements,
	Node *next; // reference to the next node in the list
	Node *prev; // reference to the previous node in the list

	Node(int capacity = 5);
	~Node();
	int getHalfNodeSize();
	bool isUnderHalfFull();
	bool isFull();
	bool isOverflow();
	bool isEmpty();
	void add(int val); // append val element to the end of the node
	void insertAt(int pos, int val); // insert val to position pos of the node
	void removeAt(int pos); // remove the position pos from the node
	void reverse(); // reverse the content of the node
	void print(); // print the content of the node
	void printDetail(); // print the detail content of the node
};



