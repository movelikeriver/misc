// Given a binary tree, connect all the sibling nodes, see the "->" in
// the example below.
//
//        1
//    2  ->  3
// 4 -> 5  ->  6
//
// Run:
//  g++ --std=c++11 bin-tree-sibling.cpp
//  ./a.out

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
  Node(int i) : id(i), left(nullptr), right(nullptr) {}
  int id;
  Node* left;
  Node* right;
  Node* next;
};

void Print(Node* root) {
  if (root == nullptr) {
    return;
  }
  cout << root->id << ": " << ((root->next) ? root->next->id : 0)
       << "\n";
  Print(root->left);
  Print(root->right);
}

class BinTreeSibling {
public:
void SiblingTwoQueues(Node* root) {
  // use two queues, one queue holds the nodes in the same level. While processing the 1st queue, adding the children to 2nd queue.
  queue<Node*> s1, s2;
  queue<Node*>* p1 = &s1;
  queue<Node*>* p2 = &s2;

  p1->push(root);
  while (!p1->empty()) {
    queue<Node*>* tmp = p1;
    p1 = p2;
    p2 = tmp;

    // process the nodes in p2.
    Node* last = nullptr;
    while (!p2->empty()) {
      Node* nd = p2->front();
      p2->pop();
      nd->next = last;
      last = nd;
      // add children for the next round.
      if (nd->right) {
	p1->push(nd->right);
      }
      if (nd->left) {
	p1->push(nd->left);
      }
    }
  }
}

void SiblingConstantSpace(Node* root) {
  Node* p1 = root;
  Node* p2 = FindFirstChild(p1);
  // process from top to buttom, then we can use the next pointer in
  // parent level to find the sibling in the child level.
  while (p2) {
    ProcessLevel(p1, p2);
    p1 = p2;
    p2 = FindFirstChild(p1);
  }
}

private:
  // find the first child node in next level. p1 has to be processed already.
  Node* FindFirstChild(Node* p1) {
    while (p1) {
      if (p1->left) {
	return p1->left;
      }
      if (p1->right) {
	return p1->right;
      }
      p1 = p1->next;
    }
    return nullptr;
  }

  // p1 is p2's parent level
  void ProcessLevel(Node* p1, Node* p2) {  
    while (p1) {
      if (p1->left && p1->left != p2) {
	p2->next = p1->left;
	p2 = p2->next;
      }
      if (p1->right && p1->right != p2) {
	p2->next = p1->right;
	p2 = p2->next;
      }
      p1 = p1->next;
    }
  }
};

int main() {
  vector<Node*> vec;
  Node* n1 = new Node(1);
  Node* n2 = new Node(2);
  Node* n3 = new Node(3);
  Node* n4 = new Node(4);
  Node* n5 = new Node(5);
  Node* n6 = new Node(6);
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

  BinTreeSibling bts;
  // bts.SiblingConstantSpace(n1);
  bts.SiblingTwoQueues(n1);
  Print(n1);

  for (int i = 0; i < vec.size(); i++) {
    delete vec[i];
  }
}
