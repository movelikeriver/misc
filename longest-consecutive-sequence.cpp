// Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
//
// For example, Given [100, 4, 200, 1, 3, 2], 
// 
// The longest consecutive elements sequence is [1, 2, 3, 4]. Return
// its length: 4.
//
// Your algorithm should run in O(n) complexity. 
//
// From https://oj.leetcode.com/problems/longest-consecutive-sequence/
//
// Run:
//  g++ -std=c++11 longest-consecutive-sequence.cpp
//  ./a.out

#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Solution {
public:
  int longestConsecutive(vector<int> &num) {
    map<int, int> m;

    for (int v : num) {
      if (m.count(v) > 0) {
	// duplicated element in the vector.
	continue;
      }
      if (m.count(v-1) > 0 && m.count(v+1) > 0) {
	m[v] = m[v-1] + m[v+1] + 1;
	m[v - m[v-1]] = m[v];
	m[v + m[v+1]] = m[v];
	continue;
      }
      if (m.count(v-1) > 0) {
	m[v] = m[v-1] + 1;
	m[v - m[v-1]] = m[v];
	continue;
      }
      if (m.count(v+1) > 0) {
	m[v] = m[v+1] + 1;
	m[v + m[v+1]] = m[v];
	continue;
      }
      m[v] = 1;
    }

    int max_len = 0;
    for (auto& p : m) {
      if (p.second > max_len) {
	max_len = p.second;
      }
    }

    return max_len;
  }
};

int main() {
  int arr1[] = {100, 4, 200, 1, 3, 2};
  vector<int> vec1(arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]));

  int arr2[] = {2147483646,-2147483647,0,2,2147483644,-2147483645,2147483645};
  vector<int> vec2(arr2, arr2 + sizeof(arr2)/sizeof(arr2[0]));

  Solution s;
  cout << s.longestConsecutive(vec1) << endl;
  cout << s.longestConsecutive(vec2) << endl;
}
