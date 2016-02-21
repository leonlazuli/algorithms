#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

#define DEBUG

bool isPrime(int num)
{
	for(int i = 2; i <= (int)sqrt(num); i++)
	{
		if(num % i == 0)
			return false;
	}
	return true;
}

int nextPrime(int num)
{
	while(true)
	{
		if(isPrime(num))
		{
#ifdef DEBUG
	std::cout << "nextPrime: " << num << std::endl;
#endif
			return num;
		}
		++num;
	}
}

class HashTable;

class HashNode
{
	friend class HashTable;
private:
	const char* value;
	HashNode* next;
public:
	HashNode(const char* s = NULL):value(s),next(NULL){};
	~HashNode()
	{
		////$$$$  注意这里如果delete p 会递归的再次调用析构函数，就导致了一片区域的多次delete
		// HashNode* p = next;
		// while(p != NULL)
		// {
		// 	std::cout << "before p is " << p << std::endl;
		// 	std::cout << "delete is running " << p->next << ' '<< p->value
		// 		 << std::endl;
		// 	HashNode* temp = p->next;
		// 	delete p;
		// 	p = temp;
		// 	std::cout << "after p is " << p << std::endl << std::endl;
		// }
		if(next != NULL)
			delete next;
	}
	const char* getValue() const 
	{
		return value;
	}
	
	void setNext(HashNode* node)
	{
		next = node;
	}
	
};

class HashTable
{
private:
	const int tableSize;
	HashNode** arr;
	
private:
	int hashing(const char* s) const
	{
		int hashValue = 0;
		while(*s != '\0')
		{
			hashValue = (hashValue << 5) + *s; // $$$最开始的时候0左移5位还是0啊
			s += 1;
		}
		hashValue = hashValue % tableSize;
#ifdef DEBUG
		std::cout << "hashValue is: " << hashValue << std::endl;
#endif
		return hashValue;
	}
public:
	HashTable(int size):tableSize(nextPrime(size)),arr(new HashNode*[tableSize])
	{
		for(int i = 0; i != tableSize; i++)
		{
			arr[i] = new HashNode(); // as a head
		}
	}
	~HashTable()
	{
		for(int i = 0; i != tableSize; i++)
		{
			delete arr[i]; // 因为是在这个class中new的，所以destructor中要负责delete掉
		}
		delete[] arr;
	}
	
	void insert(const char* s)
	{
		int index = hashing(s);
		HashNode* newNode = new HashNode(s);
		newNode->next = arr[index]->next;
		arr[index]->next = newNode;
	}
	
	HashNode* find(const char* s) const
	{
		HashNode* p = arr[hashing(s)]->next;
		while( p != NULL)
		{
			if(strcmp(p->value,s) == 0)
				return p;
			p = p->next;
		}
		return p; // p == NULL
	}
	
	void printTable()
	{
		printf("----------HashTable----------\n");
		for(int i = 0; i != tableSize; i++)
		{
			std::cout << i << ": ";
			HashNode* p = arr[i]->next;
			while(p != NULL)
			{
				std::cout << p->value << " ";
				p = p->next;
			}
			std::cout << std::endl;
		}
		printf("-----------------------------\n");
	}
	
};



int main()
{
#ifdef Test
	int candidate = 96;
	std::cout << candidate << " is prime ?" << (isPrime(candidate)?" yes":" no") << std::endl;
	std::cout << "next prime " << nextPrime(153) << std::endl;
#endif
	
	HashTable table(50);
	table.printTable();
	table.insert("hello");
	char hello2[] = {'h','e','l','l','o','\0'};
	table.insert(hello2);
	table.insert("world");
	table.insert("world");
	table.insert("world");
	table.insert("world");
	table.insert("world");
	table.insert("world");
	table.insert("wosld");
	table.insert("wld");
	const char* candidate = "hells";
	HashNode* node = table.find(candidate);
	if(node != NULL)
	{
		std::cout << node->getValue() << " found" << std::endl;
	}
	else
	{
		std::cout << candidate << " not found" << std::endl;
	}
	table.printTable();
	
}