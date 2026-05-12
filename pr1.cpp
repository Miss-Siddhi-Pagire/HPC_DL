#include<iostream>
#include<vector>
#include<queue>
#include<omp.h>
using namespace std;
class Graph{
    int V;
    vector<vector<int>> adj;
public:
    Graph(int V){
        this->V = V;
        adj.resize(V);
    }
    void addEdge(int u,int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // Parallel BFS
    void BFS(int start){
        vector<bool> visited(V,false);
        queue<int> q;
        visited[start]=true;
        q.push(start);
        cout<<"\nBFS: ";
        while(!q.empty()){
            int node=q.front();
            q.pop();
            cout<<node<<" ";
            #pragma omp parallel for
            for(int i=0;i<adj[node].size();i++){
                int n=adj[node][i];
                if(!visited[n]){
                    visited[n]=true;
                    #pragma omp critical
                    q.push(n);
                }
            }
        }
    }
    // Parallel DFS
    void DFSUtil(int node, vector<bool>& visited){
        visited[node]=true;
        cout<<node<<" ";
        #pragma omp parallel for
        for(int i=0;i<adj[node].size();i++){
            int n=adj[node][i];
            if(!visited[n])
                DFSUtil(n,visited);
        }
    }
    void DFS(int start){
        vector<bool> visited(V,false);
        cout<<"\nDFS: ";
        DFSUtil(start,visited);
    }
};
int main(){
    int V,E,u,v,start;
    cout<<"Vertices: ";
    cin>>V;
    Graph g(V);
    cout<<"Edges: ";
    cin>>E;
    cout<<"Enter edges:\n";
    for(int i=0;i<E;i++){
        cin>>u>>v;
        g.addEdge(u,v);
    }
    cout<<"Start vertex: ";
    cin>>start;
    g.BFS(start);
    g.DFS(start);
    return 0;
}