// 范浩强treap
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

const int maxn = 100;
int seed = 233, root = 0, len, n;

struct node {
    int val, key;
    int l, r;
    int size;
    int reverse;
}tr[maxn];

// 随机key值
mt19937 rnd(std::chrono::system_clock::now().time_since_epoch().count());

// 新建值为d的节点
int addNode(int val) {
    tr[++len].val = val;
    tr[len].key = rnd();
    tr[len].size = 1;
    return len;
}

// 维护子树大小
void update(int now) {
    tr[now].size = tr[tr[now].l].size + tr[tr[now].r].size + 1;
}

void pushdown(int now) {
    swap(tr[now].l, tr[now].r);
    tr[tr[now].l].reverse ^= 1;
    tr[tr[now].r].reverse ^= 1;
    tr[now].reverse = 0;
}

// split:分裂
// now为原treap, val为权值，x为左树，y为右树
// split treap now byt value d into two treaps, and store the left treap in x and right treap in y
// x树中，所有结点的值都 <= val
// y树中，所有结点的值都 > val
// 可以分为两类：按值分类 & 按大小分裂

// 按值分裂
void split(int now, int &x, int &y, int val) {
    cout << "split: now=" << now << " l=" << x << " r=" << y << endl;
    // 如果now == 0,则分割完毕
    if(!now) x = y = 0;
    else {
        if(tr[now].val <= val) {// now的key较小，顾now和其左子树都在左树上
            split(tr[now].r, tr[now].r, y, val); // 只剩右子树需要分割
            x = now;
        } else {
            split(tr[now].l, x, tr[now].l, val);
            y = now;
        }
        cout << "split end: now=" << now << " l=" << x << " r=" << y << endl;
        update(now);
    }
}

// 按大小分裂
void split_by_size(int now, int& x, int& y, int size) {
    if(!now) x = y = 0;
    else {
        if(tr[now].reverse) pushdown(now);
        if(tr[tr[now].l].size < size) {
            x = now;
            split_by_size(tr[now].r, tr[now].r, y, size - tr[tr[now].l].size - 1);
        } else {
            y = now;
            split_by_size(tr[now].l, x, tr[now].l, size);
        }
        update(now);
    }
}

// merge: 合并
int merge(int x, int y) {
    // cout << "merge " << now << " " << l << " " << r << endl;
    if(!x || !y) return x + y;
    // x.key < y.key，则y树属于x树的后代
    // 因为y树横大于x树，那么y树一定属于x树的右后代
    if(tr[x].key < tr[y].key) {
        if(tr[x].reverse) pushdown(x);
        tr[x].r = merge(tr[x].r, y);
        update(x);
        return x;
    } else {
        if(tr[y].reverse) pushdown(y);
        tr[y].l = merge(x, tr[y].l);
        update(y);
        return y;
    }
}

// 插入
void insert(int val) {
    int x = 0, y = 0, z;
    z = addNode(val);
    // cout << " z=" << z;
    split(root, x, y, val);           // 根据插入值将树分割成两部分，左树<=插入值，右树大于插入值
    // cout << " x=" << x << " y=" << y ;
    int k = merge(x, z);
    // cout << " k=" << k;
    root = merge(k, y);   // 将z与x合并，之后再和y合并
    // cout << " root=" << root << endl ;
}

// 删除
void del(int val) {
    int x = 0, y = 0, z = 0;
    split(root, x, y, val);                   // 按删除的值d分割树，左树: l.d <=d，右树: r.d >d
    split(x, x, z, val - 1);                  // 继续分割已分割的左树，左树: l.d <= d-1， 右树：z.d = d 

    int a = merge(tr[z].l, tr[z].r);          // 先合并z的左右子树
    int b = merge(x, a);                      // 将合并后的z和l合并
    root = merge(x, y);
}

// 反转区间
void reverse(int l, int r) {
    int x, y, z;
    split_by_size(root, x, y, l - 1);
    split_by_size(y, y, z, r - l + 1);

    tr[y].reverse ^= 1;
    root = merge(merge(x, y), z);
}

// 查询第k大元素
int kth(int now, int rank) {
    while(tr[tr[now].l].size + 1 != rank) {
        if(tr[tr[now].l].size >= rank) {
            now = tr[now].l;
        } else {
            rank -= (tr[tr[now].l].size + 1);
            now = tr[now].r;
        }
    }
    return now;
}

// 获取排名
int get_rank(int val) {
    int x = 0, y = 0, k;
    split(root, x, y, val-1);
    k = tr[x].size + 1;
    root = merge(x, y);
    return k;
}

// 根据rank获取值
int get_value(int rank) {
   return tr[kth(root, rank)].val;
}

// 前驱
int presuccssor(int val) {
    int x = 0, y = 0, k;
    split(root, x, y, val - 1);
    k = kth(x, tr[x].size);
    root = merge(x, y);
    return tr[k].val;
}

// 后继
int succssor(int val) {
    int x = 0, y = 0, k;
    split(root, x, y, val);
    k = kth(y, 1);
    root = merge(x, y);
    return tr[k].val;
}

// 中序遍历，测试用
void inorderWalk(int idx) {
    if(idx == 0) return;
    inorderWalk(tr[idx].l);
    cout << tr[idx].val << " ";
    inorderWalk(tr[idx].r);
}

int main() {
    // int t;
    // scanf("%d", &t);
    // cout << t << endl;
    // while(t--) {
    //     int opt, x;
    //     scanf("%d%d", &opt, &x);
    //     cout << t << opt << x << endl;
    //     if(opt == 1) insert(x);
    // }

    // cout << "inorder walk: " << endl;
    // inorderWalk(root);
    // cout << endl << endl;

    // vector<int> test = {2, 3, 4, 5, 6, 7, 8}; 
    // vector<int> test = {20, 30, 40, 50, 60, 70, 80}; 
    vector<int> test = {2, 3, 4, 5}; 
    n = test.size();

    cout << "insert: " << endl;
    for(int i = 0; i < n; ++i) {
        cout << test[i] << " ";
        insert(test[i]);
    }
    cout << endl << endl;

    cout << "result: root= " << root << endl;
    for(int i = 0; i <= n; ++i) {
        auto item = tr[i];
        cout << "tr[" << i << "]:" << " l=" << item.l << " r=" << item.r << " d="  << item.val << " key=" << item.key << " size=" << item.size << endl;
    }
    cout << endl;

    cout << "inorder walk: " << endl;
    inorderWalk(root);
    cout << endl << endl;

    int splitVal = 3;
    cout << "split by val=" << splitVal  << endl;
    int x = 0, y = 0;
    split(root, x, y, splitVal);
    cout << "split result: x=" << x << " y=" << y << endl;

    cout << "walk the two splited tree: " << endl;
    inorderWalk(x);
    cout << endl;
    inorderWalk(y);
    cout << endl << endl;

    cout << "merge to splited tree: x=" << x << " y=" << y << endl;
    root = merge(x, y);
    inorderWalk(root);
    cout << endl << endl;

    int splitSize = 3;
    cout << "split by rank=" << splitSize  << endl;
    int a = 0, b = 0;
    split_by_size(root, a, b, splitSize);
    cout << "split result: x=" << a << " y=" << b << endl;
    cout << "walk the two splited tree: " << endl;
    inorderWalk(a);
    cout << endl;
    inorderWalk(b);
    cout << endl << endl;
    root = merge(a, b);

    int v = 50;
    cout << "delete " << v << " result: " << endl;
    del(v);
    inorderWalk(root);
    cout << endl << endl;

    cout << "querys :" << endl;
    cout << "get rank by value " << 20 << " is: " << get_rank(20);
    cout << endl;
    cout << "get value by rank " << 3 << " is: " << get_value(3);
    cout << endl;
    cout << "succsor of " << 30 << " is: " << succssor(30);
    cout << endl;
    cout << "presuccsor of " << 30 << " is: " << presuccssor(30);
    cout << endl << endl;

    int l = 2, r = 4;
    cout << "reverse [" << l << ", " << r  << "]: " << endl;
    reverse(l, r);
    inorderWalk(root);
    cout << endl;

    return 0;
}

