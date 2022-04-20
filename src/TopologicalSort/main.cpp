#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;       // 结点和边数，用于构图
vector<vector<int>> adj;

vector<int> tpsort;          // 拓扑排序结果
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
    tpsort.push_back(u);
    c[u] = 2;                // 完成时涂为黑色
    f[u] = dfs_timer++;      // 记录完成时间
};

void dfsToplogicSort() {
    tpsort.clear(); 
    for(int i = 1; i <= n; ++i) {
        if(c[i] == 0) {
            dfs(i);
        }
    }
    reverse(tpsort.begin(), tpsort.end());
}

// kahn算法
vector<int> indegree;          // 图所有结点的入度表
vector<int> S;                 // 入度为0的所有元素的集合
vector<int> L;                 // 记录排序结果

bool KahnToplogicSort() {
    for(int i = 1; i <= n; ++i) {    // 统计入度为0的结点，存入集合S
        if(!indegree[i]) S.push_back(i);
    }

    while(!S.empty()) {
        int u = S.back();
        S.pop_back();
        L.push_back(u);
        for(int v : adj[u]) {
            indegree[v] -= 1;
            if(!indegree[v]) S.push_back(v);
        }
    }
    if(L.size() == n) return true;
    else return false;
}

int main() {
    n = 6, m = 6;
    // 图测试数据
    vector<vector<int>> edges = {{1, 2}, {1,4}, {2, 5}, {5, 4}, {3,5}, {3,6}};
    // 带环测试数据
    // vector<vector<int>> edges = {{1, 2}, {1,4}, {4, 2}, {2, 5}, {5, 4}, {3,5}, {3,6}};
    adj.resize(n+1);

    // dfs记录颜色，发现时间，结束时间，前驱
    c.resize(n+1);
    d.resize(n+1);
    f.resize(n+1);
    p.resize(n+1, -1);

    // kahn算法统计每个结点而入度
    indegree.resize(n+1); 

    for(int i = 0; i < edges.size(); ++i) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u].push_back(v);
        indegree[v]++;
    }

    // dfs拓扑排序
    dfsToplogicSort();

    // kahn算法
    bool res = KahnToplogicSort();
    cout << " res=" << res << endl;

    return 0;
}