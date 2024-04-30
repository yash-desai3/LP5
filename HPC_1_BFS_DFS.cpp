#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace chrono;

class Graph{
    int V;
    vector<vector<int>> adj;
    
    public:
    
    Graph(int V) : V(V), adj(V) {}
    
    void addEdge(int v, int w)
    {
        adj[v].push_back(w);
    }
    
    void parallelDFS(int startVertex)
    {
        vector<bool>visited (V,false);
        parallelDFSUtil(startVertex, visited);
    }
    
    void parallelDFSUtil(int v, vector<bool>& visited)
    {
        visited[v] = true;
        cout << v << " ";
        
        #pragma omp parallel for
        for(int i = 0 ; i < adj[v].size() ; i++)
        {
            int n = adj[v][i];
            if(!visited[n])
              {
                  parallelDFSUtil(n,visited);
              }
        }
        
    }
    
    void parallelBFS(int startVertex)
    {
        vector<bool> visited(V,false);
        queue<int> q;
        
        visited[startVertex] = true;
        q.push(startVertex);
        
        while(!q.empty())
        {
            int v = q.front();
            q.pop();
            cout << v << " ";
        
        #pragma omp parallel for
        for(int i = 0 ; i < adj[v].size() ; i++)
        {
            int n = adj[v][i];
            if(!visited[n])
            {
                visited[n] = true;
                q.push(n);
            }
        }
        }
    }
};

int main()
{
    int vertices, edges, startVertex;
    
    cout << "Enter no of vertices: ";
    cin >> vertices;
    cout << "Enter no of edges: ";
    cin >> edges;
    
    Graph g(vertices);
    
    cout << "enter " << edges << " from src to dest: ";
    for(int i = 0 ; i < edges; i++)
    {
        int src, dest;
        cin >> src >> dest;
        g.addEdge(src,dest);
    }
    
    cout<< "start vertex: ";
    cin >> startVertex;
    
    
    auto start_time = high_resolution_clock::now(); 
    g.parallelDFS(startVertex);
    auto end_time = high_resolution_clock::now(); 
    auto duration = duration_cast<nanoseconds>(end_time - start_time); 
    cout << "\nParallel DFS executed in " << duration.count() << " nanoseconds." << endl;
    
  
    
    start_time = high_resolution_clock::now(); 
    g.parallelBFS(startVertex);
    end_time = high_resolution_clock::now(); 
    duration = duration_cast<nanoseconds>(end_time - start_time); 
    cout << "\nParallel BFS executed in " << duration.count() << " nanoseconds." << endl;
}