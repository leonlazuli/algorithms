#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <vector>
#include <string> 
#include <stack>
using namespace std;

// 所有涉及指针的递归，首先检查NULL的习惯
// 这里主要是 node->left = insert(node->left, value);  这种在递归中返回node，并在上层递归中赋值的这种思想。

struct Node
{
	int value;
	Node* left;
	Node* right;
	
	Node(int v):value(v), left(NULL), right(NULL){}
};

void _innerTraversal(Node* node)
{
	if(node == NULL)
		return;
	_innerTraversal(node->left);
	cout << node->value << ' ';
	_innerTraversal(node->right);
}

void innerTraversal(Node* node)
{
	cout << "inner order: " << endl;
	_innerTraversal(node);
	cout << endl;
}

void _postTraversal(Node* node)
{
	if(node == NULL)
		return;
	_postTraversal(node->left);
	_postTraversal(node->right);
	cout << node->value << ' ';
}

void postTraversal(Node* node)
{
	cout << "post order: " << endl;
	_postTraversal(node);
	cout << endl;
}

Node* insert(Node* node, int value)
{
	if(node == NULL)
		return new Node(value);
	if(value < node->value)
		node->left = insert(node->left, value);
	else // >=
		node->right = insert(node->right,value);
	return node;
}

Node* find(Node* node, int value)
{
	if(node == NULL)
		return NULL;
	if(value < node->value)
		return find(node->left, value);
	else if(value > node->value)
		return find(node->right, value);
	else
		return node;
}

Node* findMax(Node* node)
{
	if(node == NULL)
		return NULL;
	
	if(node->right != NULL)
		return findMax(node->right);
	else
		return node;
}

Node* findMin(Node* node)
{
	if(node == NULL)
		return NULL;
	
	if(node->left != NULL)
		return findMin(node->left);
	else
		return node;
}

Node* deleteNode(Node* node, int value)
{
	if(node == NULL)
		return NULL;
	
	Node* ret = node;
	if(value < node->value)
		node->left = deleteNode(node->left, value);
	else if(value > node->value)
		node->right = deleteNode(node->right, value);
	else // do delete
	{
		if(node->left != NULL && node->right != NULL)
		{
			int rightMin = findMin(node->right)->value;
			node->right = deleteNode(node->right, rightMin);
			node->value = rightMin;
		}
		else if(node->left != NULL)
		{
			ret = node->left;
			delete node;
		}
		else
		{
			ret = node->right;
			delete node;
		}
	}
	return ret;
}

void postTravesal2(Node* root)
{
	if(root == NULL)
		return;
	stack<Node*> stack;
	stack.push(root);
	Node* pre = NULL;
	while(!stack.empty())
	{
		Node* cur = stack.top();
		if(cur->left == NULL && cur->right == NULL || pre == cur->left || pre == cur->right)
		{
			cout << cur->value << " ";
			pre = cur;
			stack.pop();
		}
		else
		{
			if(cur->right != NULL)
				stack.push(cur->right);
			if(cur->left != NULL)
				stack.push(cur->left);
		}
	}
}

int main()
{
	Node* root = insert(NULL,10);
	root = insert(root, 5);
	root = insert(root, 15);
	root = insert(root, 7);
	root = insert(root, 8);
	root = insert(root, 6);
	root = insert(root, 3);
	root = insert(root, 1);
	root = insert(root, 20);
	root = insert(root, 18);
	root = insert(root, 17);
	
	innerTraversal(root);
	postTraversal(root);

	root = deleteNode(root, 10);
	root = deleteNode(root, 3);
	root = deleteNode(root,17);
	
	innerTraversal(root);
	postTraversal(root);
	cout << "---" << endl;
	postTravesal2(root);
	cout << endl;
	
	
}


