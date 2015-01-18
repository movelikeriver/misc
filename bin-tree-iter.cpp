// Implement an iterator over a binary search tree (BST). Your
// iterator will be initialized with the root node of a BST.
//
// Calling next() will return the next smallest number in the BST.
//
// Note: next() and hasNext() should run in average O(1) time and uses
// O(h) memory, where h is the height of the tree.
//
// From: https://oj.leetcode.com/problems/binary-search-tree-iterator/
//
//
// Run:
//  g++ bin-tree-iter.cpp
//  ./a.out

#include <iostream>
#include <stack>
#include <vector>

#include "bin-tree-util.h"

using namespace std;


// Returns true if this binary tree is a BST.
bool IsBST(TreeNode* node, int prev_val) {
  if (node->left) {
    if (!IsBST(node->left, prev_val)) {
      return false;
    }
  }
  if (node->val < prev_val) {
    return false;
  }
  prev_val = node->val;
  if (node->right) {
    if (!IsBST(node->right, prev_val)) {
      return false;
    }
  }
  return true;
}

class BSTIterator {
public:
  BSTIterator(TreeNode *root) {
    TreeNode* p = root;
    while (p) {
      s_.push(p);
      p = p->left;
    }
  }

  // @return whether we have a next smallest number
  bool hasNext() {
    return !s_.empty();
  }

  // @return the next smallest number
  int next() {
    TreeNode* node = s_.top();
    s_.pop();
    if (node->right) {
      TreeNode* p = node->right;
      while (p) {
	s_.push(p);
	p = p->left;
      }
    }

    return node->val;
  }

  static void Travel(TreeNode* root, vector<int>* v) {
    if (root->left) {
      Travel(root->left, v);
    }
    v->push_back(root->val);
    if (root->right) {
      Travel(root->right, v);
    }
  }

private:
  stack<TreeNode*> s_;
};

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

  cout << "IsBST=" << IsBST(n5, -1) << endl;

  vector<int> ret;
  BSTIterator::Travel(n5, &ret);

  cout << "Travel the tree:\n";
  for (int i = 0; i < ret.size(); i++) {
    cout << ret[i] << ", ";
  }
  cout << endl;

  cout << "BSTIterator:\n";
  BSTIterator it(n5);
  while(it.hasNext()) {
    cout << it.next() << ", ";
  }
  cout << endl;
  
  for (int i = 0; i < node_vec.size(); i++) {
    delete node_vec[i];
  }
}
