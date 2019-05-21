#include "pch.h"
#include "UnrolledLinkedList.h"

void UnrolledLinkedList::add(int val) {
	// TODO
	Node *temp = head;

	if (head == NULL)
	{
		head = new Node(nodeSize);
		head->add(val);
		tail = head;
		size++;
		numOfNodes++;
		return;
	}

	if (numOfNodes == 1 && !head->isFull())
	{
		head->add(val);
		size++;
		return;
	}

	if (tail->isFull())
	{
		temp = new Node(nodeSize);

		int j = tail->getHalfNodeSize();
		for (int i = 1; i <= nodeSize - j; i++)
		{
			temp->add(tail->elements[j]);
			tail->removeAt(j);
		}

		temp->add(val);

		Node *temp_tail = tail;
		tail->next = temp;
		tail = temp;
		tail->prev = temp_tail;

		size++;
		numOfNodes++;
		return;
	}

	tail->add(val);
	size++;
}

int UnrolledLinkedList::getAt(int pos) {
	if (pos < 0 || pos >= size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not

	// TODO
	Node *temp = head;
	while (temp->numElements <= pos)
	{
		pos = pos - temp->numElements;
		temp = temp->next;
	}

	return temp->elements[pos];
}

void UnrolledLinkedList::setAt(int pos, int val) {
	if (pos < 0 || pos >= size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not

	// TODO
	Node *temp = head;
	while (temp->numElements <= pos)
	{
		pos = pos - temp->numElements;
		temp = temp->next;
	}

	temp->elements[pos] = val;
}


void UnrolledLinkedList::insertAt(int pos, int val) {
	if (pos < 0 || pos > size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not

	// TODO
	if (pos == size)
	{
		add(val);
		return;
	}

	Node *temp_traverse = head;

	// duyet den node can them
	while (pos >= temp_traverse->numElements)
	{
		pos = pos - temp_traverse->numElements;
		temp_traverse = temp_traverse->next;
	}

	// truong hop nodeSize = 1
	if (nodeSize == 1)
	{
		Node* temp_new_node = new Node(nodeSize);
		temp_new_node->add(temp_traverse->elements[0]);
		temp_traverse->elements[0] = val;

		// cap nhat linkedlist
		if (temp_traverse->next != NULL)
		{
			temp_traverse->next->prev = temp_new_node;
			temp_new_node->next = temp_traverse->next;
			temp_new_node->prev = temp_traverse;
			temp_traverse->next = temp_new_node;
		}
		else
		{
			temp_new_node->prev = temp_traverse;
			temp_traverse->next = temp_new_node;
		}

		// cap nhat tail
		if (temp_new_node->next == NULL) tail = temp_new_node;
		size++;
		numOfNodes++;
		return;
	}

	// truong hop nodeSize != 1
	// truong hop them vao node full
	if (temp_traverse->isFull())
	{
		// Cop cac phan tu vao mot array (sau khi chen val vao).
		int* a = new int[nodeSize+1];
		int i;
		for (i = 0; i < pos; i++)
		{
			a[i] = temp_traverse->elements[i];
		}
		i = pos;
		a[i] = val;
		for (int i = pos + 1; i < nodeSize + 1; i++)
		{
			a[i] = temp_traverse->elements[i-1];
		}

		// gan nua gia tri array cho temp_traverse va delete nua con lai
		for (i = 0; i < temp_traverse->getHalfNodeSize()+1; i++)
		{
			temp_traverse->elements[i] = a[i];
		}

		for (i = 1; i <= (nodeSize+1)/2-1; i++)
		{
			temp_traverse->removeAt(nodeSize/2+1);
		}

		// tao moi gan nua gia tri con lai cua array cho temp_new_node
		Node* temp_new_node = new Node(nodeSize);
		for (i = 0; i < (int)ceil(nodeSize / 2.0); i++)
		{
			temp_new_node->add(a[nodeSize / 2 + i + 1]);
		}

		// cap nhat linkedlist
		if (temp_traverse->next != NULL)
		{
			temp_traverse->next->prev = temp_new_node;
			temp_new_node->next = temp_traverse->next;
			temp_new_node->prev = temp_traverse;
			temp_traverse->next = temp_new_node;
		}
		else
		{
			temp_new_node->prev = temp_traverse;
			temp_traverse->next = temp_new_node;
		}

		// cap nhat tail
		if (temp_new_node->next == NULL) tail = temp_new_node;
		size++;
		numOfNodes++;
		return;
	}

	// truong hop them vao node khong full
	int last_int = temp_traverse->elements[temp_traverse->numElements - 1];
	for (int i = temp_traverse->numElements - 1; i > pos; i--)
	{
		temp_traverse->elements[i] = temp_traverse->elements[i - 1];
	}
	temp_traverse->add(last_int);
	temp_traverse->elements[pos] = val;
	size++;
}

void UnrolledLinkedList::deleteAt(int pos)
{
	if (pos < 0 || pos >= size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not

	// TODO
	Node *temp_traverse = head;

	// duyet den node can xoa
	while (pos >= temp_traverse->numElements)
	{
		pos = pos - temp_traverse->numElements;
		temp_traverse = temp_traverse->next;
	}

	// xoa
	temp_traverse->removeAt(pos);
	size--;

	// Neu so phan tu trong array cua node nho hon ceil(maxElements/2)
	if (temp_traverse->isUnderHalfFull())
	{
		if (numOfNodes == 1) return;
		// Neu so phan tu con lai cua array ep vao duoc prev
		if (temp_traverse->prev != NULL) // check xem co phai node dau tien hay khong
		if ((nodeSize - temp_traverse->prev->numElements) >= temp_traverse->numElements)
		{
			while (!temp_traverse->isEmpty())
			{
				temp_traverse->prev->add(temp_traverse->elements[0]);
				temp_traverse->removeAt(0);
			}

			// cap nhat linkedlist
			if (temp_traverse->prev != NULL) temp_traverse->prev->next = temp_traverse->next;
			if (temp_traverse->next != NULL) temp_traverse->next->prev = temp_traverse->prev;
			if (temp_traverse->next == NULL) tail = temp_traverse->prev; // cap nhat tail
			delete temp_traverse;
			numOfNodes--;
			return;
		}
		
		// Neu so phan tu con lai cua array ep vao duoc next
		if (temp_traverse->next != NULL) 
		if ((nodeSize - temp_traverse->next->numElements) >= temp_traverse->numElements)
		{
			while (!temp_traverse->isEmpty())
			{
				int k = temp_traverse->numElements;
				temp_traverse->next->insertAt(0,temp_traverse->elements[k-1]);
				temp_traverse->removeAt(k - 1);
			}

			// cap nhat linkedlist
			if (temp_traverse->next != NULL) temp_traverse->next->prev = temp_traverse->prev;
			if (temp_traverse->prev != NULL) temp_traverse->prev->next = temp_traverse->next;
			if (temp_traverse->prev == NULL) head = temp_traverse->next; // cap nhat head
			delete temp_traverse;
			numOfNodes--;
			return;
		}

		if (temp_traverse->next != NULL)
		{
			temp_traverse->add(temp_traverse->next->elements[0]);
			temp_traverse->next->removeAt(0);
			return;
		}
		
		int x = temp_traverse->prev->numElements;
		temp_traverse->insertAt(0, temp_traverse->prev->elements[x - 1]);
		temp_traverse->prev->removeAt(x - 1);
	}
}

int UnrolledLinkedList::firstIndexOf(int val) {
	// TODO
	Node *temp = head;
	int j = 0;
	while (temp != NULL)
	{
		for (int i = 0; i < temp->numElements; i++)
		{
			if (temp->elements[i] == val) return j;
			j++;
		}
		temp = temp->next;
	}
	return -1;
}

int UnrolledLinkedList::lastIndexOf(int val) {
	// TODO
	Node *temp = head;
	int j = 0;
	int k = -1;
	while (temp != NULL)
	{
		for (int i = 0; i < temp->numElements; i++)
		{
			if (temp->elements[i] == val)
				k = j;
			j++;
		}
		temp = temp->next;
	}
	return k;
}

bool UnrolledLinkedList::contains(int val) {
	// TODO
	Node *temp = head;
	while (temp != NULL)
	{
		for (int i = 0; i < temp->numElements; i++)
		{
			if (temp->elements[i] == val) return true;
		}
		temp = temp->next;
	}
	return false;
}

void UnrolledLinkedList::reverse() {
	// TODO
	for (int i = 0; i < size / 2; i++)
	{
		int temp = getAt(i);
		setAt(i, getAt(size - i - 1));
		setAt(size - i - 1, temp);
	}
}

int* UnrolledLinkedList::toArray() {
	// TODO
	int *array = new int[size];
	int j = 0;
	Node *temp = head;
	while (temp != NULL)
	{
		for (int i = 0; i < temp->numElements; i++)
		{
			array[j] = temp->elements[i];
			j++;
		}
		temp = temp->next;
	}
	return array;
}
