// Vector 的效率与内置的数组差不了太多，以后对于指针的数组这类容易出错的的数组，还是用Vector比较好
// 这个算法中坚持使用了 new BasicNode*[10] 这样的代码，是为了检验一些c++的语法和内部运行

#include <iostream>
#include <exception>
#include <string>
#include <assert.h>

class BasicNode // root and interior node
{
	public:
	virtual void Insert(int value) = 0;
	virtual void setAValue(int value) = 0;

	// other absract function port later
};

class LeafNode: BasicNode
{
private:
	const int minNumOfKey;
	const int maxNumOfKey;
	int numOfKey;
	int* keysList;
	BasicNode* parent;
public:
	LeafNode(int order, BasicNode* parentt = NULL):minNumOfKey((order+1)/2),maxNumOfKey(order),numOfKey(0),
			keysList(new int[order], parent(parentt)){}
	BasicNode* Insert(int value)
	{
		
	}
	void setAValue(int value)
	{
		
	}
	
};

class NonLeafNode:public BasicNode //@ just for test c++, now root and interior is same
{
private:
	const int minNumOfChild;
	const int maxNumOfChild;
	int numOfChild; // here if we use Vector, we can avoid using such seperated counter
	int* pivotsList;
	BasicNode** childList;
	BasicNode* parent;
public:
	NonLeafNode(int minNum, int maxNum,BasicNode* parentNode):minNumOfChild(minNum),maxNumOfChild(MaxNum)
				,numOfChild(0), pivotsList(new int[maxNumOfChild], childList(new BaiscNode*[maxNum])
				,parent(parentNode)){}
	
	BasicNode* Insert(int value) // overide, maybe
	{
		if(numOfChild == 0) // no child yet, craete a ~leaf~ node
		{
			childList[0] = new LeafNode(MaxNumOfChild);
			++numOfChild;
			//@ in setAValue, we compare the value with the values already in that node's array, and 
			// store the new value so that the array is still in ascending order
			childList[0]->setAValue(value);   //childList must be a leafNode
						
		}
		
		else // compare the value with pivots
		{
			//根据pivot是不是有，有的话是多少，决定去哪个child，而如果那个child还没有的话，创建一个，然后recursion调用
			// recursion 到最后一步的时候，因为child实际是leafNode的类型了，就会调用Leaf的版本的insert函数，而非这个，
			// 然后在leaf中返回插入后的leafNode（如果插入后leafNode 满了，就split，然后通过parent成员，调用NonleafNode的setValue函数，如果还是慢了，就调用parent的split）
			if(value < pivotsList[0])
				childList[0]->Set
		}
		// insert 结束后， 更新这个node的pivots，如果满了的话， split
		// 然后return这个pivot
	}
	
	void setAValue(int value)
	{
		
	}
	
private:
	// 每一个具体类的重载的virtual函数都只是一个简单的driver， 用来调用本地的recursion版本
	BasicNode* Insert_rec(BasicNode* thisNode， int value) 
	{

		if(numOfChild == 0) // no child yet, craete a ~leaf~ node
		{
			childList[0] = new LeafNode(MaxNumOfChild);
			++numOfChild;
			//@ in setAValue, we compare the value with the values already in that node's array, and 
			// store the new value so that the array is still in ascending order
			childList[0]->setAValue(value);   //childList must be a leafNode
						
		}
		
		else // compare the value with pivots
		{
			//根据pivot是不是有，有的话是多少，决定去哪个child，而如果那个child还没有的话，创建一个，然后recursion调用
			// recursion 到最后一步的时候，因为child实际是leafNode的类型了，就会调用Leaf的版本的insert函数，而非这个，
			// 然后在leaf中返回插入后的leafNode（如果插入后leafNode 满了，就split，然后通过parent成员，调用NonleafNode的setValue函数，如果还是慢了，就调用parent的split）
			if(value < thisNode)
		}
		// insert 结束后， 更新这个node的pivots，如果满了的话， split
		// 然后return这个pivot
	}

	
	
};

// class RootNode: public NodeleafNode
// {
// public:
// 	NodeLeafNode(int order):NonLeafNode(2,order){}
// };
// 
// class InteriorNode: public NonLeafNode
// {
// private:
// 	BasicNode* parent;
// public:
// 	InteriorNode(int order, BasicNode* parentt):NonLeafNode((order+1)/2,order),parent(parentt){}
// };

//@ 现在只规定最大，不规定最小
class BTree // now just a 2-3 tree because I haven't seperate root with interior
{
private:
	BasicNode* root;
public:
	BTree(int order):root(new NonLeafNode(2,3)){}
	void insert(int value)
	{
		insert_rec(root,value);
	}
private:
	void insert_rec(BasicNode root, int value)
	{
		root = root->insert(value); //first insert the key to a leaf(if no leaf, create one)
		// 因为这边的insert是一个多态的函数，所以没办法在这里统一的recursion，反之，需要在每个具体的类中
		//定义不同的virtual重载函数
	}
	
};














































































































