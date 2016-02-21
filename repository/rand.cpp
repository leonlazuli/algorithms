#include <iostream>
#include <time.h>


using namespace std;

void rand_arr(long int* arr,const int max, const long int n)
{
	//int arr[n];
	srand((unsigned)time(NULL));
	for(int i = 0; i != n; i++)
	{
		arr[i] = rand() % max;
	}
	// !! don't return a local array! return arr; 
}

void rand_arr_better(long int* arr, int max, long int n)
{
	srand((unsigned)time(NULL));
	const size_t bucket = RAND_MAX / n;
	for(int i = 0; i != n; i++)
	{
		arr[i] = rand()/bucket;
	}
}

int main()
{
	//long int n;
	//int max;
	//int count[max];
	// cout << "Enter the number of random array" << endl;
// 	cin >> n;
// 	cout << "Enter the max random number in this array" << endl;
// 	cin >> max;
	const long int n = 99999999;
	const long int max = 9999;
	
	//long int* arr = new long int[n];
	//int* count = new int[max];
	long int arr[n];
	int count[max];
	rand_arr_better(arr,max,n);
	for(int i = 0; i != n; i++)
{
		//cout << arr[i] << ' ';
		++count[arr[i]];
	}
	cout << endl;
	cout << "the difference of the occur times between 1 and max - 2: " << count[0] - count[max - 2] << endl;
	// delete [] arr;
// 	delete [] count;
}