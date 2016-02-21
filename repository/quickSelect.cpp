#include <iostream>
#include <stdlib.h>
#include <string>
#include <exception>
#include <time.h>

void swap(int* arr, int index1, int index2)
{
	int temp = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = temp;
}

int qSelect(int* arr, const int left, const int right, const int k)
{
	//$ 下面这一句要也行，不要也行。 对性能互有利弊~
	// if(right == left) // only one element in rest set, return this element
	// 	return arr[left];
	int pivot = left + rand() % (right - left);
	int pivotValue = arr[pivot];
	swap(arr,left,pivot);
	int i = left;
	int j = right + 1;
	while(i < j)
	{
		while(++i <= right && arr[i] < pivotValue);
		while(--j > left && arr[j] > pivotValue);
		if(i < j)
			swap(arr,i,j);
	}
	swap(arr,left,j);
	
	
	if(k <= (j - left)) 
		return qSelect(arr, left, j-1, k);
	else if( k == j - left + 1)
		return arr[j];
	else
		return qSelect(arr,j + 1, right,(k - j + left - 1));
	
	//$$$ 两种表示 kth smallest的方式都是可以的
	//我的方式是用在当前range中，用绝对数量表示， k是当前range中得第k smallset的，
	//	所以左边的set有 j - left 个， 右边的set有 right - j 个 ， 如果 k == j - left + 1, 则说明刚好是arr[j]
	//而textbook的方式是不管在哪个range中，k始终是指全局的第k smallest的。
	//  所以左边有 j - 0 个，  右边有 right - j 个， 当 k = j + 1 的时候，说明刚好是arr[j] 
	//  k smallset 的index 是 k - 1，  所以，当 j = k - 1 的时候， 说明了它左边恰好有 k - 1 个比它小的， 也就是 j 就是第 k 小的了
	if(k <= j) 
		return qSelect(arr, left, j-1, k);
	else if( k == j + 1) // k - 1 == j
		return arr[j];
	else
		return qSelect(arr,j + 1, right,k);
}

int quickSelect(int* arr, int arrSize, int k)
{
	return qSelect(arr, 0, arrSize - 1, k);
}

void printArray(int* arr, int size)
{
	for(int i = 0; i != size; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

int main()
{
	const int arrSize = 20;
	int arr[arrSize];
	int maxElement = 2 * arrSize;
	srand((unsigned)time(NULL));
	for(int i = 0; i != arrSize; i++)
	{
		arr[i] = rand() % maxElement;
	}
	std::cout << "----original array--------" << std::endl;
	printArray(arr,arrSize);
	int k = 4;
    std::cout << k << "th" << " smallest element is: " << quickSelect(arr,arrSize,k) << std:: endl;
	return 0;
}























































