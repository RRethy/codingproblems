#include <string>
#include <sstream>
#include <iostream>
#include "node.cpp"

// Given the root to a binary tree, implement serialize(root), which serializes
// the tree into a string, and deserialize(s), which deserializes the string
// back into the tree.

// Soln: To allow for strings as the value which can have almost anything, we
// will disallow the value to contain tabs and newlines.
//
// deserialized: Node("foo", Node("bar", nullptr, nullptr), Node("baz", Node("FOO", nullptr, nullptr), nullptr))
// serialized:
// foo
// 	bar
// 	baz
// 		FOO

void serializeNode(Node<std::string> *node, std::ostringstream &oss) {
  if (!node) {
    oss << '\n';
    return;
  }
  oss << node->value << '\n';
  serializeNode(node->l, oss);
  serializeNode(node->r, oss);
}

std::string serialize(Node<std::string> *root) {
  std::ostringstream oss;
  serializeNode(root, oss);
  return oss.str();
}

Node<std::string> *deserializedNode(std::istringstream &iss) {
  std::string line;
  std::getline(iss, line);
  if (line.empty()) {
    return nullptr;
  } else {
    Node<std::string> *l = deserializedNode(iss);
    Node<std::string> *r = deserializedNode(iss);
    return new Node<std::string>{line, l, r};
  }
}

Node<std::string> *deserialize(std::string str) {
  std::istringstream iss{str};
  return deserializedNode(iss);
}

int main() {
  Node<std::string> *root = new Node<std::string>{ "0",
      new Node<std::string>{"1", nullptr, nullptr},
      new Node<std::string>{"0",
        new Node<std::string>{"1",
          new Node<std::string>{"1", nullptr, nullptr},
          new Node<std::string>{"1", nullptr, nullptr}
        },
        new Node<std::string>{"0", nullptr, nullptr}
      }
  };
  std::string rootStr = serialize(root);
  std::cout << rootStr;

  std::cout << "==============================\n";

  Node<std::string> *newRoot = deserialize(rootStr);
  std::string newRootStr = serialize(newRoot);
  std::cout << newRootStr;

  delete newRoot;
  delete root;
}
