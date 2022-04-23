//#include <iostream>
//#include <set>
//using namespace std;
//
//// Structure of interval [low, high)
//struct Interval {
//  int low, high;
//};
//
//// Structure of tree node
//struct ITNode {
//  Interval *interval;
//  ITNode *left, *right;
//  int max;
//};
//
//// A utility function to create a new Interval Search Tree Node
//ITNode *createNode(Interval interval) {
//  ITNode *temp = new ITNode;
//  temp->interval = new Interval(interval);
//  temp->max = interval.high;
//  temp->left = temp->right = nullptr;
//  return temp;
//};
//
//// Insert a new interval
//ITNode *insert(ITNode *root, Interval interval) {
//  // Base case: tree is empty, create a new node
//  if (root == nullptr) return createNode(interval);
//
//  // Toot interval
//  int rlow = root->interval->low, rhigh = root->interval->high;
//
//  // Three cases
//  if (interval.low < rlow)
//    root->left = insert(root->left, interval);
//  else if(interval.low > rlow)
//    root->right = insert(root->right, interval);
//  else {
//    if(interval.high < rhigh) root->left = insert(root->left, interval);
//    else root->right = insert(root->right, interval);
//  }
//
//  // Update the max value
//  if (root->max < interval.high) root->max = interval.high;
//
//  return root;
//}
//
//ITNode *remove(ITNode *root, Interval interval) {
//  if (root == nullptr) return nullptr;
//  int l = interval.low, h = interval.high;
//
//  if (l < root->interval->low) {
//    root->left = remove(root->left, interval);
//  } else if (l > root->interval->low) {
//    root->right = remove(root->right, interval);
//  } else {
//    if (h < root->interval->high) {
//      root->left = remove(root->left, interval);
//    } else if (h > root->interval->high) {
//      root->right = remove(root->right, interval);
//    } else {
//      if (root->left == nullptr)
//        return root->right;
//      else if (root->right == nullptr)
//        return root->left;
//
//      ITNode *cur = root->right;
//      while (cur->left != nullptr) {
//        cur = cur->left;
//      }
//
//      root->interval->low = cur->interval->low;
//      root->interval->high = cur->interval->high;
//      Interval* iter = root->interval;
//      root->right = remove(root->right, *iter);
//    }
//  }
//  return root;
//}
//
//// check two intervals overlap
//bool checkOVerlap(Interval i1, Interval i2) {
//  return i1.low <= i2.high && i2.low <= i1.high;
//}
//
//// search a interval
//Interval *overlapSearch(ITNode *root, Interval interval) {
//  if (root == nullptr) return nullptr;
//
//  if (checkOVerlap(*(root->interval), interval)) return root->interval;
//
//  if (root->left != nullptr && root->left->max >= interval.low)
//    return overlapSearch(root->left, interval);
//
//  return overlapSearch(root->right, interval);
//}
//
//// inorder walk the tree
//void inorder(ITNode *root) {
//  if (root == nullptr) return;
//  inorder(root->left);
//
//  cout << "[" << root->interval->low << ", " << root->interval->high << ")";
//      //  << " max = " << root->max;
//
//  inorder(root->right);
//}
//
//// print
//void print(ITNode *root) {
//  inorder(root);
//  cout << endl;
//}
//
//int main() {
//  Interval intervals[] = {{1, 5}, {10, 20}, {20, 20}, {20, 21}, {2, 4}, {3, 8}};
//
//  int n = sizeof(intervals) / sizeof(intervals[0]);
//  ITNode *root = nullptr;
//
//  for (auto const interval : intervals) {
//    root = insert(root, interval);
//    cout << "Insert a range [" << interval.low << ", " << interval.high
//         << "] in the tree, result: " << endl;
//    print(root);
//  }
//
//  Interval x = {6, 7};
//
//  cout << "\nSearching for interval [" << x.low << "," << x.high << "]";
//  Interval *res = overlapSearch(root, x);
//  if (res == nullptr)
//    cout << "\nNo Overlapping Interval";
//  else
//    cout << "\nOverlaps with [" << res->low << ", " << res->high << "]\n";
//  cout << endl;
//
//  Interval d = {15, 17};
//  remove(root, d);
//  cout << "Remove a range [" << d.low << ", " << d.high
//       << "] in the tree, result: " << endl;
//  print(root);
//  return 0;
//}


#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

map<int, int> tree;

void add(int left, int right) {
  map<int, int>::iterator it = tree.lower_bound(left);
  while (it != tree.end() && it->second <= right) {
    left = min(left, it->second);
    right = max(right, it->first);
    it = tree.erase(it);
  }
  tree[right] = left;
}

void remove(int left, int right) {
  map<int, int>::iterator it = tree.upper_bound(left);
  while(it != tree.end() && it->second < right) {
    int last_left = it->second;
    int last_right = it->first;
    it = tree.erase(it);
    
    if(last_left < left) tree[left] = last_left;
    if(last_right > right) tree[last_right] = right;
  }
}

void print() {
  map<int, int>::iterator it = tree.begin();
  while (it != tree.end()) {
    cout << "[" << it->second << "," << it->first << ")";
    it++;
  }
  cout << endl;
}

int main() {
  add(1, 5);
  print();
  add(10, 20);
  print();
  add(20, 20);
  print();
  add(20, 21);
  print();
  add(2, 4);
  print();
  add(3, 8);
  print();
  
  remove(10, 10);
  print();
  remove(10, 11);
  print();
  remove(15, 17);
  print();
  remove(3, 19);
  print();
  
  return 0;
}
