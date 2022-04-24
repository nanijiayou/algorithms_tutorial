#ifndef __JERRY_TEST__
#define __JERRY_TEST__

#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

class RangeList {
 private:
  map<int, int> tree;

 public:
  RangeList() {}

  RangeList(const RangeList& rangeList) { tree = rangeList.tree; }

  RangeList& operator=(const RangeList& rangeList) {
    tree = rangeList.tree;
    return *this;
  }

  void add(int low, int high) {
    if (low > high)
      throw "invalid input, value of low should samll than value of high!";

    map<int, int>::iterator iter = tree.lower_bound(low);
    while (iter != tree.end() && iter->second <= high) {
      low = min(low, iter->second);
      high = max(high, iter->first);
      iter = tree.erase(iter);
    }
    tree[high] = low;
  }

  void remove(int low, int high) {
    map<int, int>::iterator iter = tree.upper_bound(low);
    while (iter != tree.end() && iter->second < high) {
      int last_low = iter->second;
      int last_high = iter->first;
      iter = tree.erase(iter);

      if (last_low < low) tree[low] = last_low;
      if (last_high > high) tree[last_high] = high;
    };
  }

  bool query(int low, int high) {
    auto iter = tree.lower_bound(high);
    return tree.end() != iter && iter->second <= low;
  }

  void print() {
    map<int, int>::iterator iter = tree.begin();
    while (iter != tree.end()) {
      cout << "[" << iter->second << "," << iter->first << ") ";
      iter++;
    }
    cout << endl;
  }

  ~RangeList() {}
};

int main() {
  RangeList rangeList;

  rangeList.add(1, 5);
  rangeList.print();
  rangeList.add(10, 20);
  rangeList.print();
  rangeList.add(20, 20);
  rangeList.print();
  rangeList.add(20, 21);
  rangeList.print();
  rangeList.add(2, 4);
  rangeList.print();
  rangeList.add(3, 8);
  rangeList.print();

  rangeList.remove(10, 10);
  rangeList.print();
  rangeList.remove(10, 11);
  rangeList.print();
  rangeList.remove(15, 17);
  rangeList.print();

  cout << "query [12, 14): " << rangeList.query(12, 14) << endl;
  cout << "query [18, 25): " << rangeList.query(18, 25) << endl;

  rangeList.remove(3, 19);
  rangeList.print();

  return 0;
}

#endif