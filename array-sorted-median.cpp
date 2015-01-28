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

  double FindMedian(const vector<int>& arr1, const vector<int>& arr2) {
    int n1 = arr1.size();
    int n2 = arr2.size();

    // process some simple cases first.
    if (n1 == 0) {
      int idx = (n2-1) / 2;
      if (n2 % 2) {
	return arr2[idx];
      }
      return (float)(arr2[idx]+arr2[idx+1]) / 2;
    }

    if (arr1[0] >= arr2[n2-1]) {
      int idx = (n2 + n1 - 1) / 2;
      if ((n1 + n2) % 2 == 1) {
	return arr2[idx];
      }

      // arr1 and arr2 have the same size.
      if (n1 == n2) {
	return (float)(arr1[0] + arr2[n2-1]) / 2;
      }
      return (float)(arr2[idx] + arr2[idx+1]) / 2;
    }

    if (arr2[0] >= arr1[n1-1]) {
      int idx = (n1 + n2) / 2 - n1;
      if ((n1 + n2) % 2 == 1) {
	return arr2[idx];
      }

      // arr1 and arr2 have the same size.
      if (n1 == n2) {
	return (float)(arr1[n1-1] + arr2[0]) / 2;
      }
      return (float)(arr2[idx-1] + arr2[idx]) / 2;
    }

    int start = 0;
    int end = n1-1;
    int m1 = (start+end)/2;
    int m2 = (n1+n2+1)/2 - 1 - m1;

    // Image the arrays like:
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
    while (true) {
      if (arr1[m1] > arr2[m2]) {
	end = m1;
      } else if (m1+1 < n1 && m2-1 >= 0 &&
		 arr1[m1+1] < arr2[m2-1]) {
	start = m1+1;
      } else {
	break;
      }

      int new_m1 = (start+end)/2;
      if (new_m1 == m1) {
	break;
      }
      m1 = new_m1;
      m2 = (n1+n2+1)/2 - 1 - m1;
    }

    cout << "m1, m2 = " << m1 << ", " << m2 << endl;

    if (m1 == n1-1 || m1 == 0) {
      // For (n1+n2)%2 == 0
      //  arr1:  1 2 m1
      //  arr2:  3 idx 4 m2 5 6 7
      //
      // For (n1+n2)%2 == 1
      //  arr1:  1 2 m1
      //  arr2:  3 4 idx 5 m2 6 7 8
      int idx = n2 - (n1+n2)/2 - 1;

      // This part is tricky, we need to compare m1, idx, idx-1, idx+1.
      if ((n1+n2)%2 == 1) {
	if (arr1[m1] < arr2[idx]) {
	  return arr2[idx];
	}
	return min(arr1[m1], arr2[idx+1]);
      }

      if (arr1[m1] < arr2[idx]) {
	return (float)(arr2[idx]+arr2[idx+1]) / 2;
      }
      if(arr1[m1] < arr2[idx+2]) {
	return (float)(arr1[m1]+arr2[idx+1]) / 2;
      }
      return (float)(arr2[idx+1]+arr2[idx+2]) / 2;
    }

    // For (n1+n2)%2 == 1
    //  1 2  3  m1 6 7
    //    4 idx m2 8 9
    //  m1 vs idx
    if ((n1+n2)%2 == 1) {
      int idx = m2-1;
      return max(arr1[m1], arr2[idx]);
    }

    // For (n1+n2)%2 == 0
    //  1 2 m1 6
    //  5 m2 8 9
    int v1 = max(arr1[m1], arr2[m2-1]);
    int v2 = min(arr1[m1+1], arr2[m2]);

    return (float)(v1+v2) / 2;
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
