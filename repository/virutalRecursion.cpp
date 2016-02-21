/* 作为对在重载虚函数中用指针调用这个重载虚函数的例子（类似于递归，但是调用的可能实际上不是同一个函数）， 为了加深对于递归，function stack的理解
另外在 $$$处还尝试了导致无穷递归，然后fix它，让其不会不穷递归，加深对递归的理解。*/



#include <iostream>
#include <stdlib.h>
#include <string>
#include <exception>


 
class Basic
{
protected:
	int value;
	Basic* child;
public:
	Basic():value(-1),child(NULL){}; // -1 indicate not be assigned a value yet
	virtual Basic* PassValue(int value) = 0;
	virtual void SetValue(int value) = 0;
	virtual void PrintNode(int depth) = 0;
	virtual void SetChild(Basic* node)
	{
		child = node;
	}
};


class LeafNode: public Basic
{
public:
	Basic* PassValue(int v) //@ not used, but if comment it, what happens?
	{
		if(value != -1) // old Leaf
		{
			SetValue(v);
			//$$$ 因为passvalue每调用一次，都会产生一个新的node，所以insert一次，tree的depth会增长一倍
			//更具体的说，先从PassValue一直遍历到树的最底端，然后开始返回，每个返回都会增加一个新的node
			if(child != NULL) 
				child = child->PassValue(v);
			
			 Basic* ret = new LeafNode();
			ret->SetValue(v);
			ret->SetChild(this);
			

			return ret;
		
		}
		SetValue(v);
		return this;
			
	} 
	void SetValue(int v)
	{
		if(value == -1)
			value = v;
		else
			value *= v;
	}
	void PrintNode(int depth)
	{
		for(int i = 0; i != depth; i++)
		{
			std::cout <<"\t";
		}
		std::cout << value << " leaf" << std::endl;
		if(child != NULL)
			child->PrintNode(depth + 1);
	}
};

class InteriorNode: public Basic
{

public:
	Basic* PassValue(int v)
	{
		SetValue(v);
		if(child == NULL)
			child = new LeafNode();
		child = child->PassValue(v);
		return this;
		
			
 	} 
 	void SetValue(int v)
	{
		if(value == -1)
			value = v;
		else
			value += v;
	}
	void PrintNode(int depth)
	{
		for(int i = 0; i != depth; i++)
		{
			std::cout << "\t";
		}
		std::cout << value << " interior"<< std::endl;
		child->PrintNode(depth + 1);
	}
};


class TestTree
{
private:
	Basic* root;
public:
	TestTree():root(new InteriorNode()){}
	void Insert(int value)
	{
		root->PassValue(value);
	}
	void PrintTree()
	{
		root->PrintNode(0);
	}
};

int main()
{
 	TestTree tree;
	for(int i = 1; i != 6; i++)
	{
		tree.Insert(i);
		tree.PrintTree();
		std::cout << "-------------------------------------------------------------------------" << std::endl;
		
	}
}

























































