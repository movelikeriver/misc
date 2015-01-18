// pre-order, in-order, post-order non-recursive solution.

#include <iostream>
#include <stack>

#include "bin-tree-util.h"

using namespace std;

// top, left, right
void PreOrder(TreeNode* root) {
  if (root == nullptr) {
    return;
  }
  stack<TreeNode*> s;
  s.push(root);
  while (!s.empty()) {
    TreeNode* t = s.top();
    s.pop();
    cout << t->val << ", ";
    if (t->right) {
      s.push(t->right);
    }
    if (t->left) {
      s.push(t->left);
    }
  }
  cout << endl;
}

// left, top, right
void InOrder(TreeNode* root) {
  stack<TreeNode*> s;

  TreeNode* p = root;
  // push all the left children
  while (p != nullptr) {
    s.push(p);
    p = p->left;
  }

  while (!s.empty()) {
    TreeNode* t = s.top();
    s.pop();
    cout << t->val << ", ";
    t = t->right;
    // push all the left children
    while (t != nullptr) {
      s.push(t);
      t = t->left;
    }
  }
  cout << endl;
}

// left, right, top
void PostOrder_Pair(TreeNode* root) {
  TreeNode* p = root;
  stack<pair<TreeNode*, TreeNode*> > s;  
  while (p != nullptr) {
    s.push(make_pair(p, p->right));
    p = p->left;
  }

  // The basic idea is to save pair of (top, right) in the stack, and
  // doing the same thing for top->left and its children, while doing
  // pop() in the stack, if pair.second is empty, it means that
  // pair.first is the left leaf, otherwise, push (pair.second,
  // nullptr) into the stack and continue to push pair.first->left and
  // its children.
  while (!s.empty()) {
    pair<TreeNode*, TreeNode*> pr = s.top();
    s.pop();
    if (pr.second == nullptr) {
      cout << pr.first->val << ", ";
      continue;
    }

    s.push(make_pair(pr.first, nullptr));
    TreeNode* t = pr.second;
    while (t != nullptr) {
      s.push(make_pair(t, t->right));
      t = t->left;
    }
  }
  cout << endl;
}

// left, right, top
void PostOrder_TwoStacks(TreeNode* root) {
  if (root == nullptr) {
    return;
  }
  stack<TreeNode*> s1, s2;
  s1.push(root);
  // The basic idea is to visit the tree as order of top, left, right,
  // then output the elememt to another stack to get the reverse
  // result.
  while (!s1.empty()) {
    TreeNode* t = s1.top();
    s1.pop();
    s2.push(t);
    if (t->left) {
      s1.push(t->left);
    }
    if (t->right) {
      s1.push(t->right);
    }
  }

  while (!s2.empty()) {
    cout << s2.top()->val << ", ";
    s2.pop();
  }
  cout << endl;
}

void Test(const vector<int>& input_vec) {
  vector<TreeNode*> tree_vec;
  TreeNode* root = ArrayToTree(input_vec, &tree_vec);
  string str = PrintTree(root);
  cout << str << endl;

  cout << "pre-order: ";
  PreOrder(root);

  cout << "in-order: ";
  InOrder(root);

  cout << "post-order: ";
  PostOrder_Pair(root);
  cout << "post-order: ";
  PostOrder_TwoStacks(root);

  DeleteTree(&tree_vec);
}

int main() {
  {
    int arr[] = {3, 9,20, kNull,kNull,15,7};
    vector<int> input_vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
    Test(input_vec);
  }
  {
    int arr[] = {3, 9,20, 11,12,10,7,
		 // level-4
		 kNull,kNull,14,kNull, kNull,kNull,kNull,kNull,
		 // level-5
		 kNull,kNull,kNull,kNull, 16,kNull,kNull,kNull,
		 kNull,kNull,kNull,kNull, kNull,kNull,kNull,kNull};
    vector<int> input_vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
    Test(input_vec);
  }
}
