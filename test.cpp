#include <iostream>

double eval_rec(int N)
{
	int i;
	double sum;
	if(N == 0)
		return 1.0;
	else
	{
		sum = 0.0;
		for(i = 0; i < N; i++)
			sum += eval_rec(i);
		return 2.0 * sum / N + N;
	}
}


//C(N) = 2 / N * sum(C(i:N-1)) + N   sum(C(i:N-1))指的是从 C(1) 一直加到C(N-1)
//因为计算C(N)唯一需要之前的信息就是sum(C(i:N-1)), 所以只要记录好sum就行了。
double eval(int n)
{
	if(n == 0)
		return 1.0;
	double sum = 0;
	double currentSum = 1.0;
	for(int i = 1; i <= n; i++)
	{
		sum = 2.0 * currentSum / i + i; 
		currentSum += sum;
		//std::cout << "sum = " << sum << " currentSum = " << currentSum << std::endl;
	}
	return sum;
}

int main()
{
	int n = 10;
	double a = eval_rec(n);
	double b = eval(n);
	std::cout << "eval " << n << " = " << a << ' ' << b << std::endl;
	return 0;
}