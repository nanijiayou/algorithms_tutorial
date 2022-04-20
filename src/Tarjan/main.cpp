#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int n;
vector<vector<int>> adj;
vector<bool> vis;

int timer;                                      // 全局时间
vector<int> d, dsu;                             // 发现时间, d[u]为u结点发现时间
                                                // dsu[u]为以u为根结点的子树的发现时间， 既: min{u.d} u 属于 E
stack<int> stk;                                 // 将以结点u为根的强连通分量，存入此栈中
vector<bool> in_stk;                            // 判断是否已经在栈中，如果已经在栈中，则说明是后向边

int sccidx;                                     // 强连通分量的编号
vector<int> scc, sccmp;                         // 记录强连通分量信息，
                                                // scc为每个结点的强连通分量的编号，sccmp记录每个强连通分量的结点数量

void targan(int u) {
    d[u] = dsu[u] = ++timer;                    // 记录发现时间
    in_stk[u] = true;                           // 记录u是否已被记录
    stk.push(u);                                // 记录u结点           
    for(auto v : adj[u]) {
        if(!d[v]) {                             // 如果还没有被发现过
            targan(v);                          // 递归调用
            dsu[u] = min(dsu[v], dsu[u]);       // 回溯到u，dsu[u]为所有与u相连的发现时间的最小值
        } else if(in_stk[v]) {                  // 如果已经访问过，则是一条后向边
            dsu[u] = min(dsu[u], d[v]);         // 此时，比较v结点的发现时间d[v]和dsu[u]，取更小
        }
    }

    int v = 0;
    if(d[u] == dsu[u]) {                       // 如果u的发现时间和以u为根的子树的发现时间相同，则为次子树在同一个强连通分量
        ++sccidx;                              // 发现一个强连通分量，将将其标号
        while (stk.top() != u) {               // 栈中u之后的结点都属于同一强连通分量
            v = stk.top();                     // 将栈中结点弹出并标记相同的强连通分量标号
            stk.pop();
            scc[v] = sccidx;    
            sccmp[sccidx]++;
            in_stk[v] = false;
        }
        v = stk.top();
        stk.pop();
        scc[v] = sccidx;    
        sccmp[sccidx]++;
        in_stk[v] = false;       
    }
}

vector<int> low;
vector<int> tin;
vector<vector<int>> bs;
void fb(int u, int p = -1) {
    vis[u] = true;
    low[u] = tin[u] = ++timer;
    for(int v : adj[u]) {
        if(v == p) continue;
        if(vis[v]) low[u] = min(low[u], tin[v]);
        else {
            fb(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] > tin[u]) {
                cout << u << v << endl;
                bs.emplace_back(u, v);
            }
        }
    }
}

int main() {
    n = 8;
    
    vector<vector<int>> edges = {{1,2}, {5,1}, {2,3}, {2,5}, {2,6}, {5,6}, {6,7}, {7,6}, {3,4}, {4,3}, {3,7}, {4,8}, {7,8}, {8,8}};
    vis.assign(n + 1, false);
    adj.resize(n + 1);

    in_stk.assign(n+1, false);
    d.assign(n + 1, 0);
    dsu.assign(n + 1, 0);
    scc.resize(n + 1, 0);
    sccmp.resize(n + 1, 0);

    for(int i = 0; i < edges.size(); ++i) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u].push_back(v);
    }

    for(int i = 1; i <= n; ++i) {
        if(!d[i]) targan(i);
    }

    vector<vector<int>> sccres;
    for(int i = 1; i <= n; ++i) {
        vector<int> sc;
        if(sccmp[i]) {
            for(int j = 1; j <= n && sc.size() < sccmp[i]; ++j) {
                if(scc[j] == i) sc.push_back(j);
            }
            sccres.push_back(sc);
        }
    }

    timer = 0;
    low.assign(n+1, -1);
    tin.assign(n+1, -1);
    vis.assign(n+1, false);
    for(int i = 1; i <= n; ++i) {
        if(!vis[i]) fb(i);   
    }

    return 0;
}