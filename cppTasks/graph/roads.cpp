#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <limits>

using namespace std;

struct Edge {
    int to, weight;
};

struct Node{
    int cost, vertex;
    bool operator>(const Node &other) const {
        return cost > other.cost;
    }
};

int shortest_path(int n, vector<vector<int>> &edges, int start, int end, vector<int> &traps){
    vector<vector<Edge>> graph(n);
    unordered_set<int> trapSet(traps.begin(), traps.end());

    for(const auto &edge : edges){
        int u = edge[0], v = edge[1], w = edge[2];
        graph[u].push_back({v, w});
    }

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    vector<int> dist(n, numeric_limits<int>::max());
    dist[start] = 0;
    pq.push({0, start});

    while(!pq.empty()){
        auto[cost, node] = pq.top();
        pq.pop();

        if (node == end) return cost;
        if (cost > dist[node]) continue;
        if (trapSet.count(node)) continue;

        for(const auto &edge : graph[node]){
            int next = edge.to, weight = edge.weight;
            if(!trapSet.count(next) && dist[next] > cost + weight){
                
            }
        }
    }
    return -1;
}

int main(){

}