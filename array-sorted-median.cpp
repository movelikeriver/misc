// From https://oj.leetcode.com/problems/median-of-two-sorted-arrays/
//
// Median of Two Sorted Arrays
//
// There are two sorted arrays A and B of size m and n
// respectively. Find the median of the two sorted arrays (from small
// to large). The overall run time complexity should be O(log (m+n)).

#include <iostream>
using namespace std;

class Solution {
public:
  // the basic idea is the binary search.  look for the rank of A-mid
  // in array B, if the rank is bigger than median, it means that the
  // median should be between A-s1 and A-mid, then set A-mid = (A-s1 +
  // A-mid) / 2, try to look for the rank in array B again, until find
  // the median.
  double findMedianSortedArrays(int A[], int m, int B[], int n) {
    if (m == 0) {
      return B[n/2];
    }
    if (n == 0) {
      return A[m/2];
    }

    int rank = (m + n + 1) / 2;
    bool is_even = ((m+n) % 2) == 0;
    int s1 = 0;
    int e1 = m-1;
    int s2 = 0;
    int e2 = n-1;
    int cur = (s1+e1+1)/2;

    while (s1 < e1 - 1) {
      int idx = FindRank(B, s2, e2, A[cur]);
      if (cur + idx + 1 == rank) {
	return A[cur];
      }
      if (cur + idx > rank) {
	// the median should be in left part.
	e1 = cur;
	cur = (s1 + e1 + 1) / 2;
	e2 = idx;
      } else {
	// the median should be in right part.
	s1 = cur;
	cur = (s1 + e1 + 1) / 2;
	s2 = idx;
      }
    }
    int t = A[s1];
    while (s1 + s2 < rank) {
      if (A[s1] < B[s2]) {
	s1++;
	t = A[s1];
      } else {
	s2++;
	t = B[s2];
      }
    }
    return t;
  }
    
  // find the rank of t in sorted array arr[].
  int FindRank(int arr[], int start, int end, int t) {
    int l = start;
    int h = end;
    while (l < h - 1) {
      int m = (l + h) / 2;
      if (arr[m] == t) {
	return m + 1;
      }
      if (arr[m] > t) {
	h = m;
      } else {
	l = m;
      }
    }
    if (arr[l] > t) {
      return l;
    }
    return h + 1;
  }
};

int main() {
  cout << "FindRank()\n";
  // FindRank()
  {
    int A[] = {1, 3, 5, 7};
    Solution s;
    int idx = s.FindRank(A, 0, sizeof(A)/sizeof(A[0]), 4);
    cout << idx << endl;
  }
  {
    int A[] = {1, 3, 5};
    Solution s;
    int idx = s.FindRank(A, 0, sizeof(A)/sizeof(A[0]), 4);
    cout << idx << endl;
    idx = s.FindRank(A, 0, sizeof(A)/sizeof(A[0]), 6);
    cout << idx << endl;
    idx = s.FindRank(A, 0, sizeof(A)/sizeof(A[0]), 0);
    cout << idx << endl;
    idx = s.FindRank(A, 0, sizeof(A)/sizeof(A[0]), 2);
    cout << idx << endl;
  }

  cout << "findMedianSortedArrays()\n";
  // findMedianSortedArrays()
  {
    int A[] = {1, 3, 5, 6, 8, 10, 12};
    int B[] = {2, 3, 5, 6, 9, 21};
    Solution s;
    double v = s.findMedianSortedArrays(A, sizeof(A)/sizeof(A[0]),
					B, sizeof(B)/sizeof(B[0]));
    cout << v << endl;
  }
  {
    int A[] = {};
    int B[] = {1};
    Solution s;
    double v = s.findMedianSortedArrays(A, sizeof(A)/sizeof(A[0]),
					B, sizeof(B)/sizeof(B[0]));
    cout << v << endl;
  }
  {
    int A[] = {};
    int B[] = {2, 3};
    Solution s;
    double v = s.findMedianSortedArrays(A, sizeof(A)/sizeof(A[0]),
					B, sizeof(B)/sizeof(B[0]));
    cout << v << endl;
  }
}
