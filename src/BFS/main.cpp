#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;                       // 结点数和边数
vector<vector<int>> adj;        // 邻接表

vector<int> c(n), d(n), p(n);   // color(0为白色，1为灰色，2为黑色)，d属性数组，p属性属性
queue<int> Q;

// 初始化
void init(int s) {
    // 所有节点初始化设置
    c.resize(n + 1, 0);          // 初始所有结点都为白色
    d.resize(n + 1, 0);          // 初始距离都为0
    p.resize(n + 1, -1);         // 初始p属性都设置为NIL，这里使用-1表示

    // 源点s初始化
    c[s] = 1;                    // 设置原点颜色，初始为灰色
    d[s] = 0;                    // 设置源点初始距离为1
    p[s] = -1;                   // 设置源点p属性
}

// bfs过程
void bfs(int s) {
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for(int v : adj[u]) {
            if(c[v] == 0) {
                Q.push(v);
                c[v] = 1;
                d[v] = d[u] + 1;
                p[v] = u;
            }
        }
        c[u] = 2;
    }
}

// 查询是否存在边(u,v)
bool find_edge(int u, int v) {
    for(int i : adj[u]) {
        if(i == v) return true;
    }
    return false;
}

int main() {
    n = 5, m = 14;
    // 图测试数据
    vector<vector<int>> edges = {{1, 2}, {2, 1}, {2, 3}, {3, 2}, {3, 4}, {4, 3}, {4, 5}, {5, 4}, {5, 1}, {1, 5}, {2, 5}, {5,2}, {2, 4}, {4, 2}};
    adj.resize(m);

    // 构图
    adj.resize(n + 1);
    for(int i = 0; i < m; ++i) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u].push_back(v);
    }

    // 找一定在(3,5)最短路径上的边
    vector<int> d3, d5;
   
    int s = 3;
    init(s);
    Q.push(s);                         
    bfs(s);                                      // 已3为源点bfs
    d3.assign(d.begin(), d.end());

    c.clear();
    d.clear();
    p.clear();
    
    s = 5;
    init(s);
    Q.push(s);                         
    bfs(s);                                     // 以5为源点bfs
    d5.assign(d.begin(), d.end());

    vector<vector<int>> paths;
    bool k = find_edge(1, 2);
    for(int u = 1; u <= n; ++u) {
        for(int v = 1; v <= n; ++v) {
            if(find_edge(u, v) && d3[u] + d5[v] + 1 == d3[5]) paths.push_back({u, v});
        }
    }

    return 0;
}
