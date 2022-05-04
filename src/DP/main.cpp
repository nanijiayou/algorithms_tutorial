#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

/**
问题：https://www.acwing.com/problem/content/5/
有 N 种物品和一个容量是 V 的背包。
第 i 种物品最多有 si 件，每件体积是 vi，价值是 wi。
求解将哪些物品装入背包，可使物品体积总和不超过背包容量，且价值总和最大。
输出最大价值。
测试数据:
 4 5
 1 2 3
 2 4 1
 3 4 3
 4 5 2
输出：10
*/

// w价值，v体积，s物品数量
int w[100], v[100], s[100];
int dp[1100];

/**
 // 朴素的算法
 int main() {
   int m, n;
   cin >> n >> m;
   for(int i = 1; i <= n; ++i) cin >> w[i] >> c[i] >> s[i];
  
   for(int i = 1; i <= n; i++) {
     for(int j = m; j >= 1; j--) {
       for(int k = 0; k <= s[i] && j >= k*w[i]; ++k) {
         dp[j] = max(dp[j], dp[j - k * w[i]] + k * c[i]);
       }
     }
    
     for(int k = 0; k <= m; k++) {
       cout << dp[k] << " ";
     }
     cout << endl;
   }
   return 0;
 }
*/

int main() {
  int n, m;
  cin >> n >> m;
  int cnt = 0;
  for(int i = 1; i <= n; ++i) {
    int a,b,c; // 体积，价值，数量
    cin >> a >> b >> c;
    for(int k = 1; k <= c; k *= 2) {
      cnt++;
      c -= k;
      w[cnt] = b * k; // 整体价值
      v[cnt] = a * k; // 整体体积
    }
    if(c > 0) {
      cnt++;
      w[cnt] = b * c;
      v[cnt] = a * c;
    }
  }
  
  for(int i = 0; i < cnt; i++) {
    cout << w[i] << " ";
  }
  cout << endl;
  
  for(int i = 0; i < cnt; i++) {
    cout << v[i] << " ";
  }
  cout << endl;
  
  n = cnt;
  
  for(int i = 1; i <= n; i++) {
    for(int j = m; j >= v[i]; j--) {
      dp[j] = max(dp[j], dp[j-v[i]] + w[i]);
    }
  }
  
  cout << dp[m] << endl;
  return 0;
}
