// Compute min num of steps converting from one string to another.
// You can have operators of 'insert' (1 step), 'update' (1 step),
// 'delete' (1 step).
//
// g++ common_string.cpp
// ./a.out 

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class EditDistance {
public:
  int Compute(const string& str1, const string& str2) {
    results_.resize(str1.length() + 1);
    for (int i = 0; i < results_.size(); ++i) {
      results_[i].resize(str2.length() + 1);
      for (int j = 0; j < results_[i].size(); ++j) {
	if (i == 0) {
	  results_[i][j] = j;
	} else if (j == 0) {
	  results_[i][j] = i;
	} else {
	  results_[i][j] = -1;
	}
      }
    }

    cout << "========PrintVec()=======\n";
    PrintVec();

    cout << "Start computing [" << str1 << "] " << str1.length()
	 << " v.s. [" << str2 << "], " << str2.length() << endl;

    int v = MinDist(str1, str1.length(), str2, str2.length());

    PrintVec();
    return v;
  }

private:
  void PrintVec() {
    for (int i = 0; i < results_.size(); ++i) {
      for (int j = 0; j < results_[i].size(); ++j) {
	cout << results_[i][j] << ", ";
      }
      if (!results_[i].empty()) {
	cout << endl;
      }
    }
  }

  int MinDist(const string& str1, const int idx1,
	      const string& str2, const int idx2) {
    cout << "processing: (" << idx1 << ", " << idx2 << ")" << endl;

    if (results_[idx1][idx2] >= 0) {
      return results_[idx1][idx2];
    }

    int v = max(idx1, idx2);

    if (str1[idx1-1] == str2[idx2-1]) {
      v = MinDist(str1, idx1-1, str2, idx2-1);
    } else {
      int v1=v, v2=v, v3=v;
      v1 = MinDist(str1, idx1-1, str2, idx2);
      v2 = MinDist(str1, idx1, str2, idx2-1);
      v3 = MinDist(str1, idx1-1, str2, idx2-1);
      v = min(min(v1, v2), v3) + 1;
    }

    results_[idx1][idx2] = v;
    return v;
  }

  vector<vector<int> > results_;
};

int main() {
  int v = 0;
  EditDistance ed;
  v = ed.Compute("abcd", "aac");
  cout << "*** Result: " << v << endl;

  v = ed.Compute("abcdefg", "");
  cout << "*** Result: " << v << endl;

  v = ed.Compute("abefg", "aacfgh");
  cout << "*** Result: " << v << endl;

  v = ed.Compute("abcdg", "abcbcdacfgh");
  cout << "*** Result: " << v << endl;
}
