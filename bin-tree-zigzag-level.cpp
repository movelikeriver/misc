// From https://oj.leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
//
// Binary Tree Zigzag Level Order Traversal
//
// Given a binary tree, return the zigzag level order traversal of its
// nodes' values. (ie, from left to right, then right to left for the
// next level and alternate between).
//
// For example:
// Given binary tree {3,9,20,#,#,15,7},
//
//    3
//   / \
//  9  20
//    /  \
//   15   7
//
//  return its zigzag level order traversal as:
//
// [
//  [3],
//  [20,9],
//  [15,7]
// ]
//
// Run:
//  g++ --std=c++11 bin-tree-zigzag-level.cpp
//  ./a.out

#include <iostream>
#include <queue>
#include <vector>

#include "bin-tree-util.h"

using namespace std;

 
class Solution {
public:
  vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
    vector<vector<int> > res;
    if (root == nullptr) {
      return res;
    }

    queue<TreeNode*> s1;
    queue<TreeNode*> s2;
    queue<TreeNode*>* p1 = &s1;
    queue<TreeNode*>* p2 = &s2;
    bool reverse = false;

    p1->push(root);

    while (!p1->empty()) {
      vector<int> v;
      while (!p1->empty()) {
	TreeNode* nd = p1->front();
	p1->pop();
	v.push_back(nd->val);

	if (nd->left) {
	  p2->push(nd->left);
	}
	if (nd->right) {
	  p2->push(nd->right);
	}
      }
      std::swap(p1, p2);

      if (reverse) {
	std::reverse(v.begin(), v.end());
      }
      res.push_back(v);
      reverse = !reverse;
    }
    return res;
  }
};

void TestZigzagLevelOrder(const vector<int>& input_vec) {
  vector<TreeNode*> tree_vec;
  TreeNode* root = ArrayToTree(input_vec, &tree_vec);

  Solution s;
  vector<vector<int> > levels = s.zigzagLevelOrder(root);

  for (auto& level : levels) {
    for (int v : level) {
      cout << v << ", ";
    }
    cout << "\n";
  }
  DeleteTree(&tree_vec);
}

int main() {
  {
    int arr[] = {3,9,20,kNull,kNull,15,7};
    vector<int> input_vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
    TestZigzagLevelOrder(input_vec);
  }
  {
    int arr[] = {1,2,3,4,kNull,kNull,5};
    vector<int> input_vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
    TestZigzagLevelOrder(input_vec);
  }
}
