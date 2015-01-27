#include <iostream>
#include <vector>
using namespace std;

// arr has no duplicated elements??  yes!
// arr is sorted from small to big
// returns -1 if not found.
int FindIndex(vector<int> arr, int value) { 
  int start = 0;
  int end = arr.size() - 1;
  int mid = (int)((start+end)/2);

  while (arr[mid] != value) {
    if (arr[start] > arr[end]) {
      if (arr[start] > value) {
	//  5 ... 1 .. 4 for 2, goes right
	//  5 ... 9 .. 4 for 2, goes right
	//  5 ... 3 .. 4 for 2, goes left
	if (arr[start] > arr[mid] && value > arr[mid]) {
	  start = mid;
	} else {
	  end = mid;
	}
      } else {
	//  5 ... 3 .. 4 for 7, goes left
	//  5 ... 9 .. 4 for 7, goes left
	//  5 ... 6 .. 4 for 7, goes right
	if (arr[start] < arr[mid] && value > arr[mid]) {
	  start = mid;
	} else {
	  end = mid;
	}
      }
    } else {
      //  4 ... 7 .. 9 for 2, return -1
      if (arr[start] > value || arr[end] < value) {
	return -1;
      }

      //  4 ... 5 .. 9 for 7, goes right
      //  4 ... 8 .. 9 for 7, goes left
      if (arr[mid] < value) {
	start = mid;
      } else {
	end = mid;
      }
    }

    mid = (int) ((start+end)/2);
    if (mid == start || mid == end) {
      break;
    }
  }
  
  if (arr[mid] == value) {
    return mid;
  }
  // no this value in the array
  return -1;
}

int main() {
  int arr[] = {5, 6, 7, 1, 2, 3, 4};
  int n = sizeof(arr)/sizeof(arr[0]);
  vector<int> vec(arr, arr+n);

  cout << FindIndex(vec, 2) << endl;
  cout << FindIndex(vec, 6) << endl;
}
