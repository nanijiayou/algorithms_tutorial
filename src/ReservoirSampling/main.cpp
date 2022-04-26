/*
 * @Author: kalai
 * @LastEditors: kalai
 * @Description: 水塘抽样
 * 水塘抽样是一种随机化算法
 * 给定一个数据流，数据流长度N很大，（N在处理完所有数据前不可知），如何在只遍历一遍的情况下，随机选出k个不重复的数据。
 *  1. 数据流很大且不可知，不能一次性存入内存
 *  2. 复杂度要为O(n)
 *  3. 随机选取，所以每个数被选中的概率都为 k/N
 * @FilePath: \algorithms_tutorial\src\ReservoirSampling\main.cpp
 */
#include <iostream>
#include <vector>
using namespace std;

// 对于前 k 个数全部保留。
// 对于第 i(i>k) 个数，我们以 k/i 的概率来决定该元素是否被替换到数组中(数组中的 k 个元素被替换的概率是相同的)。
// 遍历完所有数据后，数组中剩下的元素就是所需采取的样本。
vector<int> ReservoirSampling(vector<int>&res, vector<int>& nums, int k) {
  int n = nums.size();
  // 前k个全部保留
  for(int i = 0; i < k; ++i) res.push_back(nums[i]);
  // i > k 的元素，以 k / i 的概率替换数组中元素
  for(int i = k; i < n; ++i) {
    int random = rand() % i;
    if(random < k) {
      res[random] = nums[i];
    }
  }
  return res;
}

// 洗牌算法,
// 判断乱的依据: 对于包含 n 个数的序列，其全排列有 n! 种可能。所以 乱序的结果有 n! 种且每种出现的概率一样。则是真的乱序。
// 还有一个等价的判断就是：每个元素出现在每个位置上的概率都为 1/n。
// Knuth-Shuffle算法：将原数组划分为已打乱和未打乱的两部分（初始为 0 和 n个元素）。每次随机从未打乱的部分中选择一个元素加入到已打乱的部分中。
void KnuthShuffle(vector<int> &nums) {
  int n = nums.size();
  for(int i = 0; i < n; ++i) {
    // i ~ n-1 之间随机选择一个
    int k = (rand() % (n - i)) + i;
    swap(nums[i], nums[k]);
  }
}

int main() {
  vector<int> test = {7, 2, 3, 1, 3, 2, 1, 6, 4, 5, 9, 8, 8, 7, 1, 6, 8, 3, 4, 5};
  vector<int> res;
  ReservoirSampling(res, test, 5);
  for(auto n : res) {
    cout << n << " ";
  }
  cout << endl;

  vector<int> test2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  KnuthShuffle(test2);
  return 0;
}