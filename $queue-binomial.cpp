#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <vector>
#include <string> 
#include <stack>
#include <queue>
#include <stdexcept>
using namespace std;

struct A
{
	char a;
	char b;
	char c;
};

struct B
{
	A a;
	int b;
	//int* p;
};

struct C
{
	int* p;
};

int main()
{

	cout << sizeof(C) << endl;
	 
}