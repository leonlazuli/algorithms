// 两个错误
// 一个是 == 写成了 =， 这种错误不好找
// 二是 当）pop到（时，需要要（pop出来。
// 另外，textmate的 excption出现的地方通常是不对的， 还是在throwtime的地方加一个print语句比较容易debug




#include <iostream>
#include <exception>
#include <string>

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
	int getCounter()
	{
		return counter;
	}
	int getTopPosition()
	{
		return topOfStack;
	}
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
			throw runtime_error("pop empty stack");
		counter--;
		return array[topOfStack--];
	}
	
	Type top()
	{
		if(topOfStack <= -1)
			throw runtime_error("top empty stack");
		return array[topOfStack];
	}
	
	bool isEmpty()
	{
		return topOfStack == -1; ////////////////////////#
	}
	
	void print()
	{
		std::cout << "Stack:" << std::endl;
		for(int i = 0; i <= topOfStack; i++)
			std::cout << array[i] << " " ;
		std::cout << std::endl;
	}
	
};

template <typename Type> class TreeNode
{
public:
	Type value;
	TreeNode* leftChild;
	TreeNode* rightChild;
public:
	TreeNode(Type v, TreeNode* l = NULL, TreeNode* r = NULL):value(v),leftChild(l),rightChild(r){}
	void setLeft(TreeNode* left) 
	{
		leftChild = left;
	}
	void setLeft(Type value)
	{
		leftChild = new TreeNode(value);
	}
	void setRight(TreeNode* right)
	{
		rightChild = right;
	}
	void setRight(Type value)
	{
		rightChild = new TreeNode(value);
	}
	void visit()
	{
		postPrint(this);
		std::cout << std::endl;
		inorderPrint(this);
	    std::cout << std::endl;
		
	}

private:
	static void inorderPrint(TreeNode* node)
	{
		//////###### a right way is
		if(node != NULL)
		{
			inorderPrint(node->leftChild);
			std::cout << node->value <<' ';
			inorderPrint(node->rightChild);
		}
		
		// if(node->leftChild != NULL)
		// 	inorderPrint(node->leftChild);
		// std:cout << node->value << ' ';
		// if(node->rightChild != NULL)
		// 	inorderPrint(node->rightChild);
	}
	
	static void postPrint(TreeNode* node)
	{
		////////###### a better way is
		// if(node != NULL)
// 		{
// 			PostPrint(node->leftChild);
// 			std::cout << node->value;
// 			postPrint(node->rightChild);
// 		}
		
		if(node->leftChild != NULL)
			postPrint(node->leftChild);
		if(node->rightChild != NULL)
			postPrint(node->rightChild);
		std:cout << node->value << ' ';
	}
	
};

// template <typename Type> class CTree
// {
// private:
// 	TreeNode* root;
// public:
// 	CTree(Type value = NULL):root(new TreeNode(value)){}
// 	void setLeft(TreeNode* left)
// 	{
// 		
// 	}
// 	
// };

bool isDigit(char c)
{
	return (c <= '9' && c >= '0') || (c <= 'z' && c >= 'a');
}

bool isOperator(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isRightParentheses(char c)
{
	return c == ')';
}

bool isLeftParentheses(char c)
{
	return c == '(';  ///////////////////////#
}

int precedence(char c)  // in stack
{
	switch(c)
	{
		case '+':
		case '-': return 1;
		case '*': 
		case '/': return 2;
		case '(': return 0;
		default: cout << "error in precedence " << c << endl;
		throw runtime_error("Non-operator character is read");
	}
}

typedef TreeNode<char> Node;

bool lowerPrecedence(Node* node, CStack<Node*>& stack)
{

	if(stack.isEmpty())
		return false;
	else
	{   
		return precedence(node->value) <= precedence((stack.top())->value);
	}
}

void pushOperator(Node* node, CStack<Node*>& stack)
{
	node->setRight(stack.pop());
	node->setLeft(stack.pop());
	stack.push(node);
}

Node* convertExprToTree(char* input, int size)
{
	CStack<Node*> stackAll;
	CStack<Node*> stackOperator;
	for(int i = 0; i!= size; i++)
	{
		char c = input[i];
		if(isDigit(c))
			stackAll.push(new Node(c));
		else if(isOperator(c))
		{
			Node* tempNode = new Node(c);
			while(lowerPrecedence(tempNode,stackOperator))
			{
				
				Node* popNode = stackOperator.pop();
				pushOperator(popNode, stackAll);
			}
			stackOperator.push(tempNode);
		}
		else if(isLeftParentheses(c))
		{
			
			Node* tempNode = new Node(c);
			stackOperator.push(tempNode);
		}
		else if(isRightParentheses(c))
		{
			
			while(! isLeftParentheses(stackOperator.top()->value))
			{
				Node* popNode = stackOperator.pop();
				pushOperator(popNode, stackAll);
			}
			stackOperator.pop(); // pop the ( node; 
		}
		
	}
	while(!stackOperator.isEmpty())
	{
		
		pushOperator(stackOperator.pop(), stackAll);
	}
	stackAll.pop()->visit();
	//stackAll.pop()->visit();
	//stackAll.pop()->visit();
	return NULL; ///////////&    
	
}

int main()
{
	// cout << isDigit('1') << endl;
	// cout << isDigit('v') << endl;
	// TreeNode<int> root(0);
	// TreeNode<int> n1(1);
	// TreeNode<int> n2(2);
	// TreeNode<int> n3(3);
	// TreeNode<int> n4(4);
	// TreeNode<int> n5(5);
	// TreeNode<int> n6(6);
	// TreeNode<int> n7(7);
	// TreeNode<int> n8(8);
	// TreeNode<int> n9(9); 
	// TreeNode<int> n10(10);
	// root.setLeft(&n1);
	// root.setRight(&n2);
	// n2.setLeft(&n5);
	// n2.setRight(&n6);
	// n1.setLeft(&n3);
	// n3.setLeft(&n7);
	// n1.setRight(&n4);
	// n7.setLeft(&n8);
	// //n7.setRight(&n10);
	// n4.setRight(&n9);
	// root.visit();
	char input[] = {'a','+','b','*','c','+','(','d','*','e','+','f',')','*','g'}; 
	int size = sizeof(input) / sizeof(input[0]);
	Node* root = convertExprToTree(input,size);
	//root->visit();
	
	
}










