// this is a demo of binary search tree
// recuresion的部分我分别用c++ style 和 c style 实现了一遍， 感觉c 
//style更加容易理解，扩展性也更强，（主要表现在对自身是null的情况也可以在这个recursion中处理，
//而c++则必须在parent中就判断child是不是null）那么以后这类的问题，都可以在类中public一个driver函数，
// 然后底层的recursion函数还是可以用c style的。


#include <iostream>
#include <exception>
#include <string>

template<class ValueType> class BinaryTree
{
private: 
	BinaryTree* leftChild;
	BinaryTree* rightChild;
	ValueType value;
public:
	//@ this is a binary search tree， constructor just for contruct the root, all other operations 
	// are done with public port like insert, delete, print
	BinaryTree(ValueType v):value(v),leftChild(NULL),rightChild(NULL){}
	~BinaryTree()
	{
		//releaseNode(this);
		if(leftChild != NULL)
			delete leftChild;
		if(rightChild != NULL)
			delete rightChild;
		/*$$ 这里的经验是，Destruction是递归的调用所有member variable的析构函数，如果
		member的类型的内置的（指针也是！），这部分不需要程序员做。对应的，如果不是内置的，
		则会调用其析构函数，但注意，指针是内置的，所以，不会主动的（delete 某个指针成员），
		这也就是为什么，如果有指针成员，通常都需要析构函数（和配套的copy constructor等）的
		原因。就是要在析构的时候把指针成员所对应的memory也析构了。
		-- 而class中有自己的指针，只是这里的一种特殊情况而已，对于指针来说，delete ptr则是
		~递归~的调用ptr对应对象的析构函数。 所以，因为这种调用本身是递归的，就不用再deconstructor
		里面自己来递归了。也就是说，deconstrutor只管自己的直接的指针成员就可以了*/
	}
	
	void releaseNode(BinaryTree* thisNode)
	{
		if(thisNode != NULL)
		{
			releaseNode(thisNode->leftChild);
			releaseNode(thisNode->rightChild);
			// delete thisNode;
			/* $$$ 这里如果有delete 就会出现segement fault， 因为delete thisNode本身调用的就是
			~BinaryTree(), 而~BinaryTree中又隐式的调用了~BinaryTree（）这样就会导致无穷递归
			*/
			
			
		}
	}
	
	BinaryTree* insert(ValueType v) 
	{
		
		if(v > value)
		{
			if(rightChild == NULL)
				rightChild = new BinaryTree(v);  // here we have donw the connection stuff
			else 
				rightChild =  rightChild->insert(v);  // here we have donw the connection stuff
		}
		else if(v < value)
		{
			if(leftChild == NULL)
				leftChild = new BinaryTree(v);
			else 
				leftChild =  leftChild->insert(v);
		}
		else
		{
			std::cerr << "this value is already in searchi tree";
		}
		return this;
	} 
	
	BinaryTree<ValueType>* find(ValueType v)
	{
		return find_rec(this,v);
	}
	
	BinaryTree* insert_oldStyle(ValueType v)
	{
		insert_rec(this, v); //$$ this is not a good way in c++ 
	} 
	
	BinaryTree* deleteElement_oldStyle(ValueType e)
	{
		
		return delete_rec(this,e);
		
	}
	
	//@ now i'm trying not to return a pointer of tree, 
	//$$ seems that you have to return a pointer of current tree, and assignment it in 
	//$$ upper level like left = left.deleteElement(v), because you when you delete a node
	//$$ you must connect the node that replace the deleted one with its original parent,
	//$$ if you don't return that new node's pointer, then, you have to determine that 
	//$$ right->value == target or left->value == target, then if so, right = right.deleteElement,
	//$$ that's not a good sytle for recursion, because you have to know the state of next recursion
	//$$ whereas if you return current pointer, then, you don't have to know whether the child is
	//$$ equal or not or even a null.
	BinaryTree* deleteElement(ValueType v)
	{
		BinaryTree* ret = this;
		if(v > value)
		{
			if(rightChild == NULL)
				std::cerr << "element not found" << std::endl;
			else
				rightChild = rightChild->deleteElement(v);
		}
		else if(v < value)
		{
			if(leftChild == NULL)
				std::cerr << "element not found" << std::endl;
			else
				leftChild = leftChild->deleteElement(v);
		}
		else // is this node
		{
			if(leftChild != NULL && rightChild != NULL)
			{
				ValueType rightMin = findMin(rightChild);
				value = rightMin;
				rightChild = rightChild->deleteElement(rightMin);
			}
			else 
			{
				if(leftChild == NULL) // also handle 0 children
					ret = rightChild;
				else if(rightChild == NULL)
					ret = leftChild;
				delete this;
			}
		}
		return ret;
	}

	
	void printWholeTree()
	{
		printNode(0);
	}
	
	
private:
	static BinaryTree<ValueType>* find_rec(BinaryTree* thisNode, ValueType v)
	{
		if(thisNode == NULL)
			return NULL;
		if(thisNode->value < v)
			return find_rec(thisNode->rightChild,v);
		else if(thisNode->value > v)
			return find_rec(thisNode->leftChild,v);
		else // is this node
			return thisNode; 
			
	}
	
	//@ still bugs, if this root is a one child node, then , the node call delete will be a null
	//$$ fix this bug by add a new parent layer whose has a memeber variable root.
	static BinaryTree* delete_rec(BinaryTree* thisNode, ValueType e)
	{
		if(thisNode == NULL)
		{
			std::cerr << "element doesn't exist in this node";
		}
		if(e > thisNode->value)
			thisNode->rightChild = thisNode->delete_rec(thisNode->rightChild,e);
		else if (e < thisNode->value)
			thisNode->leftChild = thisNode->delete_rec(thisNode->leftChild,e);
		else // is this node
		{
			if(thisNode->leftChild != NULL && thisNode->rightChild != NULL)
			{
				//$ to assign the pointer with rightMin' pointer is not good
				//$ for this algorithm, because that means we will delelte the 
				//$ memory of thisNode, whereas just move the pointer of other 
				//$ associate node (rightMin and so on), when this recursion reach
				//$ right mean, we can't know whether this is a fake delete(move to other position)
				//$ or a real delete (delete the memory), this different delete action are not
				//$ consisitent. But, if we just the assignment the keyValue, then the node
				//$ that be released is always a node with less than 1 child, that one is much more 				//$ consistent
				// // findMin return the pointer of that node
				// BinaryTree* tempNode = thisNode;
				// thisNode = findMin(thisNode->rightChild); 
				// delete tempNode;
				// delete_rec(rightMin,rightMin.value);
				
				ValueType rightMin= findMin(thisNode->rightChild);
				thisNode->value = rightMin;
				thisNode->rightChild = delete_rec(thisNode->rightChild,rightMin);
			}
			// else if(thisNode->leftChild != NULL)
			// {
			// 	BinaryTree* tempNode = thisNode->leftChild;
			// 	delete thisNode;
			// 	return tempNode;
			// }
			// else if(thisNode->rightChild != NULL)
			// {
			// 	BinaryTree* tempNode = thisNode->rightChild;
			// 	delete thisNode;
			// 	return tempNode;
			// }
			// else // is a leaf
			// {
			// 	delete thisNode;
			// 	return NULL;
			// }
			//$ since last three else all delete thisNode, we can combine them
			else
			{
				BinaryTree* tempNode = thisNode;
				if(thisNode->leftChild == NULL) //also handle 0 children
					thisNode = thisNode->rightChild;
				else if (thisNode->rightChild == NULL)
					thisNode = thisNode->leftChild;
				delete tempNode; // now this Node is already another pointer
			}
		}
		return thisNode;
	}
	
	static ValueType findMin(BinaryTree* thisNode)
	{
		while(thisNode->leftChild != NULL)
		{
			//note that thisNode is a copy of pointer, change this copy won't affect the tree
			// but like thisNode->left = balabala, is different, this will change the memory of 
			// thisNode, and that memory is shared by every poiner point to that node
			thisNode = thisNode->leftChild;
		}
		return thisNode->value;
	}
	void printNode(int height)
	{
		for(int i = 0; i != height; i++) // print indentation according to height of this node
		{
			std::cout << '\t';
		}
		std::cout << value << std::endl;
		if(leftChild != NULL)
			leftChild->printNode(height+1);
		else 
		{
			for(int i = 0; i != height + 1; i++) // print indentation according to height of this node
			{
				std::cout << '\t';
			}
			std::cout << "empty left child" << std::endl;
		}
		if(rightChild != NULL)
		{
			
			rightChild->printNode(height+1);
		}
		else 
		{
			for(int i = 0; i != height + 1; i++) // print indentation according to height of this node
			{
				std::cout << '\t';
			}
			std::cout <<"empty right child" << std::endl;
		}
	}
	static BinaryTree* insert_rec(BinaryTree* thisNode, ValueType v) // maybe too C style, not used
	{
		if(thisNode == NULL)
		{
			return new BinaryTree(v);
		}
		if(v > thisNode->value)
		{
			thisNode->rightChild = insert_rec(thisNode->rightChild, v);
		}
		else if(v < thisNode->value)
		{
			thisNode->leftChild = insert_rec(thisNode->leftChild,v );
		}
		else
		{
			throw std::runtime_error("this value is already in search tree");
		}
		return thisNode;
	} 
		
};

template <class ValueType> class BinarySearchTree
{
private:
	BinaryTree<ValueType>* root;
public:
	BinarySearchTree(ValueType v):root(new BinaryTree<ValueType>(v)){}
	~BinarySearchTree()
	{
		delete root;
	}
	
	void insert(ValueType value)
	{
		root = root->insert(value);
	}
	void deleteElement(ValueType value)
	{
		root = root->deleteElement(value);
	}
	void printWholeTree()
	{
		root->printWholeTree();
	}
	BinaryTree<ValueType>* find(ValueType value)
	{
		return root->find(value);
	}
};


int main()
{
	// BinarySearchTree<int> BST(5);
	// BST.insert(3);
	// BST.insert(7);
	// BST.insert(8);
	// BST.insert(2);
	// BST.insert(6);
	// BST.insert(0);
	// BST.insert(4);
	// BST.insert(9);
	// BST.insert(1);//
	// BST.deleteElement(5);
	// BST.printWholeTree();
	// (BST.find(3))->printWholeTree();
	
    BinarySearchTree<int>* BST	= new BinarySearchTree<int>(5);
	BST->insert(3);
	BST->insert(7);
	BST->insert(8);
	BST->insert(2);
	BST->insert(6);
	BST->insert(0);
	BST->insert(4);
	BST->insert(9);
	BST->insert(1);//
	BST->deleteElement(5);
	BST->printWholeTree();
	BinaryTree<int>* subTree_3 =  BST->find(3);
	//subTree_3->printWholeTree();
	delete BST;
	subTree_3->printWholeTree();
	
	
	
// 	BinarySearchTree<int> BST(1);
// 	for(int i = 2; i!= 10; i++)
// 	{
// 		BST.insert(i);
// 	}
// 	BST.printWholeTree();
// 	BST.deleteElement(1);
// 	BST.printWholeTree();
//
 }













































