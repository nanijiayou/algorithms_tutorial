#include <iostream>
#include <unordered_map>
using namespace std;

struct Node {
  int key, val;
  Node *next, *pre;
  Node(int key, int val) : key(key), val(val), next(nullptr), pre(nullptr){};
};

class LinkedList {
 private:
  int size;
  Node *head, *tail;

 public:
  LinkedList(/* args */);
  Node* push_back(int key, int val);  // 在末尾插入
  Node* pop();                        // 弹出头部元素
  Node* remove(Node* x);              // 删除一个node
  inline Node* getHead() { return head; };
  inline Node* getTail() { return tail; };
  inline int getSize() { return size; };
  void print();
  ~LinkedList();
};

LinkedList::LinkedList() {
  head = new Node(0, 0);
  tail = new Node(0, 0);
  head->next = tail;
  tail->pre = head;
  size = 0;
}

Node* LinkedList::push_back(int key, int val) {
  Node* node = new Node(key, val);
  node->pre = tail->pre;
  node->next = tail;
  tail->pre->next = node;
  tail->pre = node;
  size++;
  return node;
}

Node* LinkedList::pop() {
  if (head->next == tail)
    return tail;
  else {
    Node* temp = head->next;
    head->next = head->next->next;
    head->next->pre = head;
    size--;
    return temp;
  }
}

Node* LinkedList::remove(Node* x) {
  if (x == head || x == tail)
    return x;
  else {
    Node* temp = x;
    temp->pre->next = temp->next;
    temp->next->pre = temp->pre;
    size--;
    return temp;
  }
}

void LinkedList::print() {
  Node* cur = head->next;
  cout << "list data: ";
  while (cur != tail) {
    cout << "[" << cur->key << " " << cur->val << "]";
    cur = cur->next;
  }
  cout << endl;
}

LinkedList::~LinkedList() {
  delete head;
  delete tail;
};

class LRU {
 private:
  int size = 0;
  int cmp;
  unordered_map<int, Node*> mp;
  LinkedList list;

 public:
  LRU(int size = 0);
  int get(int key);
  void put(int key, int val);
  void print();
  ~LRU();
};

LRU::LRU(int cmp) : cmp(cmp) {}

int LRU::get(int key) {
  if (mp.find(key) == mp.end())
    return -1;
  else {
    // 先删除该结点，然后在链表尾部插入该结点
    Node* removedNode = list.remove(mp[key]);
    Node* node = list.push_back(removedNode->key, removedNode->val);
    // 更新map的key
    mp[key] = node;
    return node->val;
  }
}

void LRU::put(int key, int val) {
  if (mp.find(key) != mp.end()) {
    // 如果有，则将其放到list尾部，然后更新map
    list.remove(mp[key]);
    Node* node = list.push_back(key, val);
    mp[key] = node;
  } else {
    // 如果没有，先检查容量，容量不够，删除list头部结点
    if (list.getSize() >= cmp) {
      Node* node = list.pop();
      mp.erase(node->key);
      size--;
    }
    // 新结点都插入list尾部
    Node* node = list.push_back(key, val);
    // 需要更新map中key的指向
    mp[key] = node;
    size++;
  }
}

void LRU::print() {
  auto head = list.getHead();
  auto tail = list.getTail();

  Node* cur = head->next;
  cout << "lru list data: ";
  while (cur != tail) {
    cout << "[" << cur->key << " " << cur->val << "]";
    cur = cur->next;
  }
  cout << endl;
}

LRU::~LRU(){};


int main() {
  int a[7] = {1, 3, 5, 8, 9, 7, 2};
  LinkedList list;
  for (int i = 0; i < 7; ++i) {
    list.push_back(a[i], a[i]);
  }
  list.print();

  list.pop();
  list.print();

  Node* node = list.getHead();
  node = node->next->next;
  list.remove(node);
  list.print();

  LRU lru(3);
  lru.put(1, 1);
  lru.print();
  lru.put(3, 3);
  lru.print();
  lru.put(5, 5);
  lru.print();
  lru.put(7, 7);
  lru.print();

  cout << "get 3 " << lru.get(3) << endl;
  lru.print();

  return 0;
}
