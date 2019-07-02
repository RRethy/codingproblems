// https://www.youtube.com/watch?v=7HgsS8bRvjo

#include <iostream>
#include "node.cpp"

struct Result {
  int num;
  bool isUnivalue;
};

Result helper(Node *root) {
  if (!root) return Result{0, true};

  Result lres = helper(root->l);
  Result rres = helper(root->r);

  int lval = root->l ? root->l->value : root->value;
  int rval = root->r ? root->r->value : root->value;
  bool isCurTreeUnival = root->value == lval && root->value == rval
    && lres.isUnivalue && rres.isUnivalue;

  int num = lres.num + rres.num;
  if (isCurTreeUnival) num++;

  return Result{num, isCurTreeUnival};
}

int main() {
  Node *root = new Node{ 0,
      new Node{1, nullptr, nullptr},
      new Node{0,
        new Node{1,
          new Node{1, nullptr, nullptr},
          new Node{1, nullptr, nullptr}
        },
        new Node{0, nullptr, nullptr}
      }
  };
  Result res = helper(root);
  std::cout << res.num << '\n';
  delete root;
}
