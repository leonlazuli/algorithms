#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <string> 
using namespace std;

// template<class T>
// class Node
// {
// private:
// 	Node(const Node& rhs);
// public:
// 	T Value;
// 	Node* Next;
//
// public:
// 	Node(T v):Value(v),Next(NULL){}
// 	~Node(){delete Next;}
// 	bool isLast()
// 	{
// 		return Next == NULL;
// 	}
// };
// //这里其实可以只声明一个最简单的struct，把所有的复杂度都放到LinkList中，这样就不用记住某些特殊处理（比如NULL）是放在Node中还是LinkList中了。
//
//
// template <class T>
// class LinkList
// {
// private:
// 	Node<T>* _header;
// 	LinkList(const LinkList& rhs);
// public:
// 	LinkList():_header(NULL){}
// 	~LinkList()
// 	{
// 		delete _header;
// 	}
// 	Node<T>* findLastNode()
// 	{
// 		Node<T>* thisNode = NULL;
// 		Node<T>* nextNode = _header;
// 		while(nextNode != NULL)
// 		{
// 			thisNode = nextNode;
// 			nextNode = nextNode->Next;
// 		}
// 		return thisNode;
//
// 	}
// 	void push(T value)
// 	{
// 		Node<T>* newNode = new Node<T>(value);
// 		Node<T>* lastNode = findLastNode();
// 		if(lastNode == NULL)
// 			_header = newNode;
// 		else
// 		{
// 			lastNode->Next = newNode;
// 		}
// 	}
// 	void print()
// 	{
// 		Node<T>* temp = _header;
// 		while(temp != NULL)
// 		{
// 			cout << temp->Value << ' ';
// 			temp = temp->Next;
// 		}
// 		cout << endl;
// 	}
//
//
// };

// 以上是简单的c++版本，目的是为了练习使用模板。

struct Node
{
	int Value;
	Node* Next;
};

Node* FindLastNode(Node* header)
{
	//cout << "find " << endl;
	Node* thisNode = NULL;
	Node* nextNode = header;
	while(nextNode != NULL)
	{
		thisNode = nextNode;
		nextNode = nextNode->Next;
	}
	return thisNode;
}

Node* Push(Node* header, int value)
{
	Node* lastNode = FindLastNode(header);
	Node* newNode = new Node();
	newNode->Value = value;
	newNode->Next = NULL;
	
	if(lastNode == NULL)
		return newNode;
	else
	{
		lastNode->Next = newNode;
		return header;
	}
}

void Destroy(Node* header)
{
	Node* temp = header;
	Node* next = NULL;
	while(temp != NULL)
	{
		next = temp->Next;
		delete temp;
		temp = next;
	}
}

Node* FindNode(Node* header, int value)
{
	Node* temp = header;
	while(temp != NULL)
	{
		if(temp->Value == value)
			return temp;
		temp = temp->Next;
	}
	return NULL;
}

Node* FindPreviousNode(Node* header, int value)
{
	Node* thisNode = NULL;
	Node* nextNode = header;
	while(nextNode != NULL)
	{
		if(nextNode->Value == value)
			return thisNode;
		thisNode = nextNode;
		nextNode = nextNode->Next;
	}
	return NULL;
}

Node* Insert(Node* header, int positionValue, int value)
{
	Node* nodeInPosition = FindNode(header, positionValue);
	if(nodeInPosition == NULL)
		return header;
	Node* newNode = new Node();
	newNode->Value = value;
	newNode->Next = nodeInPosition->Next;
	nodeInPosition->Next = newNode;
	return header;
	
}

Node* Delete(Node* header, int value)
{
	if(FindNode(header,value) == NULL)
		return header;
	Node* previousNode = FindPreviousNode(header,value);
	if(previousNode == NULL) // 要delete的是header
	{
		Node* ret = header->Next;
		delete header;
		return ret;
	}
	else
	{
		Node* temp = previousNode->Next;
		previousNode->Next = temp->Next;
		delete temp;
		return header;
	}
}

void Print(Node* header)
{
	Node* temp = header;
	while(temp != NULL)
	{
		cout << temp->Value << ' ';
		temp = temp ->Next;
	}
	cout << endl;
}



int main()
{
	Node* header = NULL;
	for(int i = 1; i != 10; i++)
	{
		header = Push(header,i * i);
	}
	Print(header);
	header = Delete(header, 16);
	Print(header);
	header = Delete(header, 54);
	Print(header);
	header = Delete(header, 1);
	Print(header);
	header = Delete(header, 4);
	Print(header);
	header = Insert(header, 2, 33);
	Print(header);
	header = Insert(header, 36, 33);
	Print(header);
	header = Insert(header, 33, 333);
	Print(header);
	Destroy(header);
	
}