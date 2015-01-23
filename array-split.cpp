// A string[] array of word and number, like: { c1, n1, c2, n2, ...,
// cN, nN }, convert it to { c1, c2, ..., cN, n1, n2, ..., nN }. The
// approach should be constant space limit.
//
// Run:
//  g++ --std=c++11 array-split.cpp
//  ./a.out

#include <iostream>
#include <vector>
#include <string>
using namespace std;


int FindTarget(int i, int half) {
  if (i % 2 == 0) {
    // cX
    return i / 2;
  } else {
    // nX
    return half + ((i-1) / 2);
  }
}

bool IsProcessed(const string& str) {
  if (str.empty()) {
    // should never happen.
    return false;
  }
  if (str[str.size() - 1] == '$') {
    return true;
  }
  return false;
}

string Process(const string& str) {
  return str + "$";
}

void Revert(string* str) {
  if (IsProcessed(*str)) {
    *str = str->substr(0, str->size()-1);
  }
}

void Convert(vector<string>* input) {
  int half = input->size() / 2;
  for (int i = 0; i < half; i++) {
    if (IsProcessed((*input)[i])) {
      continue;
    }

    string cur = Process((*input)[i]);
    int t = FindTarget(i, half);

    while (t != i) {
      string tmp = Process((*input)[t]);
      (*input)[t] = cur;
      cur = tmp;
      t = FindTarget(t, half);
    }

    (*input)[t] = cur;
  }

  for (int i = 0; i < input->size(); i++) {
    Revert(&(*input)[i]);
  }
}

void Print(const vector<string>& vec) {
  for (const string& s : vec) {
    cout << s << ", ";
  }
  cout << endl;
}

int main() {
  {
    string arr[] = {"a", "1", "b", "2", "c",
		    "3", "d", "4", "e", "5"};
    vector<string> vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
    Convert(&vec);
    Print(vec);
  }

  {
    string arr[] = {"a", "1", "b", "2", "c", "3",
		    "d", "4", "e", "5", "f", "6"};
    vector<string> vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
    Convert(&vec);
    Print(vec);
  }

  {
    string arr[] = {"a", "1", "b", "2", "c", "3", "d",
		    "4", "e", "5", "f", "6", "g", "7"};
    vector<string> vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
    Convert(&vec);
    Print(vec);
  }

  {
    string arr[] = {"a", "1", "b", "2", "c", "3", "d", "4",
		    "e", "5", "f", "6", "g", "7", "h", "8"};
    vector<string> vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
    Convert(&vec);
    Print(vec);
  }
}

