#include <iostream>
#include <vector>

using namespace std;

const int maxn = 100;
int n, m, cnt; // 那个结点，m条边
struct Edge
{
    int to, w, next;
}edge[maxn];

int head[maxn];

void add_edge(int u, int v, int w) {
    edge[cnt].to = v;
    edge[cnt].w = w;
    edge->next = head[u];
    head[u] = cnt++;
}

int main() {
    for(int i = 0; i <= n; ++i)
        head[i] = -1;

    vector<vector<int>> test = {{1,2,1}, {2,3,2},{3,4,3},{1,3,4},{4,1,5},{1,5,6},{4,5,7}};
    for(int i = 0; i < test.size(); ++i) {
        add_edge(test[i][0], test[i][1], test[i][2]);
    }
    
    return 0;
}