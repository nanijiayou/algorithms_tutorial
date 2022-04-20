#include <iostream>
#include <vector>
#include <algorithm>
using namespace  std;

vector<int> a;
const int maxn = 5;
vector<int> t(maxn << 2, 0);

int merge(int l, int r) {
    return t[l] + t[r];
};

// k为当前需要建立的节点索引， tl为当前需要建立的区间的左端点，tr为当前需要建立的区间的右端点
// tl = k * 2 左儿子下标为父节点下标的两倍 
// tr = k * 2 + 1 右儿子下标为父节点下标的两倍+1
void build(int k, int tl, int tr) {
    if(tl == tr) t[k] = a[tl];                  // 如果左端点等于右端点，既为叶子节点，直接赋值即可
    else {
        int m = tl + (tr - tl >> 1);            // m为中间节点，左子树节点区间：[l, m]；右子树区间：[m+1, r];
        build(k << 1, tl, m);                   // 递归构造左儿子节点
        build((k << 1) + 1, m + 1, tr);         // 递归构造右儿子节点
        t[k] = merge(k << 1, (k << 1) + 1);     // 完成阶段，更新父节点
    }
};

// 递归范围查询
// [tr, tl]为当前结点包含的区间，[ql, qr]查询的区间既查询接口输入的区间参数
// 分为三种情况：
//   1. [ql, qr] == [tl, tr]，直接返回当前结点存储的预处理的值
//   2. [ql, qr]完全处在[tl,tr]的左边或者右边，此时递归查询左侧或者右侧即可
//   3. [ql, qr]横跨[tl,tr]的左右两边，此时分别处理左右两边并合并结果
int queryInTree(int k, int tl, int tr, int ql, int qr) {
    if(tl > qr || tr < ql) return 0;
    if(tl == ql && tr == qr) return t[k];
    // int mid = tl + (tr - tl >> 1);
    // if(qr <= mid) return queryInTree(k << 1, tl, mid, ql, qr);
    // else if(ql > mid) return queryInTree((k << 1) + 1, mid + 1, tr, ql, qr);
    // else return queryInTree(k << 1, tl, mid, ql, mid) + queryInTree((k << 1) + 1, mid + 1, tr, mid + 1, qr);
    int tm = tl + (tr - tl >> 1);
    return queryInTree(k << 1, tl, tm, ql, min(tm, qr)) + queryInTree((k << 1) + 1, tm+1, tr, max(tm + 1, ql), qr);
}

// 对外查询接口
int query(int ql, int qr) {
    return queryInTree(1, 0, maxn - 1, ql, qr);
}

// 更新结点
// [tl, tr]为结点所在区间
// pos为更新接口输入的位置参数，new_val为更新结点输入的更新之后的值
// 分2两种情况：
//   1. tl == tr，既找到该结点位置，更新t[k]的值
//   2. pos 在区间[tl, tr]的左侧，或者右侧，递归更新
void updateInTree(int k, int tl, int tr, int pos, int new_val) {
    if(tl == tr) {
        t[k] = new_val;
        return;
    }

    int mid = tl + (tr - tl >> 1);
    if(pos <= mid) updateInTree(k << 1, tl, mid, pos, new_val);
    else updateInTree((k << 1) + 1, mid + 1, tr, pos, new_val);
    t[k] = merge(k << 1, (k << 1) + 1);
}

// 对外提供的更新接口
void update(int pos, int new_val) {
    updateInTree(1, 0, maxn - 1, pos, new_val);
}

void printArr(vector<int>& A) {
    for(int i = 0; i < A.size(); ++i) {
        cout << " " << A[i];
    }
    cout << endl;
};





int main() {
    //           [0,4]
    //           /   \
    //       [0,2]   [3,4]
    //        / \     /  \
    //     [0,1][2,2][3,3][4,4]
    //      / \
    //  [0,0] [1,1]

    a = {1, 3, -2, 8, -7};
    build(1, 0, maxn-1);
    printArr(t);

    cout << "query(0, 2) " << query(0, 2) << endl;
    cout << "query(3, 4) " << query(3, 4) << endl;
    cout << "query(2, 4) " << query(2, 4) << endl;

    update(2, 3);
    cout << "query(0, 2) " << query(0, 2) << endl;

    update(1, 5);
    cout << "query(0, 2) " << query(0, 2) << endl;

    return 0;
}