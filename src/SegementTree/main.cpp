#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int n = 5;
int nums [] = {1, 3, -2, 8, -7};

int t[n << 2];
void build(int k, int tl, int tr){
    if(tr == tl) t[k] = nums[tl];
    else {
        int m = (tl + tr) / 2;
        build(k * 2, tl, m);
        build(k * 2 + 1, m + 1, tr);
        t[k] = t[k * 2] + t[k * 2 + 1];
    }
};

int query(int k, int tl, int tr, int l, int r) {
    if(l > r) return 0;
    if(tl == l && tr == r) return t[k];
    int m = (tl + tr) / 2;
    return query(k * 2, tl, m, l, min(m, r)) + query(k * 2 + 1, m + 1, tr, max(m + 1, l), r);
}

void update(int k, int tl, int tr, int pos, int val) {
    if(tl == tr) t[k] = val; 
    else  {
        int m = (tl + tr) / 2;
        if(pos <= m) update(k * 2, tl, m, pos, val);
        else update(k * 2 + 1, m + 1, tr, pos, val);
    }
    t[k] = t[k*2] + t[k*2 + 1];
}

int main() {
  cout << " " << endl;
  build(1, 0, n - 1);
  cout<< "sum[1..3] " << query(1, 0, n - 1, 0, 3) << endl;
  update(1, 0, n - 1, 2, 5);
  cout<< "sum[1..3] " << query(1, 0, n - 1, 0, 3) << endl;
  return 0;
}
