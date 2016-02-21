#include <iostream>

int gcd(int n, int m)
{
	while(n != 0)
	{
		int temp = m % n;
		m = n;
		n = temp;
	}
	return m;
}

int main()
{
	std::cout << gcd(45,135);
	return 0;
}