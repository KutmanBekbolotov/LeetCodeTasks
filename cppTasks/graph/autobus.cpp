#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;
vector<int> pairU, pairV, dist;

bool isBipartite(int n, vector<vector<int>>& graph, vector<int>& color){
    queue<int> q;

    for(int i = 0; i < n; i++){
        if(color[i] == -1){
            color[i] = 0;
            q.push(i);

            while(!q.empty()){
                int u = q.front();
                q.pop();

                for(int v : graph[u]){
                    if(color[v] == -1){
                        color[v] = 1 - color[u];
                        q.push(v);
                    }else if(color[v] == color[u]){
                        cout << "Ошибка! Граф не двудольный. Проблема на ребре: " << u+1 << " - " << v+1 << endl;
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool bfs(int U, vector<vector<int>>& adj){
    queue<int> q;
    int NIL = U; 

    for(int u = 0; u < U; u++){
        if(pairU[u] == -1){
            dist[u] = 0;
            q.push(u);
        }else{
            dist[u] = INF;
        }
    }
    dist[NIL] = INF;

    while(!q.empty()){
        int u = q.front();
        q.pop();

        if(dist[u] < dist[NIL]){
            for(int v : adj[u]){
                if(dist[pairV[v]] == INF){
                    dist[pairV[v]] = dist[u] + 1;
                    q.push(pairV[v]);
                }
            }
        }
    }
    return (dist[NIL] != INF);
}

bool dfs(int u, vector<vector<int>>& adj){
    if(u != -1){
        for(int v : adj[u]){
            if(dist[pairV[v]] == dist[u] + 1 && dfs(pairV[v], adj)){
                pairV[v] = u;
                pairU[u] = v;
                return true;
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}

int hopcroftKarp(int U, int V, vector<vector<int>>& adj){
    pairU.assign(U, -1);
    pairV.assign(V, -1);
    dist.assign(U + 1, INF);

    int matching = 0;
    while(bfs(U, adj)){
        for(int u = 0; u < U; u++){
            if(pairU[u] == -1 && dfs(u, adj)){
                matching++;
            }
        }
    }
    return matching;
}

int main(){
    int n, m;
    cout << "Enter quantity of cities (n) and roads (m): ";
    cin >> n >> m;

    vector<vector<int>> graph(n);
    cout << "Enter roads between cities:" << endl;
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> color(n, -1);
    if(!isBipartite(n, graph, color)){
        cout << "Graph is not bipartite!" << endl;
        return 0;
    }

    int U = 0, V = 0;
    for(int u = 0; u < n; u++){
        if(color[u] == 0) U++;
        else V++;
    }

    vector<vector<int>> adj(U);
    for(int u = 0; u < n; u++){
        if(color[u] == 0){
            for(int v : graph[u]){
                adj[u].push_back(v - U);
            }
        }
    }

    int minBuses = hopcroftKarp(U, V, adj);
    cout << "Minimal quantity of buses: " << minBuses << endl;
    return 0;
}