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
// See sumNumbers() as solution.
//
// From https://oj.leetcode.com/problems/path-sum-ii/
// Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
// For example:
// Given the below binary tree and sum = 22,
//
//              5
//             / \
//            4   8
//           /   / \
//          11  13  4
//         /  \    / \
//        7    2  5   1
//
// return
//
// [
//  [5,4,11,2],
//  [5,8,4,5]
// ]
//
// See pathSum() as solution.
//
// Run:
//  g++ --std=c++11 bin-tree-sum-root.cpp
//  ./a.out

#include <iostream>
#include <vector>

#include "bin-tree-util.h"

using namespace std;


class Solution {
public:
  int sumNumbers(TreeNode *root) {
    vector<int> leaves;
    SumTravel(root, 0, &leaves);
    int s = 0;
    for (int v : leaves) {
      cout << v << endl;
      s += v;
    }
    return s;
  }

  vector<vector<int> > pathSum(TreeNode *root, int sum) {
    vector<vector<int> > res;
    vector<int> leaves;
    PathTravel(root, 0, sum, &leaves, &res);
    return res;
  }

private:
  // assume there's no overflow.
  void SumTravel(TreeNode* root, int curr_val, vector<int>* leaves) {
    if (root == nullptr) {
      return;
    }
    if (root->left == nullptr && root->right == nullptr) {
      leaves->push_back(curr_val * 10 + root->val);
      return;
    }
    SumTravel(root->left, curr_val*10 + root->val, leaves);
    SumTravel(root->right, curr_val*10 + root->val, leaves);
  }

  // assume there's no overflow.
  void PathTravel(TreeNode* root, int curr_val, int sum,
		  vector<int>* leaves, vector<vector<int> >* res) {
    if (root == nullptr) {
      return;
    }
    if (root->left == nullptr && root->right == nullptr) {
      if (curr_val + root->val == sum) {
	leaves->push_back(root->val);
	res->push_back(*leaves);
	leaves->pop_back();
      }
      return;
    }

    leaves->push_back(root->val);
    PathTravel(root->left, curr_val + root->val, sum, leaves, res);
    PathTravel(root->right, curr_val + root->val, sum, leaves, res);
    leaves->pop_back();
  }
};


void TestSumNumbers() {
  vector<TreeNode*> vec;
  TreeNode* n1 = AddNewNode(1, &vec);
  TreeNode* n2 = AddNewNode(2, &vec);
  TreeNode* n3 = AddNewNode(3, &vec);
  TreeNode* n4 = AddNewNode(4, &vec);
  TreeNode* n5 = AddNewNode(5, &vec);
  TreeNode* n6 = AddNewNode(6, &vec);
  n1->left = n2;
  n1->right = n3;
  n2->left = n4;
  n2->right = n5;
  n3->right = n6;

  Solution s;
  int sum = s.sumNumbers(n1);
  cout << "Total sum: " << sum << endl;

  DeleteTree(&vec);
}

void TestPathSum() {
  vector<TreeNode*> vec;
  TreeNode* n1 = AddNewNode(1, &vec);
  TreeNode* n2 = AddNewNode(2, &vec);
  TreeNode* n41 = AddNewNode(4, &vec);
  TreeNode* n42 = AddNewNode(4, &vec);
  TreeNode* n51 = AddNewNode(5, &vec);
  TreeNode* n52 = AddNewNode(5, &vec);
  TreeNode* n7 = AddNewNode(7, &vec);
  TreeNode* n8 = AddNewNode(8, &vec);
  TreeNode* n11 = AddNewNode(11, &vec);
  TreeNode* n13 = AddNewNode(13, &vec);
  n51->left = n41;
  n51->right = n8;
  n41->left = n11;
  n11->left = n7;
  n11->right = n2;
  n8->left = n13;
  n8->right = n42;
  n42->left = n52;
  n42->right = n1;

  Solution s;
  vector<vector<int> > paths = s.pathSum(n51, 22);
  for (auto& path : paths) {
    for (int i : path) {
      cout << i << ", ";
    }
    cout << "\n";
  }

  DeleteTree(&vec);
}

int main() {
  // TestSumNumbers();
  TestPathSum();
}
