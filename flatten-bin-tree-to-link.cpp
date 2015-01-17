// From https://oj.leetcode.com/problems/flatten-binary-tree-to-linked-list/
//
/**********
Given a binary tree, flatten it to a linked list in-place.

  For example,
Given

         1
        / \
       2   5
      / \   \
     3   4   6

  The flattened tree should look like:

   1
    \
     2
      \
       3
        \
         4
          \
           5
            \
             6

**********/

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

class Solution {
public:
  void flatten(TreeNode *root) {
    Process(root);
  }

private:
  // The main idea is to recursively process the tree from leaf to
  // node. If a node has leaf children only, it would be very easy to
  // process: just to make the node->right as right child of
  // node->left, then move node->left to node->right. After recursive
  // function call, Once we have tree like:
  //
  //     R
  //  A     B   
  //   O     O
  //    O     O
  //     O     O
  //      O
  //       C
  //
  // We need to find the rightest leaf node of A (the result is C),
  // and move B as the right child of C, then move A from R->left to
  // R->right.

  void Process(TreeNode* node) {
    if (node == nullptr) {
      return;
    }
    if (node->left != nullptr && node->right != nullptr) {
      Process(node->left);
      Process(node->right);
      TreeNode* r = FindRight(node->left);
      r->right = node->right;
      node->right = node->left;
      node->left = nullptr;
      return;
    }
    if (node->right == nullptr) {
      node->right = node->left;
      node->left = nullptr;
    }
    if (node->right) {
      Process(node->right);
      return;
    }
  }
    
  TreeNode* FindRight(TreeNode* root) {
    while (root->right) {
      root = root->right;
    }
    return root;
  }
};

void TestFlatten(const vector<int>& input_vec) {
  vector<TreeNode*> tree_vec;
  TreeNode* root = ArrayToTree(input_vec, &tree_vec);

  string str = PrintTree(root);
  cout << str << endl;

  Solution s;
  s.flatten(root);
  str = PrintTree(root);
  cout << str << endl;
}

int main() {
  {
    int arr[] = {3,9,20,kNull,kNull,15,7};
    vector<int> input_vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
    TestFlatten(input_vec);
  }
}
