/* bionomial heap 
这里出过两个找了比较久的bug
一个是某个root被连接到别的root的child位置后，root的位置没有置成NULL
一个是for中index是递减的，可以后面还是写成了递增的，这个bug如果要查起来比较快的话，
应该是，先判断是array或者vector的index越界了，然后排查每个index。还是应该从问题出现
的直接地方开始查起。

-- textbook上 merge一个比较tricky的地方是：
	- 通过 !! 来让一个指针转换为0或者1， 比如 !!Ptr 那么如果Ptr不是NULL，就会返回1，否则返回0，然后用多个这种值相加，就可以case出
	多种不同的组合了。
*/



#include <iostream>
#include <exception>
#include <string>
#include <limits>
#include <algorithm>
#include <vector>
#include <queue>
#include <assert.h>

// 因为是给BioTree使用，而不是直接面向用户的，所以用struct
// 或者因为不打算给用户使用，所以直接用class， 然后所有都private， 再给BioTree一个友元
template<class ElementType> class BioHeap;

template<class ElementType> class BioNode
{
	friend class BioHeap<ElementType>;
	
	ElementType element;
	BioNode* firstChild;
	BioNode* nextSibling;
	#ifndef NDEBUG
	int rank; //@ maybe not necessary
	#endif
	
	BioNode(ElementType value):element(value),firstChild(NULL),nextSibling(NULL)
	{
		#ifndef NDEBUG
		rank = 0;
		#endif
	}
	
	BioNode* add(BioNode* newTree)
	{
		return add1(this,newTree);
	}
	
	BioNode* add1(BioNode* node1, BioNode* node2)
	{
		assert(node1 != NULL && node2 != NULL);
		#ifndef NDEBUG
		if(node1->rank != node2->rank)
		{
			node1->print();
			std::cout << "------" << std::endl;
			node2->print();
			assert(false);
		}
		#endif
		//XXX $$$ 这个算法中，只把parent的第一层child 用nextSibling 连接了， 而
		//实际上，应该把每一层child都链接
		// √√√ 实际上，原本的方法就可以实现bioheap了，加更多的nextSibling反而变得复杂
		// 不应该为了print而改变数据结构本身
		
		if(node1->element < node2->element)
		{
			node2->nextSibling = node1->firstChild;
			node1->firstChild = node2;
			(node1->rank)++;
			return node1;
		}
		//else node1->element >= node2
		node1->nextSibling = node2->firstChild;
		node2->firstChild = node1;
		(node2->rank)++;
		return node2;
	}
	void print()
	{
		std::cout << element << std::endl;
		BioNode* child = firstChild;
		while(child != NULL)
		{
			std::cout << child->element << "  ";
			BioNode* sibling = child->nextSibling;
			while(sibling != NULL)
			{
				std::cout << sibling->element << "  ";
				sibling = sibling->nextSibling;
			}
			std::cout << std::endl;
			child = child->firstChild;
		}
	}
};

//对于merge有好几种返回IDE方式
//作为一个友元函数，返回一个新的bioheap， 被merge的两个bioheap在merge结束后被delete（不delete其数组中得指针）
//或者作为一个成员函数，调用这个函数的instance作为运算结束之后的新的bioheap，而被merge的instance可以选择不管，
//也可以选择在merge结束之后delete（不delete其数组中得指针）

template<class ElementType> class BioHeap
{
private:
	static const int maxHeapRank = 10;
	std::vector<BioNode<ElementType>*> rootArr;
public:
	BioHeap()
	{
		for(int i = 0; i!= maxHeapRank; i++)
			rootArr.push_back(NULL);
	}
	
	void merge(BioHeap& heap2)
	{
		//$$ merge 的时候应该判断， 有没有可能两个merge之后，会超出heap能够表示的范围
		merge1(rootArr, heap2.rootArr);
	}
	
	ElementType deleteMin()
	{
		BioNode<ElementType>* minNode = NULL;
		int minNodeIndex = 0;
		for(int i = 0; i != maxHeapRank; i++ )
		{
			if(rootArr[i] != NULL)
			{
				if(minNode == NULL)
				{
					minNode = rootArr[i];
					minNodeIndex = i;
				}
				else if(minNode->element > rootArr[i]->element)
				{
					minNode = rootArr[i];
					minNodeIndex = i;
				}
			}
		}
		if(minNode == NULL)
		{
			throw std::runtime_error("heap is already empty");
		}
		rootArr[minNodeIndex] = NULL;
		//$$$ minNodeIndex 决定了它的rank，也就可以知道其有几个children，下面这句getNumCHild就不需要了
		int numChild = getNumChildren(minNode);
		BioHeap tempHeap;
		BioNode<ElementType>* child = minNode->firstChild;
		for(int i = numChild; i != 0; i--)
		{
			tempHeap.rootArr[i-1] = child;
			child = child->nextSibling;
			tempHeap.rootArr[i-1]->nextSibling = NULL;
		}
		merge(tempHeap);
		ElementType ret = minNode->element;
		delete minNode;
		return ret;
		
		
	}
	
	bool isEmpty()
	{
		for(int i = 0; i!= maxHeapRank; i++)
		{
			if(rootArr[i] != NULL)
				return false;
		}
		return true;
	}
	
	void insert(ElementType value)
	{
		BioNode<ElementType>* newNode = new BioNode<ElementType>(value);
		for(int i = 0; i != maxHeapRank; i++)
		{
			if(rootArr[i] != NULL)
			{
				newNode = newNode->add(rootArr[i]);
				rootArr[i] = NULL;
			}
			else
			{
				rootArr[i] = newNode;
				break; //$$$
			}
		}
	}
	
	void print()
	{		
		for(int i = 0; i != maxHeapRank; i++)
		{
			if(rootArr[i] == NULL)
				continue;
			rootArr[i]->print();
			std::cout <<"------------------------------------" << std::endl;
			
		}
	}
private:
	// in fact if change the return type to Bio heap, and craete a new heap  
	// as the return heap, this function can be a friend function outside the BioHeap class
	// arr1 will be the new bioHeap's array
	static int getNumChildren(BioNode<ElementType>* node)
	{
		int ret = 0;
		node = node->firstChild;
		while(node != NULL)
		{
			++ret;
			node = node->nextSibling;
		}
		return ret;
	}
	
	void merge1(std::vector<BioNode<ElementType>*>& arr1,  std::vector<BioNode<ElementType>*>& arr2)
	{
		BioNode<ElementType>* carry = NULL;
		for(int i = 0; i != maxHeapRank; i++)
		{
			if(carry != NULL)
			{
				if(arr2[i] != NULL)
				{
					carry = carry->add(arr2[i]);
					arr2[i] = NULL; //$$
				}
				else if(arr1[i] != NULL)
				{
					carry = carry->add(arr1[i]);
					arr1[i] = NULL;
				}
				else
				{
					arr1[i] = carry;
					carry = NULL;
				}
			}
			else
			{
				if(arr1[i] == NULL)
				{
					arr1[i] = arr2[i]; // no matter arr2[i] is null or not
					arr2[i] = NULL;
				}
				else if(arr2[i] != NULL)
				{
					carry = arr1[i]->add(arr2[i]);
					arr1[i] = NULL;
					arr2[i] = NULL;
				}
			}
		}
	}
	
	
};

int main()
{
	BioHeap<float> heap1;
	for(int i = 0; i != 7; i++)
		heap1.insert(2 * i);
	BioHeap<float> heap2;
	for(int i = 0 ; i!= 6; i++)
		heap2.insert(2 * i + 1);
	heap1.print();
	std::cout << "-------heap2-----------" << std::endl;
	heap2.print();
	heap1.merge(heap2);
	std::cout << "---------heap1 + heap2----------" << std::endl;
	heap1.print();
	for(int i = 0; i != 5; i++)
	{
		std::cout << "--------------" << i << "th delete---------------" << std::endl;
		std::cout << "min: " << heap1.deleteMin() << std:: endl;

	}
	for(int i = 0; i != 4; i++)
	{
		heap1.insert(i * 4);
	}
	for(int i = 0; i != 8; i++)
	{
		std::cout << "--------------" << i << "th delete---------------" << std::endl;
		std::cout << "min: " << heap1.deleteMin() << std:: endl;

	}
}




































































