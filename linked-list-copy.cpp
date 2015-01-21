// From https://oj.leetcode.com/problems/copy-list-with-random-pointer/
//
// Copy List with Random Pointer
//
// A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.
//
// Return a deep copy of the list. 


#include <iostream>
#include <unordered_map>
using namespace std;

// Definition for singly-linked list with a random pointer.
struct RandomListNode {
  int label;
  RandomListNode *next, *random;
  RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

class Solution {
public:
  RandomListNode *copyRandomList(RandomListNode *head) {
    // the basic idea is 1) to copy all the nodes from original list
    // to a new list, make the random pointer to point to the
    // corespond node in original list, then 2) to travel the new list
    // again, and copy the random pointers.
    unordered_map<RandomListNode*, RandomListNode*> m;
    RandomListNode* head2 = CopyList(head, &m);
    SetRandom(head, m);
    return head2;
  }
    
  void Insert(RandomListNode* k, RandomListNode* v, unordered_map<RandomListNode*, RandomListNode*>* m) {
    if (m->count(k) == 0) {
      (*m)[k] = v;
    }
  }
    
  RandomListNode* CopyList(RandomListNode* head, unordered_map<RandomListNode*, RandomListNode*>* m) {
    if (head == nullptr) {
      return nullptr;
    }
    RandomListNode* head2 = nullptr;
    RandomListNode* p = nullptr;
    while (head) {
      RandomListNode* tmp = new RandomListNode(head->label);
      Insert(head, tmp, m);
            
      if (head2 == nullptr) {
	head2 = tmp;
      } else {
	p->next = tmp;
      }
      p = tmp;
      head = head->next;
    }
    p->next = nullptr;  // last one
    return head2;
  }
    
  void SetRandom(RandomListNode* head, const unordered_map<RandomListNode*, RandomListNode*>& m) {
    while (head) {
      if (head->random == nullptr) {
	m.find(head)->second->random = nullptr;
      } else {
	m.find(head)->second->random = m.find(head->random)->second;
      }
      head = head->next;   
    }
  }
};

int main() {
}
