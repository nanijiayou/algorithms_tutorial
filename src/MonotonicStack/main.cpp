/*
 * @Author: kalai
 * @LastEditors: kalai
 * @Description: 
 * @FilePath: \algorithms_tutorial\src\MonotonicStack\main.cpp
 */

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> test = {1, 4, 2, 3, 6, 5};
vector<int> res(6);
/**
 * 给出项数为 n 的整数数列 a[1…n]
 * 定义函数 f(i) 代表数列中第 i 个元素之后第一个大于 a[i] 的元素的下标，即 f(i)=\min_{i<j\leq n, a_j > a_i} \{j\}f(i)=min i<j≤n,a j > a i{j}。
 * 若不存在，则 f(i) = 0。 试求出 f(1…n)。
 */
void fn(vector<int>& nums, vector<int>& res) {
  int n = nums.size();
  stack<int> stk;
  for(int i = n - 1; i >= 0; --i) {
    while(!stk.empty() && nums[stk.top()] <= nums[i]) stk.pop();
    res[i] = stk.empty() ? 0 : stk.top();
    stk.push(i);
  }
};

vector<int> res2(6);
void fn2(vector<int>& nums, vector<int>& res) {
  int n = nums.size();
  stack<int> stk;
  for(int i = 0; i < n; ++i) {
    if(stk.empty() || nums[stk.top()] >= nums[i]) {
      stk.push(i);
    } else {
      while(!stk.empty() && nums[stk.top()] < nums[i]) {
        res[i] = stk.top();
        stk.pop();
      }
      stk.push(i);
    }
  }
}

int main() {
  fn(test, res);
  fn2(test, res2);
  return 0;
}