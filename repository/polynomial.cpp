#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <exception>

using namespace std;

// this list has a header as sentinel.

struct Node
{
	int Coefficient;
	int Exponent;
	Node* next;
	Node(int co, int ex):Coefficient(co),Exponent(ex),next(NULL){}
};

class CPolinomial
{
	friend CPolinomial* polynomial_add(const CPolinomial& po1, const CPolinomial& po2);
	friend CPolinomial* polynomial_mul(const CPolinomial& po1, const CPolinomial& po2);
private:
	Node* p_polinomial;
public:
	CPolinomial():p_polinomial(NULL){};
	CPolinomial(int co, int ex){p_polinomial = new Node(co, ex);} // potential error, no delete
	void insert(int co, int ex)
	{
		if(p_polinomial == NULL)
		{
			p_polinomial = new Node(co, ex);
			return;
		}
		
		if(ex > p_polinomial->Exponent)
		{
			Node* p_temp = p_polinomial;
			p_polinomial = new Node(co, ex);
			p_polinomial->next = p_temp;
			return;
		}
		else if(ex == p_polinomial->Exponent)
		{
			p_polinomial->Coefficient += co;
			return;
		}
		
		Node* p_temp = p_polinomial;
		while(p_temp->next != NULL)
		{
			if(p_temp->next->Exponent > ex)
				p_temp = p_temp->next;
			else if(p_temp->next->Exponent == ex)
			{
				p_temp->next->Coefficient += co;
				return;
			}
			else
			{
				Node* p_temp2 = p_temp->next;
				p_temp->next = new Node(co,ex);
				p_temp->next->next = p_temp2;
				return;
			}
				
		}
			p_temp->next = new Node(co,ex);  // while loop finish with p_temp->next == NULL
		
	}
	
	void print()
	{
		Node* p = p_polinomial;
		cout << p->Coefficient << " * X"<< p->Exponent ;
		p = p->next;
		while(p != NULL)
		{
			if(p->Coefficient >= 0)
			{
				cout << " + " << p->Coefficient << " * X"<< p->Exponent ;
			}
			else
				cout << " - " << - p->Coefficient << " * X" << p->Exponent;
			p = p->next; 
		}
		cout << endl;
	}
	
};

CPolinomial* polynomial_mul(const CPolinomial& po1, const CPolinomial& po2)
{
	
	
	CPolinomial* ret = new CPolinomial();
	for(Node* p1 = po1.p_polinomial; p1 != NULL; p1 = p1->next)
		for(Node* p2 = po2.p_polinomial; p2 != NULL; p2 = p2->next)
		{
			ret->insert(p1->Coefficient * p2->Coefficient, p1->Exponent + p2->Exponent);
		}
		return ret;
}

CPolinomial* polynomial_add(const CPolinomial& po1, const CPolinomial& po2)
{
	CPolinomial* ret = new CPolinomial();
	Node* p1 = po1.p_polinomial;
	Node* p2 = po2.p_polinomial;
	Node* p = NULL;
	
	if(p2 == NULL || p1->Exponent > p2->Exponent)
	{
		Node* node = new Node(p1->Coefficient, p1->Exponent);
		ret->p_polinomial = node;
		p1 = p1->next;
		
	}
	else if(p1 == NULL || p1->Exponent < p2->Exponent)
	{
		Node* node = new Node(p2->Coefficient, p2->Exponent);
		ret->p_polinomial = node;
		p2 = p2->next;
	}
	else 
	{
		Node* node = new Node(p2->Coefficient + p1->Coefficient, p2->Exponent);
		ret->p_polinomial = node;
		p1 = p1->next;
		p2 = p2->next;
	}
	
	p = ret->p_polinomial;
	
	while(p1 != NULL || p2 != NULL)
	{
		if(p2 == NULL || p1->Exponent > p2->Exponent)
		{
			Node* node = new Node(p1->Coefficient, p1->Exponent);
			p->next = node;
			p = p->next;
			p1 = p1->next;
			
		}
		else if(p1 == NULL || p1->Exponent < p2->Exponent)
		{
			Node* node = new Node(p2->Coefficient, p2->Exponent);
			p->next = node;
			p = p->next;
			p2 = p2->next;
		}
		else 
		{
			Node* node = new Node(p2->Coefficient + p1->Coefficient, p2->Exponent);
			p->next = node;
			p = p->next;
			p1 = p1->next;
			p2 = p2->next;
		}
		 ret->print();
	}
	return ret;
}

int main()
{
	CPolinomial p1(2,5);
	CPolinomial p2(1,2);
	p1.insert(3,2);
	p1.insert(-2,7);
	p1.insert(3,5);
	p1.insert(20,19);
	p2.insert(2,3);
	p2.insert(4,6);
	p2.insert(5,3);
	p2.insert(5,7);
	p1.print();
	p2.print();
	cout << "---------------------\n";
	CPolinomial* add_result = polynomial_add(p1,p2);
	cout << "---------------------\n";
	CPolinomial* mul_result = polynomial_mul(p1,p2);
	add_result->print();
	printf("\n");
	mul_result->print();
	
	return 0;
}
















