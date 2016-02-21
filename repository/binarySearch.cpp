#include <iostream>


#define NELEMS(array) (sizeof(array) / sizeof(array[0]))

using namespace std;

struct NameVal
{
	char* name;
	int val;
};

NameVal htmlChars[] = {
	"AE1ig", 0x00c6, 
	"Aacute", 0x00c1, 
	"Acirc", 0x00c2,    
	"Bsfes", 0x00c4,
	"Csdfsa", 0x00c5,
	"Dsdsf", 0x00c6, 
	"zeta", 0x03b6,	
};

int lookUp(char* word, NameVal* htmlChars) // return the index of the word if founded, else return -1
{
	int left, right, mid;
	int len = 7; //NELEMS(htmlChars);  ????????  how to use size of on arrayÅ˜
	cout << sizeof(htmlChars) << endl;
	cout << sizeof(htmlChars[0]) << endl;
	cout << len << endl; ////////
	left = 0;
	right = len;
	while(left <=right) //while(left < right) becuase left = right and there is only one element to scan 
	{
		mid = (left + right) / 2;
		if(strcmp(word,htmlChars[mid].name) == 0)   
		// make strcmp a integer to eliminate the redundance of function call
			return mid;
		else if(strcmp(word,htmlChars[mid].name) < 0)
			right = mid;
		else if(strcmp(word,htmlChars[mid].name) >0)
			left = mid;
	}
	
	return -1;
}

int main()
{
	std::cout << lookUp("Dsdsf",htmlChars) << std::endl;
}