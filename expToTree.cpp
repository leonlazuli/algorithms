#include <iostream>
#include <stack>
using namespace std;

struct Node
{
	Node(char v)
	{
		value = v;
		left = NULL;
		right = NULL;
	}
	char value;
	Node* left;
	Node* right;
};

typedef Node* Tree;


void PreOrder(Node* node)
{
	if(node != NULL)
	{
		cout << node->value << " ";
		PreOrder(node->left);
		PreOrder(node->right);
	}
}

void PostOrder(Node* node)
{
	if(node != NULL)
	{
		PostOrder(node->left);
		PostOrder(node->right);
		cout << node->value << " ";
	}
}

void MidOrder(Node* node)
{
	if(node != NULL)
	{
		MidOrder(node->left);
		cout << node->value << " ";
		MidOrder(node->right);
	}
}

bool IsOperator(char c)
{
	switch(c)
	{
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
		case ')':
		return true;
		default: return false;
	}
}

bool IsAddSub(char c)
{
	return c == '+' || c == '-';
}

bool IsMulDiv(char c)
{
	return c == '*' || c == '/';
}

bool IsOperand(char c)
{
	return c <= '9' && c >= '0';
}

void PopUntilMeetLeft(stack<Node*>& nodesStack, stack<char>& charStack)
{
	char op;
	while((op = charStack.top()) != '(')
	{
		charStack.pop();
		Node* right = nodesStack.top();
		nodesStack.pop();
		Node* left = nodesStack.top();
		nodesStack.pop();
		Node* node = new Node(op);
		node->left = left;
		node->right = right;
		nodesStack.push(node);
	}
	nodesStack.pop(); //"("
	
}

Tree Convert(char* s)
{
	stack<Node*> nodesStack = stack<Node*>();
	stack<char> operatorStack = stack<char>();
	char c;
	int i = 0;
	while((c = s[i++]) != '\0')
	{
		if(IsOperand(c))
			nodesStack.push(new Node(c));
		else if(IsOperator(c))
		{
			if(operatorStack.size() == 0)  //不要忽略为空的情况
			{
				operatorStack.push(c);
				continue;
			}
			char oldOp = operatorStack.top();
			if(c == '(')
			{
				operatorStack.push(c);
			}
			else if(c == ')')
			{
				// //operatorStack.pop();
				// cout << "before pop to left " ;
				// while(operatorStack.size() != 0)
				// {
				// 	cout << operatorStack.top() << " ";
				// 	operatorStack.pop();
				// }
				// cout << "after";
				char op;
				while((op = operatorStack.top()) != '(')
				{
					cout << "pop " << op << endl;
					operatorStack.pop();
					cout << "op top after pop = " << operatorStack.top() << endl;
					if(operatorStack.size() == 0)
						cout << "reach eampty of stack" << endl;
					Node* right = nodesStack.top();
					nodesStack.pop();
					Node* left = nodesStack.top();
					nodesStack.pop();
					Node* node = new Node(op);
					node->left = left;
					node->right = right;
					nodesStack.push(node);
				}

				operatorStack.pop(); // pop "(" 不要混淆两个stack
			}
			else if((oldOp != '(') && (IsAddSub(c) || IsMulDiv(oldOp)))  //注意"("入栈后优先级变为最低
			{
				operatorStack.pop();  //pop oldOp
				Node* right = nodesStack.top();
				nodesStack.pop();
				Node* left = nodesStack.top();
				nodesStack.pop();
				Node* node = new Node(oldOp);
				node->left = left;
				node->right = right;
				nodesStack.push(node);
				operatorStack.push(c);
			}
			else
			{
				operatorStack.push(c);
			}			
		}
		else
		{
			cout << "wrong input" << endl;
		}
	}
	
	cout << "end " <<  nodesStack.size() <<  endl;
	
	while(!(operatorStack.size() == 0))
	{
		char oldOp = operatorStack.top();
		cout << "end top " << oldOp << endl;
		operatorStack.pop(); 
		Node* right = nodesStack.top();
		nodesStack.pop();
		Node* left = nodesStack.top();
		nodesStack.pop();
		Node* node = new Node(oldOp);
		node->left = left;
		node->right = right;
		nodesStack.push(node);
	}
	
	return nodesStack.top();
}



int main()
{
	// cout << IsOperand('+');
	// cout << IsOperand('5');
	// cout << IsOperator('(');
	// cout << IsOperator('6');
	Tree tree = Convert("3-4/(5+2+3)*6");
	MidOrder(tree);
 	cout << endl;
	PreOrder(tree);
	cout << endl;
	PostOrder(tree);
	return 0;
}