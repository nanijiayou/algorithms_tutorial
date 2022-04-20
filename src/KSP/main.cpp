#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAXN 50

// 链式前向星存图
struct Edge {
    int to, next, w;
} edges[MAXN];
int head[MAXN];
int cnt_e;
void add_edge(int u, int v, int w) {
    edges[++cnt_e].to = v;
    edges[cnt_e].w = w;
    edges[cnt_e].next = head[u];
    head[u] = cnt_e;
}

vector<int> dist;
vector<bool> vis;
vector<int> cnt_n;      // 路径上结点数量，用于判断负环路
queue<int> q;
// SPFA算法
bool SPFA(int s, int n) {
    dist.resize(n+1, INT_MAX);
    vis.resize(n+1, false);
    cnt_n.resize(n+1, 0);

    dist[s] = 0, vis[s] = true;
    q.push(s);
    while(!q.empty()) {
        int u = q.front();
        q.pop(), vis[u] = false;
        for(int j = head[u]; j; j = edges[j].next) {
            int v = edges[j].to, w = edges[j].w;
            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                cnt_n[v] = cnt_n[u] + 1;
                if(cnt_n[v] >= n) return false;
                if(!vis[u]) q.push(v), vis[v] = true;
            }
        }
    }
    return true;
}

int main() {
    int n = 5;                      //  结点数
    vector<vector<int>> test = {{1,2,0}, {1,5,-1}, {4,1,4}, {3,1,5}, {4,3,-1}, {2,5,1}, {5,3,-3}, {5,4,-3}};
    for(auto e : test) {
        add_edge(e[1],e[0],e[2]);   // 这里约束条件构成的图G需要转置才是约束图
    }

    int s = 0;                      // 添加s结点(文中的v0结点），s到有到各个顶点的边，权重为0
    for(int i = 1; i <= n; ++i) {
        add_edge(s, i, 0);
    }
    // 检查负换，打印可行解
    cout << " check no nagtive cylce " << SPFA(s, n) << endl;
    for(auto k : dist) {
        cout << k << " ";
    }
    cout << endl;

    return 0;
}