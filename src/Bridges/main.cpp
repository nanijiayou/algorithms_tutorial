#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int n;
vector<vector<int>> adj;
vector<bool> vis;

int timer;
vector<int> low;
vector<int> tin;
vector<vector<int>> bs;
void dfs(int u, int p = -1) {
    vis[u] = true;
    low[u] = tin[u] = ++timer;
    for(auto v : adj[u]) {
        if(v == p) continue;
        if(vis[v]) low[u] = min(low[u], tin[v]);
        else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] > tin[u]) bs.push_back({u, v});
        }
    }
}

void find_bridges() {
    timer = 0;
    low.assign(n+1, -1);
    tin.assign(n+1, -1);
    vis.assign(n+1, false);
    for(int i = 1; i <= n; ++i) {
        if(!vis[i]) dfs(i);
    }
}

int main() {
    n = 8;
    vector<vector<int>> edges = {{1,6}, {1,7}, {1,2}, {6,1}, {7,1}, {2,1}, {6,7}, {7,6}, {2,3}, {3,5}, {5,3}, {3,2}, {3,4}, {5,4}, {4,3},{4,5}};
    vis.assign(n + 1, false);
    adj.resize(n + 1);

    for(int i = 0; i < edges.size(); ++i) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u].push_back(v);
    }

    find_bridges();

    return 0;
}
