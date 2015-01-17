// From https://oj.leetcode.com/problems/maximum-subarray/
//
// Find the contiguous subarray within an array (containing at least one number) which has the largest sum.
//
// For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
// the contiguous subarray [4,−1,2,1] has the largest sum = 6. 
//
// 

#include <iostream>
using namespace std;

class Solution {
public:
  int maxSubArray(int A[], int n) {
    if (n <= 0) {
      return 0;
    }
    int v = A[0];
    int curr_max = v;
    for (int i = 1; i < n; i++) {
      int a = A[i];

      // for minus value, just find the first positive or the biggest negative element.
      if (v < 0) {
	if (a > v) {
	  v = a;
	  if (v > curr_max) {
	    curr_max = v;
	  }
	}
	continue;
      }

      // the basic idea of O(n) processing is: keep adding elements
      // and getting the sum, if the sum keeps positive, just updating
      // the curr_max, once the sum becomes negative from positive, it
      // means that it can't add more value by adding with following
      // elements, then just start the next round of processing.
      if (v + a < 0) {
	if (v > curr_max) {
	  curr_max = v;
	}
	v = a;
	continue;
      }

      v += a;
      if (v > curr_max) {
	curr_max = v;
      }
    }
    return curr_max;
  }
};

int main() {
  Solution s;
  {
    int arr[] = {-2,1,-3,4,-1,2,1,-5,4};
    cout << s.maxSubArray(arr, sizeof(arr)/sizeof(arr[0])) << endl;
  }
  {
    int arr[] = {-2};
    cout << s.maxSubArray(arr, sizeof(arr)/sizeof(arr[0])) << endl;
  }
  {
    int arr[] = {-2, 1};
    cout << s.maxSubArray(arr, sizeof(arr)/sizeof(arr[0])) << endl;
  }
}
