#include <iostream>
#include <vector>
using namespace std;

#define N 5
int dist[N][N];     // 最短路径矩阵
int p[N][N];        // 前驱矩阵

void FloydWarshall(int graph[][N]) {
    for (int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            dist[i][j] = graph[i][j];
            if(i != j && dist[i][j] < INT_MAX) p[i][j] = i;
            else p[i][j] = -1;
        }
    } 
    for (int k = 0; k < N; ++k) {
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                if(dist[i][k] == INT_MAX || dist[k][j] == INT_MAX) continue;
                if(dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    p[i][j] = p[k][j];
                }
            }
        }
    }
}

void print_path (int i, int j) {
    if (i != j) print_path(i, p[i][j]);
    cout << j << " ";
}

void printMatrix(int matrix[][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (matrix[i][j] == INT_MAX) cout << "INF ";
      else cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
}

int main() {
    int graph[N][N] = {
        {0, 3, 8, INT_MAX, -4},
        {INT_MAX, 0, INT_MAX, 1, 7},
        {INT_MAX, 4, 0, INT_MAX, INT_MAX},
        {2, INT_MAX, -5, 0, INT_MAX},
        {INT_MAX, INT_MAX, INT_MAX, 6, 0},
    };
    FloydWarshall(graph);
    printMatrix(dist);
    print_path(0, 1);
    cout << endl;
    return 0;
}