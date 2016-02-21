#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <vector>
#include <string> 
#include <stack>
#include <queue>
using namespace std;

struct Node
{
	int value;
	Node* left;
	Node* right;
	
	Node(int v):value(v),left(NULL),right(NULL){};
	//don't put delete in destructor
};

void view(Node* node)
{
	cout << node->value << ' ';
}

void innerTraversal_r(Node* node)
{
	if(node == NULL)
		return;
	innerTraversal_r(node->left);
	view(node);
	innerTraversal_r(node->right);
}

void traversal(Node* root)
{
	if(root == NULL)
		return;
	stack<Node*> stack;
	Node* node = root;
	while(node != NULL || !stack.empty())
	{
		while(node != NULL)
		{
			stack.push(node);
			node = node->left;
		}
		Node* top = stack.top();
		stack.pop();
		view(top);
		node = top->right;
		
	}
}

int main()
{
	Node* nodes[9];
	for(int i = 1; i <= 8; i++)
	{
		nodes[i] = new Node(i);
	}
	Node* root = nodes[1];
	nodes[1]->left = nodes[2];
	nodes[1]->right = nodes[3];
	nodes[2]->left = nodes[4];
	nodes[2]->right = nodes[5];
	nodes[3]->left = nodes[6];
	nodes[3]->right = nodes[7];
	nodes[4]->right = nodes[8];
	
	innerTraversal_r(root);
	cout << endl;
	traversal(root);
	
	
}