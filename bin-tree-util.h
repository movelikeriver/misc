#ifndef BIN_TREE_UTIL_H
#define BIN_TREE_UTIL_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

static const int kNull = -1;

// Definition for binary tree
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* AddNewNode(int val, vector<TreeNode*>* vec) {
  TreeNode* n = (val != kNull) ? new TreeNode(val) : nullptr;
  vec->push_back(n);
  return n;
}

void DeleteTree(vector<TreeNode*>* vec) {
  for (int i = 0; i < vec->size(); i++) {
    delete (*vec)[i];
  }
}

string PrintTree(TreeNode* root) {
  if (root == nullptr) {
    return "";
  }
  return (std::to_string(root->val) + "(" + PrintTree(root->left) + ", " +
	  PrintTree(root->right) + ") ");
}
 
TreeNode* ArrayToTree(const vector<int>& vec, vector<TreeNode*>* nodes) {
  nodes->clear();
  if (vec.empty()) {
    return nullptr;
  }

  for (int v : vec) {
    AddNewNode(v, nodes);
  }
  for (int i = 0; i < nodes->size(); ++i) {
    int left = i * 2 + 1;
    int right = i * 2 + 2;
    if (left < nodes->size()) {
      (*nodes)[i]->left = (*nodes)[left];
    }
    if (right < nodes->size()) {
      (*nodes)[i]->right = (*nodes)[right];
    }
  }
  return (*nodes)[0];
}

#endif  // BIN_TREE_UTIL_H
