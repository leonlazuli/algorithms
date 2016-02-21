// priority queue 的实现方法之一
//主要是体会了，设计某一种特性，比如npl，但在实现中得时候，并不是直接通过
//npl的定义来找npl，而是通过parent和child npl之间的相对关系，以及一些“初始情况”来
//确定npl的。 这种感觉有点像，知道 a0 a1， 然后用 ai = f（ai - 1） 来算ai


#include <iostream>
#include <exception>
#include <string>
#include <limits>
#include <algorithm>
#include <vector>
#include <assert.h>

template<class ElementType> class LeftistTree;

template<class ElementType> class LeftistNode
{
	friend class LeftistTree<ElementType>;
private:
	ElementType element;
	LeftistNode* left;
	LeftistNode* right;
	int npl; // null path level, min(leftnpl rightnpl), null's npl = -1
public:
	LeftistNode(ElementType value):element(value),left(NULL),right(NULL),npl(0){}
	
	ElementType getElement()
	{
		return element;
	}
	
	LeftistNode* Merge(LeftistNode* tree2)
	{
		return Merge_rec(this,tree2);
	}
	
	LeftistNode* merge_iter(LeftistNode* tree2)
	{
		std::vector<LeftistNode*> rightPath;
		LeftistNode* root1 = this;
		LeftistNode* root2 = tree2;
		while(root1 != NULL && root2 != NULL)
		{
			if(root1->element < root2->element)
			{
				rightPath.push_back(root1);
				root1 = root1->right;
			}
			else
			{
				rightPath.push_back(root2);
				root2 = root2->right;
			}
		}
		assert (root1 != NULL || root2 != NULL);
		if(root1 == NULL) // put the rest in root2's rightPath to rightPath
		{
			while(root2 != NULL)
			{
				rightPath.push_back(root2);
				root2 = root2->right;
			}
		}
		else // put the rest in root1's rightpath to rightPath
		{
			while(root1 != NULL)
			{
				rightPath.push_back(root1);
				root1 = root1->right;
			}
		}
		for(int i = rightPath.size() - 1; i != 0; i-- )
		{
			LeftistNode* child = rightPath[i];
			LeftistNode* parent = rightPath[i-1];
			child->updateNpl();
			parent->right = child;
			if(GetNpl(parent->left) < GetNpl(parent->right))
			{
				SwapChild(parent);
			}
		}
		rightPath[0]->updateNpl();
		return rightPath[0];
		
	}
	
	void PrintNode(int depth)
	{
		PrintBlank(depth);
		std::cout << element << " np" << npl << std::endl;
		if(left != NULL)
			left->PrintNode(depth+1);
		else
		{
			PrintBlank(depth + 1);
			std::cout << "empty leftChild" << std::endl;
		}
		if(right != NULL)
			right->PrintNode(depth+1);
		else
		{
			PrintBlank(depth + 1);
			std::cout << "empty rightChild" << std::endl;
		}
	} 
private:
	void updateNpl()
	{
		npl = std::min(GetNpl(left),GetNpl(right)) + 1;
	}
	LeftistNode* Merge_rec(LeftistNode* tree1, LeftistNode* tree2)
	{
		//@ this return value must be a non-null, and it's npl is 0 
		//@ because it is a new node(npl is set to 0 in constructor), or a leaf node in some tree
		//@ in this case, its npl is also 0 because when that tree is used to merge, it has updated
		//@ all its nodes' npl
		if(tree1 == NULL) //@ both == null ? no  possibility
			return tree2;
		if(tree2 == NULL) 
			return tree1;
		LeftistNode* ret; // new root
		if(tree1->element <= tree2->element)
		{
			tree1->right = Merge_rec(tree1->right,tree2);
			ret = tree1; // tree1 will be the new root
		}
		else
		{
			tree2->right = Merge_rec(tree2->right,tree1);
			ret = tree2;
		}
		if(GetNpl(ret->left) < GetNpl(ret->right)) // violates leftistHeap's property
		{
			SwapChild(ret);
		}
		//$$$ 这种计算，考虑的是parent与child之间的关系，和null 以及leaf的情况
		//而不是直接用定义（看这个node有几个child，它的child有几个node什么的）
		ret->npl = std::min(GetNpl(ret->left),GetNpl(ret->right)) + 1;
		return ret;
	}
	void SwapChild(LeftistNode* node)
	{
		LeftistNode* temp = node->left;
		node->left = node->right;
		node->right = temp;
	}
	int GetNpl(LeftistNode* node)
	{
		if(node == NULL)
			return -1;
		else
			return node->npl;
	}
	static void PrintBlank(const int num)
	{
		for(int i = 0; i != num; i++)
		{
			std::cout << '\t';
		}
	}
	
	
};

template<class ElementType> class LeftistTree
{
private:
	LeftistNode<ElementType>* root;
public:
	LeftistTree(ElementType value):root(new LeftistNode<ElementType>(value)){}
	
	void insert(ElementType value)
	{
		LeftistNode<ElementType>* newNode = new LeftistNode<ElementType>(value);
		root = root->Merge(newNode);
	}
	
	void merge(LeftistTree& tree)
	{
		root = tree.root = root->merge_iter(tree.root);
	}
	
	ElementType deleteMin()
	{
		ElementType ret = root->getElement();
		LeftistNode<ElementType>* left = root->left;
		LeftistNode<ElementType>* right = root->right;
		LeftistNode<ElementType>* temp = root;
		root = left->merge_iter(right);
		delete temp;
		return ret;
	}
	
	void print()
	{
		root->PrintNode(0);
	}
};

int main()
{
	LeftistTree<float> tree(5);
	for(int i = 0; i != 12; i++)
	{
		tree.insert(i);
	}
	tree.print();
	std::cout << "----------------------------------" << std::endl;
	
	LeftistTree<float> tree2(5);
	tree2.insert(2);
	tree2.insert(8);
	tree2.insert(12);
	tree2.insert(4);
	tree2.insert(9);
	tree2.insert(10);
	// tree2.insert(16);
	// tree2.insert(17);
	// tree2.insert(18);
	// tree2.insert(19);
	tree2.print();
	
	std::cout << "----------------------------------" << std::endl;
	tree.merge(tree2);
	tree2.print();
	std::cout << "min: " << tree.deleteMin() << std::endl;
	std::cout << "min: " << tree.deleteMin() << std::endl;
	tree.print();
	
	return 0;
}













































































