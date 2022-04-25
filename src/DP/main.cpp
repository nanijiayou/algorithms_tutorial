/*
 * @Author: kalai
 * @LastEditors: kalai
 * @Description:
 * @FilePath: \algorithms_tutorial\src\DP\main.cpp
 */
#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

vector<int> a = {2, 4, 3, 1, 5, 6, 7};
vector<int> b = {2, 4, 6, 7, 3, 7, 5};
int n = a.size();
int mem[7];

// LIS(Longest Increasing Subsequence) promble

/** solution1: 记忆话化搜索 */
int dfs(int i) {
  if (mem[i] != -1) return mem[i];
  int ret = 1;
  for (int j = 0; j < i; ++j) {
    if (a[j] < a[i]) ret = max(ret, dfs(j) + 1);
  }
  mem[i] = ret;
  return mem[i];
}

/** solution2: dp */
// f(i)为以第i个元素为结尾的最长上升子序列长度
// O(n^2)
// dp_i = max{dp_j + 1} (1 <= j < i and a_j < a_i);/
int LIS(vector<int> &a) {
  int n = a.size();
  int ans = 1;
  vector<int> f(n + 1, 1);
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      if (a[i] > a[j]) {
        f[i] = max(f[i], f[j] + 1);
        ans = max(ans, f[i]);
      }
    }
  }
  return ans;
};

// int LIS2(vector<int> &a) {
//   int n = a.size();
//   vector<int> f(n + 1, INT_MAX);
//   f[1] = a[0];
//   int len = 1;
//   for (int i = 2; i <= n; ++i) {
//     int l = 0, r = n, mid;
//     if (a[i] > f[len]) f[++len] = a[i];
//     else {
//       while (l < r) {
//         mid = (l + r) / 2;
//         if (f[mid] > a[i])
//           r = mid;
//         else
//           l = mid + 1;
//       };
//     };
//     f[l] = min(a[i], f[l]);
//   };
//   return len;
// };

/** solution2: dp optimal */
// dp[k]表示长度为k的不下降子序列末尾元素的最小值/
int LIS3(vector<int> &a) {
  int n = a.size();
  vector<int> dp(n, INT_MAX);
  for (int i = 0; i < n; ++i) {
    auto iter = upper_bound(dp.begin(), dp.end(), a[i]);
    *iter = a[i];
  }
  int ans = 0;
  while (dp[ans] != INT_MAX) ++ans;
  return ans;
}

// LCS Longest Common Subsequence
int LCS(vector<int> &a, vector<int> &b) {
  int len1 = a.size(), len2 = b.size();
  vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
  // dp[i][j]代表a的前i位，b的前j位的LCS长度
  for (int i = 1; i < len1; ++i) {
    for (int j = 1; j < i; ++j) {
      if (a[i] == a[j])
        dp[i][j] = dp[i - 1][j - 1] + 1;
      else
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    }
  }
  return dp[len1][len2];
}

int main() {
  memset(mem, -1, sizeof(mem));
  int res1 = dfs(n-1);
  cout << "LIS dfs " << res1 << endl;

  int res2 = LIS(a);
  cout << "LIS 1 " << res2 << endl;

  int res3 = LIS3(a);
  cout << "LIS 2 " << res3 << endl;

  int lcs = LCS(a, b);
  cout << "LCS " << res1 << endl;
  return 0;
}
