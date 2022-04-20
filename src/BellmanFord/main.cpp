#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
};

int main() {
    int n = 5; // 顶点【1，2，3，4，5】
    vector<Edge> test = {{1,2,6}, {1,4,7}, {2,3,5}, {3,2,-2}, {4,5,9}, {2,4,8}, {5,3,7}, {4,3,-3}, {2,5,-4},{5,1,2}};
    int s = 1;

    vector<int> dist(n+1, INT_MAX);
    vector<int> prev(n+1, -1);
    dist[s] = 0;
    bool nagtiveCylce;
    for(int i = 1; i < n; ++i) {
        nagtiveCylce = false;
        for(auto e : test) {
            if(dist[e.u] != INT_MAX && dist[e.v] > dist[e.u] + e.w) {
                dist[e.v] = dist[e.u] + e.w;
                prev[e.v] = e.u;
                nagtiveCylce = true;
            }
        }
        if(!nagtiveCylce) break;
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