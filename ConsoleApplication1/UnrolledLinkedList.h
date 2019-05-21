/* Copyright (C) 2018
* Course: CO2003
* Author: Rang Nguyen
* Ho Chi Minh City University of Technology
*/

#pragma once
#include "Node.h"

class UnrolledLinkedList {
private:
	Node* head;
	Node* tail;
	int size;
	int numOfNodes;
	int nodeSize;
public:

	// Your tasks: complete the implementation of the below methods in UnrolledLinkedList.h
	void add(int val);
	bool contains(int val);
	int getAt(int pos);
	void setAt(int pos, int val);
	int firstIndexOf(int val);
	int lastIndexOf(int val);
	void insertAt(int pos, int val);
	void deleteAt(int pos);
	void reverse();
	int* toArray();

	UnrolledLinkedList(int capacity) {
		nodeSize = capacity;
		head = tail = NULL;
		size = numOfNodes = 0;
	}

	~UnrolledLinkedList() {
		Node* p;
		while (p = head) {
			head = head->next;
			delete p;
		}
		size = numOfNodes = 0;
		head = tail = NULL;
	}

	int getSize() { return size; }
	int getHalfNodeSize() { return (int)ceil(nodeSize / 2.0); }

	void print() {
		printf("=================METADATA================\n");
		printf("Size = %d, nodeSize = %d, halfNodeSize = %d\n", size, nodeSize, getHalfNodeSize());
		printf("-----------------CONTENTS----------------\n");
		Node* p = head;
		if (p == NULL) {
			printf("NULL\n");
			return;
		}

		while (p != NULL) {
			// check whether your implementation satisfied the requirements
			if ((p->isUnderHalfFull() && size >= getHalfNodeSize()) ||
				p->isOverflow()) {
				throw "Something wrong with your implementation";
			}
			p->print();
			p = p->next;

		}
		printf("\n-------------------END-------------------\n");
	}

	void printDetail() {
		printf("=================METADATA================\n");
		printf("Size = %d, numOfNodes = %d, nodeSize = %d\n", size, numOfNodes, nodeSize);
		printf("-----------------CONTENTS----------------\n");

		Node* p = head;
		if (p == NULL) printf("NULL\n");
		while (p != NULL) {
			p->printDetail();
			p = p->next;
		}
		printf("-------------------END-------------------\n");
	}
};

