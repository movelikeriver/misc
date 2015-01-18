// Find if an element with arr[i] = i exists in a sorted int array
// with no duplicates.

#include <iostream>
using namespace std;

int FindArray(int arr[], int n) {
  int l = 0;
  int r = n-1;
  while (l < r-1) {
    int mid = (l+r) / 2;
    if (arr[mid] == mid) {
      return mid;
    }
    if (arr[mid] > mid) {
      r = mid;
    } else {
      l = mid;
    }
  }
  // because (r-1 + r) / 2 == r-1, we need to handle the last element
  // separately.
  if (arr[r] == r) {
    return r;
  }
  return -1;
}

int main() {
  {
    int arr[] = {-1, 0, 2, 5, 6};
    cout << FindArray(arr, sizeof(arr)/sizeof(arr[0])) << endl;
  }
  {
    int arr[] = {0, 2, 4, 5, 6};
    cout << FindArray(arr, sizeof(arr)/sizeof(arr[0])) << endl;
  }
  {
    int arr[] = {-3, -2, 1, 2, 4};
    cout << FindArray(arr, sizeof(arr)/sizeof(arr[0])) << endl;
  }
}
