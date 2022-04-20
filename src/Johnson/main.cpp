#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, w;
};
vector<Edge> edges;
vector<vector<Edge>> adj;
vector<int> dist;

// Bellman-Ford子过程
bool BellmanFord(vector<Edge> &edges, int n, int s) {
    dist.resize(n+1, INT_MAX);
    dist[s] = 0;
    bool negtiveCycle;
    for(int i = 1; i <= n; ++i) {
        negtiveCycle = false;
        for(auto e: edges) {
            if(dist[e.u] < INT_MAX && dist[e.v] > dist[e.u] + e.w) {
                dist[e.v] = dist[e.u] + e.w;
                negtiveCycle = true;
            }
        }
        if(!negtiveCycle) break;
    }
    return negtiveCycle;
}

// Dijkstra子过程
vector<int> Dijkstra(int n, int s) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(n+1, INT_MAX);
    vector<bool> vis(n+1, false);

    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto node = pq.top();
        pq.pop();
        int u = node.second;
        if(vis[u]) continue;
        vis[u] = true;
        for(auto e : adj[u]) {
            int v = e.v, w = e.w;
            if(dist[u] < INT_MAX && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main() {
    int n = 5;
    edges = {{1,2,3}, {3,2,4}, {1,3,8}, {2,4,1}, {2,5,7}, {1,5,-4}, {4,1,2}, {5,4,6}, {4,3,-5}};

    // 构建新图 G'，新增结点 s，并将设置到各结点的权重为0，即： w(s,v)=0 v in G.V
    int s = 0;
    vector<Edge> edges_new = edges;
    for(int v = 1; v <= n; ++v) {
        edges_new.push_back({s, v, 0});
    }
    // 执行 BellmanFord算法，计算s的单源最短路径
    bool hasCycle = BellmanFord(edges_new, n, s);
    if(hasCycle) cout << "the input graph contains a negative-weight cycle" << endl;

    // 重新赋予权重 w'(u,v) = w(u,v) + h(u) - h(v)
    for(auto &e : edges_new) {
        e.w = e.w + dist[e.u] - dist[e.v];
    }

    // 构建新图G'的邻接表，Dijkstra算法需要使用到
    adj.resize(n+1);
    for(auto const e : edges_new) {
        adj[e.u].push_back(e);
    }

    // 在新图上以每个顶点为源点，执行Dijkstra算法，计算单源最短路径
    vector<vector<int>> dist_all(n+1, vector<int>(n+1, 0));
    for(int i = 1; i <= n; ++i) {
       auto d = Dijkstra(n, i);
       for(int j = 1; j <= n; ++j) {
           if(d[j] == INT_MAX) continue;
           dist_all[i][j] = d[j] + dist[j] - dist[i]; // 恢复权值
       }
    }

    cout << " has nagetive cycle" << hasCycle << endl;

    return 0;
}