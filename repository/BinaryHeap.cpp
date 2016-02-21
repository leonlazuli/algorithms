/*
	这里实现的是从1开始的，实际上heap从0开始也很简单，只是left right 的实现都加了1而已
*/

#include <iostream>
#include <exception>
#include <string>
#include <limits>
#define NDEBUG
#include <assert.h>

template<class ElementType >class BinaryHeap
{
private:
	const int maxHeapSize;
	int currentSize;
	ElementType* arr;
public:
	// maxSize + 1, that one is for the sentinel in index 0
	BinaryHeap(int maxSize):maxHeapSize(maxSize + 1),currentSize(0),arr(new ElementType[maxSize + 1])
	{
		arr[0] = INT_MIN; // as a sentinel
	};
	void insert(ElementType value)
	{
		//$$$ 忘记了检测full的情况
		if(currentSize == maxHeapSize)
			throw std::runtime_error("heap is already full");
		int i = ++currentSize;
		while(value < getParentValue(i)) //$$ 这里用一个for loop， i = 1/2 更方便	
		{
			arr[i] = getParentValue(i);
			i = (i - 1) / 2; //$$ 不用减1， 整数本来就是取下界
		}
		arr[i] = value;
	}
	
	ElementType finMin()
	{
		if(currentSize == 0)
			throw std::runtime_error("the heap is empty");
		return arr[1];
	}
	
	ElementType deleteMin()
	{
		//$$$忘记检查isEmpty的情况
		if(currentSize == 0)
			throw std::runtime_error("the heap is empty");
		ElementType ret = arr[1];
		if(--currentSize == 0)
			return ret;
		ElementType lastElement = arr[currentSize + 1];
		int i = 1;
		int smallerChildIndex;
		ElementType smallerChildValue = findSmallerChildValue(i,smallerChildIndex);
		while(lastElement >= smallerChildValue) // should go deep （percolate down）
		{
			assert(smallerChildIndex != -1);
			arr[i] = smallerChildValue;
			i = smallerChildIndex;
			smallerChildValue = findSmallerChildValue(i,smallerChildIndex);
		}
		arr[i] = lastElement;
		return ret;
	}
	
	void printHeap()
	{
		if(currentSize == 0)
		{
			std::cout << "empty heap." << std::endl;
			return;
		}
		printNode(1,0);
	}
		
private:
	void printNode(int index, int depth)
	{
		for(int i = 0; i != depth; i++)
		{
			std::cout << '\t';
		}
		std::cout << arr[index] << std::endl;
		if(hasLeft(index))
			printNode(2 * index, depth + 1);
		if(hasRight(index))
			printNode(2 * index + 1, depth + 1);
	}
	bool hasLeft(int index)
	{
		return index * 2 <= currentSize;
	}
	bool hasRight(int index)
	{
		return index * 2 + 1 <= currentSize;
	}
	ElementType getParentValue(int index)
	{
		int parentIndex = (index - 1) / 2;
		return arr[parentIndex];
	}
	//$$$ 这里其实不用返回value， 因为返回了index，就可以直接从arr accesss value， 如果没有child返回个index -1 就行了
	ElementType findSmallerChildValue(int index, int& smallerChildIndex) // smallerChildIndex will be "return" too
	{
		if(index * 2 > currentSize)
		{
			#ifndef NDEBUG
			smallerChildIndex = -1;
			#endif
			return INT_MAX; //@@$$ in fact here should return the max value of ElementType 
			               //return a sentinel
		}
		else if(index * 2 + 1 > currentSize )
		{

			smallerChildIndex = index * 2;
			return arr[index * 2]; // only has left child
		}
		else
		{
			if(arr[index * 2] < arr[index * 2 + 1])
				smallerChildIndex = index * 2;
			else
				smallerChildIndex = index * 2  + 1;
			return  arr[smallerChildIndex];
		}
	}
	
};

int main()
{
	BinaryHeap<float> heap(50);
	for(float i = 1; i < 18; i++)
	{
		heap.insert(i);
	}
	heap.deleteMin();
	heap.deleteMin();
	heap.deleteMin();
	heap.deleteMin();
	heap.deleteMin();
	heap.deleteMin();
	heap.deleteMin();
	heap.deleteMin();

	
	heap.printHeap();
}



























































































