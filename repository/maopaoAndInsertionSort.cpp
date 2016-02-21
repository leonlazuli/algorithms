#include <iostream>
#include <ctime>
#include <limits>

void printArray(int* arr, int size)
{
	for(int i = 0; i != size; i++)
	{
		std::cout << arr[i] << ' ';
	}
	std::cout << std::endl;
}

void swap(int* arr, int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void insertionSort(int* arr, int size)
{
	int temp = 0;
	for(int i =0 ; i != size; i++)
	{
		temp = arr[i];;
		int j = i;
		for( ; j > 0 && arr[j-1] > temp; j-- )
		{
			arr[j] = arr[j-1];
		}
		arr[j] = temp;
	}
}

void maoPaoSort(int* arr, int size)
{
	int index = 0;
	int currentMin = std::numeric_limits<int>::max();
	for(int i = 0; i != size; i++)
	{
		currentMin = std::numeric_limits<int>::max();
		for(int j = i; j != size; j++)
		{
			if(arr[j] < currentMin)
			{
				index = j;
				currentMin = arr[j];
			}
		}
		swap(arr,i,index);
	}
}

int main()
{
	const int size = 30;
	const int maxNum = 50;
	int arr[size];
	srand((unsigned)time(NULL));
	for(int i = 0; i != size; i++)
	{
		arr[i] = rand() % maxNum;
	}
	printArray(arr,size);
	maoPaoSort(arr,size);
	printArray(arr,size);
	return 0;
}