#include <iostream>
#include <cstdlib>
 
// once a element pointed by last is swaped by a element less than pivot, the last will augment by one, so the less element will never be swapped evermore. And the element next to last is guaranteed to be larger or equal than the pivot in this algorithem. So, after scan all the element in the array, all the element left to pivot will less than than pivot, and the right ones will large than the pivot

#define NELEMS(array) (sizeof(array) / sizeof(array[0]))
using namespace std;

void swap(int*, int, int);

int Trace = 0;

int nums[] = {45,3,5,6,67,2,7,9,33,55,36,49,54,35,19,22,39,33,1,3,4,6};

// a stack to simulate the recursion
class Stack   //int
{
private:
	int size;
	int current;
	int * ary;
public:
	Stack(int s):size(s),current(0){ary = new int[size];}
	~Stack(){delete ary;}
	void push(int n)
	{
		if(current == size)
		{
			cout << "error: stack is full";
			exit(1);
		}
		ary[current++] = n;
	}	
	int pop()
	{
		if(current == 0)
		{
			cout << "error: stack is empty";
			exit(1);
		}
		return ary[--current]; 
	}	
	void showStack()
	{
		cout << "stack: ";
		for(int i = 0; i != current; i++)
			cout << ary[i] << ' ';
		cout << endl;
	}	
};

// void quicksort(int v[], int begin, int end)  // use N, and relative index rather than absolute index
// {
// 	int last = begin; // to trace the last one less than the pivot. 
// 	if(end - begin <= 1)
// 		return;
// 	swap(v, begin, rand() % (end - begin) + begin);    //here need to use begin as base
// 	for(int i = begin + 1; i != end; i++)
// 		if(v[i] < v[begin])
// 			swap(v, ++last, i);
// 	swap(v, begin, last);
// 	std::cout << "Trace = " << Trace++ << std::endl;
// 	std::cout << "begin = " << begin << "   end = " << end << std::endl;
// 	std::cout << "Pivot = " << v[last] << std::endl;
// 	for(int i = 0; i != 8; i++)
// 	{
// 		std::cout << nums[i] << ' ';
// 	}
// 	std::cout << std::endl;
// 	
// 	quicksort(v, begin, last);
// 	quicksort(v, last + 1, end);
// }

/* quicksort: sort v[O]. .v[n-11 into increasing order */ 
void quicksort(int v[], int n)    // use the relationship between [) and N to simplify your mind
{
	int last = 0;
	if(n <= 1) 
		return;
	swap(v,0,rand()%n);
	last = 0; //$$ last is the number of element less that pivot as well as the index of next less-than element should be
	for(int i = 1; i != n; i++)
		if(v[i] < v[0])
			swap(v,++last,i);
	swap(v, 0, last); 
	// $$ after one iteration, v[0] is the pivot, v[last] is just a element less than pivot, we swap it to v[0], just because
	// it is less than pivot, it does't have to be the minimum one.
	quicksort(v, last);
	quicksort(v + last + 1, n - last - 1);
	
}

void quicksort_stack(int v[], int b, int e)
{
	Stack stack(1000);
	int begin, end;
	stack.push(b);
	stack.push(e);
	int nloop = 0;
	while(!(end == e && end - begin <= 1 ))
	{
		cout << nloop++ << " loop" << endl;
		stack.showStack();
			
			
		end = stack.pop();
		begin = stack.pop();
		if(end - begin <=1)
			continue;
		int last = begin;
		swap(v, begin, rand() % (end - begin) + begin);
		for(int i = begin + 1; i != end; i++)
			if(v[i] < v[begin])
				swap(v, ++last, i);
		swap(v, begin, last);
		stack.push(last + 1);
		stack.push(end);
		stack.push(begin);
		stack.push(last);	
	}
}


void swap(int v[], int i, int j)
{
	int temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int ncmp (const void* v1, const void* v2)  // parameter for qsort
{
	int n1 = *(int*)v1;    // to cast a void pointer to the type you need. something similar with template
	int n2 = *(int*)v2;
	if(n1 < n2)
		return -1;
	else if(n1 > n2)
		return 1;
	else 
		return 0;
}


int main()
{
	
	int len = NELEMS(nums);
	std::cout << "length: " << len << std::endl;
	quicksort_stack(nums, 0, len); 
	//quicksort(nums,len);
	//qsort(nums, len, sizeof(nums[0]), ncmp);  // library qsort
	for(int i = 0; i != len; i++)
	{
		std::cout << nums[i] << ' ';
	}
	
}




// length: 8
// Trace = 0
// Pivot = 9
// 7 3 5 6 2 9 67 45 
// Trace = 1
// Pivot = 2
// 2 3 5 6 7 
// Trace = 2
// Pivot = 5
// 3 5 6 7 
// Trace = 3
// Pivot = 6
// 6 7 
// Trace = 4
// Pivot = 67
// 45 67 
// 2 3 5 6 7 9 45 67















































































































