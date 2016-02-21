#include <iostream>
#include <stdlib.h>

struct NameVal
{
	char* name;
	int val;
};

struct NVTab
{
	int nval;
	int max;
	NameVal *nvArray;
};

NVTab nvTab;

const int NVTABLEINITI = 3;

int addName(NameVal newName)
{
	if(nvTab.nvArray == NULL)
	{
		nvTab.max = NVTABLEINITI;
		nvTab.nval = 0;
		nvTab.nvArray = (NameVal*) malloc(sizeof(NameVal) * NVTABLEINITI); 
		if(nvTab.nvArray == NULL)
			return -1;
	}
	else if(nvTab.nval + 1 >= nvTab.max)
	{
		NameVal* nvp =(NameVal*)realloc(nvTab.nvArray, sizeof(NameVal) * nvTab.max * 2);
		//double the size of the array
		if(nvp == NULL)
			return -1;
		else
		{	nvTab.nvArray = nvp;
			nvTab.max *= 2;
			std::cout << "The array size has doubled to " << nvTab.max << std::end;
			
		}
	}
	nvTab.nvArray[nvTab.nval++] = newName;
	return 0;
}

int main()
{
	NameVal name1;
	name1.name = "Leon";
	name1.val = 100;
	for(int i = 0; i != 100; i++)
	addName(name1);
	for(int i = 0; i !=10; i++)
		std::cout << "hello " << nvTab.nvArray[i].name;
	
}