#include <stdlib.h>
#include <iostream>
#include <stdio.h>

using namespace std;

struct NameVal
{
	char *name;
	int val;
	NameVal *next;
};

NameVal* new_name(char* name, int val)
{
	NameVal *nvp = (NameVal*) malloc(sizeof(NameVal)); 
	// can use emalloc which guarantee the correct of execution, otherwise it reports the error and exit 
	if(nvp == NULL)
		cerr << "failed to allocate for nvp\n";
	else
	{
		nvp->name = name;  // $$$ should I just use = or strcpy?
		nvp->val = val;
		nvp->next = NULL;
	}
	return nvp;
}

NameVal* add_front(NameVal *listp, NameVal *newp)
{
	if(newp == NULL)
	{
		std::cerr << "error!\n";
		return listp;
	}
	else
	{
		newp->next = listp;
		return newp;
	}
}

NameVal* add_end(NameVal *listp, NameVal *newp)
{
	if(listp == NULL)
		return newp;
	else
	{
		NameVal *p = listp;
		for(; p->next != NULL; p = p->next);
		p->next = newp;
		return listp;
	}
}

NameVal* look_up(NameVal *listp, char* name)
{
	// // if(list == NULL) // don't need
	// // 	return NULL;
	// for(NameVal* p = list, p->next != NULL, p = p->next) 
	// 	//  the p witchs conform to the judge condition doesn't excute the for body, Wrong! the boundary of 
	// {
	// 	if(strcmp(name,p->name) == 0)
	// 		return p;
	// }
	for(; listp != NULL; listp = listp->next)
	{
		if(strcmp(name, listp->name) == 0);
			return listp;
	}
	return NULL;
		
}

void apply(NameVal *listp, void *arg, void (*fn)(NameVal*, void*))
{
	for(; listp != NULL; listp = listp->next)
	{
		(*fn)(listp, arg);
	}
}

void print_list(NameVal *listp, void* arg)
{
	char* fmt = (char*) arg;
	printf("%s: %d\n", listp->name, listp->val);
	//std::cout << "print executed\n";
	//std::cout << "format is :" << fmt << std::endl;
}

void inc_counter(NameVal *listp, void* arg)
{
	int * counterp = (int*) arg;
	(*counterp)++;   //pay attention to the precedence of * and ++
}

void delete_list(NameVal *listp)
{
	NameVal *p = listp;
	while( (p = listp) != NULL)
	{
		free(listp);
		listp = p->next;
	}
	
}

NameVal* delete_name(NameVal *listp, char* name) // my version
{
	NameVal *p = NULL;
	NameVal *rep = listp;
	if(strcmp(listp->name,name) == 0)
	{
		std::cout << "1 = 1 \n";
		p = listp->next;
		std::cout <<"name of p" << p->name << std::endl;
		free(listp);
		return p;
	}
	for(;listp->next!= NULL; listp = listp->next)
	{
		if(strcmp(listp->next->name,name) == 0)
		{
			p = listp;
			p->next = p->next->next;
			free(listp++);
			return rep;
		}
	}
	return rep;
}

void delete_name_version2(NameVal* better)
{
	09870p9o-87
}

int main()
{
	NameVal* listp = new_name("leon", 100);
	NameVal *store = listp;
	listp = add_front(listp, new_name("lazuli", 99));
	listp = add_end(listp, new_name("leon lazuli",100));
	char* format = "hello world";
	apply(listp, format,print_list);
	int counter = 0;
	apply(listp, &counter,inc_counter);
	std::cout << "list has " << counter << " elements\n";
	listp = delete_name(listp,"leon");
	std::cout << "pppp pppp  " << store->name << "    ppppp\n";
	apply(listp, format, print_list);
	
	
}



 






















 