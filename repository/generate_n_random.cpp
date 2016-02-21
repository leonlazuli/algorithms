#include <stdlib.h>
#include <time.h>

void generate_n_random(int arr[], int max, int N)
{
	srand((unsigned)time(NULL));
	for(int i = 0; i != N; i++)
		arr[i] = rand() % max;
}

void generate_n_presorted_random(int arr[], int N)
{
	arr[0] = 0;
	srand((unsigned)time(NULL));
	for(int i = 1; i != N; i++)
	{
		arr[i] = arr[i - 1] + rand() % 5;
	}
}

int main()
{
	const int size = 10;
	int arr[size];
	generate_n_presorted_random(arr,size);
	for(int i = 0; i != size; i++)
		printf("%d ",arr[i]);
	printf("\n");
}