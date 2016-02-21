#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <vector>
#include <string> 
using namespace std;

void print(int* arr, int n)
{
	cout << "arr: ";
	for(int i = 0 ; i != n; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;
}

void swap(int* arr, int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void qSort(int* arr, int left, int right)
{
	if(left >= right)
		return;
	
	int pivot = left + rand() % (right - left);
	int pivotValue = arr[pivot];
	swap(arr,left,pivot);
	
	int i = left;
	int j = right + 1;
	while(i < j)
	{
		while(++i <=right && arr[i] < pivotValue);
		while(--j >= left && arr[j] > pivotValue);
		
		if(i < j)
			swap(arr,i,j);
	}
	
	swap(arr,left,j);
	qSort(arr,left,j - 1);
	qSort(arr,j + 1, right);
	
}


void quickSort(int* arr, int size)
{
	qSort(arr, 0, size - 1);
}


int main()
{
	const int size = 100;
	const int max = 100;
	int arr[size];
	srand(time(NULL));
	for(int i = 0 ; i!= size; i++)
	{
		arr[i] = rand() % max;
	}
	print(arr,size);
	quickSort(arr,size);
	print(arr,size);
	
	return 0;
}