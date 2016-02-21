#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <vector>
#include <string> 
#include <stack>
#include <queue>
#include <stdexcept>
using namespace std;

//Depth first search
//对于树来讲其实就是前序遍历，对于图来讲，注意要标记是否visit过了

void Dfs(Vertex* v)
{
	process(node);
	foreach(Vertex w adjacent to v)
		if(!Visited[w])
			Dfs(w);
}

void Dfs_Stack(Vertex* vertex)
{
	Stack stack;
	stack.push(vertex);
	while(!stack.empty())
	{
		Vertex v = stack.pop();
		process(v);
		Visited[v] = true;
		foreach(w adjacentTo v)
		{
			if(!Visited[w])
			{
				stack.push();
				break; // Important
			}
		}
	}
}

// DFS 用stack   BFS用queue，  但是注意，push的东西不太一样，  stack是push 没有处理的，而queue是push处理过了的。  这个和他们自己的策略有关，同时注意，它俩都是前序的操作，即先处理这个点，再处理这个点的相邻点


//Breadth first search
void Bfs(Vertex* vertex)
{
	Queue queue;
	process(vertex);
	Visited[vertex] = true;
	queue.push(vertex);
	while(!queue.empty())
	{
		Vertex v = queue.pop();
		foreach(w adjacent to v)
			if(!Visited[w])
			{
				Process[w];
				Visited[w] = true;
				queue.push(w);
			}
	}
	
}