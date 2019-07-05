#include <iostream>
#include <string>

// An XOR linked list is a more memory efficient doubly linked list. Instead of
// each node holding next and prev fields, it holds a field named both, which
// is an XOR of the next node and the previous node. Implement an XOR linked
// list; it has an add(element) which adds the element to the end, and a
// get(index) which returns the node at index.

template<class T>
struct Node {
  T val;
  Node<T> *both = nullptr;
};

template<class T>
struct XorLinkedList {

  Node<T> *head;

  ~XorLinkedList() {
    Node<T> *cur = head;
    Node<T> *prev = nullptr;
    while (cur) {
      Node<T> *tmp = cur;
      cur = (Node<T> *)((uintptr_t)cur->both ^ (uintptr_t)prev);
      prev = tmp;
      delete prev;
    }
  }

  void add(Node<T> *newNode) {
    if (!head) {
      head = newNode;
      return;
    }

    Node<T> *cur = head;
    Node<T> *prev = nullptr;
    while (cur) {
      Node<T> *tmp = cur;
      cur = (Node<T> *)((uintptr_t)cur->both ^ (uintptr_t)prev);
      prev = tmp;
    }
    prev->both = (Node<T> *)((uintptr_t)newNode xor (uintptr_t)prev->both);
    newNode->both = prev;
  }

  Node<T> *get(int index) {
    Node<T> *cur = head;
    Node<T> *prev = nullptr;
    for (int i = 0; i < index; ++i) {
      if (!cur) return nullptr;
      Node<T> *tmp = cur;
      cur = (Node<T> *)((uintptr_t)cur->both ^ (uintptr_t)prev);
      prev = tmp;
    }
    return cur;
  }

};

int main() {
  XorLinkedList<std::string> xorLL;
  xorLL.add(new Node<std::string>{"Hello1"});
  xorLL.add(new Node<std::string>{"Hello2"});
  xorLL.add(new Node<std::string>{"Hello3"});
  xorLL.add(new Node<std::string>{"Hello4"});
  xorLL.add(new Node<std::string>{"Hello5"});
  for (int i = 0; i < 5; ++i) {
    std::cout << xorLL.get(i)->val << '\n';
  }
}
