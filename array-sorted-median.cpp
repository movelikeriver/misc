// From https://oj.leetcode.com/problems/median-of-two-sorted-arrays/
//
// Median of Two Sorted Arrays
//
// There are two sorted arrays A and B of size m and n
// respectively. Find the median of the two sorted arrays (from small
// to large). The overall run time complexity should be O(log (m+n)).

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  double findMedianSortedArrays(int A[], int m, int B[], int n) {
    if (m == 0 && n == 0) {
      return 0;
    }

    vector<int> arr1(A, A+m);
    vector<int> arr2(B, B+n);
    if (m > n) {
      return FindMedian(arr2, arr1);
    }
    return FindMedian(arr1, arr2);
  }

  // arr1.size() <= arr2.size(), the benefit to have vector instead of
  // array is to catch out-of-bound error if anything wrong in the index.
  double FindMedian(const vector<int>& arr1, const vector<int>& arr2) {
    int n1 = arr1.size();
    int n2 = arr2.size();
    int start = 0;
    int end = n1;
    int half = (n1+n2+1)/2;
    while (start <= end) {
      int m1 = (start + end) / 2;
      int m2 = half - m1;
      // Image the arrays are like below:
      //
      // 1 3(m1) 5
      // 2 4(m2) 6
      //
      // 1 3(m1) 5
      // 2 4 6(m2) 8
      //
      // The basic idea is to binary in arr1, until it reaches the
      // bound. The binary is to compare m1,m1+1 and m2-1,m2, if m1>m2,
      // it means that the median should be left of m1, if
      // (m2-1)>(m1+1), it means the median should be in right of m1+1.
      // The trick is to deal with the odd and even number of size.
      if (m1>0 && m2<n2 && arr1[m1-1]>arr2[m2]) {
	end = m1-1;
	continue;
      }
      if (m2>0 && m1<n1 && arr1[m1]<arr2[m2-1]) {
	start = m1+1;
	continue;
      }

      cout << "m1, m2 = " << m1 << ", " << m2 << endl;

      int v1;
      if (m1 == 0) {
	v1 = arr2[m2-1];
      } else if (m2 == 0) {
	v1 = arr1[m1-1];
      } else {
	v1 = max(arr1[m1-1], arr2[m2-1]);
      }
      if ((n1+n2) % 2 == 1) {
	return v1;
      }

      int v2;
      if (m1 == n1) {
	v2 = arr2[m2];
      } else if (m2 == n2) {
	v2 = arr1[m1];
      } else {
	v2 = min(arr1[m1], arr2[m2]);
      }

      return (float)(v1+v2)/2;
    }

    cout << "should never happen...\n";
    return -1;
  }
};

int main() {
  cout << "findMedianSortedArrays()\n";
  // findMedianSortedArrays()
  {
    int A[] = {1, 3, 5, 6, 8, 10, 12};
    int B[] = {2, 3, 5, 6, 9, 21};
    Solution s;
    double v = s.findMedianSortedArrays(A, sizeof(A)/sizeof(A[0]),
					B, sizeof(B)/sizeof(B[0]));
    cout << "6 == " << v << endl;
  }
  {
    int A[] = {};
    int B[] = {1};
    Solution s;
    double v = s.findMedianSortedArrays(A, sizeof(A)/sizeof(A[0]),
					B, sizeof(B)/sizeof(B[0]));
    cout << "1 == " << v << endl;
  }
  {
    int A[] = {};
    int B[] = {2, 3};
    Solution s;
    double v = s.findMedianSortedArrays(A, sizeof(A)/sizeof(A[0]),
					B, sizeof(B)/sizeof(B[0]));
    cout << "2.5 == " << v << endl;
  }
  {
    int A[] = {};
    int B[] = {1, 1};
    Solution s;
    double v = s.findMedianSortedArrays(A, sizeof(A)/sizeof(A[0]),
					B, sizeof(B)/sizeof(B[0]));
    cout << "1 == " << v << endl;
  }
  {
    int A[] = {1, 2};
    int B[] = {1, 2};
    Solution s;
    double v = s.findMedianSortedArrays(A, sizeof(A)/sizeof(A[0]),
					B, sizeof(B)/sizeof(B[0]));
    cout << "1.5 == " << v << endl;
  }
  {
    int A[] = {1, 1};
    int B[] = {1, 2};
    Solution s;
    double v = s.findMedianSortedArrays(A, sizeof(A)/sizeof(A[0]),
					B, sizeof(B)/sizeof(B[0]));
    cout << "1 == " << v << endl;
  }
  {
    int A[] = {1, 1, 3, 3};
    int B[] = {1, 1, 3, 3};
    Solution s;
    double v = s.findMedianSortedArrays(A, sizeof(A)/sizeof(A[0]),
					B, sizeof(B)/sizeof(B[0]));
    cout << "2 == " << v << endl;
  }
  {
    int A[] = {2};
    int B[] = {1, 3};
    Solution s;
    double v = s.findMedianSortedArrays(A, sizeof(A)/sizeof(A[0]),
					B, sizeof(B)/sizeof(B[0]));
    cout << "2 == " << v << endl;
  }
  {
    int A[] = {2};
    int B[] = {1, 3, 4};
    Solution s;
    double v = s.findMedianSortedArrays(A, sizeof(A)/sizeof(A[0]),
					B, sizeof(B)/sizeof(B[0]));
    cout << "2.5 == " << v << endl;
  }
  {
    int A[] = {1};
    int B[] = {2, 3, 4};
    Solution s;
    double v = s.findMedianSortedArrays(A, sizeof(A)/sizeof(A[0]),
					B, sizeof(B)/sizeof(B[0]));
    cout << "2.5 == " << v << endl;
  }
  {
    int A[] = {1, 4};
    int B[] = {2, 3};
    Solution s;
    double v = s.findMedianSortedArrays(A, sizeof(A)/sizeof(A[0]),
					B, sizeof(B)/sizeof(B[0]));
    cout << "2.5 == " << v << endl;
  }
  {
    int A[] = {1, 2, 2};
    int B[] = {1, 2, 3};
    Solution s;
    double v = s.findMedianSortedArrays(A, sizeof(A)/sizeof(A[0]),
					B, sizeof(B)/sizeof(B[0]));
    cout << "2 == " << v << endl;
  }
  {
    int A[] = {1, 2, 3};
    int B[] = {1, 2, 2};
    Solution s;
    double v = s.findMedianSortedArrays(A, sizeof(A)/sizeof(A[0]),
					B, sizeof(B)/sizeof(B[0]));
    cout << "2 == " << v << endl;
  }
  {
    int A[] = {4};
    int B[] = {1, 2, 3, 5};
    Solution s;
    double v = s.findMedianSortedArrays(A, sizeof(A)/sizeof(A[0]),
					B, sizeof(B)/sizeof(B[0]));
    cout << "3 == " << v << endl;
  }
  {
    int A[] = {3};
    int B[] = {1, 2, 4, 5};
    Solution s;
    double v = s.findMedianSortedArrays(A, sizeof(A)/sizeof(A[0]),
					B, sizeof(B)/sizeof(B[0]));
    cout << "3 == " << v << endl;
  }
  {
    int A[] = {5, 6};
    int B[] = {1, 2, 3, 4, 7};
    Solution s;
    double v = s.findMedianSortedArrays(A, sizeof(A)/sizeof(A[0]),
					B, sizeof(B)/sizeof(B[0]));
    cout << "4 == " << v << endl;
  }
}
