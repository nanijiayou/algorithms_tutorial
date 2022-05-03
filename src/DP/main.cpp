#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

int w[100], c[100], s[100];
int dp[1100];

/**
test data
5 1000
80 20 4
40 50 9
30 50 7
40 30 6
20 20 1
*/
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
