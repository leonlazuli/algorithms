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

//topSort

void TopSort(Graph G)
{
	int inDegree[G.VectexNum + 1]; // 0 没有用到
	ComputeInDegree(G, inDegree);
	int counter == 0;
	Queue<Vertex> queue;
	
	for(int i = 1; i <= G.VertexNum; G++)
	{
		if(inDegree[i] == 0)
			queue.push(G.Vertex[i]);
	}
	
	while(!queue.isEmpty())
	{
		Vertex v = queue.pop();
		TopSort[v.index] = ++Counter;
		foreach(Vertex w adjacentTo v)
		{
			--inDegree[w];
			if(inDegree[w] == 0)
				queue.push()
		}
	}
	if(counter != G.vertexCount)
	{
		cerr << "there is a circle" << endl;
	}s
	
}