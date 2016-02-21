#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <vector>
#include <string> 
using namespace std;

// 首先把算法想清楚了，再开始写。 想的时候先观察规律，至少把简单形式的算法自己的跑通一遍了，再用代码实现。
// 不是非常确定的时候，宁愿把情况多罗列几个，不要用一些很有技巧的东西来把很多种情况放在一个表达式里


template<class T>
class Stack
{
public:
	const int MaxElement;
private:	
	int Top;
	T* Array;
public:
	Stack(int max):MaxElement(max),Top(-1),Array(new T[max]){}
	bool isFull()
	{
		return Top >= MaxElement - 1;
	}
	bool isEmpty()
	{
		return Top < 0;
	}
	
	void push(T v)
	{
		if(!isFull())
		{
			Array[++Top] = v;
		}
		else
		{
			cout << "Stack don't have enough space" << endl;
		}
	}
	
	T top()
	{
		if(!isEmpty())
			return Array[Top];
		else
		{
			cout << "Stack is empty" << endl;
			return 0;
		}
	}
	
	void pop()
	{
		if(!isEmpty())
			--Top;
		else
			cout << "Stack is empty, can't pop" << endl;
	}
	
	T popAndTop()
	{
		if(!isEmpty())
			return Array[Top--];
		else
		{
			cout << "Stack is empty, can't popAndTop" << endl;
			return 0;
		}
	}
	
	void dump()
	{
		cout << "stack MaxElement: " << MaxElement << "  Top: " << Top << endl; 
		cout << "elements: ";
		for(int i = 0; i <= Top; i++)
		{
			cout << Array[i] << ' ';
		}
		cout << endl;
	}
	
	
};

bool isOperator(string c)
{
	return c == "+" || c == "-" || c == "*" || c == "/" || c == "(" || c == ")";
}

int priorityRand(string op)
{
    if(op == "+" || op == "-")
		return 1;
	else if(op == "*" || op == "/")
		return 2;
	else if(op == "(")
		return 0;
	else
	{
		cout << "invalid operator: " << op << endl;
		return -1;
	}
}

bool lowerOrEqualTo(string newOp, string oldOp)
{
	//cout << newOp << " <= " << oldOp << ": " << (priorityRand(newOp) <= priorityRand(oldOp)) << endl;
	return priorityRand(newOp) <= priorityRand(oldOp);
}

void popOperator(Stack<string>& operatorStack, string& result)
{
	cout << "try pop " << operatorStack.top() << endl;
	result += operatorStack.popAndTop();
}

void infixToPostfix()
{
	string exp[] = {"a", "+", "b", "*", "c", "+", "(", "d", "*", "e", "+", "f", ")", "*", "g"};
	Stack<string> operandStack = Stack<string>(1000);
	Stack<string> operatorStack = Stack<string>(1000);
	string result = "";
	int size = sizeof(exp) / sizeof(exp[0]);
	//cout << "size " << size << endl;
	for(int i = 0; i != size; i++)
	{
		string c = exp[i];
		if(isOperator(c))
		{
			if(c == ")")
			{
				while(!operatorStack.isEmpty() && operatorStack.top() != "(")
					popOperator(operatorStack, result);
				if(!operatorStack.isEmpty() && operatorStack.top() == "(")
					operatorStack.pop();
			}
			else if(c == "(")
			{
				operatorStack.push(c);
			}
			else
			{
				while(!operatorStack.isEmpty() && lowerOrEqualTo(c, operatorStack.top()))
				{
					popOperator(operatorStack, result);
				}
				operatorStack.push(c);
			}		

		}
		else // is operand
		{
			//operandStack.push(c);
			result += c;
		}
		//cout << "result now is " << result;
	}
	while(!operatorStack.isEmpty())
		popOperator(operatorStack, result);
	cout << "result: " << result << endl;
}

int main()
{
	infixToPostfix();
	
}