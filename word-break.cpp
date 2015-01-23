// From https://oj.leetcode.com/problems/word-break-ii/
//
// Word Break II
//
// Given a string s and a dictionary of words dict, add spaces in s to construct a sentence where each word is a valid dictionary word.
//
// Return all such possible sentences.
//
//  For example, given
//  s = "catsanddog",
//  dict = ["cat", "cats", "and", "sand", "dog"].
//
//  A solution is ["cats and dog", "cat sand dog"]. 
//
// Run:
//   g++ --std=c++11 word-break.cpp
//   ./a.out

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
  vector<string> wordBreak(string s, unordered_set<string> &dict) {
    int max_len = 0;
    for (const string& word : dict) {
      if (word.size() > max_len) {
	max_len = word.size();
      }
    }

    vector<string> final;
    unordered_map<int, vector<string>> m;
    Break(0, s, max_len, dict, &final, &m);
    return final;
  }

private:
  // the basic idea is the DP approach. The formula is F(start) =
  // word(start, i) + F(start + i), and we can save F(x) to avoid
  // computing it again as DP approach.
  bool Break(int start, const string& s, int max_len,
	     unordered_set<string> &dict,
	     vector<string>* res, unordered_map<int, vector<string>>* m) {
    if (m->count(start) > 0) {
      // no valid result
      if ((*m)[start].empty()) {
	return false;
      }
      *res = (*m)[start];
      return true;
    }

    bool success = false;
    int len = max_len < (s.size() - start) ?
      max_len : (s.size() - start);
    for (int i = 1; i <= len; i++) {
      string word = s.substr(start, i);
      if (dict.count(word)) {
	if (start+i == s.size()) {
	  // found the last one.
	  res->push_back(word);
	  success = true;
	  continue;
	}

	vector<string> sub;
	if (Break(start+i, s, max_len, dict, &sub, m)) {
	  for (const string& v : sub) {
	    res->push_back(word + " " + v);
	  }
	  success = true;
	}
      }
    }

    // save the result to avoid computing again, for both success or
    // fail case, otherwise it may lead to dead loop.
    (*m)[start] = *res;

    return success;
  }
};


unordered_set<string> ArrayToSet(string arr[], int n) {
  unordered_set<string> s;
  for (int i = 0; i < n; i++) {
    s.insert(arr[i]);
  }
  return s;
}

int main() {
  {
    string arr[] = {"cat", "cats", "and", "sand", "dog"};
    string str = "catsanddog";
    unordered_set<string> dict = ArrayToSet(arr, sizeof(arr)/sizeof(arr[0]));
    Solution s;
    vector<string> vec = s.wordBreak(str, dict);
    for (const string& v : vec) {
      cout << v << "\n";
    }
  }

  {
    string arr[] = {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
    string str = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
    unordered_set<string> dict = ArrayToSet(arr, sizeof(arr)/sizeof(arr[0]));
    Solution s;
    vector<string> vec = s.wordBreak(str, dict);
    for (const string& v : vec) {
      cout << v << "\n";
    }
  }


}
