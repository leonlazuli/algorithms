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

class String
{
private:
	char* data;
private:
	void copyToData(const char* s)
	{
		if(s == NULL)
		{
			data = new char;
			*data = '\0';
		}
		else
		{
			int length = strlen(s);
			data = new char[length + 1];
			strcpy(data,s);
		}
	}
public:
	String(const char* s)
	{
		copyToData(s);
	}

	~String()
	{
		delete[] data;
	}

	String(const String& s)
	{
		copyToData(s.data);
	}

	String& operator=(const String& s)
	{
		if(&s != this)
		{
			delete [] data;
			copyToData(data);
		}
		return *this;
	}
	void print()
	{
		cout << data << endl;
	}
};

int main()
{
	String s1("hello");
	String s2 = s1;
	String s3("world");
	s1.print();
	s2.print();
	s3.print();
	s2 = s3;
	s1.print();
	s2.print();
	s3.print();
	s2 = s2;
	s1.print();
	s2.print();
	s3.print();
}


