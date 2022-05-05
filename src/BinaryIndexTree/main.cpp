#include <iostream>
#include <vector>
using namespace std;


class FenwickTree {
private:
  vector<int> bit;
  int n;
  inline int lowbit(int i) { return i & (-i); };
public:
  FenwickTree(int n): n(n) {
    bit.assign(n+1, 0);
  }

  FenwickTree(vector<int> a): FenwickTree(a.size()) {
    // for(int i = 1; i <= n; i++) {
    //   bit[i] += a[i-1];
    //   int j = i + lowbit(i);
    //   if(j <= n) bit[j] += bit[i];
    // }
    for(size_t i = 1; i <= a.size(); i++) {
      add(i, a[i-1]);
    }
  }

  void add(int i, int val) {
    // cout << " ";
    for(; i <= n; i += lowbit(i)) {
      // cout << i << " ";
      bit[i] += val;
    }
    // cout << endl;
  }

  int sum(int r) {
    int sum  = 0;
    for(; r > 0; r -= lowbit(r)) sum += bit[r];
    return sum;
  }

  int sum(int l, int r) {
    return sum(r) - sum(l);
  }

  void range_add(int l, int r, int val) {
    add(l, val);
    add(r+1, -val);
  }
};

class FenwickTreeMin {
  private:
    int n;
    vector<int> bit;
    const int INF = 0x3f3f;
    inline int lowbit(int x) { return x & (-x); };
  public:
    FenwickTreeMin(int n): n(n) {
      bit.assign(n+1, INF);
    }

    FenwickTreeMin(vector<int> a): FenwickTreeMin(a.size()) {
      for(int i = 1; i <= n; i++) {
        update(i, a[i-1]);
      }
    }

    void update(int i, int val) {
      for(; i <= n; i += lowbit(i)) {
        bit[i] = min(bit[i], val);
      }
    }

    int query(int r) {
      int ret = INF;
      for(; r > 0; r -= lowbit(r)) {
        ret = min(ret, bit[r]);
      }
      return ret;
    }
};

class FenwickTree2D {
  private:
    int m, n;
    vector<vector<int>> bit;
    inline int lowbit(int x) { return x & (-x); };
  public:
    FenwickTree2D(int m, int n): m(m), n(n) {
      bit.assign(n+1, vector<int>(m+1, 0));
    }

    FenwickTree2D(vector<vector<int>> a) {
      n = a.size();
      m = a[0].size();
      bit.assign(n + 1, vector<int>(m + 1, 0));

      for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
          add(i, j, a[i-1][j-1]);
        }
      }
    }

    void add(int x, int y, int val) {
      for(int i = x; i <= n; i += lowbit(i)) {
        for(int j = y; j <= m; j += lowbit(j)) {
          bit[i][j] += val;
        }
      }
    }

    int sum(int x, int y) {
      int ret = 0;
      for(int i = x; i > 0; i -= lowbit(i)) {
        for(int j = y; j > 0; j -= lowbit(j)) {
          ret += bit[i][j];
        }
      }
      return ret;
    }
};

int main() {
  vector<int> nums {12, 2, 8, 5, 3, 9, 6, 10};
  FenwickTree ft(nums);

  cout << "sum of [1, 3] is " << ft.sum(3) << endl;
  cout << "sum of [1, 5] is " << ft.sum(5) << endl;
  cout << "sum of [4, 6] is " << ft.sum(4, 6) << endl;

  cout << "range [1, 3] add 3 " << endl;
  ft.range_add(1, 3, 3);
  cout << "sum of [1, 3] is " << ft.sum(3) << endl;

  FenwickTreeMin ftm(nums);
  cout << "min of [1, 3] is " << ftm.query(3) << endl;

  vector<vector<int>> nums2 {{12, 2, 8, 5, 3, 9, 6, 10}, {12, 2, 8, 5, 3, 9, 6, 10}, {12, 2, 8, 5, 3, 9, 6, 10}};
  FenwickTree2D ft2d(nums2);

  cout << "sum of [3, 5] in 2d arr is " << ft2d.sum(3, 5) << endl;

  return 0;
}