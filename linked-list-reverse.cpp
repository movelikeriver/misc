// Revert a linked-list.
//

#include <iostream>
#include <vector>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

void PrintListNode(ListNode* p1) {
  while (p1 != nullptr) {
    cout << p1->val << "-->";
    p1 = p1->next;
  }
  cout << endl;
}

ListNode* AddNode(int val) {
  ListNode* p = new ListNode(val);
  return p;
}

ListNode* CreateList(const vector<int>& input_vec) {
  ListNode* head = nullptr;
  ListNode* p = nullptr;
  for (int v : input_vec) {
    ListNode* nd = AddNode(v);
    if (p == nullptr) {
      p = nd;
      head = p;
    } else {
      p->next = nd;
      p = p->next;
    }
  }
  return head;
}

void Delete(ListNode* head) {
  ListNode* p = head;
  while (p) {
    ListNode* tmp = p;
    p = p->next;
    delete tmp;
  }
}
 
class Solution {
public:
  // ... (head --> ... --> ... ) --> tail ...
  //   === revert head to tail ===>
  // ... (tail --> ... --> ... ) --> tail ...
  ListNode* reverseList(ListNode* head, ListNode* tail) {
    if (head == tail) {
      return head;
    }
    ListNode* p1 = head;
    ListNode* p2 = nullptr;
    while (p1->next != tail) {
      //   ... <-- p2     p1 --> p3 --> ...
      //       === convert to ===>
      //   ... <-- p2 <-- p1     p3 --> ...
      ListNode* p3 = p1->next;
      p1->next = p2;
      p2 = p1;
      p1 = p3;
    }
    p1->next = p2;
    return p1;
  }

  ListNode *reverseKGroup(ListNode *head, int k) {
    ListNode* newhead = head;
    ListNode* head2 = nullptr;
    while (true) {
      // maintain pointers: head, tail, head2, tail2:
      //
      // ... head2 --> (head --> ... --> tail) --> tail2 ...
      //   === revert head to tail ===>
      // ... head2 --> (tail --> ... --> head) --> tail2 ...
      //
      // only tail2 can be nullptr.
      ListNode* tail;
      if (!Skip(head, k, &tail)) {
	break;
      }
      cout << "revert: " << "(" << head->val << ", " << tail->val << ")" << endl;

      ListNode* tail2 = tail->next;
      reverseList(head, tail2);

      head->next = tail2;
      if (head2 == nullptr) {
	head2 = tail;
	newhead = tail;
      } else {
	head2->next = tail;
      }

      head2 = head;
      head = tail2;
    }
    return newhead;
  }

private:
  // number of range [head, tail] is k, including head and tail.
  bool Skip(ListNode* head, int k, ListNode** tail) {
    if (head == nullptr) {
      return false;
    }
    for (; k > 1; k--) {
      head = head->next;
      if (head == nullptr) {
	// not enough elements for this skip.
	return false;
      }
    }
    *tail = head;
    return true;
  }
};

void TestListNode(const vector<int>& vec) {
  ListNode* head = CreateList(vec);
  PrintListNode(head);
  Solution s;
  ListNode* p = s.reverseList(head, nullptr);
  PrintListNode(p);

  Delete(p);
}

void TestReverseGroup(const vector<int>& vec, int k) {
  ListNode* head = CreateList(vec);
  PrintListNode(head);
  Solution s;
  ListNode* newhead = s.reverseKGroup(head, 3);
  PrintListNode(newhead);
  Delete(newhead);
}

int main() {
  {
    int arr[] = {1, 2, 3, 4, 5, 6};
    vector<int> vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
    TestReverseGroup(vec, 3);
  }

  {
    int arr[] = {1};
    vector<int> vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
    TestReverseGroup(vec, 2);
  }

  {
    int arr[] = {1, 2};
    vector<int> vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
    TestListNode(vec);
  }

}
