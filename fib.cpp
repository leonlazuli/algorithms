#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <string> 
using namespace std;

// 8拆成7和6  7拆成两个 6拆成两个  所以是1 + 2 + 4。。。。  所以是2^n的复杂度
int fib(int n)
{
	if(n < 3)
		return 1;
	return fib(n - 1) + fib(n - 2);
}

// 先写一个短的fib数列观察，计算某一项，只需要前两项，所以我们只需要始终保存即将计算的两项的值就可以了,这里用到了动态规划的思想
int fib_2(int n)
{
	if(n < 3)
		return 1;
	int a = 1;
	int b = 1;
	int current = 0;
	for(int i = 3; i <= n; i++)
	{
		current = a + b;
		a = b;
		b = current;
	}
	return current;
}


int main()
{
	for(int i = 1; i != 11; i++)
	{
		cout << fib(i) << ' ';
	}
	cout << endl;
	
	for(int i = 1; i != 11; i++)
	{
		cout << fib_2(i) << ' ';
	}
	cout << endl;
}
		
			