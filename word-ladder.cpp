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
#include <set>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;


class Solution {
public:
  // the basic idea is to build the graph by BFS, and travel the graph
  // by DFS.
  vector<vector<string>> findLadders(string start, string end,
				     unordered_set<string> &dict) {
    vector<string> dict_vec;
    for (const string& s : dict) {
      dict_vec.push_back(s);
    }

    vector<int> solution;
    vector<vector<int> > final;
    vector<vector<string> > ret;
    Graph g;
    if (!BuildGraph(dict_vec, &g)) {
      cout << "unexpected input dict" << endl;
      return ret;
    }
    cout << "graph has been built!" << endl;

    set<int> visited;
    int cur_min = dict_vec.size();  // max num as initial value
    for (int i = 0; i < dict_vec.size(); i++) {
      if (Dist(start, dict_vec[i]) == 1) {
	solution.push_back(i);
	visited.insert(i);
	BFS(i, end, g, dict_vec, &visited, &cur_min, &solution, &final);
	solution.pop_back();
	visited.erase(i);
      }
    }

    int minsize = -1;
    for (const vector<int>& v : final) {
      if (minsize == -1 || v.size() < minsize) {
	minsize = v.size();
      }
    }

    for (const vector<int>& v1 : final) {
      if (v1.size() == minsize) {
	vector<string> v2;
	v2.push_back(start);
	for (int i : v1) {
	  v2.push_back(dict_vec[i]);
	}
	v2.push_back(end);
	ret.push_back(v2);
      }
    }
    return ret;
  }

  static void PrintVec(const vector<string>& vec) {
    for (const string& v : vec) {
      cout << v << ", ";
    }
    cout << "\n";
  }

private:
  struct Graph {
    vector<set<int> > neighbors;
  };

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
	  return count;
	}
      }
    }
    return count;
  }

  bool BuildGraph(const vector<string>& dict_vec, Graph* g) {
    for (int i = 0; i < dict_vec.size(); i++) {
      set<int> neighbors;
      for (int j = 0; j < dict_vec.size(); j++) {
	if (i == j) {
	  continue;
	}
	int dist = Dist(dict_vec[i], dict_vec[j]);
	if (dist == -1) {
	  return false;
	}
	if (dist == 1) {
	  neighbors.insert(j);
	}
      }
      g->neighbors.push_back(neighbors);
    }
    return true;
  }



  void BFS(const int i, const string& end,
	   const Graph& g, const vector<string>& dict_vec,
	   set<int>* visited, int* cur_min,
	   vector<int>* solution, vector<vector<int> >* final) {
    if (Dist(dict_vec[i], end) == 1) {
      if (solution->size() > *cur_min) {
	return;
      }

      // keep the shortest path only for memory optimization.
      if (solution->size() < *cur_min) {
	final->clear();
	*cur_min = solution->size();
      }
      final->push_back(*solution);
      return;
    }

    for (int v : g.neighbors[i]) {
      if (visited->count(v)) {
	continue;
      }

      solution->push_back(v);
      visited->insert(v);
      BFS(v, end, g, dict_vec, visited, cur_min, solution, final);
      solution->pop_back();
      visited->erase(v);
    }
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
    string arr[] = {"hot","dot","dog","lot","log"};
    TestFindLadders("hit", "cog", arr, sizeof(arr)/sizeof(arr[0]));
  }
  {
    string arr[] = {"si","go","se","cm","so","ph","mt","db","mb","sb","kr","ln","tm","le","av","sm","ar","ci","ca","br","ti","ba","to","ra","fa","yo","ow","sn","ya","cr","po","fe","ho","ma","re","or","rn","au","ur","rh","sr","tc","lt","lo","as","fr","nb","yb","if","pb","ge","th","pm","rb","sh","co","ga","li","ha","hz","no","bi","di","hi","qa","pi","os","uh","wm","an","me","mo","na","la","st","er","sc","ne","mn","mi","am","ex","pt","io","be","fm","ta","tb","ni","mr","pa","he","lr","sq","ye"};
    TestFindLadders("qa", "sq", arr, sizeof(arr)/sizeof(arr[0]));
  }
}
