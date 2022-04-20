#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> parent, rk;
void make_set(int u) {
    parent[u] = u;
    rk[u] = 0;
}

int find_set(int u) {
    if(u == parent[u]) return u;
    return parent[u] = find_set(parent[u]);
}

void union_sets(int u, int v) {
    u = find_set(u);
    v = find_set(v);
    if(u != v) {
        if(rk[u] < rk[v]) swap(u, v);
        parent[v] = u;
        if(rk[u] == rk[v]) rk[u]++;
    }
}

struct Edge {
    int u, v, w;
    bool operator<(Edge const& other) const {
        return w < other.w;
    }    
};


int main() {
    int n = 9;
    parent.resize(n + 1);
    rk.resize(n + 1);
    vector<Edge> edges = {
        {1,2,4}, {2,1,4}, {2,3,8}, {3,2,8}, {3,4,7}, {4,3,7}, {4,5,9}, {5,4,9}, {5,6,10}, {6,5,10}, {6,7,2}, {7,6,2}, {7,8,1}, {8,7,1}, {8,1,8}, {1,8,8},
        {2,8,11}, {8,2,11}, {8,9,7}, {9,8,7}, {9,7,6}, {7,9,6}, {9,3,2}, {3,9,2}, {3,6,4}, {6,3,4}, {4,6,14}, {6,4,14}
    };

    vector<Edge> mst;
    int cost = 0;

    for(int i = 0; i <= 10; ++i)
        make_set(i);

    sort(edges.begin(), edges.end());

    for(int i = 0; i < edges.size(); ++i) {
        int u = edges[i].u;
        int v = edges[i].v;
        if(find_set(u) != find_set(v)) {
            cost += edges[i].w;
            mst.push_back(edges[i]);
            union_sets(u, v);
        }
    }
    cout << "cost=" << cost << endl;

    return 0;
}