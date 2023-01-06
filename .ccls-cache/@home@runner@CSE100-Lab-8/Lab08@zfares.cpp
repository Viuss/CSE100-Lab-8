//Used Geeks for Geeks as a resource for Bellman-Ford and miscellaneous parts
//Received help from Andrew Mouillesseaux for printArr function
#include <bits/stdc++.h>
#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

struct Edge 
{
	int initial, final, weight;
};

struct Graph 
{
	int Verts, Edges;
	struct Edge* edge;
};

// Make graph with amount of vertices and edges
struct Graph* createGraph(int Verts, int Edges)
{
	struct Graph* graph = new Graph;
	graph->Verts = Verts;
	graph->Edges = Edges;
	graph->edge = new Edge[Edges];
	return graph;
}

void printArr(int length[], int n)
{
  cout<<"TRUE"<<endl;
  for (int i = 0; i < n; ++i){
    if(length[i]!=INT_MAX)
      cout<<length[i]<<endl;
    else
      cout<<"INFINITY"<<endl;
  }
}

// Find shortest distance from initial to all other vertices and detect negative weight cycle
void BellmanFord(struct Graph* graph, int initial)
{
	int Verts = graph->Verts;
	int Edges = graph->Edges;
	int length[Verts];

	// Set distance from initial to all vertices as infinity.
	for (int i = 0; i < Verts; i++)
		length[i] = INT_MAX;
	length[initial] = 0;

	// See if pathing can be improved from current position. Shortest path can have
	// at-most |V| - 1 edges
	for (int i = 1; i <= Verts - 1; i++) {
		for (int j = 0; j < Edges; j++) {
			int u = graph->edge[j].initial;
			int v = graph->edge[j].final;
			int weight = graph->edge[j].weight;
			if (length[u] != INT_MAX
				&& length[u] + weight < length[v])
				length[v] = length[u] + weight;
		}
	}

	// Check if weights sum to negative number (negative cycle). If we get 
	// a shorter path than in the previous loop, we know there is negative cycle.
	for (int i = 0; i < Edges; i++) 
  {
		int u = graph->edge[i].initial;
		int v = graph->edge[i].final;
		int weight = graph->edge[i].weight;
		if (length[u] != INT_MAX
			&& length[u] + weight < length[v]) {
			cout << "FALSE" << endl;
			return; // If negative cycle -> return
		}
	}
	printArr(length, Verts);
	return;
}


int main()
{
  int Verts,Edges;
  cin>> Verts>> Edges;
  struct Graph* graph = createGraph(Verts, Edges);
  
  for(int i = 0; i < Edges; i++){
    cin>>graph->edge[i].initial;
    cin>>graph->edge[i].final;
    cin>>graph->edge[i].weight;
  }
  BellmanFord(graph, 0);
}