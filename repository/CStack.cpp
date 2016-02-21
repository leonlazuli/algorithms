#include <iostream>
#include <exception>

using namespace std;


template <class Type> class CStack
{
private:
	static const int size = 300;
	Type array[size];
	int counter;
	int topOfStack;
public:
	CStack():counter(0),topOfStack(-1){};
	void push(Type element)
	{
		if(topOfStack >= size - 1)
			throw runtime_error("stack overflow!");
		array[++topOfStack] = element;
		counter++;
	}
	
	Type pop()
	{
		if(topOfStack <= -1)
			throw runtime_error("empty stack");
		counter--;
		return array[topOfStack--];
	}
	void print()
	{
		std::cout << "Stack:" << std::endl;
		for(int i = 0; i <= topOfStack; i++)
			std::cout << array[i] << " " ;
		std::cout << std::endl;
	}
	
};