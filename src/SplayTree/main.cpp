#include <iostream>
#include <vector>
using namespace std;

const int maxn = 100;
struct Node {
    int val, key;
    int l, r, p;
    int size;
}tr[maxn];

int len, root;

int add(int val, int p) {
    tr[++len].val = val;
    tr[len].p = p;
    tr[len].size = 1;
    return len;
}

// 判断x是 x.p的哪个儿子
// 左儿子返回0， 右儿子返回1
int ident(int x) {
    return tr[tr[x].p].l == x ? 0 : 1;
};

void connect(int x, int p, int how) {
    how == 0 ? tr[p].l = x : tr[p].r = x;
    tr[x].p = p;
}

void rotate(int x) {
    int Y = tr[x].p;
    int R = tr[Y].p;

    int Yson = ident(x), Rson = ident(Y);
    int B = !Yson ? tr[x].r : tr[x].l;

    connect(B, Y, Yson);
    connect(Y, x, Yson^1);
    connect(x, R, Rson);
}

void splay(int x, int to) {
    to = tr[to].p;
    while (tr[x].p != to) {
        int y = tr[x].p;
        if(tr[y].p == to) rotate(x);
        else if(ident(x) == ident(y)) rotate(y), rotate(x);
        else rotate(x), rotate(x);
    }
}

void insert(int x) {
    int now = root;
    if(root == 0) { add(x, 0); root = len; }
    else {
        while (1) {
            tr[now].size++;
            if(tr[now].val == x) {
                splay(now, root);
                return;
            }
            int ident = x < tr[now].val ? 0 : 1;
            int next = !ident ? tr[now].l : tr[now].r;
            if(!next) {
                int node = add(x, now);
                !ident ? tr[now].l = node : tr[now].r = node;
                splay(node, root);
                return;
            }
            now = !ident ? tr[now].l : tr[now].r;
        }
    }
}

// 中序遍历，测试用
void inorderWalk(int idx) {
    if(idx == 0) return;
    inorderWalk(tr[idx].l);
    cout << tr[idx].val << " ";
    inorderWalk(tr[idx].r);
}


// SplayTree
int main() {
    vector<int> test = {10, 20, 30, 40, 50, 60, 70}; 
    int n = test.size();

    cout << "insert: " << endl;
    for(int i = 0; i < n; ++i) {
        cout << test[i] << " ";
        insert(test[i]);
    }
    cout << endl << endl;

    cout << "result: root= " << root << endl;
    for(int i = 0; i < n + 2; ++i) {
        auto item = tr[i];
        cout << "tr[" << i << "]:" << " l=" << item.l << " r=" << item.r << " d="  << item.val << " key=" << item.key << " size=" << item.size << endl;
    }
    cout << endl;

    cout << "inorder walk: " << endl;
    inorderWalk(root);
    cout << endl << endl;

    return 0;
}
