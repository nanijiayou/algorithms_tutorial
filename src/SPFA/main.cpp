#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Edge {
    int u, v, w;
};

int main() {
    int n = 5; // 顶点【1，2，3，4，5】
    vector<Edge> test = {{1,2,6}, {1,4,7}, {2,3,5}, {3,2,-2}, {4,5,9}, {2,4,8}, {5,3,7}, {4,3,-3}, {2,5,-4},{5,1,2}};
    vector<vector<Edge>> adj(n+1);

		// 建图
    for(auto e : test) {
        adj[e.u].push_back(e);
    }

    int s = 1;                       // 源点s
    bool nagtiveCylce;               // 负环flag
    queue<int> q;                    // 可能会引起松弛操作的结点的集合
    vector<int> dist(n+1, INT_MAX);  // 最短路径
    vector<int> prev(n+1, -1);       // 前驱结点
    vector<bool> vis(n+1, false);    // 是否访问过
    vector<int> cnt(n+1, 0);         // 源点到该结点的边数，小于n，否则说明有负环

		// 初始状态
    dist[s] = 0;
    vis[s] = true;
    q.push(s);

    while(!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for(auto e : adj[u]) {
            int v = e.v, w = e.w;
            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                cnt[v] = cnt[u] + 1;
                if(cnt[v] >= n) {
                    nagtiveCylce = true;
                    break;
                }
								if(vis[v]) continue;
                q.push(v);
                vis[v] = false;
            }
        }
    }

    cout << " has nagative cylces: " << nagtiveCylce << endl;
    int t = 5;
    cout << dist[t] << endl;
    vector<int> path;
    for (int cur = t; cur != -1; cur = prev[cur])
        path.push_back(cur);

    std::reverse(path.begin(), path.end());
    return 0;
}