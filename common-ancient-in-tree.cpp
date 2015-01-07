// Find the lowest level common ancient node in a binary tree.
//
// Run:
//  g++ common-ancient-in-tree.cpp
//  ./a.out

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Find the lowest level common ancient for n1 and n2, and n1 != n2.
TreeNode* Find(TreeNode* root, TreeNode* n1, TreeNode* n2) {
  if (root == nullptr) {
    return nullptr;
  }
  if (root == n1) {
    return n1;
  }
  if (root == n2) {
    return n2;
  }
  TreeNode* left = Find(root->left, n1, n2);
  TreeNode* right = Find(root->right, n1, n2);
  if (left != nullptr && right != nullptr) {
    return root;
  }
  if (left) {
    return left;
  }
  if (right) {
    return right;
  }
  return nullptr;
}

int main() {
  // Create a tree below:
  //        5
  //     /     \
  //    3       8
  //   / \     / \
  //  1   4   7   9

  vector<TreeNode*> node_vec;
  TreeNode* n1 = new TreeNode(1);
  node_vec.push_back(n1);
  TreeNode* n3 = new TreeNode(3);
  node_vec.push_back(n3);
  TreeNode* n4 = new TreeNode(4);
  node_vec.push_back(n4);
  TreeNode* n5 = new TreeNode(5);
  node_vec.push_back(n5);
  TreeNode* n7 = new TreeNode(7);
  node_vec.push_back(n7);
  TreeNode* n8 = new TreeNode(8);
  node_vec.push_back(n8);
  TreeNode* n9 = new TreeNode(9);
  node_vec.push_back(n9);

  n5->left = n3;
  n5->right = n8;
  n3->left = n1;
  n3->right = n4;
  n8->left = n7;
  n8->right = n9;

  TreeNode* res = nullptr;
  res = Find(n5, n7, n9);
  cout << "expected: " << n8->val << ", actual: " << res->val << endl;
  res = Find(n5, n1, n9);
  cout << "expected: " << n5->val << ", actual: " << res->val << endl;
  res = Find(n5, n1, n3);
  cout << "expected: " << n3->val << ", actual: " << res->val << endl;
}
