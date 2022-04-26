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

vector<int> a = {2, 4, 3, 3, 1, 5, 6, 7};
vector<int> c = {7, 7, 7, 7, 7, 7, 7, 7};

int n = a.size();
int mem[8];

// LIS(Longest Increasing Subsequence) promble
// 最长上升（递增）子序列问题

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
int LIS(vector<int> a) {
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


/** 最长上升子序列 二分优化 */
int LISBIN(vector<int> a) {
  // dp[i]表示长度为i的最长上升子序列的末尾的最小值
  vector<int> dp;
  for(auto n : a) {
    auto iter = lower_bound(dp.begin(), dp.end(), n);
    if(iter != dp.end()) *iter = n;
    else dp.push_back(n);
  }
  return dp.size();
}

// 最长严格递增子序列
// dp[k]表示长度为k的不下降子序列末尾元素的最小值/
int LIS3(vector<int> a) {
  vector<int> dp;
  for(auto n : a) {
    auto iter = upper_bound(dp.begin(), dp.end(), n);
    if(iter != dp.end()) *iter = n;
    else dp.push_back(n);
  }
  return dp.size();
}

// LCS Longest Common Subsequence
string str1 = "abcde", str2 = "ace";
int LCS(string &a, string &b) {
  int len1 = a.size(), len2 = b.size();
  vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
  // dp[i][j]代表a的前i位，b的前j位的LCS长度
  // 这里i,j从1开始，而字符串中的位置则是i-1
  for (int i = 1; i <= len1; ++i) {
    for (int j = 1; j <= len2; ++j) {
      if (a[i-1] == a[j-1])
        dp[i][j] = dp[i - 1][j - 1] + 1;
      else
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    }
  }
  return dp[len1][len2];
}

int main() {
  memset(mem, -1, sizeof(mem));
  cout << "LIS 记忆化搜索: " << dfs(n-1) << endl;
  cout << "LIS dp: " << LIS(a) << endl;
  cout << "LIS 二分优化: " << LISBIN(a) << endl;
  cout << "LIS 二分优化: " << LISBIN(c) << endl;
  cout << "LIS 不下降最长子序列: " << LIS3(a) << endl;
  cout << "LCS 最长公共子序列: " << LCS(str1, str2) << endl;
  return 0;
}
