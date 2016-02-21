#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <string> 
using namespace std;

// 最大子串问题， 三种方式

// 这里要注意的问题是，可以一个都不选，所以max至少为0
int maxSubString_1(int* arr, int n)
{
	// int max = -10000;  WRONG
	int max = 0; // RIGHT
	for(int i = 0; i != n; i++)
	{
		for(int j = 0; j != n; j++)
		{
			int sum = 0;
			for(int k = i; k <= j; k++)
			{
				sum += arr[k];
			}
			if(sum > max)
				max = sum;
		}
	}
	return max;
}

int max(int a, int b, int c)
{
	int max = a;
	if(b > max)
		max = b;
	if(c > max)
		max = c;
	return max;
}

int mss(int* arr, int left, int right)
{
	if(left == right)
	{
		return arr[left] > 0? arr[left]:0; // RIGHT
		// return arr[left]; // WRONG  这里还是要考虑不选的情况，所以至少为0 
	}
	int mid = (left + right) / 2;
	int leftMax = mss(arr, left, mid);
	int rightMax = mss(arr, mid + 1, right);
	//WRONG 分治的目的就是要解除左右的联系，这种枚举的方式，则又让左右联系到一起考虑了，实际上的复杂度还是三次方
	//midMax这种情况一定包括了中间的两个数，所以，只需要计算出从mid到左边的最大值，再算出
	//从mid+1到右边的最大值 加起来就是横跨左右的最大值了，这种情况下，左右分开计算，复杂度就为O（N）
	// for(int i = mid; i >= left; i--)
	// {
	// 	for(int j = mid + 1; j <= right; j++)
	// 	{
	// 		int sum = 0;
	// 		for(int k = i; k <= j; k++)
	// 			sum += arr[k];
	// 		if(sum > midMax)
	// 			midMax = sum;
	// 	}
	// }
	int leftBorderMax = 0;
	int leftBorderSum = 0;
	for(int i = mid; i >= left; i--)
	{
		leftBorderSum += arr[i];
		if(leftBorderSum > leftBorderMax)
			leftBorderMax = leftBorderSum;
	}
	
	int rightBorderMax = 0;
	int rightBorderSum = 0;
	for(int i = mid + 1; i <= right; i++)
	{
		rightBorderSum += arr[i];
		if(rightBorderSum > rightBorderMax)
			rightBorderMax = rightBorderSum;
	}
	
	return max(leftMax,rightMax,leftBorderMax + rightBorderMax);
}

int maxSubString_2(int* arr, int n)
{
	return mss(arr, 0, n-1);
}

int maxSubString_3(int* arr, int n)
{
	int sum = 0;
	int max = 0;
	for(int i = 0; i != n; i++)
	{
		sum += arr[i];
		if(sum > max)
			max = sum;
		if(sum < 0)
			sum = 0;
	}
	return max;
}

int main()
{
	int arr[] = {4,-3,5,-2,-1,2,6,-2};
	int size = sizeof(arr) / sizeof(arr[0]);
	cout << maxSubString_1(arr, size) << endl;
	cout << maxSubString_2(arr, size) << endl;
	cout << maxSubString_3(arr, size) << endl;
	return 0;
}
		
			