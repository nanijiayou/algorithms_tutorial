#include <iostream>
#include <vector>
using namespace std;

int n, m;       // 结点和边数，用于构图
vector<vector<int>> adj;

int dfs_timer = 1;           // 全局计时器
vector<int> c,               // c记录颜色， 0为白色，1为灰色，2为黑色
            d,               // 记录发现时间
            f,               // 记录完成时间
            p;               // 记录前驱

void dfs(int u) {
    d[u] = dfs_timer++;      // 记录发现时间
    c[u] = 1;                // 发现时涂为灰色
    for(int v : adj[u]) {    // 搜索邻接表
        if(c[v] == 0) {      // 如果颜色是白色（也就是没有被发现过的结点）
            p[v] = u;        // 设置前驱属性
            dfs(v);          // 递归搜索
        } 
    }
    c[u] = 2;                // 完成时涂为黑色
    f[u] = dfs_timer++;      // 记录完成时间
};

int main() {
    n = 6, m = 8;
    // 图测试数据
    vector<vector<int>> edges = {{1, 2}, {1,4}, {2, 5}, {4,2}, {5, 4}, {3,5}, {3,6}, {6, 6}};
    adj.resize(n+1);
    c.resize(n+1);
    d.resize(n+1);
    f.resize(n+1);
    p.resize(n+1, -1);

    for(int i = 0; i < edges.size(); ++i) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u].push_back(v);
    }

    for(int i = 1; i <= n; ++i) {
        if(c[i] == 0) {
            dfs(i);
        }
    }

    return 0;
}