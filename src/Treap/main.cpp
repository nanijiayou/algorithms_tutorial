#include <iostream>
#include <vector>
#include <algorithm>

using namespace  std;

// treap
// treap is a data structure that strores pairs(X, Y) in a binary tree 
// in such a way that is a binary search tree by X and a binary heap by Y.
// assuming that all X and all Y are different, we can see that if some node
// of the tree contains values(X0, Y0), all nodes in the left subtree have X < X0
// all nodes in the right subtree have X > X0, and all nodes in both left and right
// subtrees have Y < Y0

struct Node {
    int key, priority;
    Node *l, *r;
    Node() {}
    Node(int key): key(key), priority(rand()), l(nullptr), r(nullptr) {};
};

typedef Node* pnode;

// split treap t by value key into two treaps, 
// and store the left treaps in l and right treap in r
void split(pnode t, int key, pnode &l, pnode &r) {
    if(!t) l = r = nullptr;
    else if(t->key <= key)
        split(t->r, key, t->r, r), l = t;
    else
        split(t->l, key, l, t->l), r = t;
};

void merge(pnode &t, pnode l, pnode r) {
    if(!l || !r) t = l ? l : r;
    else if(l->priority > r->priority)
        merge(l->r, l->r, r), t = l;
    else merge(r->l, l, r->l), t = r;
}

void insert(pnode &t, pnode &it) {
    if(!t) t = it;
    else if(it->priority > t->priority)
        split(t, it->key, it->l, it->r), t = it;
    else
        insert(t->key <= it->key ? t->r : t->l , it);
}

void erase(pnode &t, int key) {
    if(t->key == key) {
        pnode th = t;
        merge(t, t->l, t->r);
        delete th;
    } else erase(key < t->key ? t->l : t->r, key);
}

pnode unite(pnode l, pnode r) {
    if(!l || !r) return l ? l : r;
    if(l->priority < r->priority) swap(l, r);
    pnode lt, rt;
    split(r, l->key, lt, rt);
    l->l = unite(l->l, lt);
    l->r = unite(l->r, rt);
    return l;
}

int main() {
    return 0;
}

