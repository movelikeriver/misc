// Find max num of common elements between two strings, e.g. "abcd"
// and "aybycef", the max num of common elements is 3 (they are 'a',
// 'b', 'c').

#include <iostream>
#include <vector>

using namespace std;


class CommonStr {
public:
  CommonStr() {
  }

  ~CommonStr() {
  }

  int Compute(const string& str1, const string& str2) {
    results_.resize(str1.length());
    for (int i = 0; i < results_.size(); ++i) {
      results_[i].resize(str2.length());
      for (int j = 0; j < results_[i].size(); ++j) {
	results_[i][j] = -1;
      }
    }

    cout << "========PrintVec()=======\n";
    PrintVec();

    cout << "Start computing [" << str1 << "] " << str1.length()
	 << " v.s. [" << str2 << "], " << str2.length() << endl;


    int v = CommonString(str1, str1.length() - 1,
			str2, str2.length() - 1);

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

  int CommonString(const string& str1, const int idx1,
		   const string& str2, const int idx2) {
    if (idx1 == -1 || idx2 == -1) {
      return 0;
    }
    if (results_[idx1][idx2] >= 0) {
      return results_[idx1][idx2];
    }

    int v = 0;
    if (str1[idx1] == str2[idx2]) {
      if (idx1 >= 1 && idx2 >= 1) {
	v = 1 + CommonString(str1, idx1-1, str2, idx2-1);
      }
    } else {
      int v1 = 0, v2 = 0;
      if (idx1 >= 1) {
	v1 = CommonString(str1, idx1-1, str2, idx2);
      }
      if (idx2 >= 1) {
	v2 = CommonString(str1, idx1, str2, idx2-1);
      }
      v = max(v1, v2);
    }
    results_[idx1][idx2] = v;
    return v;
  }

  vector<vector<int> > results_;
};


int main() {
  int v = 0;
  CommonStr cs;
  v = cs.Compute("abcdefg", "aacfgh");
  cout << "*** Result: " << v << endl;

  v = cs.Compute("abcdefg", "");
  cout << "*** Result: " << v << endl;

  v = cs.Compute("abefg", "aacfgh");
  cout << "*** Result: " << v << endl;

  v = cs.Compute("abcdg", "abcbcdacfgh");
  cout << "*** Result: " << v << endl;
}
