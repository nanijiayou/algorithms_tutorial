#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
const int MAXN = 100;

struct Edge {
    int to, next, cap, rc;
}edge[MAXN];
int head[MAXN];

int s, t; // 源点与汇点
int cnt = 1;
// 这里有一个小技巧， cnt初值1，第一条边的标号为2（二进制10），第二条是3（二进制11） ，
// 这样做的目的是方便查找反向边：
//  我们加入一条边时，紧接着加入它的反向边
//  这两条边的标号就是二进制最后一位不相同，一个0、一个1
//  所以要查找 p 这条边的反向边时，只需用 p ^ 1，如果cnt初值为0，这样做就不行
void add_edge(int u, int v, int w) {
    cnt++;
    edge[cnt].to = v;
    edge[cnt].cap = w;
    edge[cnt].rc = w;
    edge[cnt].next = head[u];
    head[u] = cnt;
}

// dfs记录vis
bool vis[MAXN];

// dfs寻找增广路径，c为当前结点，t为汇点，m为路径上最小残存容量
int dfs(int c, int t, int m) {
    if(c == t) return m;
    vis[c] = true;

    for(int u = head[c]; u; u = edge[u].next) {
        auto &e = edge[u]; int v = e.to;
        if(e.rc == 0 || vis[v]) continue;
        int mrc = dfs(v, t, min(m, e.rc));
        if(mrc > 0) {
            e.rc -= mrc;                    // 减少边的残存容量
            edge[u ^ 1].rc += mrc;          // 反向边容量相应增加
            return mrc;
        }
    }
    return 0;
}

int FordFulkerson() {
    int max_flow = 0;

    while (true) {
        memset(vis, 0, sizeof(vis));
        int df = dfs(s, t, 10000);          // 查找增广路径，并计算路径上流量的增量
        if(df == 0) break; 
        max_flow += df;                     // 叠加增量 
    }
    return max_flow;
}


int main() {
    // 测试图，{from, to, cap}
    vector<vector<int>> test = {{0,1,16}, {1,2,12}, {2,5,20}, {3,1,4}, {4,2,7}, {2,3,9}, {0,3,13}, {3,4,14}, {4,5,4}};

    // 构建残存图，反向边容量初始值为0
    for(int i = 0; i < test.size(); ++i) {
        int from = test[i][0], to = test[i][1], w = test[i][2];
        add_edge(from, to, w);
        add_edge(to, from, 0);
    }

    s = 0, t = 5;
    int max_flow = FordFulkerson();
    cout << "max flow = " << max_flow << endl;
    return 0;
}
