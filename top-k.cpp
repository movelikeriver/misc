// Top K problem's heap implementation.
//
// Run:
//   g++ --std=c++11 top-k.cpp
//   ./a.out

#include <iostream>
#include <vector>
using namespace std;

class TopK {
public:
  explicit TopK(int n) {
    if (n <= 0) {
      cout << "n has to be positive." << endl;
      return;
    }
    vec_.reserve(n);
  }

  void Add(int val) {
    if (vec_.capacity() > vec_.size()) {
      vec_.push_back(val);
      if (vec_.capacity() == vec_.size()) {
	InitHeap();
	cout << "InitHeap() done!" << endl;
	PrintAsHeap();
      }
      return;
    }

    if (vec_[0] >= val) {
      cout << "Skip " << val << endl;
      return;
    }

    vec_[0] = val;
    AdjustHeap();
  }

  void Print() {
    for (int v : vec_) {
      cout << v << ", ";
    }
    cout << endl;
  }

  void PrintAsHeap() {
    int cut = 0;
    for (int i = 0; i < vec_.size(); i++) {
      cout << vec_[i] << " ";
      if (i == cut) {
	// move to a new line
	cout << "\n";
	cut = (cut + 1) * 2;
      }
    }
    cout << endl;
  }

private:
  // Heap sort approach, move the smallest element to the top of heap.
  // Less than O(log(n) * n)
  void InitHeap() {
    // Image the array as heap like below:
    //
    //    0
    //  1   2
    // 3 4 5 6
    //
    // Start from the parent of largest leaf nodes to the top.
    int end = (vec_.size() % 2) ? (vec_.size()-3)/2 : (vec_.size()-2)/2;
    // i is per level, for each round, the smallest element will be
    // set on the i-index, then narrow the range as from next level to
    // the end. Level by level, until the last 2nd level.
    for (int i = 0; i < end; i = i*2 + 1) {
      // create heap, each node should be smaller than left and right
      // children. Process the heap from bottom to top, then the
      // smallest one will be selected.
      for (int j = end; j >= i; j--) {
	int left = j*2 + 1;
	int right = j*2 + 2;
	int target = left;
	if (j != end || right < vec_.size()) {
	  if (vec_[right] < vec_[left]) {
	    target = right;
	  }
	}
	if (vec_[j] > vec_[target]) {
	  SwapVec(j, target);
	}
      }
    }
  }

  // Less than O(log(n))
  void AdjustHeap() {
    int i = 0;
    int left = i*2 + 1;
    int right = i*2 + 2;

    while (left < vec_.size()) {
      int target = left;
      if (right < vec_.size() && vec_[right] < vec_[left]) {
	target = right;
      }
      if (vec_[i] < vec_[target]) {
	// adjust done
	break;
      }
      SwapVec(i, target);
      i = target;
      left = i*2 + 1;
      right = i*2 + 2;
    }
  }

  void SwapVec(int a, int b) {
    int tmp = vec_[a];
    vec_[a] = vec_[b];
    vec_[b] = tmp;
  }

  vector<int> vec_;
};

int main() {
  TopK top_k(5);
  int arr[] = {2, 4, 5, 6, 77, 65, 34, 32, 87, 23, 44, 56, 21, 189, 54, 2, 1, 234, 5, 1, 3, 102};
  for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
    top_k.Add(arr[i]);
  }

  top_k.Print();
}
