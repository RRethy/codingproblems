#include "node.cpp"
#include <iostream>

using namespace std;

int countNodes(Node<int> *root) {
  if (!root) return 0;
  return 1 + countNodes(root->l) + countNodes(root->r);
}

int main() {
  Node<int> *root = new Node<int>{ 0,
      new Node<int>{1, nullptr, nullptr},
      new Node<int>{0,
        new Node<int>{1,
          new Node<int>{1, nullptr, nullptr},
          new Node<int>{1, nullptr, nullptr}
        },
        new Node<int>{0, nullptr, nullptr}
      }
  };
  cout << countNodes(root) << '\n';
}
