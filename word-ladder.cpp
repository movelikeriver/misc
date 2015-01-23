// From https://oj.leetcode.com/problems/word-ladder-ii/
//
// Word Ladder II
//
// Given two words (start and end), and a dictionary, find all shortest transformation sequence(s) from start to end, such that:
//
//    Only one letter can be changed at a time
//    Each intermediate word must exist in the dictionary
//
//  For example,
//
//  Given:
//  start = "hit"
//  end = "cog"
//  dict = ["hot","dot","dog","lot","log"]
//
//  Return
//
//  [
//   ["hit","hot","dot","dog","cog"],
//   ["hit","hot","lot","log","cog"]
//  ]
//
//  Note:
//
//    All words have the same length.
//    All words contain only lowercase alphabetic characters.

#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;


class Solution {
public:
  // the basic idea is to build the graph by BFS, and travel the graph
  // by DFS + DP.
  vector<vector<string>> findLadders(string start, string end,
				     unordered_set<string> &dict) {
    unordered_map<string, unordered_set<string> > graph;
    BuildGraph(start, end, &dict, &graph);
    cout << "Graph has been built!" << endl;
    PrintGraph(graph);
    
    unordered_map<string, vector<string> > m;
    vector<string> res;
    unordered_set<string> visited;
    DFS(start, end, graph, &res, &m, &visited);

    vector<vector<string> > final;
    for (const string& str : res) {
      vector<string> vec;
      Split(str, &vec);
      final.push_back(vec);
    }
    return final;
  }

  static void PrintVec(const vector<string>& vec) {
    for (const string& v : vec) {
      cout << v << ", ";
    }
    cout << "\n";
  }

  static void PrintGraph(const unordered_map<string, unordered_set<string> >& graph) {
    for (const auto& it : graph) {
      cout << it.first << ":  ";
      for (const string& v : it.second) {
	cout << v << ", ";
      }
      cout << "\n";
    }
    cout << endl;
  }

  static void Split(const string& str, vector<string>* vec) {
    if (str.empty()) {
      return;
    }

    int end = 0;
    while(str[end] == ' ') {
      end++;
    }
    // 1st non-space char.
    int start = end;

    for (; end < str.size();) {
      if (str[end] == ' ') {
	vec->push_back(str.substr(start, end-start));

	while(str[end] == ' ') {
	  end++;
	}
	start = end;
      } else {
	end++;
      }
    }

    if (start < str.size()) {
      vec->push_back(str.substr(start, end-start));
    }
  }

private:
  int Dist(const string& s1, const string& s2) {
    if (s1.size() != s2.size()) {
      // unexpected
      return -1;
    }
    int count = 0;
    for (int i = 0; i < s1.size(); i++) {
      if (s1[i] != s2[i]) {
	count++;
	if (count == 2) {
	  // > or = 2 doesn't matter. it's not necessary to compare
	  // > further.
	  return count;
	}
      }
    }
    return count;
  }

  // build a graph with shortest path from start to end, it's allowed
  // to have circle.
  void BuildGraph(const string& start, const string& end,
		  unordered_set<string>* dict,
		  unordered_map<string, unordered_set<string> >* graph) {
    dict->erase(start);

    stack<string> process;
    process.push(start);
    while (!process.empty()) {
      unordered_set<string> remove;
      while (!process.empty()) {
	string str = process.top();
	process.pop();

	// BFS
	for (const string& v : *dict) {
	  if (Dist(str, v) == 1) {
	    (*graph)[str].insert(v);
	    remove.insert(v);
	  }
	}
      }  // end while

      if (remove.count(end)) {
	// reach the end.
	break;
      }

      // remove visited points. it's allowed to have circle, so we
      // have to remove the nodes after while-loop.
      for (const string& v : remove) {
	dict->erase(v);
      }

      bool reach = false;
      for (const string& v : remove) {
	// prepare for the next degree.
	process.push(v);
	// in case reaching end, we can wrap up the graph building.
	if (Dist(v, end) == 1) {
	  (*graph)[v].insert(end);
	  reach = true;
	}
      }
      if (reach) {
	break;
      }
    }
  }

  // travel the graph with DFS + DP.
  bool DFS(const string& start, const string& end,
	   const unordered_map<string, unordered_set<string> >& graph,
	   vector<string>* res,
	   unordered_map<string, vector<string> >* m,
	   unordered_set<string>* visited) {
    if ((*m).count(start)) {
      if ((*m)[start].empty()) {
	return false;
      }
      *res = (*m)[start];
      return true;
    }

    bool success = false;
    if (start == end) {
      res->push_back(end);
      success = true;
    } else {
      // be aware of the nodes which are not the key of the map.
      unordered_map<string, unordered_set<string> >::const_iterator it =
	graph.find(start);
      if (it != graph.end()) {
	visited->insert(start);
	// check all the neighbors
	for (const string& v : it->second) {
	  if (visited->count(v)) {
	    // be aware of the circle.
	    continue;
	  }

	  vector<string> sub;
	  if (DFS(v, end, graph, &sub, m, visited)) {
	    for (const string& sv : sub) {
	      res->push_back(start + " " + sv);
	    }
	    success = true;
	  }
	}
	visited->erase(start);
      }
    }
    // save the result as DP
    (*m)[start] = *res;
    return success;
  }
};

void TestFindLadders(const string& start, const string& end,
		     string arr[], int n) {
  unordered_set<string> dict;
  for (int i = 0; i < n; i++) {
    dict.insert(arr[i]);
  }
  Solution s;
  vector<vector<string>> vec = s.findLadders(start, end, dict);
  for (const vector<string>& v : vec) {
    Solution::PrintVec(v);
  }
  cout << endl;
}

int main() {
  {
    vector<string> vec;
    Solution::Split("as af asd ad", &vec);
    Solution::PrintVec(vec);
  }

  {
    vector<string> vec;
    Solution::Split("  as af asd ad  ", &vec);
    Solution::PrintVec(vec);
  }

  {
    string arr[] = {"hot","dot","dog","lot","log"};
    TestFindLadders("hit", "cog", arr, sizeof(arr)/sizeof(arr[0]));
  }
  {
    string arr[] = {"si","go","se","cm","so","ph","mt","db","mb","sb","kr","ln","tm","le","av","sm","ar","ci","ca","br","ti","ba","to","ra","fa","yo","ow","sn","ya","cr","po","fe","ho","ma","re","or","rn","au","ur","rh","sr","tc","lt","lo","as","fr","nb","yb","if","pb","ge","th","pm","rb","sh","co","ga","li","ha","hz","no","bi","di","hi","qa","pi","os","uh","wm","an","me","mo","na","la","st","er","sc","ne","mn","mi","am","ex","pt","io","be","fm","ta","tb","ni","mr","pa","he","lr","sq","ye"};
    TestFindLadders("qa", "sq", arr, sizeof(arr)/sizeof(arr[0]));
  }

  {
    string arr[] = {"a","b","c"};
    TestFindLadders("a", "c", arr, sizeof(arr)/sizeof(arr[0]));
  }

  {
    string arr[] = {"ted","tex","red","tax","tad","den","rex","pee"};
    TestFindLadders("red", "tax", arr, sizeof(arr)/sizeof(arr[0]));
  }
}
