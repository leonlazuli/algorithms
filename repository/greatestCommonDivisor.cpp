#include <iostream>

int gcd(int i, int j) // 实际上不用比较谁大谁小，写的时候为了方便记住，假设一个大一个小，然后用大的余小的就行了
{
	int t;
	while(j != 0)
	{
		t = j;
		j = i % j;
		i = t;
	}
	return i;
}

int main()
{
	int a = 121;
	int b = 77;
	std::cout << "greatest common divisor of " << a << " and " << b << " is: " << gcd(a,b) << std::endl;
	return 0;
}