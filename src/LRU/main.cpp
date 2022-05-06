#include <iostream>
#include <unordered_map>
using namespace std;

class Node {
public:
  int val, key;
  Node *prev, *next;
  Node(int key, int val): key(key), val(val), prev(nullptr), next(nullptr) {};
  Node(int key, int val, Node* prev, Node* next): key(key), val(val), prev(prev), next(next) {};
};

class LinkedList {
private:
  int size;
public:
  Node *head, *tail;
  
  LinkedList() {
    size = 0;
    head = new Node(0, 0);
    tail = new Node(0, 0);
    head->next = tail;
    tail->prev = head;
  };
  
  void push_back(Node* node) {
    //  Node* node = new Node(key, val);
    node->next = tail;
    node->prev = tail->prev;
    tail->prev = node;
    node->prev->next = node;
    size++;
  }
  
  Node* pop_front() {
    Node* node = head->next;
    Node* temp = node;
    head->next = node->next;
    head->next->prev = head;
    size--;
    return temp;
  }
  
  Node* erase(Node* node) {
    Node* temp = node;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    return temp;
    size--;
  }
  
  int getSize() {
    return size;
  }
  
  void print() {
    Node* node = head;
    while(node != tail) {
      cout << " [" << node->key << " " << node->val << "]";
      node = node->next;
    }
    cout << endl;
  }
};

class LRU {
private:
  int capacity;
  LinkedList list;
  unordered_map<int, Node*> mp;
public:
  LRU(int capacity): capacity(capacity) {};
  
  int get(int key) {
    if(mp.find(key) == mp.end()) {
      return -1;
    }
    Node* oldNode = mp[key];
    list.erase(oldNode);
    Node* node = new Node(key, oldNode->val);
    list.push_back(node);
    mp[key] = node;
    return node->val;
  };
  
  void put(int key, int val) {
    if(mp.find(key) != mp.end()) {
      Node* oldNode = mp[key];
      if(oldNode->val == val) return;
      else {
        list.erase(oldNode);
        Node* node = new Node(key, val);
        list.push_back(node);
        mp[key] = node;
      }
    } else {
      Node* node = new Node(key, val);
      list.push_back(node);
      mp[key] = node;
      if(list.getSize() > capacity) {
        Node* node = list.pop_front();
        mp.erase(node->key);
      }
    }
  };
  
  void print() {
    Node* node = list.head->next;
    while(node != list.tail) {
      cout << " [" << node->key << " " << node->val << "]";
      node = node->next;
    }
    cout << endl;
  }
};


int main() {
  LinkedList list;
  list.push_back(new Node(1, 2));
  list.push_back(new Node(2, 3));
  list.push_back(new Node(3, 4));
  list.push_back(new Node(4, 5));
  list.print();
  
  list.pop_front();
  list.print();
  
  
  LRU lru(3);
  lru.put(1, 2);
  lru.print();
  lru.put(2, 3);
  lru.print();
  lru.put(3, 4);
  lru.print();
  lru.put(5, 6);
  lru.print();
  
  cout << " get 2 " << lru.get(2) << endl;
  lru.print();
  
  cout << " get 3 " << lru.get(3) << endl;
  lru.print();
  
  cout << " get 3 " << lru.get(5) << endl;
  lru.print();
  
  return 0;
}
