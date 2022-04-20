#include <iostream>
#include <vector>

#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<bool> visited;
vector<vector<int>> adj;

// 查询是否有u到v的边
bool find_edge(int u, int v) {
    for (int i = 0; i < adj[u].size(); ++i) {
        if(adj[u][i] == v) return true;
    }
    return false;
}

void dfs(int u) {
    if(visited[u]) return;
    visited[u] = true;
    cout << "u=" << u << endl;
    for(int i = 0; i < adj[u].size(); ++i) dfs(adj[u][i]);
}

// 邻接矩阵
int main() {
    n = 5;
    m = 7;

    vector<vector<int>> edges = {{1, 2}, {2, 1}, {2, 3}, {3, 2}, {3, 4}, {4, 3}, {4, 5}, {5, 4}, {5, 1}, {1, 5}, {2, 5}, {5,2}, {2, 4}, {4, 2}};

    visited.resize(n + 1, false);
    adj.resize(n + 1);

    for(int i = 0; i < edges.size(); ++i) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u].push_back(v);
    }

    dfs(1);

    cout << find_edge(4, 3) << endl;
    cout << find_edge(1, 3) << endl;

    return 0;
}
