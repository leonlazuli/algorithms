#include <ctime>
#include <assert.h>
#include <iostream>

void print(int* arr, int size)
{
	std::cout << "{ ";
	for(int i = 0; i != size; i++)
		std::cout << arr[i] << ' ';
	std::cout << '}' << std::endl;
}

void swap(int* arr, int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

int max3(int a, int b, int c) 
{
	// //$$$ 问题出在这里，一开始是 a > b, a > c 这样如果有等于的情况就不会返回值了， 也就是说返回值是未定义的，这样是非常非常危险的。
	// if(a >= b && a >= c )
	// 	return a;
	// if(b >= a && b >= c)
	// 	return b;
	// if(c >= a && c >= b)
	// 	return c;
	// assert(false);
	int max = 0;
	if(a > b)
		max = a;
	else
		max = b;
	if(c > max)
		max = c;
	return max;
}

int maxSeq(int* arr, int left, int right)
{
	assert(left <= right);
	if(left == right)
	{
		if(arr[left] > 0)
			return arr[left];
		return 0;
	}
	int mid = (left + right) / 2;
	
	int lsum = 0;
	int lmax = 0;
	
	for(int i = mid; i >= left; i--)
	{
		lsum += arr[i];
		if(lsum > lmax)
			lmax = lsum;
	}

	// 注意这里 lmax 和 rmax 必须分开算，因为当l方向计算出m时， 此时的sum不一定是lmax
	int rsum = 0;
	int rmax = 0;
	
	for(int i = mid + 1; i <= right; i++)
	{
		rsum += arr[i];
		if(rsum > rmax)
			rmax = rsum;
	}
	
	int leftM = maxSeq(arr,left,mid);
	int rightM = maxSeq(arr,mid + 1, right);
	std::cout << mid << ' ' << left << ' ' << right << ' ' << rmax + lmax << ' ' << leftM << ' ' << rightM << std::endl;
	
	return max3(lmax + rmax, leftM,rightM);
}

int maxSequence_liner(int* arr, int size)
{
	int max = 0;
	int sum = 0;
	for(int i = 0; i != size; i++)
	{
		sum += arr[i];
		if(sum > max)
			max = sum;
		if(sum < 0)
			sum = 0;
	}
	return max;
}



int maxSequence(int* arr, int size)
{
	return maxSeq(arr, 0, size - 1);
}

int main()
{
	const int size = 6;
	const int maxNum = 10;
	int arr[size]; // = { 2, -3, 2, 2, -3, -1};
	srand((unsigned)time(NULL)); // seed for random
	for(int i = 0; i != size; i++)
	{
		arr[i] = rand()% maxNum;
		if(arr[i] % 2)
			arr[i] = - arr[i];
	}
	print(arr,size);
	int max =  maxSequence(arr,size);
	int max2 = maxSequence_liner(arr,size);
	std::cout << "max sequence number " << max << ' ' << max2 << std::endl;
	
}