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
    for(int j = wts[i-1]; j <= capacity; j++) {
      dp[j] = max(dp[j], dp[j-wts[i-1]] + vals[i-1]);
    }
  }
  return dp[capacity];
}

int Ep(char *s, int n, int left, int right) {
  int k = 0;
  while(left >= 0 && right < n) {
    if(s[left] == s[right]) {
      left--; right++;
      k++;
    } else {
      break;
    }
  }
  return k;
}

int Lep(char *s) {
  int n = strlen(s);
  if(n <= 0) return 0;
  
  int max_len = 1;
  for(int i = 0; i < n; i++) {
    int k1 = Ep(s, n, i - 1, i + 1);
    int k2 = Ep(s, n, i, i + 1);
    
    int len1 = k1 * 2 + 1;
    int len2 = k2 * 2;
    int m = max(len1, len2);
    max_len = max(m, max_len);
  }
  return max_len;
}

int LepD(char * s) {
  int n = strlen(s);
  if(n <= 0) return 0;
  // dp[j] 代表以位置为j结尾的最长回文子串的起始位置，ans=j - dp[j]  + 1/
  vector<int> dp(n + 1, 0);
  dp[0] = 0;
  int max_len = 1;
  for(int j = 1; j < n; ++j) {
    if(dp[j-1] > 0 && s[j] == s[dp[j-1] - 1]) {
      dp[j] = dp[j-1] - 1;
    } else {
      int left = dp[j-1], right = j, start = left;
      while(left < right) {
        if(s[left] == s[right]) {
          right = j;
          start = left + 1;
        } else  {
          right--;
        }
        left++;
      }
      dp[j] = start;
    }
    
    int len = j - dp[j] + 1;
    max_len = max(max_len, len);
  }
  return max_len;
}


int LepD2(char* s) {
  int n = strlen(s);
  // dp[i][j] 代表 s[i...j]是否为回文/
  vector<vector<bool>> dp(n, vector<bool>(n, false));
  for(int i = 0; i < n; ++i) dp[i][i] = true;
  int max_len = 0;
  for(int i = n - 1; i >= 0; i--) {
    for(int j = i; j < n; j++) {
      if(s[i] == s[j]) {
        if(j - 1 >= i + 1) if(dp[i+1][j-1]) dp[i][j] = true;
      } else {
        dp[i][j] = true;
      }
      if(dp[i][j]) {
        int len = j - i + 1;
        max_len = max(max_len, len);
      }
    }
  }
  return max_len;
}

// 完全平方数/
int numSqua(int n) {
  vector<int> dp(n + 1, 2e9);
  dp[0] = 0;
  for(int i = 1; i * i <= n; ++i) {
    for (int j = i * i; j <= n; j++) {
      dp[j] = min(dp[j], dp[j- i * i] + 1);
    }
  }
  return dp[n];
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
  
  char* a = "abaabcecbacef";
  cout << "max center " << Lep(a) << endl;
  cout << "max dp1 " << LepD(a) << endl;
  cout << "max dp2 " << LepD2(a) << endl;
  cout << " num squares: " << numSqua(12) << endl;
  return 0;
}
