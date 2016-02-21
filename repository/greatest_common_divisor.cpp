#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

// Euclid's Algorithm   greatest commom divisor

int Gcd(int m, int n)
{
	int rem;
	while(n != 0)
	{
		rem = m % n;
		m = n;
		n = rem;
	}
	return m;
}

int main()
{
	cout << Gcd(21,35) << endl;
}