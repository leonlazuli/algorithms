#include <iostream>
#include <cmath>
#include <cassert>

bool isPrime(size_t num )
{
	for(int i = 2; i <= (size_t)sqrt(num); i++)
	{
		if(num % i == 0)
			return false;
	}
	return true;
}

size_t findNextPrime(size_t num)
{
	while(!isPrime(num))
	{
		++num;
	}
	return num;
}

class HashTable;

class HashNode
{
	friend class HashTable;
	enum State{empty, legitimate, deleted};
private:
	const char* value;
	State state;
public:
	HashNode(const char* s = NULL):value(s), state(empty){};
	bool isEmpty()
	{
		return state == empty;
	}
	bool isLegitimate()
	{
		return state == legitimate;
	}
	bool isDeleted()
	{
		return state == deleted;
	}
	
};

class HashTable
{
private:
	const size_t tableSize;
	HashNode** arr;
private:
	size_t hashing(const char* s) const
	{
		size_t hashValue = 0;
		while(*s != '\0')
		{
			hashValue = hashValue * 131 + *s++;
		}
		return hashValue % tableSize;
	}

public:
	// here the prime should be twice of the required size, becaue we employ the 
	// quadradic probing, which requires double size.
	HashTable(size_t size):tableSize(findNextPrime(size * 2)),arr(new HashNode*[tableSize])
	{
		//memset(arr,NULL,sizeof(HashNode*));
		for(int i = 0; i != tableSize; i++)
		{
			arr[i] = new HashNode();
		}
	}
	~HashTable()
	{
		for(size_t i = 0; i != tableSize; i++)
		{
			delete arr[i];
		}
			delete [] arr;
	}
	size_t find(const char* s)
	{
		size_t index = hashing(s);
		// size_t i = 0;
		// while(true)
		// {
		// 	size_t newIndex = index + i * i;
		// 	if(arr[newIndex]->isEmpty())
		// 	{
		// 		return newIndex; // is not found, return the right position to insert this string
		// 	}
		// 	else if(arr[newIndex]->isLegitimate() || arr[newIndex]->isDeleted())
		// 	{
		// 		if(strcmp(arr[newIndex]->value, s) == 0) // is found or is deleted
		// 			return newIndex;
		// 		else 
		// 			++i;
		// 	}
		// 	// else if(arr[newIndex]->isDeleted())
		// 	// {
		// 	// 	++i;
		// 	// }
		// 	else 
		// 		assert(false); // should never happens
		// }
		
		// a better code
		int h = 0;
		while(!arr[index]->isEmpty() && strcmp(arr[index]->value,s) != 0)
		{
			index = index + 2 * ++h - 1;
			if(index >= tableSize) //注意这里加了之后，有可能会大于tablesize
				index -= tableSize;
		}
		return index;
	}
	
	void insert(const char* s)
	{
		size_t index = find(s);
		if(arr[index]->isEmpty() || arr[index]->isDeleted())
		{
			arr[index]->value = s;
		}
		// if is already there , do nothing. which means we don't allow multiple instance of same key
		arr[index]->state = HashNode::legitimate;
	}
	void printTable()
	{
		std::cout << "---------------HashTable---------------" << std::endl;
		for(int i = 0; i != tableSize; i++)
		{
			std::cout << i << ": ";
			if(arr[i]->isLegitimate())
				std::cout << arr[i]->value;
			std::cout << std::endl;
		} 
	}
	
};

int main()
{
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
	table.printTable();
	return 0;
}