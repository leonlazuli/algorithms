#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

class Cls1
{
public:
	virtual void print() const {cout << "c1" << endl;}
	void display(){this->print();}
};

class Cls2: public Cls1
{
private:
	void print() const {cout << "c2" << endl;}
};

void print(const Cls1& c)
{
	c.print();
}

int main()
{
	Cls2 c2;
	Cls1 c1;
	c1.display();
	c2.display();
}