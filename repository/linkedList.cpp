#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <exception>

using namespace std;

// this list has a header as sentinel.

struct Node;
typedef Node* List;
typedef Node* Position;

struct Node
{
	int element;
	Node* next;
};

// bool is_empty(List L) // xxx has a header
// {
// 	if(L == NULL)
// 		return true;
// 	else
// 		return false;
// }

bool is_empty(List L)
{
	if(L->next == NULL)
		return true;
	else
		return false;
}

bool is_last(Node* p, List L)
{
	if(p->next == NULL)
		return true;
	else
		return false;
}

Node* find(int x, List L)
{
	Node* p = L;
	while(p != NULL && p->element != x)
		p = p->next;
	return p;
}

Node* find_previous(int x, List L) // return last node means not found
{
	Node* p = L;
	while(p->next != NULL && p->next->element != x)
		p = p->next;
	// if(is_last(p,L))  // if p is the last one, it must indicate that x is not found
// 		return NULL;
	return p;
}

void list_delete(int x, List L)
{
	Node* preNode = find_previous(x, L);

	if(!is_last(preNode,L))
	{
		// Node* nextNextNode = preNode->next->next;
// 		delete preNode->next;
// 		preNode->next = nextNextNode;
		Node* tempCell = preNode->next;
		preNode->next = tempCell->next;
		delete tempCell;
	}

}

void insert(int x, List L, Node* p)
{
	Node* tempNode = new Node;
	if(tempNode == NULL) //!!! note on this check
		throw runtime_error("allocate failed");
	tempNode->element = x;
	tempNode->next = p->next;
	p->next = tempNode;
}

void delete_whole_list(List list)
{
	Node* p = list;
	Node* nextP = p;
	while(p != NULL)
	{
		nextP = p->next;
		delete p;
		p = nextP; // !!!!!!
	}
}

int main()
{
	List list = new Node;
	list->element = -1;
	list->next = NULL;
	insert(2,list,list);
	Node* tempNode = find(2,list);
	cout << tempNode->element << endl;
	list_delete(2,list);
	tempNode = find(2,list);
	cout << tempNode->element;
}