#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printVec(vector<int>& vec) {
    for(auto const v : vec) {
        cout << v << " ";
    }
    cout << endl;
}

void printAns(vector<vector<int>>& ans) {
    for(auto iter = ans.begin(); iter != ans.end(); iter++) {
        printVec(*iter);
    }
}

void dfs(vector<int> &nums, vector<vector<int>> &ans, vector<int> &path, int t) {
    if(path.size() == nums.size()) {
        ans.push_back(path);
        return;
    }
    
    for(int i = t; i < nums.size(); ++i) {
        path.push_back(nums[i]);
        dfs(nums, ans, path, i+1);
        path.pop_back();
    }
}

void dfs(vector<int> &nums, vector<vector<int>> &ans, vector<bool> &vis, vector<int> &path, int t) {
    if(path.size() == 2) {
        ans.push_back(path);
        return;
    }
    
    for(int i = t; i < nums.size(); ++i) {
        if(vis[i]) continue;
        if(i > 0 && nums[i] == nums[i-1] && !vis[i]) continue;
        vis[i] = true;
        path.push_back(nums[i]);
        dfs(nums, ans, vis, path, i + 1);
        vis[i] = false;
        path.pop_back();
    }
}


int main() {
    vector<int> test = {1, 4, 2, 2, 3, 3, 4, 5};
    
    vector<vector<int>> ans;
    vector<int> path;
    vector<bool> vis(test.size(),false);
    sort(test.begin(), test.end());
    dfs(test, ans, vis, path, 0);
    
    printAns(ans);
    return 0;
}
