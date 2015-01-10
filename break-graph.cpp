// Question: Given a graph with even num of vertexes but without
// circle, try to cut the edges to break the graph into small
// sub-graph which also has even num of vertexes, return the maximum
// num of sub-graphs.
//
// Solution: since there's no circle in the graph, we can merge the
// vertexes from leaf nodes, and make the num of merged nodes as the
// value of node. After the merging, the new leaf node's value may be
// an even number, then we can cut off this new leaf node, total_num
// += 1, then continue from the main graph. If the new leaf node is
// still odd, continue the merging process in graph. Until there's one
// node left. Return the total_num as final result.
//
// Run:
//  g++ -std=c++11 break-graph.cpp
//  ./a.out

#include <iostream>
#include <set>
#include <vector>
using namespace std;

class BreakGraph {
public:
  explicit BreakGraph(int n) {
    Reset(n);
  }

  // n has to be even.
  void Reset(int n) {
    vertex_.resize(n);
    links_.resize(n);

    for (int i = 0; i < vertex_.size(); i++) {
      vertex_[i] = 1;
      valid_.insert(i);
      links_[i].clear();
    }

    count_ = 1;
  }

  void AddEdge(int node1, int node2) {
    if (node1 < 0 || node1 >= vertex_.size() ||
	node2 < 0 || node2 >= vertex_.size() ||
	node1 == node2) {
      cout << "can't add edge between " << node1
	   << " and " << node2 << endl;
      return;
    }
    links_[node1].insert(node2);
    links_[node2].insert(node1);
  }

  int NumOfSubGraph() {
    Print();
    while (Merge()) {
      Print();
    }
    return count_;
  }

  void Print() {
    cout << "valid: ";
    for (int i : valid_) {
      cout << i << " ";
    }
    cout << "\n";

    for (int i = 0; i < vertex_.size(); i++) {
      cout << "vertex[" << i << "] = " << vertex_[i] << " has vertexes: ";
      for (int j : links_[i]) {
	cout << j << " ";
      }
      cout << "\n";
    }
    cout << endl;
  }

private:
  int Merge() {
    // removed edges (i, i+1) in this round.
    vector<int> removed_edges;

    for (int i : valid_) {
      if (vertex_[i] == 0) {
	// some vertexes have been removed when processing their
	// neighbours.
	continue;
      }

      for (int j : links_[i]) {
	if (IsLeaf(j)) {
	  // merge vertex-j to vertex-i.
	  vertex_[i] += vertex_[j];
	  vertex_[j] = 0;
	  // save to removed_edges for update links_ in next step,
	  // because we can't modify links_[i] when it's in for-loop.
	  removed_edges.push_back(i);
	  removed_edges.push_back(j);
	}
      }
    }

    // the vertex which may become new leaves after eating some
    // leaves.
    set<int> new_leaves;
    // Update valid_ and links_ by merging the leaves.
    for (int i = 0; i < removed_edges.size(); i+=2) {
      // watch out: it's easy to typo removed_edges[i] to i...
      int node1 = removed_edges[i];
      int node2 = removed_edges[i+1];
      RemoveEdge(node1, node2);
      valid_.erase(node2);
      new_leaves.insert(node1);
    }

    for (int i : new_leaves) {
      if ((vertex_[i] % 2 == 0) && IsLeaf(i)) {
	Cut(i);
	++count_;
      }
    }

    return new_leaves.size();
  }

  bool IsLeaf(int i) {
    return links_[i].size() == 1;
  }

  // vertex-j will be eaten vertex-i.
  void RemoveEdge(int i, int j) {
    links_[i].erase(j);
    links_[j].erase(i);
  }

  void Cut(int i) {
    int target = *links_[i].begin();
    links_[i].erase(target);
    links_[target].erase(i);
    vertex_[i] = 0;
  }

  int count_ = 1;
  // graph
  set<int> valid_;  // valid vertexes in graph.
  vector<int> vertex_;
  vector<set<int> > links_;
};


int main() {
  // Bread a graph like below:
  //
  //      0       5
  //       \     / 
  //    1 - 2 - 3 - 4
  //            |
  //   10 - 9 - 7 - 6
  //       /    | 
  //      11    8
  
  BreakGraph bg(12);
  bg.AddEdge(0, 2);
  bg.AddEdge(1, 2);
  bg.AddEdge(2, 3);
  bg.AddEdge(3, 5);
  bg.AddEdge(3, 4);
  bg.AddEdge(3, 7);
  bg.AddEdge(7, 6);
  bg.AddEdge(7, 8);
  bg.AddEdge(7, 9);
  bg.AddEdge(9, 10);
  bg.AddEdge(9, 11);

  int n = bg.NumOfSubGraph();
  cout << "Num of subgraph: " << n << endl;
}
