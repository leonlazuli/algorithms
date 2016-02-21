/*筛选法又称筛法，是求不超过自然数N（N＞1）的所有质数的一种方法。据说是古希腊的埃拉托斯特尼（Eratosthenes，约公元前274～194年）发明的，又称埃拉托斯特尼筛子。
  具体做法是：先把N个自然数按次序排列起来。1不是质数，也不是合数，要划去。第二个数2是质数留下来，而把2后面所有能被2整除的数都划去。2后面第一个没划去的数是3，把3留下，再把3后面所有能被3整除的数都划去。3后面第一个没划去的数是5，把5留下，再把5后面所有能被5整除的数都划去。这样一直做下去，就会把不超过N的全部合数都筛掉，留下的就是不超过N的全部质数。因为希腊人是把数写在涂腊的板上，每要划去一个数，就在上面记以小点，寻求质数的工作完毕后，这许多小点就像一个筛子，所以就把埃拉托斯特尼的方法叫做“埃拉托斯特尼筛”，简称“筛法”。（另一种解释是当时的数写在纸草上，每要划去一个数，就把这个数挖去，寻求质数的工作完毕后，这许多小洞就像一个筛子。）*/

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

void find_prime(int MAX, std::vector<int>& vec)
{
    int i;
    int j;
    char table[MAX];
    
    for(i = 2;i < MAX;i++)
        table[i] = 1;
    for(i = 2;i <= (int)sqrt(MAX) + 1;i++) // 这里可以只到sqrt（max） 就可以了， 注意是<=
        if(table[i] == 1)
            for(j = i;i*j < MAX;j++)
                table[i*j] = 0;
    for(i = 2;i < MAX;i++)
        if(table[i] == 1)
            vec.push_back(i);
}

bool isPrime(int num)
{
	//printf("sqrt(num) = %d\n", (int)sqrt(num));
	for(int i = 2; i != (int)sqrt(num); i++) //$$$ note int
	{
		if(num % i == 0)
			return false;
	}
	return true;
}

void findPrime(int max, std::vector<int>& vec)
{
	bool arr[max + 1];
	for(int i = 2; i <= max; i++) // initialize
	{
		arr[i] = true;
	}
	for(int i = 2; i <= (int)sqrt(max); i++)
	{
		if(arr[i])
		{
			for(int j = 2; i * j <= max; j++)
			{
				arr[i * j] = false; 
			}
			
		}
	}
	for(int i = 2; i <= max; i++)
	{
		if(arr[i])
			vec.push_back(i);
	}
}

void findPrime2(int max, std::vector<int>& vec)
{
	bool arr[max + 1];
	for(int i = 2; i <= max; i++)
	{
		arr[i] = true;
	}
	
	//$$$ 因为sqrt（max） 之前的*2 *3 之类的在之前都已经做过了，所以
	for(int i = 2; i <= (int)sqrt(max); i++) 
	{
		if(arr[i])
		{
			for(int j = 2; j * i <= max; j++)
			{
				arr[i * j] = false;
			}
		}
	}
	int counter = 0;
	for(int i = 2; i <= max; i++)
	{
		if(arr[i])
		{
			vec.push_back(i);
			++counter;
		}
	}
	std::cout << "totally " << counter << " prime number " << std::endl;
}

void printVector(const std::vector<int>& vec)
{
	for(int i = 0; i != vec.size(); i++)
	{
		std::cout << vec[i] << ' ' ;
	}
	std::cout << std::endl;
}

int main(void)
{
	std::vector<int> vec;
	findPrime2(1000000,vec);
	printVector(vec);
	int candidate = 96;
	std::cout << candidate << " is prime? " << (isPrime(candidate)? "true":"false") << std::endl;
    return 0;
}