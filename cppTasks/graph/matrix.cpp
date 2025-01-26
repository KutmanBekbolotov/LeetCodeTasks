#include <iostream>
#include <vector>

using namespace std;

void dfs(int v, const vector<vector<int>>& graph, vector<bool>& visited) {
    visited[v] = true;

    for (int neighbor : graph[v]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited);
        }
    }
}

bool canReach(int start, int target, const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);

    dfs(start, graph, visited);

    return visited[target];
}

int main() {
    int V = 5; 
    vector<vector<int>> graph(V);

    graph[0].push_back(1);
    graph[0].push_back(2);
    graph[1].push_back(3);
    graph[2].push_back(4);

    int start = 0, target = 4;

    if (canReach(start, target, graph)) {
        cout << "Можно попасть из вершины " << start << " в вершину " << target << endl;
    } else {
        cout << "Нельзя попасть из вершины " << start << " в вершину " << target << endl;
    }

    return 0;
}