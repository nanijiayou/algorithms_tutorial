#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> adj;

vector<int> euler, segtree, first, height; // first[k]为结点k在欧拉序列中第一次出现的位置, height[k]为结点深度
vector<int> vis;

// dfs创建欧拉序列，并记录first和height
void dfs(vector<vector<int>> &adj, int u, int h = 0) {
    vis[u] = true;
    height[u] = h;
    first[u] = euler.size();
    euler.push_back(u);
    for(auto v : adj[u]) {
        if(!vis[v]) {
            dfs(adj, v, h+1);
            euler.push_back(u);
        }
    }
}

// 线段树build
void build(int k, int l, int r) {
    if(l == r) segtree[k] = euler[l];
    else {
        int mid = l + ((r - l) >> 1);
        int lc = (k << 1);
        int rc = (k << 1) + 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        segtree[k] = height[segtree[lc]] < height[segtree[rc]] ? segtree[lc] : segtree[rc];
    }
}

// 线段树query
int query(int k, int l, int r, int ql, int qr) {
    if(l > qr || r < ql) return -1;
    if(l >= ql && r <= qr) return segtree[k];
    int mid = l + ((r - l) >> 1);

    int left = query((k << 1), l, mid, ql, qr);
    int right = query((k << 1) + 1, mid + 1, r, ql, qr);

    if(left == -1) return right;
    if(right == -1) return left;

    return height[left] < height[right] ? left : right;
}

int lca(int u, int v) {
    int l = first[u], r = first[v];
    if(l > r) swap(l, r);
    return query(1, 0, euler.size() - 1, l, r);
}

int main() {
    int n = 8;

    // 测试图数据
    vector<vector<int>> test = {{1,2}, {2,5}, {2,6}, {1,3}, {1,4}, {4,7}};
    // 建图
    adj.resize(n);
    for(auto e: test) {
        int u = e[0];
        int v = e[1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    height.resize(n);
    first.resize(n);
    vis.assign(n, false);

    // dfs记录欧拉序列和first，height信息
    dfs(adj, 1);

    // 根据欧拉序列，构建线段树
    int m = euler.size();
    segtree.resize(m * 4);
    build(1, 0, m - 1);

    cout << "lca(6,4)=" << lca(6,4) << endl;
    cout << "lca(5,6)=" << lca(5,6) << endl;

    return 0;
}