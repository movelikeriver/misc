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
	AdjustHeap();
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

private:
  // Heap sort approach, move the smallest element to the top of heap.
  void AdjustHeap() {
    int i = (vec_.size() % 2) ? ((vec_.size()-3) / 2) : ((vec_.size()-2) / 2);
    // Image the array as heap like below:
    //
    //    0
    //  1   2
    // 3 4 5 6
    //
    // Start from the parent of largest leaf nodes to the top.
    bool is_last = true;
    for (; i >= 0; i--) {
      int left = i * 2 + 1;
      int right = i * 2 + 2;
      int target = left;
      if (!is_last || right < vec_.size()) {
	if (vec_[left] > vec_[right]) {
	  target = right;
	}
      } else {
        if (is_last) {
	  is_last = false;
	}
      }

      if (vec_[i] > vec_[target]) {
	SwapVec(i, target);
      }
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
