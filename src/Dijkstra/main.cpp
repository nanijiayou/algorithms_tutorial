#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
};
vector<vector<Edge>> adj;

int main() {
    int n = 5;
    // 测试图数据，和文中示意Dijsktra算法流程的图一致
    vector<Edge> test = {{1,2,10}, {1,4,5}, {2,3,1}, {4,5,2}, {2,4,2}, {4,2,3}, {3,5,4}, {5,3,6}, {4,3,9},{5,1,7}};
    adj.resize(n+1);
    for(auto e : test) {
        adj[e.u].push_back(e);
    };

    // Dijkstra算法部分
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(n+1, INT_MAX);
    vector<int> prev(n+1, -1);
    vector<bool> vis(n+1, false);

    int s = 1;
    dist[s] = 0;
    pq.push({0, s});
    while(!pq.empty()) {
        auto node = pq.top();
        pq.pop();
        int u = node.second;
        if(vis[u]) continue;
        vis[u] = true;
        for(auto e : adj[u]) {
            int v = e.v, w = e.w;
            if(dist[u] != INT_MAX && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    // 测试
    int t = 5;
    cout << dist[t] << endl;
    vector<int> path;
    for (int cur = t; cur != -1; cur = prev[cur])
        path.push_back(cur);
    std::reverse(path.begin(), path.end());

    return 0;
}