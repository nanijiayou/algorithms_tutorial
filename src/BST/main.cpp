#include<iostream>
using namespace std;

// 二叉搜索树BST
class BSTNode {
public:
    int key;
    BSTNode* left;
    BSTNode* right;
    BSTNode* parent;
    BSTNode(int k = 0, BSTNode* left = nullptr, BSTNode* right = nullptr, BSTNode* parent = nullptr): 
    key(k), left(left), right(right), parent(parent) {}
};

class BSTTree {
private:
    BSTNode* root; 
public:
    BSTTree();
    // 查询
    BSTNode* Search(int key);                           // 查询结点，递归版
    BSTNode* Search(BSTNode* root, int key);            // 查询结点，递归版
    BSTNode* IntertiveSearch(BSTNode* root, int key);   // 查询非递归
    BSTNode* Minimum(BSTNode* node);                    // 以node为根的子树的最小关键字结点
    BSTNode* Maximum(BSTNode* node);                    // 以node为根的子树的最大关键字结点
    BSTNode* Successor(BSTNode* node);                  // 后续
    BSTNode* PreSuccessor(BSTNode* node);               // 前驱

    // 插入与删除
    void Transparent(BSTNode* u, BSTNode* v);           // 交换两棵子树
    void Insert(int key);                               // 插入
    void Delete(int key);                               // 删除结点
    BSTNode* Delete(BSTNode* node);                     // 删除结点

    // 遍历
    void InorderWalk(BSTNode* root);                    // 中序遍历
    void InorderWalk();                                 // 中序对外借口
};

BSTTree::BSTTree(): root(nullptr) {
}

void BSTTree::InorderWalk(BSTNode* node) {
    if(node != nullptr) {
        InorderWalk(node->left);
        cout << node->key << " ";
        InorderWalk(node->right);
    }
}

void BSTTree::InorderWalk() {
    this->InorderWalk(root);
}

BSTNode* BSTTree::Search(BSTNode* root, int key) {
    if(root == nullptr || root->key == key) {
        return root;
    }
    if(key < root->key) {
        return Search(root->left, key);
    } else {
        return Search(root->right, key);
    }
}

BSTNode* BSTTree::Search(int key) {
    return this->Search(root, key);
}

BSTNode* BSTTree::IntertiveSearch(BSTNode* root, int key) {
    while(root != nullptr && key != root->key) {
        if(key < root->key) root = root->left;
        else root = root->right;
    }
    return root;
}

BSTNode* BSTTree::Minimum(BSTNode* root) {
    while(root->left != nullptr) root = root->left;
    return root;
}

BSTNode* BSTTree::Maximum(BSTNode* root) {
    while(root->right != nullptr) root = root->right;
    return root;
}

BSTNode* BSTTree::Successor(BSTNode* x) {
    if(x->right != nullptr) return this->Minimum(x->right);
    BSTNode* y = x->parent;
    while(y != nullptr && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

BSTNode* BSTTree::PreSuccessor(BSTNode* x) {
    if(x->left != nullptr) return this->Maximum(x->left); 
    BSTNode* y = x->parent;
    while(y != nullptr && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

void BSTTree::Insert(int key) {
    BSTNode* z = new BSTNode(key, nullptr, nullptr, nullptr);

    BSTNode* y = nullptr;
    BSTNode* x = root;

    while(x != nullptr) {
        y = x;
        if(z->key < x->key) x = x->left;
        else x = x->right;
    }
    z->parent = y;
    
    if(y == nullptr) root = z;
    else if(z->key < y->key) y->left = z;
    else y->right = z; 
}

void BSTTree::Transparent(BSTNode* u, BSTNode* v) {
    if(u->parent == nullptr) root = v;
    else if(u == u->parent->left) u->parent->left = v;
    else if(u == u->parent->right) u->parent->right = v;
    if(v != nullptr) v->parent = u->parent;
}

void BSTTree::Delete(int key) {
    BSTNode* z = Search(key);
    if(z != nullptr) {
        Delete(z);
        delete z;
    }
}

BSTNode* BSTTree::Delete(BSTNode* z) {
    if(z->left == nullptr) Transparent(z, z->right);
    else if(z->right == nullptr) Transparent(z, z->left);
    else {
        BSTNode* y = this->Minimum(z->right);
        if(y->parent != z) {
            Transparent(y, y->right);
            y->right = z->right;
            z->right->parent = y;
        }
        Transparent(z, y);
        y->left = z->left;
        z->left->parent = y;
    }
    return z;
}

int main() {
    BSTTree* tree = new BSTTree();
    int test[11] = {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};

    // 插入
    for(int i = 0; i < 11; ++i) {
        tree->Insert(test[i]);
    }
    tree->InorderWalk();
    cout << endl;

    // 查询
    int k1 = 6;
    BSTNode* kn1 = tree->Search(k1);
    if(kn1) {
        cout 
        << "seacrh key = 6: parent is " << kn1->parent->key
        << "; left child is " << kn1->left->key 
        << "; right child is " << kn1->right->key 
        << endl;
    }

    // maximum and minimum
    BSTNode* minkn1 = tree->Minimum(kn1);
    BSTNode* maxkn1 = tree->Maximum(kn1);
    cout << "minimum of 6 is " << minkn1->key << endl;
    cout << "maximum of 6 is " << maxkn1->key << endl;

    // 后续 && 前驱
    BSTNode* ks1 = tree->Successor(kn1);
    BSTNode* kp1 = tree->PreSuccessor(kn1);
    cout << "successor of 6 is " << ks1->key << endl;
    cout << "pre-successor of 6 is " << kp1->key << endl;

    // 删除
    tree->Delete(6);
    cout << "delete node key = 6 " << endl;
    tree->InorderWalk();
    cout << endl;

    return 0;
}