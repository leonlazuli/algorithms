#include <iostream>
#include <list>
#include <exception>
#include <queue>

class Vertex
{
	friend class Graph;
private:
	std::list<Vertex*> adjacentList;
	int inDegree; // 
	int index; // just for print
public:
	Vertex(int indegree = 0):inDegree(indegree){}
	void addEdge(Vertex* pV)
	{
		adjacentList.push_back(pV);
	}
	void setIndex(int i)
	{
		index = i;
	}
	void printAdjacentVertices() const
	{
		int counter = 0;
		for(std::list<Vertex*>::const_iterator iter = adjacentList.begin(); iter != adjacentList.end(); iter++)
		{
			std::cout << (*iter)->index + 1 << " ";
			++counter; // just for print a better format of inDegree
		}
		int nBlank = 20 - 2 * counter;
		for(int i = 0; i != nBlank; i++)
			std::cout << ' ';
		std::cout << "indegree: " << inDegree;
	}
	void remove()
	{
		for(std::list<Vertex*>::const_iterator iter = adjacentList.begin(); iter != adjacentList.end(); iter++)
		{
			--(*iter)->inDegree;
		}
	}
	// maybe other values
};

class Graph
{
private:
	int numVertices;
	Vertex* arr;
public:
	Graph(int size):numVertices(size),arr(new Vertex[numVertices])
	{
		for(int i = 0; i != numVertices; i++)
		{
			arr[i].setIndex(i);
		}
	}
	~Graph(){delete [] arr;}
	
	void addEdge(int from, int to)
	{
		arr[from - 1].addEdge(&arr[to - 1]);	
	}
	
	void print()
	{
		for(int i = 0; i != numVertices; i++)
		{
			std::cout << "vertex " << i + 1 << ": ";
			arr[i].printAdjacentVertices(); 
			std::cout << std::endl;
		}
	}
	
	void topologicalSort()
	{
		std::queue<Vertex*> que;
		// bool tag[numVertices];
		// for(int i = 0; i != numVertices; i++)
		// {
		// 	tag[i] = false;
		// }
		updateIndegree();
		for(int i = 0; i != numVertices; i++)
		{
			if(arr[i].inDegree == 0)
			{
				que.push(&arr[i]);
			}
		}
		if(que.empty())
			throw std::runtime_error("not a DAG");
		int counter = 0;
		//因为没有回路，所以当一个vertex inqueue之后它不可能再有机会在之后的vertex中被处理（--indegree什么的），所以这里不需要一个Known的tag
		// 也就是说 当inqueue的时候，indegree已经为0了，也就是说，它之前（to它）的所有东西都已经处理过了，之后不会再
		//遇到 to 它的vertex了，所以不用tag
		while(!que.empty())
		{
			++counter;
			Vertex* v = que.front();
			que.pop();
			const std::list<Vertex*>& list = v->adjacentList;
			for(std::list<Vertex*>::const_iterator iter = list.begin(); iter != list.end(); iter++)
			{
				if(--(*iter)->inDegree == 0) //$$  here I change (*iter)->inDegree, 那么const 就应该不是
					//递归的，也就是说，只是const了 那个 *iter 不能改变 而*iter本身也是个指针，就是说这个指针不恩能够改变， 而指针指向的东西还是可以的
					que.push(*iter);
			}
			std::cout << v->index + 1 << std::endl;
		}
		if(counter != numVertices)
			throw std::runtime_error("not a DAG");
	}
	
private:
	void updateIndegree()
	{
		for(int i = 0; i != numVertices; i++)
		{
			std::list<Vertex*>& rList = arr[i].adjacentList;
			for(std::list<Vertex*>::iterator iter = rList.begin(); iter != rList.end(); iter++)
			{
				++((*iter)->inDegree);
			}
		}
	}
	
	
};

int main()
{
	Graph g(7);
	g.addEdge(1,3);
	g.addEdge(1,4);
	g.addEdge(1,2);
	g.addEdge(2,4);
	g.addEdge(2,5);
	g.addEdge(3,6);
	g.addEdge(4,3);
	g.addEdge(4,6);
	g.addEdge(4,7);
	g.addEdge(5,4);
	g.addEdge(5,7);
	g.addEdge(7,6);
	g.topologicalSort();
	g.print();
	return 0;
}