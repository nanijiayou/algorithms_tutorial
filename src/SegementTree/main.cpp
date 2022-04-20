/*
 * @Author: hzheyuan
 * @Date: 2021-09-22 10:28:18
 * @LastEditTime: 2021-11-19 16:30:23
 * @LastEditors: hzheyuan
 * @Description: 
 * @FilePath: \SegementTree\SegmentTree.cpp
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace  std;

const int MAXN = 50;
pair<int,int> tree[MAXN << 2];

pair<int, int> combine(pair<int, int> a, pair<int, int> b) {
    if(a.first > b.first) return a;
    if(a.first < b.first) return b;
    return make_pair(a.first, a.second + b.second);
}

void build(vector<int> &a, int k, int tl, int tr) {
    if(tl == tr) {
        tree[k] = make_pair(a[tl], 1);
    } else {
        int tm = tl + (tr - tl >> 1);
        build(a, k << 1, tl, tm);
        build(a, (k << 1) + 1, tm + 1, tr);
        tree[k] = combine(tree[k << 1], tree[(k << 1) + 1]);
    }
}

pair<int, int> queryInTree(int k, int tl, int tr, int ql, int qr) {
    if(ql > qr) return make_pair(INT_MIN, 0);
    if(tl == ql && tr == qr) return tree[k];
    int tm = tl + (tr - tl >> 1);
    return combine(queryInTree(k << 1, tl, tm, ql, min(tm, qr)), queryInTree((k << 1) + 1, tm + 1, tr, max(tm+1, ql), qr));
}

pair<int, int> get_max(int ql, int qr) {
    return queryInTree(1, 0, MAXN, ql, qr);
}

void updateInTree(int k, int tl, int tr, int pos, int val) {
    if(tl == tr) tree[k] = make_pair(val, 1);
    else {
        int tm = tl + ((tr - tl) >> 1);
        if(pos <= tm) updateInTree(k << 1, tl, tm, pos, val);
        else updateInTree((k << 1) + 1, tm+1, tr, pos, val);
        tree[k] = combine(tree[k<<1], tree[(k<<1) + 1]);
    }
}

void update(int pos, int val) {
    updateInTree(1, 0, MAXN-1, pos, val);
}

int main() {
    //           [0,4]
    //           /   \
    //       [0,2]   [3,4]
    //        / \     /  \
    //     [0,1][2,2][3,3][4,4]
    //      / \
    //  [0,0] [1,1]

    vector<int> a = {1, 3, -2, 8, -7};
    build(a, 1, 0, MAXN-1);
    // // printArr(t);

    cout << "query(0, 1) " << get_max(0, 1).first << endl;
    cout << "query(0, 2) " << get_max(0, 2).first << endl;
    cout << "query(3, 4) " << get_max(3, 4).first << endl;
    cout << "query(2, 4) " << get_max(2, 4).first << endl;
    cout << "query(0, 4) " << get_max(0, 4).first << endl;

    cout << "query(0, 4) " << get_max(0, 4).second << endl;

    update(2, 5);
    cout << "query(0, 2) " << get_max(0, 2).first << endl;

    update(1, 9);
    cout << "query(0, 2) " << get_max(0, 2).first << endl;

    return 0;
}