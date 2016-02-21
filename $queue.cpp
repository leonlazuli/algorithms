#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <vector>
#include <string> 
using namespace std;

//queue的话，记住front gear size 就可以了

template<class T>
class Queue
{
private:
	int front;
	int rear;
	int size;
	int capacity;
	T* array;

private:
	void moveFront()
	{
		if(front + 1 >= capacity)
			front = 0;
		else
		{
			++front;
		}
		--size;
	}	
	
	void moveRear()
	{
		if(rear + 1 >= capacity)
			rear = 0;
		else
			++rear;
		++size;
	}

public:
	Queue(int capa = 10):front(0),rear(0),size(0),capacity(capa),array(new T[capa]){}
	~Queue(){delete [] array;}
	
	void enqueue(T value)
	{
		if(size >= capacity)
		{
			cerr << "queue is full" << endl;
			return;
		}
		array[rear] = value;
		moveRear();
	}
	
	T dequeue()
	{
		if(size <= 0)
		{
			cerr << "queue is empty" << endl;
			return -1;
		}
		T ret = array[front];
		moveFront();
		return ret;
	}
	
	void dump()
	{
		cout << "dump: "; 
		for(int i = 0; i != capacity; i++)
		{
			cout << array[i] << ' ';
		}
		cout << endl;		
	}
	
	
};


int main()
{
	Queue<int> queue;
	
	for(int i = 0; i != 10; i++)
	{
		queue.enqueue(i * i);
	}
	queue.dump();
	cout << queue.dequeue() << endl;
	cout << queue.dequeue() << endl;
	queue.enqueue(33);
	queue.enqueue(333);
	cout << queue.dequeue() << endl;
	cout << queue.dequeue() << endl;
	cout << queue.dequeue() << endl;
	cout << queue.dequeue() << endl;
	cout << queue.dequeue() << endl;
	cout << queue.dequeue() << endl;
	cout << queue.dequeue() << endl;
	cout << queue.dequeue() << endl;
	cout << queue.dequeue() << endl;
	cout << queue.dequeue() << endl;

	
}
