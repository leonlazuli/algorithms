#include<iostream>

using namespace std;

class Foo
{
private:
	int value;
public:
	Foo(int i):value(i){};
	int GetValue()
	{
		return value;
	}
	friend Foo operator+ (const Foo& f1, const Foo& f2);
	friend ostream& operator<< (ostream& os, const Foo f)
	{
		os << f.value;
		return os;
	}
};

class Boo
{
private:
	int * pi;
public:
	Boo(int i)
	{
		pi = new int(i);
	}
	Boo(const Boo& b)
	{
		pi = new int(*(b.pi));
	}
	~Boo(){delete pi;}
	int Get()
	{
		return *pi;
	}
	void Set(int i)
	{
		*pi = i;
	}
	Boo& operator = (const Boo& b)
	{
		if(&b != this)
		{
			delete pi; // ATTENTION 这里注意要释放LHS之前的参数
			pi = new int(*(b.pi));
		}
		return *this;
	}
};


Foo operator+(const Foo& f1, const Foo& f2)
{
	return Foo(f1.value+f2.value);
}

int main()
{
	Boo b1 = Boo(3);
	Boo b2 = Boo(b1);
	Boo b3 = Boo(9);
	b3 = b1;
	b1.Set(6);
	cout << b1.Get() << " " << b2.Get() << " " << b3.Get() << endl;
	
}