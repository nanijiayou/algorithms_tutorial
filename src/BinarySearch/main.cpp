#include <iostream>
#include <vector>
using namespace std;

int lower_bound(vector<int> arr, int target) {
  int low = 0, high = arr.size();
  while(low < high) {
    int mid = low + (high - low) / 2;
    if(arr[mid] < target) low = mid + 1;
    else high = mid;
  }
  return low;
}

int upper_bound(vector<int> arr, int target) {
  int low = 0, high = arr.size();
  while(low < high) {
    int mid = low + (high - low) / 2;
    if(arr[mid] <= target) low = mid + 1;
    else high = mid;
  }
  return low;
}

int binary_search(vector<int> arr, int target) {
  int i = lower_bound(arr, target);
  return i != arr.size() && !(arr[i] > target) ? i : -1;
}


int main() {
  vector<int> test = {-1, 0, 3, 4, 5, 5, 5, 6, 6, 9, 12};
  vector<int> test2 = { 3 };
  
  cout << "lower bound of 2 is "  << lower_bound(test, 2) << endl;
  cout << "lower bound of 5 is "  << lower_bound(test, 5) << endl;
  cout << "lower bound of 6 is "  << lower_bound(test, 6) << endl;
  cout << "lower bound of 7 is "  << lower_bound(test, 7) << endl;
  cout << "lower bound of 12 is " << lower_bound(test, 12) << endl;
  
  cout << "lower bound of 2 is " << lower_bound(test2, 2) << endl;
  cout << "lower bound of 3 is " << lower_bound(test2, 3) << endl;
  cout << "lower bound of 5 is " << lower_bound(test2, 5) << endl;
  
  cout << "binary search of 2 is " << binary_search(test, 2) << endl;
  cout << "binary search of 5 is " << binary_search(test, 5) << endl;
  cout << "binary search of 6 is " << binary_search(test, 6) << endl;
  cout << "binary search of 7 is " << binary_search(test, 7) << endl;
  
  cout << "binary search of 2 is " << binary_search(test2, 2) << endl;
  cout << "binary search of 3 is " << binary_search(test2, 3) << endl;
  cout << "binary search of 5 is " << binary_search(test2, 5) << endl;
  
  cout << "upper bound of 2 is " << upper_bound(test, 2) << endl;
  cout << "upper bound of 5 is " << upper_bound(test, 5) << endl;
  cout << "upper bound of 6 is " << upper_bound(test, 6) << endl;
  cout << "upper bound of 7 is " << upper_bound(test, 7) << endl;
  cout << "upper bound of 12 is " << upper_bound(test, 12) << endl;
  
  
  return 0;
}
