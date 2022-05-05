#include <iostream>
#include <vector>
using namespace std;

vector<int> nums {1, 2, 8, 5, 3, 9, 6};
int n = 7;
int tree[7];
int lowbit(int x) {
  return x & -x;
}

void init(vector<int>& nums) {
  int n = nums.size();
  // 每个结点值由所有与自己相连的儿子的值求和得到。/
  // 可以每次确定完儿子的值之后，用自己的值更新自己直接父亲的值/
  for(int i = 1; i <= n; ++i) {
    tree[i] += nums[i - 1];
    int j = i + lowbit(i);
    cout << i << " " << j << endl;
    if(j <= n) tree[j] += tree[i];
  }

  for(int i = 0; i < n; i++) {
    cout << tree[i] << " ";
  }
  cout << endl;
}

void add(int k, int val) {
  while(k <= n) {
    tree[k] += val;
    k += lowbit(k);
  }
}

void update(int k, int val) {
  add(k, val - nums[k-1]);
  nums[k] = val;
}

int getSum(int k) {
  int ret = 0;
  while(k) {
    ret += tree[k];
    k -= lowbit(k);
  }
  return ret;
}

int lg(int n) {
  int k = 0;
  while(n != 1) {
    n >>= 1;
    ++k;
  }
  return k;
}

// 查找第 k 小/
int kth(int k) {
  int cnt = 0, ret = 0;
  for(int i = lg(n); ~i; --i) {
    ret += 1 << i;
    if(ret >= n || cnt + tree[ret] >= k) ret -= 1 << i;
    else cnt += tree[ret];
  }
  return ret + 1;
}

int main() {
  // build
  init(nums); 
  cout << " get sum of 3  " << getSum(3) << endl;
  cout << " get sum of 5  " << getSum(5) << endl;
  cout << " get sum of 6  " << getSum(6) << endl;
  cout << " get sum of 7  " << getSum(7) << endl;
  cout << endl;

  add(1, 3);
  cout << " get sum of 3  " << getSum(3) << endl;
  cout << " get sum of 5  " << getSum(5) << endl;
  cout << " get sum of 6  " << getSum(6) << endl;
  cout << " get sum of 7  " << getSum(7) << endl;
  cout << endl;

  // update index of element
  update(4, 7);
  cout << " get sum of 3  " << getSum(3) << endl;
  cout << " get sum of 5  " << getSum(5) << endl;
  cout << " get sum of 6  " << getSum(6) << endl;
  cout << " get sum of 7  " << getSum(7) << endl;
  cout << endl;

  // kth
  cout << " get small kth of 3 is " << kth(2) << endl;

  return 0;
}