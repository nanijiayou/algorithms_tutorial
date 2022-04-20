#include <iostream>
#include <vector>

using namespace std;

int n;
vector<bool> vis;
vector<vector<int>> adj;                   // 原图
vector<vector<int>> adj_rev;               // 原图的转置图GT

vector<int> order;                         // 记录排序结果，原图进行dfs得到的完成时间的反序
vector<vector<int>> components;            // 记录所有联通分量 
vector<int> component;                     // 记录当前正在dfs的联通分量

void dfs1(int u) {                         // 第一次dfs，用于记录完成时间
    vis[u] = true;
    for(int v : adj[u]) {
        if(!vis[v]) dfs1(v);
    }
    order.push_back(u);
}

void dfs2(int u) {                         // 第二次dfs，在GT上执行。
    vis[u] = true;
    component.push_back(u);
    for(int v : adj_rev[u]) {
        if(!vis[v]) dfs2(v);
    }
}

int main() {
    int n = 8;

    vector<vector<int>> edges = {{1,2}, {5,1}, {2,3}, {2,5}, {2,6}, {5,6}, {6,7}, {7,6}, {3,4}, {4,3}, {3,7}, {4,8}, {7,8}, {8,8}};
    vis.assign(n + 1, false);
    adj.resize(n + 1);
    adj_rev.resize(n + 1);

    for(int i = 0; i < edges.size(); ++i) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u].push_back(v);                   // 原图邻接表
        adj_rev[v].push_back(u);               // 转置图邻接表
    }

    for(int i = 1; i <= n; ++i) {
        if(!vis[i]) dfs1(i);
    }

    vis.assign(n + 1, false);                  
    reverse(order.begin(), order.end());       // 将记录的完成时间反序，也就是拓扑排序 

    for(int u : order) {                       // 按照上面记录的排序，在GT上进行第二次DFS
        if(!vis[u]) {
            dfs2(u);
            components.push_back(component);   // 将当前记录的分量加入结果
            component.clear();
        }
    }
    
    return 0;
}