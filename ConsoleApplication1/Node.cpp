/* Copyright (C) 2018
* Course: CO2003
* Author: Rang Nguyen
* Ho Chi Minh City University of Technology
*/

#include "pch.h"
#include"Node.h"

Node::Node(int capacity) {
	maxElements = capacity;
	elements = new int[maxElements];
	numElements = 0;
	prev = next = NULL;
}

Node::~Node() {
	if (elements != NULL)
		delete[] elements;
}

int Node::getHalfNodeSize() {
	return (int)ceil(maxElements / 2.0);
}

bool Node::isUnderHalfFull() {
	return numElements < getHalfNodeSize();
}

bool Node::isFull() {
	return numElements >= maxElements;
}

bool Node::isOverflow() {
	return numElements > maxElements;
}

bool Node::isEmpty() {
	return numElements == 0;
}

void Node::add(int val) {
	if (isFull())
		throw "NodeOverflowExeception";
	else
	{
		elements[numElements] = val;
		numElements++;
	}

}

void Node::insertAt(int pos, int val) {
	if (isFull()) throw "NodeOverflowExeception";
	else if (pos < 0 || pos > numElements) throw "IndexOutOfBoundsException";
	else {
		memmove(elements + pos + 1, elements + pos, (numElements - pos) * sizeof(int));
		elements[pos] = val;
		numElements++;
	}
}

void Node::removeAt(int pos) {
	if (pos < 0 || pos >= numElements) throw "IndexOutOfBoundsException";
	else {
		memmove(elements + pos, elements + pos + 1, (numElements - pos - 1) * sizeof(int));
		numElements--;
	}
}

void Node::reverse() {
	for (int i = 0; i < numElements / 2; i++)
		std::swap(elements[i], elements[numElements - 1 - i]);
}

void Node::print() {
	for (int i = 0; i < numElements; i++)
		printf("%d ", elements[i]);
}

void Node::printDetail() {
	printf("| prev(%d) |", prev);
	for (int i = 0; i < numElements; i++)
		printf(" %d |", elements[i]);
	for (int i = numElements; i < maxElements; i++)
		printf(" X |");
	printf(" next(%d) |\n", next);
}