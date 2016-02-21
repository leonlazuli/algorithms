
#include <iostream>
#include <exception>
#include <string>
#include <limits>
#include <algorithm>
#include <vector>
#include <queue>
#include <assert.h>
#include <ctime>

#define BETTERALGORITHM

void printArray(int* arr, int arrSize)
{
	for(int i = 0; i != arrSize; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

void insertionSort(int* arr, int size)
{
#ifndef BETTERALGORITHM
	std::cout << "my Algorithm" << std::endl;
	for(int i = 1; i != size; i++)
	{
		int rightPosition = i;
		int thisElement = arr[i];
		for(int j = i - 1; j >= 0; j--)
		{
			if(thisElement < arr[j])
				rightPosition = j;
		}
		if(rightPosition != i)
		{
			for(int j = i - 1; j >= rightPosition; j--)
			{
				arr[j+1] = arr[j];
			}
			arr[rightPosition] = thisElement;
		}
	}
#else
	for(int i = 1; i < size; i++)
	{
		int thisElement = arr[i];
		int j;
		for(j = i; j > 0 && arr[j - 1] > thisElement; j--)
		{
			arr[j] = arr[j-1];
		}
		arr[j] = thisElement;
	}
	
#endif
		
}

void shellSort(int* arr, int arrSize)
{
	for(int distance = arrSize / 2; distance > 0; distance /= 2)
		for(int i = 0; i < distance; i++)
			for(int k = i + distance; k < arrSize; k += distance)
			{
				int thisElement = arr[k];
				int j;
				for(j = k; j - distance >= 0 && arr[j - distance] > thisElement; j -= distance )
					arr[j] = arr[j - distance];
				arr[j] = thisElement; 
			}
}

inline int leftChild(int index)
{
	return 2 * index + 1;
}
inline int rightChild(int index)
{
	return 2 * index + 2;
}

int findLargerChild(int* arr, int heapSize, int i) //note that heap begins from 0 not 1
{
	if(leftChild(i) > heapSize - 1) // no child
		return -1; //means no child
	if(rightChild(i) > heapSize - 1) // only left Child
		return leftChild(i); // 
	if(arr[leftChild(i)] > arr[rightChild(i)])
		return leftChild(i);
	return rightChild(i);
}

void percolateDown(int* arr, int heapSize, int index) // max Heap, to perform the ascend sort result
{
	assert(index <= heapSize);
	int i = index;
	int parentValue = arr[i];
	// while(true)
	// {
	// 	int largerChild = findLargerChild(arr, heapSize,i);
	// 	//$$ note here always use parentValue to compare, not arr[i]
	// 	if(largerChild == -1 || parentValue > arr[largerChild]) // current node is a leaf
	// 		break;
	// 	else
	// 	{
	// 		arr[i] = arr[largerChild];
	// 		i = largerChild;
	// 	}
	// }
	int largerChild = findLargerChild(arr, heapSize,i);
	while(largerChild != -1 && parentValue < arr[largerChild])
	{
		arr[i] = arr[largerChild];
		i = largerChild;
		largerChild = findLargerChild(arr,heapSize,i);
		
	}
	arr[i] = parentValue;
	
}

void swap(int* arr, int index1, int index2)
{
	int temp = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = temp;
}

void heapSort(int* arr, int arrSize) // arrSize is heapSize since we won't insert element to this heap
{
	for(int i = arrSize / 2; i >= 0; i--) // build the max heap
		percolateDown(arr,arrSize,i);
	for(int i = arrSize - 1; i > 0; i--)
	{
		swap(arr,0,i);
		percolateDown(arr,i,0);
	}
}

int tempArr[1000];
void merge(int* arr, const int left, const int mid, const int right) // [ ]
{
	for(int i = left; i <= right; i++)
	{
		tempArr[i] = arr[i]; 
	}
	int i = left; // left half
	int j = mid + 1; // right half
	int k = left; // original array
	while(i <= mid && j <= right)
	{
		if(tempArr[i] < tempArr[j])
			arr[k++] = tempArr[i++];
		else
			arr[k++] = tempArr[j++];
	}
	// $$ 当没有用[ )的时候，边界，以及出边界的条件一定要小心
	// 实际上，这个if是没有必要，也不会提升性能的，因为while的condition足够了
	// if(i > mid) // put the rest of right half to result array
	// {
	// 	while(j <= right)
	// 	{
	// 		arr[k++] = tempArr[j++];
	// 	}
	// }
	// else 
	// {
	// 	while(i <= mid)
	// 	{
	// 		arr[k++] = tempArr[i++];
	// 	}
	// }
		while(j <= right)
		{
			arr[k++] = tempArr[j++];
		}
		while(i <= mid)
		{
			arr[k++] = tempArr[i++];
		}
}

void mSort(int* arr, int left, int right) //[]
{
	assert(right >= left);
	if(right == left) 
		return;
	int mid = (right + left) / 2;
	mSort(arr, left, mid);
	mSort(arr, mid + 1, right);
	merge(arr, left, mid, right);
}


void mergeSort(int* arr, int arrSize)
{
	mSort(arr,0,arrSize - 1);
}

int getMedianIndex(int* arr, int left, int right)
{
	int mid = (left + right) / 2;
	int leftValue = arr[left];
	int rightValue = arr[right];
	int midValue = arr[mid];	
	//$$ XXX note here we use >= to let mid index is returned when all three or two of them are identical
	// by doing so, we can avoid the bad case when lots of element in array are identical
	// √√√ 实际上，这个对于全部identical是没用的，因为决定拆分的是 currentLTP最后的位置，而不是pivot选在哪里。
	if((midValue >= leftValue && rightValue >= midValue) || (midValue >= rightValue && leftValue >= midValue))
		return mid;
	if((rightValue >= leftValue && midValue >= rightValue) || (rightValue >= midValue && leftValue >= rightValue))
		return right;
	return left;
	
}
#ifndef BETTERALGORITHM
//$$$ 这种方法在 all element are identical 的情况下，性能下降的太快，不要使用。
void qSort(int* arr, int left, int right)
{
	//assert(right >= left);
	if(left >= right)
		return;
	//@ later use insertion sort when right - left is relatively small
	int pivot = getMedianIndex(arr,left,right); //left + rand() % (right - left); 
	swap(arr, left, pivot);
	int currentLTP = left; // current position that element that less than pivot should be swapped to 
	for(int i = left + 1; i <= right; i++)
	{
		if(arr[i] < arr[left])
			swap(arr,i,++currentLTP);
	}
	swap(arr,left,currentLTP);
	qSort(arr,left,currentLTP - 1); // smaller than pivot part
	qSort(arr,currentLTP + 1,right); // larger than pivot part
}
#else
int getPivot(int* arr, int left, int right) // sort the left mid right of origin array, and return the value of pivot
{	
	int mid = (left + right) / 2;
	//++left; // in fact we sort left + 1, mid, and right 
	if(arr[left] > arr[mid])
		swap(arr,mid,left);
	if(arr[left] > arr[right])
		swap(arr,left,right);
	if(arr[mid] > arr[right])
		swap(arr,mid,right);
	std::cout << arr[left] << " " << arr[mid] << " " << arr[right] << std::endl;
	return arr[mid];

}
const int CutOff = 0; // the threshold of using quickSort or insertion sort

// void qSort(int* arr, int left, int right)
// {
// 
// 	if(left >= right)
// 		return;
// 	int pivot =  left + rand() % (right - left);  
// 	swap(arr, left, pivot);
// 	int i = left; // left is pivot, left + 1 is the smallest among median3(), it must be less than pivot
// 	int j = right+1; // right is the largest among median3(), it must larger than pivot
// 	while(i < j)
// 	{
// 		while(++i <= right && arr[i] < arr[left]) // when equal, also stop
// 		{
// 			std::cout << "i " << i << std::endl;
// 		}
// 		while(--j >= left && arr[j] > arr[left])
// 		{
// 		
// 		}
// 		if(i < j)
// 		{
// 			swap(arr,i,j);
// 		}
// 		
// 	} 
// 	swap(arr,left,j);  // swap pivot with the last last one that less it
// 	qSort(arr,left,j-1);
// 	qSort(arr,j+1,right);
// }

// void qSort(int* arr, int left, int right)
// {
// 	// if(left >= right)
// 	// 	return;
// 	if(right-left > CutOff) // when range is relatively large, use quick sort, else, use insertion sort
// 	{
// 		int pivot = left + rand() % (right - left);//getPivot(arr,left,right); // this function sort the left+1 mid right in array, return arr[mid]
// 		swap(arr,left,pivot);
// 		int i = left;
// 		int j = right + 1;
// 		while(i < j)
// 		{
// 			while(++i <= right && arr[i] < arr[left]) ; //empty body, left + 1 is a sentinel for i,
// 			while(--j > left && arr[j] > arr[left]) ; //empty body, right is a sentinel for j,
// 			
// 			if(i < j)
// 				swap(arr,i,j);
// 		}
// 		swap(arr,left,j);
// 		qSort(arr,left,j - 1);
// 		qSort(arr,j + 1, right);
// 	}
// 	else
// 	{
// 		insertionSort(arr+left, right - left + 1);
// 	}
// }
//#define MEDIAN_VERSION

#ifdef MEDIAN_VERSION
void qSort(int* arr, const int left, const int right)
{
	assert(CutOff > 1);
	if(right - left > CutOff) // @@ 当cutoff等于0的时候，还有问题，
	{
		int pivotValue = getPivot(arr,left,right);
		swap(arr,left + 1, (left + right) / 2); // pivot at left + 1
		int i = left + 1; // left + 1 is the pivot
		int j = right; // right is the largest one in median3
		while(i < j)
		{
			//while(++i <= right && arr[i] < pivotValue) ;
			//while(--j > left && arr[j] > pivotValue) ;
			//$$$用median的smallest 和largest做sentinel，并不适合当range中只有两个的情况,如果要用下面这种
			//$$$ 没有边界检测，而单纯用sentinel来结束while loop，在range = 2 的时候就会出错，所以还是要种
			//$$$ 上面注释的那种，有显示的 ++i 和 --j 边界检测的，这样，比起rand pivot的版本，就没有太多优势了
			//$$$ 而且还需要多自己写一个getPivot的函数，需要注意的地方更多，且没有很高的性能提升。除非在及其注重性能的
			//$$$ 情况下，再用median的版本，并且要显示的注明cutoff必须大于1。 在其他所有情况下，都用rand，并且显示边界检测
			//$$$ 的版本。
			while(arr[++i] < pivotValue) ;
			while(arr[--j] > pivotValue) ;
			if(i < j)
				swap(arr,i,j);
			else 
				break;
		}
		swap(arr,left + 1,j);
		qSort(arr,left,j - 1);
		qSort(arr,j + 1,right);
	}
	else
	{
		insertionSort(arr + left, right - left + 1);
	}

}

#else
void qSort(int* arr,const int left, const int right)
{
	if(right - left > CutOff) 
	{
		int pivot = left + rand() % (right - left);
		int pivotValue = arr[pivot];
		swap(arr,left,pivot); // after here, pivot has no use anymore
		int i = left; // left is the pivot, don't need to cover
		int j = right + 1; // because --j, so + 1 to cover arr[right]
		while(i < j)
		{
			while(++i <= right && arr[i] < pivotValue);
			while(--j > left && arr[j] > pivotValue);
			if(i < j)
				swap(arr,i,j);
		}
		swap(arr,left,j);
		qSort(arr,left,j - 1);
		qSort(arr,j + 1, right);
		
	}
	else
	{
		insertionSort(arr + left, right - left + 1);
	}
}
#endif

#endif

void quickSort(int* arr, int arrSize)
{
	qSort(arr, 0, arrSize - 1);
}


#define OTHERTEST

int main()
{
#ifdef OTHERTEST
	const int arrSize = 1000000;
	const int maxElement = 2 * arrSize;
	int arr[arrSize];
	srand((unsigned)time(NULL));
	time_t startTime = time(0);
	for(int i = 0; i != 50; i++)
	{
		for(int i = 0; i != arrSize; i++)
		{
			//arr[i] = 10; 
			arr[i] = rand() % maxElement;
		}
		quickSort(arr,arrSize);
	}
	std::cout << "---------sorted array--------------" << std::endl;
	std::cout << "duration: " << time(0) - startTime << std::endl;
	//printArray(arr,arrSize);
#else
	const int arrSize = 100000;
	const int maxElement = 2 * arrSize;
	int arr[arrSize];
	srand((unsigned)time(NULL));
	for(int i = 0; i != arrSize; i++)
	{
		//arr[i] = 10; 
		arr[i] = rand() % maxElement;
	}
	std::cout << "---------original array--------------" << std::endl;
	//printArray(arr, arrSize);
	time_t startTime = time(0);
	quickSort(arr,arrSize);
	std::cout << "---------sorted array--------------" << std::endl;
	std::cout << "duration: " << time(0) - startTime << std::endl;
	//printArray(arr,arrSize);
	return 0;
	
#endif
}





























































