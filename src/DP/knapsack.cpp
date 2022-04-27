#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

int n = 4;
vector<int> vals = {1, 6, 10, 16};
vector<int> wts = {1, 2, 3, 5};
// vector<int> vals = {10, 30, 20};
// vector<int> wts = {5, 10, 15};

// dp[i][j] = max(dp[i-1][j], dp[i-1][j-wts[i-1]] + vals[i-1]);
int solveKnapsack(vector<int> &wts, vector<int> &vals, int capacity) {
  vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
  for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= capacity; j++) {
      dp[i][j] = dp[i-1][j];
      if(j >= wts[i-1]) { 
        // 这里只是要保证 j >= wts[i-1]，容错：dp[i-1][j-wts[i-1]]
        dp[i][j] = max(dp[i-1][j], dp[i-1][j-wts[i-1]] + vals[i-1]);
      }
    }
  }
  return dp[n][capacity];
}

// 空间优化
int solveKnapsackOpt(vector<int> &wts, vector<int> &vals, int capacity) {
  vector<int> dp(capacity + 1, 0);
  for(int i = 1; i <= n; i++) {
    for(int j = capacity; j >= wts[i-1]; --j) {
      dp[j] = max(dp[j], dp[j-wts[i-1]] + vals[i-1]);
    }
  }
  return dp[capacity];
}

// 完全背包
int solveUnboundedKnapsack(vector<int> &wts, vector<int> &vals, int capacity) {
  vector<int> dp(capacity + 1, 0);
  for(int i = 1; i <= n; ++i) {
    for(int c = wts[i-1]; c <= capacity; c++) {
      dp[c] = max(dp[c], dp[c-wts[i-1]] + vals[i-1]);
    }
  }
  return dp[capacity];
}

int main() {
  int ans = solveKnapsack(wts, vals, 7);
  cout << " ans of capacity of 7 is: " << ans << endl; 

  int ans2 = solveKnapsack(wts, vals, 6);
  cout << " ans of capacity of 6 is: " << ans2 << endl; 

  int ans3 = solveKnapsackOpt(wts, vals, 6);
  cout << " ans of capacity of 6 is: " << ans3 << endl; 

  int ans4 = solveUnboundedKnapsack(wts, vals, 6);
  cout << " ans of unbounded capacity of 6 is: " << ans4 << endl; 

  return 0;
}
