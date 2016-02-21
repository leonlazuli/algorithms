#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <string> 
using namespace std;

struct Node
{
	int value;
	Node* left;
	Node* right;
	Node(int v):value(v),left(NULL),right(NULL){}
	~Node()
	{
		delete left;
		delete right;
	}
};

void PostOrderTraversal(Node* node)
{
	if(node == NULL)
		return;
	PostOrderTraversal(node->left);
	PostOrderTraversal(node->right);
	cout << node->value << ' ';
}

void MidOrderTraversal(Node* node)
{
	if(node == NULL)
		return;
	MidOrderTraversal(node->left);
	cout << node->value << ' ';
	MidOrderTraversal(node->right);
}


int MaxDepth = 6;
int WordWidth = 2;
int Gap = 12;
int Margin = 20;

int PositionOfThisNode(int PositionOfParent, int isLeft)
{
	return isLeft ? PositionOfParent - Gap / 2 : PositionOfParent + Gap / 2;
}

string IntToString(int n)
{
	if(n < 0)
		return string("不支持负数");
	char ret[100];
	int num = n;
	if(num != 0)
	{
		int temp[100];
		int i = 0;
		while(num != 0)
		{
			temp[i++] = num % 10;
			num /= 10;
		}
		for(int j = 0; j != i; j++)
		{
			ret[j] = temp[i - j - 1] + '0';
		}
		ret[i] = '\0';
		
	}
	else
	{
		ret[0] = '0';
		ret[1] = '\0';
	}
	return string(ret);
}

string FormatInt(int i)
{
	string ret = IntToString(i);
	int k = 0;
	if(i == 0)
		k = 1;
	else
	{
		int n = i;
		while(n != 0)
		{
			n /= 10;
			++k;
		}
	}
	int nBlank = WordWidth - k;
	for(int j = 0; j < nBlank; j++)
	{
		ret = " " + ret;
	}
	return ret;
}

void Print(Node* node, int depth, int position, vector<string> & lines)
{
	if(node  == NULL)
		return;
	string s = FormatInt(node->value);
	lines[depth].replace(position, s.size(), s);
	Print(node->left, depth + 1, position - Gap / 2 + depth * 2, lines);
	Print(node->right, depth + 1, position + Gap / 2 - depth * 2, lines);
}

void PrintTree(Node* root, int maxDepth)
{
	int widthOfTree =  100; //pow(2, maxDepth) * (WordWidth + Gap) - Gap + Margin;
	string emptyLine = string(widthOfTree, ' ');
	emptyLine += 'E';
	vector<string> lines = vector<string>(maxDepth + 1, emptyLine);
	Print(root, 0, widthOfTree / 2, lines);
	for(int i = 0; i != lines.size(); i++)
	{
		cout << lines[i] << endl;
	}
}


Node* GenerateCompleteBinaryTree(int nNode)
{
	if(nNode < 1)
		return NULL;
	vector<Node*> nodes = vector<Node*>(nNode, NULL);
	for(int i = 0; i != nNode; i++)
	{
		Node* node = new Node(i);
		nodes[i] = node;
	}
	for(int i = 0; i * 2 + 1 <= nNode - 1; i++)
	{
		nodes[i]->left = nodes[i * 2 + 1];
		if(i * 2 + 2 <= nNode - 1)
		{
			nodes[i]->right = nodes[i * 2 + 2];
		}
	}
	return nodes[0];
}

int main()
{	
	Node* root = GenerateCompleteBinaryTree(7);
	PostOrderTraversal(root);
	cout << endl;
	MidOrderTraversal(root);
	cout << endl;
	PrintTree(root, 4);
	cout << "Finished" << endl;

}

