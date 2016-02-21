#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <vector>
#include <string> 
#include <stack>
#include <queue>
#include <stdexcept>
#include <exception>

using namespace std;
const int MAX = 128;


class Graph
{
public:
	const int nVertex;
private:
	int* vertexs;
	int** edges;
	
public:
	Graph(int n):nVertex(n),vertexs(new int[nVertex]),edges(new int*[nVertex])
	{
		for(int i = 0; i < nVertex; i++)
		{
			edges[i] = new int[nVertex]();
		}
		for(int i = 0; i < nVertex; i++)
		{
			 // 这里其实没什么用，不赋值也行。真正代表这个Vertex的是index 实际代码中，这里可能存的是一个Vertex类型，有其他相关的信息。
			vertexs[i] = i;
		}

	}
	
	~Graph()
	{
		delete [] vertexs;
		for(int i =0; i < nVertex; i++)
		{
			delete [] edges[i];
		}
	}
	
	void AddEdge(int i, int j) // from i to j
	{
		if(i >= nVertex || j >= nVertex)
		{
			throw range_error("bad index for vertex");
		}
		edges[i][j] = 1;
		edges[j][i] = 1; //无向图。
	}
	
	int GetEdge(int i, int j)
	{
		if(i >= nVertex || j >= nVertex)
		{
			throw range_error("bad index for vertex");
		}
		return edges[i][j];	
	}
	
};

Graph* GenerateGraph()
{
	Graph* g = new Graph(9);
	g->AddEdge(0,1);
	g->AddEdge(0,2);
	g->AddEdge(1,4);
	g->AddEdge(2,3);
	g->AddEdge(6,7);
	g->AddEdge(5,3);
	g->AddEdge(8,2);
	g->AddEdge(6,4);
	g->AddEdge(3,6);
	g->AddEdge(0,7);
	
	return g;
}



void DFS(Graph* g, int vertex, int visited[])
{
	cout << vertex << endl;
	visited[vertex] = 1;
	for(int i = 0; i < g->nVertex; i++)
	{
		if(g->GetEdge(vertex,i)==1 && visited[i] != 1)
		{
			DFS(g,i,visited);
		}
	}
}

void DFS_nonrecursive(Graph* g, int startVertex)
{
	int visited[MAX];
	memset(visited,0,sizeof(visited));
	stack<int> s = stack<int>();
	s.push(startVertex);
	while(!s.empty())
	{
		int v = s.top();
		s.pop();
		if(visited[v] != 1)
		{
			cout << v << endl;
			visited[v] = 1;
			for(int i = g->nVertex-1; i >=0 ; i--)
			{
				if(g->GetEdge(v,i) == 1 && visited[i] != 1)
				{
					s.push(i);
				}
			}
		}
	}
}

void DFS_nonrecursive2(Graph* g, int startVertex)
{
	int visited[MAX];
	memset(visited,0,sizeof(visited));
	stack<int> s = stack<int>();
	s.push(startVertex);
	while(!s.empty())
	{
		int v = s.top();
		bool done = true;
		if(visited[v] != 1)
		{
			cout << v << endl;
			visited[v] = 1;
		}
		for(int i = 0; i < g->nVertex ; i++) // 注意这里因为模拟的是栈，所以顺序，不需要逆序
		{
			if(g->GetEdge(v,i) == 1 && visited[i] != 1)
			{
				s.push(i);
				done = false;
				break;
			}
		}
		if(done)
		{
			s.pop();
		}
	}
}


void BFS(Graph* g, int startVertex)
{
	int visited[MAX];
	memset(visited,0,sizeof(visited));
	queue<int> q = queue<int>();
	cout << startVertex << endl;
	q.push(startVertex);
	visited[startVertex] = 1;
	while(!q.empty())
	{
		int v = q.front();
		q.pop();
		for(int i = 0; i < g->nVertex; i++)
		{
			if(g->GetEdge(v,i) == 1 && visited[i] != 1)
			{
				cout << i << endl;
				visited[i] = 1;
				q.push(i);
			}
		}
	}
}



int main()
{	
	Graph* g = GenerateGraph();
	cout << "here" << endl;
	int visited[MAX];
	memset(visited,0,sizeof(visited));
	int start = 0;
	DFS(g,start,visited);
	cout << "-----------------------------" << endl;
	DFS_nonrecursive2(g, start);
	cout << "-----------------------------" << endl;
	BFS(g,start);
	delete g; 
	

}














	
	
	
	
	