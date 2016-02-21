#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

void generate_n_presorted_random(int arr[], int N)
{
	arr[0] = 0;
	srand((unsigned)time(NULL));
	for(int i = 1; i != N; i++)
	{
		arr[i] = arr[i - 1] + rand() % 5;
	}
}

int binary_search(int arr[], int N, int target) // xxx
{	
	int left = 0;
	int right = N;
	int mid = (left + right) / 2;
	while(left <= right) // <= is better than !=
	{
		mid = (left + right) / 2;
		if(arr[mid] == target)
			return mid;
		else if(arr[mid] > target)
		{
			right = mid;
		}
		else
			left = mid + 1;    // !!! [)
	}
	
		printf("left: %d \n",left);
		printf("rigtht: %d \n",right);
	
	if(arr[left] == target)  // !!!
		return left;
	else 
		return -1;
}

int s_binary_search(int arr[], int N, int target)
{
	int low, mid, high;
	low = 0;
	high = N - 1; // [ ] ,所以后面mid + 1 mid - 1 是对称的。
	while(low <= high) 
	// ！！！ low == high 的时候， 判断的是只有一个的情况。之后，小的变大或者大的变小，所以一定会让 low 不小于 high
	{
		mid = (low + high) / 2;
		if(arr[mid] <target)
			low = mid + 1;
		else if (arr[mid] > target)
			high = mid - 1; 
		//！！！ high有可能等于-1，但是，由于判断条件是<= 所以，还是可以跳出循环的，而且，没有在循环外使用high，所以不会内存越界
		else 
			return mid;
	}
	if(low < 0 || high <0)
	{
		cout << "error" << endl;
		cout << "low" << low << endl;
		cout << "high" << high << endl;
	}
	return -1;
}

int main()
{
	const int size = 10;
	int arr[size] = {1,2,3,4,5,6,7,7,9,10};
	//generate_n_presorted_random(arr,size);
	for(int i = 0; i != size; i++)
		printf("%d ",arr[i]);
	printf("\n");
	int target = 11;
	printf("find %d: %d\n", target, binary_search(arr,size,target));
}