// From https://oj.leetcode.com/problems/permutations-ii/
//
// Permutations II
//
// Given a collection of numbers that might contain duplicates, return all possible unique permutations.
//
//  For example,
//  [1,1,2] have the following unique permutations:
//  [1,1,2], [1,2,1], and [2,1,1]. 


#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
  vector<vector<int> > permuteUnique(vector<int> &num) {
    vector<vector<int> > out;
    set<string> keys;
    Perm(num, 0, &out, &keys);
    return out;
  }

  static string VecToStr(const vector<int>& num) {
    string str = "";
    for (int v : num) {
      if (str.empty()) {
	str = to_string(v);
      } else {
	str = str + "," + to_string(v);
      }
    }
    return str;
  }

private:
  void Perm(vector<int>& num, int s, vector<vector<int> >* out, set<string>* keys) {
    // the basic idea is to dedup the Perm for num+s.
    string key = VecToStr(num) + "," + to_string(s);
    if (keys->count(key) > 0) {
      return;
    }
    keys->insert(key);

    if (s == num.size() - 1) {
      out->push_back(num);
      return;
    }

    for (int i = s; i < num.size(); i++) {
      Swap(num, s, i);
      Perm(num, s+1, out, keys);
      Swap(num, s, i);
    }
  }

  void Swap(vector<int>& num, int i, int j) {
    if (i == j || num[i] == num[j]) {
      return;
    }
    int tmp = num[j];
    num[j] = num[i];
    num[i] = tmp;
  }
};

void Print(const vector<int>& num) {
  cout << Solution::VecToStr(num) << "\n";
}

int main() {
  Solution s;

  {
    int arr[] = {1, 1, 3, 4};
    vector<int> vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
    vector<vector<int> > res = s.permuteUnique(vec);
    for (const vector<int>& vec : res) {
      Print(vec);
    }
  }

  {
    int arr[] = {3,3,0,0,2,3,2};
    vector<int> vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
    vector<vector<int> > res = s.permuteUnique(vec);
    for (const vector<int>& vec : res) {
      Print(vec);
    }
  }
}
