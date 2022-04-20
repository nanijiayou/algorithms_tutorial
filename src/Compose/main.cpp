#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> ans;
void printArr(vector<vector<int>>& arr) {
    for(int i = 0; i < arr.size(); ++i) {
        vector<int>::iterator iter = arr[i].begin();
        while(iter != arr[i].end()) {
            cout << *iter;
            iter++;
        }
        cout << endl;
    }
}

void bt(vector<int>& num, vector<int>& path, int t) {
    if(num.size() == path.size()) ans.push_back(path);
    for(int i = t; i < num.size(); ++i) {
        path.push_back(num[i]);
        bt(num, path, i+1);
        path.pop_back();
    }
}

int main() {
    vector<int> test{1, 3, 4};
    vector<int> path;
    bt(test, path, 0);
    printArr(ans);
}