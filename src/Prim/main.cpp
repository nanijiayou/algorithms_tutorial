#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>

using namespace std;
struct Edge {
    int u, v, w;
    bool operator<(Edge const &other) const {
        return w < other.w;
    }
};

int n;
vector<vector<Edge> > adj;

vector<int> key;
vector<int> parent;
vector<bool> in_mst;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

int main() {
    n = 9;
    vector<Edge> edges = {
        {1,2,4}, {2,1,4}, {2,3,8}, {3,2,8}, {3,4,7}, {4,3,7}, {4,5,9}, {5,4,9}, {5,6,10}, {6,5,10}, {6,7,2}, {7,6,2}, {7,8,1}, {8,7,1}, {8,1,8}, {1,8,8},
        {2,8,11}, {8,2,11}, {8,9,7}, {9,8,7}, {9,7,6}, {7,9,6}, {9,3,2}, {3,9,2}, {3,6,4}, {6,3,4}, {4,6,14}, {6,4,14}
    };
    
    // 建图
    adj.resize(n+1);
    for(auto e : edges) {
        adj[e.u].push_back(e);
    }

    // 方便理解，这里定义集合A,B。也就是切割切除的两个集合
    // 集合A：代表从根开始逐渐生长出最小生成树mst的结点集合
    // 集合B：代表G中还未被加入A的结点，即G.V-A，也就是存储在pq中的结点

    // key[v]存储的是：B中的一个结点v，到A中结点的所有边中权重的最小值
    // 初始所有结点key未INF
    key.resize(n + 1, INT_MAX);

    // p[v]存储的是：上面v结点找到的那条最小权值边的另一个在A中的端点
    // 初始为NIL，用-1表示
    parent.resize(n + 1, -1);

    // 记录结点是否已经放入A中
    in_mst.resize(n + 1, false);

    // 初始，随机选择一个作为mst的根结点
    int r = 1;
    key[r] = 0;

    // 统计mst权重
    int cost = 0;

    // 优先队列pq存储的是B，初始所有结点都在B中
    for(int i = 1; i <= n; ++i) {
        pq.push(make_pair(key[i], i));
    }

    // 随着算法的推进，不断删除B中结点，并添加到A中，直到B为空
    while(!pq.empty()) {
        auto u = pq.top().second;
        pq.pop();

        if(in_mst[u]) continue;
        in_mst[u] = true;

        for(auto e : adj[u]) {
            int v = e.v;
            int w = e.w;
            if(!in_mst[v] && w < key[v]) {
                parent[v] = u;
                key[v] = w;
            }
        }
        cost += key[u];
    }

    for(int i = 1; i <= n; ++i) {
        cout << parent[i] << i << " ";
    }
    cout << endl;

    cout << "cost=" << cost << endl;

    return 0;
}