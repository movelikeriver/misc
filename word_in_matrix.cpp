// Given a matrix below:
//   a b c d e
//   w e f a g
//   e s a d z
//   m o d f p
//
// Implement WordInMatrix() function:
//
// WordInMatrix("awesome") == true, because:
//   A b c d e
//   W E f a g
//   E S a d z
//   M O d f p
//
// WordInMatrix("age") == true, because:
//   a b c d E
//   w e f A G
//   e s a d z
//   m o d f p
//
//
// Usage:
//   g++ word_in_matrix.cpp
//   ./a.out

#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;


class Matrix {
public:
  Matrix() {
    Init();
  }

  bool WordInMatrix(const string& input) {
    for (int i = 0; i < m_.size(); i++) {
      for (int j = 0; j < m_[i].size(); j++) {
	// try every point
	if (Match(i, j, input, 0)) {
	  return true;
	}
      }
    }
    return false;
  }

  void Print() {
    for (int i = 0; i < m_.size(); i++) {
      for (int j = 0; j < m_[i].size(); j++) {
	cout << m_[i][j] << ", ";
      }
      if (!m_[i].empty()) {
	cout << endl;
      }
    }
  }

private:
  void Init() {
    m_.clear();
    char chs0[] = {'a', 'b', 'c', 'd', 'e'};
    m_.push_back(vector<char>(&chs0[0], &chs0[0]+5));
    char chs1[] = {'w', 'e', 'f', 'a', 'g'};
    m_.push_back(vector<char>(&chs1[0], &chs1[0]+5));
    char chs2[] = {'e', 's', 'a', 'd', 'z'};
    m_.push_back(vector<char>(&chs2[0], &chs2[0]+5));
    char chs3[] = {'m', 'o', 'd', 'f', 'p'};
    m_.push_back(vector<char>(&chs3[0], &chs3[0]+5));
   }

  int Key(int x, int y) {
    return x*m_[0].size() + y;
  }

  bool IsVisited(int x, int y) {
    return visited_.count(Key(x, y)) > 0;
  }

  void Visit(int x, int y) {
    visited_.insert(Key(x, y));
  }

  void Leave(int x, int y) {
    visited_.erase(Key(x, y));
  }

  bool Match(int x, int y, const string& input, int i) {
    if (i >= input.length()) {
      return true;  // match entire input string.
    }

    if (IsVisited(x, y)) {
      return false;
    }

    if (x < 0 || x >= m_.size() || y < 0 || y >= m_[0].size()) {
	return false;
    }

    if (m_[x][y] == input[i]) {
      // dynamic programming
      Visit(x, y);
      if (Match(x-1, y, input, i+1)) {
	return true;
      }
      if (Match(x+1, y, input, i+1)) {
	return true;
      }
      if (Match(x, y-1, input, i+1)) {
	return true;
      }
      if (Match(x, y+1, input, i+1)) {
	return true;
      }
      Leave(x, y);
    }
    return false;
  }

  vector<vector<char> > m_;
  set<int> visited_;
};

int main() {
  Matrix m;
  m.Print();
  cout << "==========\n";

  cout << m.WordInMatrix("age") << endl;      // 1
  cout << m.WordInMatrix("awesome") << endl;  // 1
  cout << m.WordInMatrix("hello") << endl;    // 0
}
