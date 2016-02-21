#include <iostream>
#include <exception>
#include <string>

template <class Type > class Queue
{
private:
	Type* arr;
	int capacity;
	int size;
	int rear;
	int front;
	

private:
	int nextRear( ) // 
	{
		return rear = (rear + 1) % capacity;
	}
	int nextFront()
	{
		return front = (front + 1) % capacity;
	}


public:
	Queue(int arraySize = 10):arr(new Type[arraySize]),capacity(arraySize),rear(0),front(1),size(0){}
	~Queue(){delete[] arr;}
	
	bool isFull()
	{
		return size == capacity;
	}
	
	bool isEmpty()
	{
		return size == 0;
	}
	
	void printState()
	{
		std::cout << "capacity: " << capacity << std::endl;
		std::cout << "size: " << size << std::endl;
		std::cout << "rear: " << rear << std::endl;
		std::cout << "front: " << front << std::endl << "array elements are: ";
		for(int i = 0; i != capacity; i++)
		{
			std::cout << arr[i] << " ";
		}
		std::cout << std::endl;
	}
	
	void enqueue(Type element)
	{
		if(isFull())
			throw std::runtime_error("Try to enqueue a full queue.");
		arr[nextRear()] = element;
		size++;
	}
	
	Type dequeue()
	{
		if(isEmpty())
			throw std::runtime_error("Try dequeue a empty queue.");
		Type ret = arr[front];
		nextFront();
		size--;
		return ret;
	}
	
};

int main()
{
	Queue<std::string> q1;
	for(int i = 0; i != 7; i++)
	{
		q1.enqueue("ruler");
	}
	for(int i = 0; i != 7; i++)
	{
		std::cout << q1.dequeue() << std::endl;
	}
	q1.printState();
	for(int i = 0; i != 7; i++)
	{
		q1.enqueue("ruler");
	}
	for(int i = 0; i != 7; i++)
	{
		std::cout << q1.dequeue() << std::endl;
	}
	q1.printState();
	
	
}