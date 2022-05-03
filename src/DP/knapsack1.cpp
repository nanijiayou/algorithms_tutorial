#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

int w[35], c[35];
int dp[35][200];
int dp2[200];
int dp3[200];

/**
test data
10 4
2 1
3 3
4 5
7 9
*/
int main() {
  int m,n;
  cin >> m >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> w[i] >> c[i];
  }
  
  cout << "01背包问题：" << endl;
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      if(j < w[i]) dp[i][j] = dp[i-1][j];
      else dp[i][j] = max(dp[i-1][j], dp[i-1][j-w[i]]+c[i]);
    }
  }

  for(int i = 0; i <= n; i++) {
    for(int j = 0; j <= m; j++) {
      cout << dp[i][j] << " ";
    }
    cout << endl;
  }

  cout << "01背包问题一维dp：" << endl;
  for(int i = 1; i <= n; i++) {
    for (int j = m; j >= 1; --j) {
      if(j >= w[i])
        dp2[j] = max(dp2[j], dp2[j-w[i]] + c[i]);
    }
    for(int k = 0; k <= m; k++) {
      cout << dp2[k] << " ";
    }
    cout << endl;
  }

  cout << "完全背包问题：" << endl;
  for(int i = 1; i <= n; i++) {
    for (int j = w[i]; j <= m; j++) {
        dp3[j] = max(dp3[j], dp3[j-w[i]] + c[i]);
    }
    for(int k = 0; k <= m; k++) {
      cout << dp3[k] << " ";
    }
    cout << endl;
  }
  
  return 0;
}
