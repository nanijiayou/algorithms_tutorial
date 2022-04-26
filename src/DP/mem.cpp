/*
 * @Author: kalai
 * @LastEditors: kalai
 * @Description:
 * @FilePath: \algorithms_tutorial\src\DP\mem.cpp
 */

// 山洞里有M株不同的草药，采每一株都需要一些时间t_i，每一株也有它自身的价值W_i。给你一段时间T，在这段时间里，你可以采到一些草药。让采到的草药的总价值最大。/
#include <iostream>
#include <cstring>

using namespace std;
const int INF = 2e9;
int n, t;
int tcost[103], mget[103];
int mem[103][1003];
int ans = 0;

/** dfs */
void dfs(int pos, int tleft, int trans) {
  if (tleft < 0) return;
  if (pos == n + 1) {
    ans = max(ans, trans);
    return;
  }
  dfs(pos + 1, tleft, trans);
  dfs(pos + 1, tleft - tcost[pos], trans + mget[pos]);
}

/** dfs with mem */
int dfs_mem(int pos, int tleft) {
  if(mem[pos][tleft] != -1) return mem[pos][tleft];
  if(pos = n+1) return mem[pos][tleft] = 0;
  int val1, val2 = -INF;
  val1 = dfs_mem(pos + 1, tleft);
  if(tleft >= tcost[pos])
    val2 = dfs_mem(pos + 1, tleft - tcost[pos]) + mget[pos];
  mem[pos][tleft] = max(val1, val2);
  return mem[pos][tleft];
}

/** dp */
int dp[103][1003];
int getMaxVal() {
  for(int i = 1; i < n; ++i) {
    for(int j = 0; j < t; ++j) {
      dp[i][j] = dp[i-1][j];
      if(j >= tcost[i]) {
        dp[i][j] = max(dp[i][j], dp[i-1][j-tcost[i]] + mget[i]);
      }
    }
  }
  return dp[n][t];
}

int main() {
  memset(mem, -1, sizeof(mem));
  cin >> n >> t;
  for (int i = 1; i < n; ++i) cin >> tcost[i] >> mget[i];
  dfs(1, t, 0);
  int ans = dfs_mem(1, t);
  cout << ans << endl;
  return 0;
}