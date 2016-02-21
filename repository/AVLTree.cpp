// AVLTree balanced binarySearchTree
// 生成的树在textbook p115


#include <iostream>
#include <exception>
#include <string>
#include <assert.h>

template <class KeyType> class AVLTree;

template <class KeyType> class AVLNode
{
	friend class AVLTree<KeyType>;
private:
	KeyType value;
	AVLNode* left; // left child
	AVLNode* right;
	int height;
public:
	AVLNode(KeyType k):value(k),left(NULL),right(NULL),height(0){}
	~AVLNode()
	{
		if(left != NULL)
			delete left;
		if(right != NULL)
			delete right;
	}
	void setLeft(AVLNode* leftChild)
	{
		left = leftChild;
	}
	void setRight(AVLNode* rightChild)
	{
		right = rightChild;
	}
	int getHeight()
	{
		return height;
	}
	void setHeight(int h)
	{
		height = h;
	}
	void updateHeight()
	{
		height = Max(Height(left),Height(right)) + 1;
	}
	int Height(AVLNode<KeyType>* avlNode)
	{
		if(avlNode == NULL)
			return -1;
		else
			return avlNode->getHeight();
	}
	int Max(int a, int b)
	{
		if(a > b)
			return a;
		return b;
	}
};

template <class KeyType> class AVLTree
{
private:
	AVLNode<KeyType>* root;
public:
	AVLTree(KeyType k):root(new AVLNode<KeyType>(k)){}
	~AVLTree(){delete root;}
	
	void insert(KeyType value)
	{
		//$$  remeber here root may also change, it has no difference with any other AVLNode
		root = insert_rec(root, value); 
	}
	void printTree()
	{
		printNode(root,0);
	}
	
private:
	void printNode(AVLNode<KeyType>* thisNode,int height)
	{
		for(int i = 0; i!= height; i++)
		{
			std::cout << "\t";
		}
		std::cout  << thisNode->value << " h-" << thisNode->height << std::endl;
		if(thisNode->left != NULL)
			printNode(thisNode->left,height + 1);
		else
		{
			for(int i = 0; i!= height + 1; i++)
			{
				std::cout << "\t";
			}
			std::cout << "empty left child" << std::endl;
		}
		if(thisNode->right != NULL)
			printNode(thisNode->right, height + 1);
		else
		{
			for(int i = 0; i!= height + 1; i++)
			{
				std::cout << "\t";
			}
			std::cout << "empty right child" << std::endl;
		}
		
			
	}
	AVLNode<KeyType>* insert_rec(AVLNode<KeyType>* thisNode, KeyType value)
	{
		if(thisNode == NULL) // should insert here
		{
			return new AVLNode<KeyType>(value);
		}
		if(value >thisNode->value)
		{
			thisNode->right = insert_rec(thisNode->right, value);
			// insert_rec for right child is already returned, and its
			// height is already updated.
			if(Height(thisNode->right) - Height(thisNode->left) > 1) // unbalanced
			{
				// since we perform a insert, thisNode->right can't be NULL
				if(value > thisNode->right->value) // RR
				{
					thisNode = RightRightRotate(thisNode,thisNode->right);
				} 
				else if (value < thisNode->right->value)
				{
					thisNode = RightLeftRotate(thisNode,thisNode->right);
				}
				else 
				{
				//since this insertion cause a unbalance, right->value will never equals value
					std::cout << "right child: " << thisNode->right->value << " height: " 
						<< thisNode->right->height << std::endl;
					std::cout << "left child " << thisNode->left->value << " height: " 
						<< thisNode->left->height << std::endl;
					std::cout << "value: " << value << std::endl;
					printTree();
					assert(false); 
					//$ 这里这个用法其实不好，因为没有通过assert中得expression来表达为啥这里错了。
				}	
			}
		}
		else if(value < thisNode->value)
		{
			thisNode->left = insert_rec(thisNode->left, value);
			if(Height(thisNode->left) - Height(thisNode->right) > 1)
			{
				if(value < thisNode->left->value)
					thisNode = LeftLeftRotate(thisNode,thisNode->left);
				else if(value > thisNode->left->value)
					thisNode = LeftRightRotate(thisNode,thisNode->left);
				else
				{
					assert(false);
				}
			}
		}
		else
		{
			std::cerr << "this element is already in tree" << std::endl;	
		}
		// remeber to update the height of current node
		thisNode->height = Max(Height(thisNode->left),Height(thisNode->right)) + 1;
		// //DEBUG
		// if(thisNode->value == 6)
		// {
		// 	printNode(thisNode,0);
		// 	std::cout << "----------------------------------------------" << std::endl;
		// }
		// //DEBUG
		return thisNode;
	}
	int Max(int a, int b)
	{
		if(a > b)
			return a;
		return b;
	}
	AVLNode<KeyType>* RightRightRotate(AVLNode<KeyType>* thisNode,AVLNode<KeyType>* rightNode)
	{
		thisNode->right = rightNode->left;
		rightNode->left = thisNode;
		
		//$$$ remember to update the height of node that rotate from parent to child
		// because it won't have chance to update in insert_rec if it rotate to a child position
		thisNode->updateHeight(); 
		return rightNode;
	}
	AVLNode<KeyType>* RightLeftRotate(AVLNode<KeyType>* thisNode, AVLNode<KeyType>* rightNode)
	{
		//$ since insert cause unbalance and key is less than thisNode->right, thisNode->right->left 
		// won't be NULL
		assert(rightNode->left != NULL);
		AVLNode<KeyType>* rightLeftNode = rightNode->left; 
		thisNode->right = rightLeftNode->left;
		rightNode->left = rightLeftNode->right;
		rightLeftNode->left = thisNode;
		rightLeftNode->right = rightNode;
		
		thisNode->updateHeight();
		rightNode->updateHeight();
		return rightLeftNode;
	}
	AVLNode<KeyType>* LeftLeftRotate(AVLNode<KeyType>* thisNode, AVLNode<KeyType>* leftNode)
	{
		thisNode->left = leftNode->right;
		leftNode->right = thisNode;
		
		thisNode->updateHeight();
		return leftNode;
	}
	AVLNode<KeyType>* LeftRightRotate(AVLNode<KeyType>* thisNode, AVLNode<KeyType>* leftNode)
	{
		assert(leftNode->right != NULL);
		AVLNode<KeyType>* leftRightNode = leftNode->right;
		leftNode->right = leftRightNode->left;
		thisNode->left = leftRightNode->right;
		leftRightNode->right = thisNode;
		leftRightNode->left = leftNode;
		
		thisNode->updateHeight();
		leftNode->updateHeight();
		return leftRightNode; 
	}
	int Height(AVLNode<KeyType>* avlNode)
	{
		if(avlNode == NULL)
			return -1;
		else
			return avlNode->getHeight();
	}
};

int main()
{
	AVLTree<int> avlTree(3);
	avlTree.insert(2);
	avlTree.insert(1);
	for(int i = 4; i != 8; i++)
	{
		avlTree.insert(i);
	}
	for(int i = 16; i!= 9; i--)
	{
		avlTree.insert(i);
	}
	avlTree.insert(8);
	avlTree.insert(9);
	avlTree.printTree();
	return 0;
}






















































































































