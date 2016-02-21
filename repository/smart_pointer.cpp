#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

class U_ptr
{
	friend class Class1;
	int value; // change to int* later, see what happens
	size_t count;
	U_ptr(int i):value(i),count(1){}
	
	
};

class Class1
{
private:
	U_ptr* ptr;
public:
	Class1(int i = 0):ptr(new U_ptr(i)){};
	Class1(const Class1& cls):ptr(cls.ptr){++ptr->count;}
	~Class1()
	{
		if(ptr->count == 0)
			delete ptr;
		else 
			--ptr->count;
	}
	Class1& operator =(const Class1& cls) // !!! 左边的指针需要先“删除”，然后再赋值右边的指针，两边有可能之前不是指向同一个副本，所以不能直接赋值指针，然后自增count
	{
		++(cls.ptr->count);
		if(--ptr->count == 0)
			delete ptr;
		ptr = cls.ptr;
		return *this;
	}
	void set(int i){ptr->value = i;}
	void print(){cout << ptr->value << endl;}
	void print_count(){cout << "count now is " << ptr->count << endl;}
	
};

int  main()
{
	Class1* pc1 = new Class1(2);
	Class1 c2(*pc1);
	Class1 c3(2);
	pc1->print_count();
	c3 = c2;
	c3 = c3;
	c3.print_count();
	c3.print();
	pc1->print();
	c2.print();
	pc1->set(10);
	c2.print();
	delete pc1;
	c2.print();
	c2.print_count();
}