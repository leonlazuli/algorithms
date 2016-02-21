#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <vector>
#include <string> 
#include <stack>
#include <queue>
#include <stdexcept>
using namespace std;

void printArray(int* arr, int n)
{
	for(int i = 0; i != n; i++)
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

// 每一次迭代，都把第i个放到前i个中正确的位置，所以一旦发现arr[j-1] >temp 就可以终止这一次迭代了
void insertSort(int* arr, int n)
{
	for(int i = 1; i != n; i++)
	{
		int temp = arr[i];
		int j;
		for(j = i; j > 0 && arr[j - 1] > temp; j--)
			arr[j] = arr[j - 1];
		arr[j] = temp;
	}
}

// 每一次迭代，都把通过相邻的数字两两交换位置来把最大的一个放到了最后去，然后下一次迭代中，就可以少管一个
void maopaoSort(int* arr, int n)
{
	for(int i = 0; i < n - 1; i++)
	{
		for(int j = 0; j < n - 1 - i; j++)
		{
			if(arr[j + 1] < arr[j])
			{
				int temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

int buf[10000]; // 动态申请一个一样大的，传参传进去也挺好的
void mSort(int* arr, int left, int right)
{
	if(left >= right)
		return;
	int mid = (left + right) / 2;
	mSort(arr,left, mid);
	mSort(arr,mid + 1, right);
	int i = left;
	int j = mid + 1;
	int k = left;
	while(i <= mid && j <= right)
	{
		if(arr[i] < arr[j])
		{
			buf[k++] = arr[i++];
		}
		else
			buf[k++] = arr[j++];
	}
	while(i <= mid)
		buf[k++] = arr[i++];
	while(j <= right)
		buf[k++] = arr[j++];
	
	for(int i = left; i <= right; i++)
	{
		arr[i] = buf[i];
	}
}

void mergeSort(int* arr, int n)
{
	mSort(arr, 0, n - 1);
}

int main()
{
	const int size = 10;
	const int max = 20;
	int array[size];
	srand((unsigned)time(NULL));
	for(int i = 0; i != size; i++)
	{
		array[i] = rand() % max;
	}
	printArray(array,size);
	mergeSort(array,size);
	printArray(array,size);
	return 0;
}
