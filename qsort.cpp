#include <iostream>
#include <ctime>

void printArray(int* arr, int N)
{
	for(int i = 0; i != N; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

void swap(int* arr, int index1, int index2)
{
	int temp = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = temp;
	
}

void qSort(int* arr, int left, int right)
{
	if(left >= right) // only one or negative number of this sub array
		return;
	int pivot = left + rand() % (right - left + 1); // choose a pivot randomly
	int pivotValue = arr[pivot];
	swap(arr,left,pivot);
	int i = left; // because we will ++i first later
	int j = right + 1; // we will --j first later
	while(j >= i)
	{
		while(++i && i <= right && arr[i] < pivotValue) ; // empty body
		while(--j && j > left && arr[j] > pivotValue); // empty body
		if(j > i)
			swap(arr,i,j);
	}
	swap(arr,left,j); // because after i and j cross,  j will point to a number smaller than pivot
	qSort(arr,left,j - 1);
	qSort(arr,j + 1, right);
	
}

void quickSort(int* arr, int N)
{
	qSort(arr,0, N - 1);
}

//#define EXTREME_TEST
int main()
{
	const int maxNum = 1000;
	const int N = 10000;
	int arr[N];
	srand((unsigned)time(NULL)); // seed
	for(int i = 0; i != N; i++)
	{
#ifndef EXTREME_TEST
		arr[i] = rand() % maxNum;
#else 
		arr[i] = 10;
#endif
	
	}
	std::cout << "------------" << "original array" << "--------------" << std::endl;
	printArray(arr,N);
	std::cout << std::endl;
	quickSort(arr,N);
	std::cout << "-------------" << "after sort" << "---------------" << std::endl;
	printArray(arr,N);
	
	
	
	
	return 0;
}