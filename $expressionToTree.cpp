#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <vector>
#include <string> 
using namespace std;

// 首先把算法的每一步想清楚了，再开始写。 想的时候先观察规律，至少把简单形式的算法自己的跑通一遍了，再用代码实现。
// 不是非常确定的时候，宁愿把情况多罗列几个，不要用一些很有技巧的东西来把很多种情况放在一个表达式里

void breakPoint(string s)
{
	cout << s << endl;
}

struct Node
{
	string Value;
	Node* Left;
	Node* Right;
	
	Node(string v):Value(v),Left(NULL),Right(NULL){}
};

void innerOrderTraversal(Node* node)
{
	if(node == NULL)
		return;
	innerOrderTraversal(node->Left);
	cout << node->Value << ' ';
	innerOrderTraversal(node->Right);
}

void postOrderTraversal(Node* node)
{
	if(node == NULL)
		return;
	postOrderTraversal(node->Left);
	postOrderTraversal(node->Right);
	cout << node->Value << ' '; 
}

template<class T>
class Stack
{
public:
	const int MaxElement;
private:	
	int Top;
	T* Array;
public:
	Stack(int max):MaxElement(max),Top(-1),Array(new T[max]){}
	bool isFull()
	{
		return Top >= MaxElement - 1;
	}
	bool isEmpty()
	{
		return Top < 0;
	}
	
	void push(T v)
	{
		if(!isFull())
		{
			Array[++Top] = v;
		}
		else
		{
			cout << "Stack don't have enough space" << endl;
		}
	}
	
	int size()
	{
		return Top + 1;
	}
	
	T top()
	{
		if(!isEmpty())
			return Array[Top];
		else
		{
			cout << "Stack is empty" << endl;
			return 0;
		}
	}
	
	void pop()
	{
		if(!isEmpty())
			--Top;
		else
			cout << "Stack is empty, can't pop" << endl;
	}
	
	T popAndTop()
	{
		if(!isEmpty())
			return Array[Top--];
		else
		{
			cout << "Stack is empty, can't popAndTop" << endl;
			return 0;
		}
	}
	
	void dump()
	{
		cout << "stack MaxElement: " << MaxElement << "  Top: " << Top << endl; 
		cout << "elements: ";
		for(int i = 0; i <= Top; i++)
		{
			cout << Array[i] << ' ';
		}
		cout << endl;
	}
	
	
};

bool isOpereator(const string& s)
{
	return s == "+" || s == "-" || s== "*" || s == "/" || s == "(" || s == ")";
}

int inStackPriorityRank(string s)
{
	int ret = -1;
	if(s == "(")
		ret = 0;
	else if(s == "+" || s == "-")
		ret = 1;
	else if(s == "*" || s == "/")
		ret = 2;
	else
	{
		cerr << "invalid operator " << s << endl;
	}
	return ret;
}


void popOperatorAndPushNode(Stack<string>& operatorStack, Stack<Node*>& nodeStack)
{
	breakPoint("pop operator");
	Node* newNode = new Node(operatorStack.popAndTop());
	breakPoint("---------newNode " + newNode->Value);
	breakPoint("pop node");
	Node* rightChild = nodeStack.popAndTop();
	breakPoint("node1: " + rightChild->Value);
	Node* leftChild = nodeStack.popAndTop();
	breakPoint("node 2: " + leftChild->Value);
	newNode->Left = leftChild;
	newNode->Right = rightChild;
	nodeStack.push(newNode);
	nodeStack.dump();

}


Node* convert(string* expression, int size)
{
	Stack<string> operatorStack = Stack<string>(1000);
	Stack<Node*> nodeStack =  Stack<Node*>(1000);
	
	for(int i = 0; i < size; i++)
	{
		string s = expression[i];
		if(isOpereator(s))
		{
			breakPoint("operator " + s + " processing");
			if(s == "(")
				operatorStack.push(s);
			else if(s == ")")
			{
				while(!operatorStack.isEmpty() && operatorStack.top() != "(")
				{
					breakPoint("pop by )");
					popOperatorAndPushNode(operatorStack, nodeStack);
				}
				if(!operatorStack.isEmpty() && operatorStack.top() == "(")
					operatorStack.pop();
			}
			else
			{
				while(!operatorStack.isEmpty() && (inStackPriorityRank(operatorStack.top()) >= inStackPriorityRank(s)))
				{
					breakPoint("pop by priority " + operatorStack.top() + " >= " + s);
					popOperatorAndPushNode(operatorStack, nodeStack);
				}
				operatorStack.push(s);
			}
		}
		else
		{
			Node* node = new Node(s);
			nodeStack.push(node);
			breakPoint("node " + node->Value + " pushed");
		}
		
	}	
	breakPoint("finish input");
	operatorStack.dump();
	while(!operatorStack.isEmpty())
		popOperatorAndPushNode(operatorStack, nodeStack);
	
	if(nodeStack.size() != 1)
	{
		cerr << "invalid expression" << endl;
		return NULL;
	}
	else
	{
		return nodeStack.popAndTop();
	}
	
}

int main()
{
	string expression[] = {"(","a","+","b","*","c",")","+","(","(","d","*","e","+","f",")","*","g",")"};
	//string expression[] = {"(","(","d","*","e","+","f",")","*","g",")"};
	int size = sizeof(expression) / sizeof(expression[0]);
	Node* root = convert(expression, size);
	cout << "result: ";
	innerOrderTraversal(root);
	cout << endl;
	postOrderTraversal(root);
	
}