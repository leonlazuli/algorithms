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

class B
{
public:
	B(){cout << "default constructor"  << endl;}
	B(int i){cout << "int constructor" << endl;}
	B(const B& rhs){cout <<"copy constructor" << endl;}
	~B(){cout << "destructor" << endl;};
};

class C:public B
{
public:
	C(){cout << "derived constructor" << endl;}
	~C(){cout << "derived destructor" << endl;}
};

B play(B b)
{
	return b;
}

void copyTest()
{
	B temp = play(5);
	cout << "----------------" << endl;
	B temp2 = play(temp);
	//return 0;
}

void derivedTest()
{
	C c;
}

int main()
{
	copyTest();
	return 0;
}

