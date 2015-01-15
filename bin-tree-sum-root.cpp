// From https://oj.leetcode.com/problems/sum-root-to-leaf-numbers/
// Given a binary tree containing digits from 0-9 only, each
// root-to-leaf path could represent a number.
//
// An example is the root-to-leaf path 1->2->3 which represents the
// number 123.  Find the total sum of all root-to-leaf numbers.
//
// For example,
//
//    1
//   / \
//  2   3
//
// The root-to-leaf path 1->2 represents the number 12.
// The root-to-leaf path 1->3 represents the number 13.
//
// Return the sum = 12 + 13 = 25.
//
// Run:
//  g++ --std=c++11 bin-tree-sum-root.cpp
//  ./a.out

#include <iostream>
#include <vector>
using namespace std;

// Definition for binary tree
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class Solution {
public:
  int sumNumbers(TreeNode *root) {
    vector<int> leaves;
    sum(root, 0, &leaves);
    int s = 0;
    for (int v : leaves) {
      cout << v << endl;
      s += v;
    }
    return s;
  }

private:
  // assume there's no overflow.
  void sum(TreeNode* root, int curr_val, vector<int>* leaves) {
    if (root == nullptr) {
      return;
    }
    if (root->left == nullptr && root->right == nullptr) {
      leaves->push_back(curr_val * 10 + root->val);
      return;
    }
    sum(root->left, curr_val*10 + root->val, leaves);
    sum(root->right, curr_val*10 + root->val, leaves);
  }
};


int main() {
  vector<TreeNode*> vec;
  TreeNode* n1 = new TreeNode(1);
  TreeNode* n2 = new TreeNode(2);
  TreeNode* n3 = new TreeNode(3);
  TreeNode* n4 = new TreeNode(4);
  TreeNode* n5 = new TreeNode(5);
  TreeNode* n6 = new TreeNode(6);
  n1->left = n2;
  n1->right = n3;
  n2->left = n4;
  n2->right = n5;
  n3->right = n6;
  vec.push_back(n1);
  vec.push_back(n2);
  vec.push_back(n3);
  vec.push_back(n4);
  vec.push_back(n5);
  vec.push_back(n6);

  Solution s;
  int sum = s.sumNumbers(n1);
  cout << "Total sum: " << sum << endl;

  for (int i = 0; i < vec.size(); i++) {
    delete vec[i];
  }
}
