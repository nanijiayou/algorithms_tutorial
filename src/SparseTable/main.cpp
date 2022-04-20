/*
 * @Author: hzheyuan
 * @Date: 2022-02-14 15:48:13
 * @LastEditTime: 2022-02-14 16:47:01
 * @LastEditors: hzheyuan
 * @Description: 
 * @FilePath: \SparseTable\spfa.cpp
 */
#include <iostream>
#define MAXN 2000001
#define LOGN 25
using namespace std;

int Log2[MAXN], st[MAXN][LOGN];

void comLog2() {
    Log2[1] = 0;
    for(int i = 2; i <= MAXN; ++i) {
        Log2[i] = Log2[i/2] + 1;
    }
}

int main() {
    int test[] = {0,5,2,5,4,3,1,6,3}; 
    int n = 9;

    comLog2();

    for(int i = 0; i < n; i++)
        st[i][0] = test[i];

    for(int j = 1; j <= LOGN; ++j) {
        for(int i = 0; i + (1 << j) <= 9; i++) {
            st[i][j] = max(st[i][j-1], st[i + (1 << (j-1))][j-1]);
        }
    }

    int l = 4, r = 6;
    int j = Log2[r - l + 1];
    int ans = max(st[l][j], st[r - (1 << j) + 1][j]);

    cout << "max= " << ans << endl;

    return 0;
}