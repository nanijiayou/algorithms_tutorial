#include <iostream>
#include <vector>

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

void dfs(vector<int> &nums, vector<vector<int>> &ans, vector<int> &path, vector<bool> &vis) {
    if (path.size() == nums.size()) {
        ans.push_back(path);
        return;;
    }
    
    for (int i = 0; i < nums.size(); ++i) {
        if(vis[i]) continue;
        if(i > 0 && nums[i] == nums[i-1] && !vis[i-1]) continue;
        
        vis[i] = true;
        path.push_back(nums[i]);
        dfs(nums, ans, path, vis);
        vis[i] = false;
        path.pop_back();
    }
}


int main() {
    vector<int> test = {1, 1, 2};
    sort(test.begin(), test.end());
    
    vector<vector<int>> ans;
    vector<int> path;
    vector<bool> vis(test.size(), false);
    dfs(test, ans, path, vis);
    
    printAns(ans);
    return 0;
}

