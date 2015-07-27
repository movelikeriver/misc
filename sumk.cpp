#include <iostream>
#include <list>
#include <vector>
using namespace std;


#define PRINT(inputs)				\
  for (const int v : inputs) {			\
    cout << v << ", ";				\
  }						\
  cout << endl;					\


bool Sum2(const list<int>& inputs, int value, int* ii, int* jj) {
  if (inputs.empty()) {
    return false;
  }
  auto i = inputs.begin();
  auto j = inputs.rbegin();
  while (*i < *j) {
    cout << *i << " vs " << *j << endl;

    int s = *i + *j;
    if (s == value) {
      *ii = *i;
      *jj = *j;
      return true;
    } else if (s < value) {
      i++;  // from left to right
    } else {
      j++;  // from right to left
    }
  }
  return false;
}

void TestSum2() {
  //  list<int> inputs = {1, 2, 3, 5, 8, 10, 12, 16, 18};
  list<int> inputs = {3, 5, 8, 10, 12, 16, 18};
  PRINT(inputs);

  int ii = 0, jj = 0;
  vector<int> values = {8, 11, 20, 15, 18, 34, 33};
  for (const int value : values) {
    if (Sum2(inputs, value, &ii, &jj)) {
      cout << "ii=" << ii << ", jj=" << jj << " === " << value << endl;
    } else {
      cout << "fail to find " << value << "\n";
    }
  }
}

bool SumK(list<int>* inputs, int value, int k, vector<int>* results) {
  cout << "sum k=" << k << ", value=" << value << endl;
  PRINT(*inputs);

  if (k == 2) {
    int ii=0, jj=0;
    if (Sum2(*inputs, value, &ii, &jj)) {
      cout << "find1: " << ii << ", " << jj << endl;

      results->emplace_back(ii);
      results->emplace_back(jj);
      cout << "find2: " << ii << ", " << jj << endl;
      return true;
    }
    return false;
  }

  for (auto it = inputs->begin(); it != inputs->end(); it++) {
    int v = *it;
    // erase and emplace can recover the original list.
    auto it2 = inputs->erase(it);
    results->emplace_back(v);
    bool found = SumK(inputs, value - v, k - 1, results);

    cout << "==begin==";
    it = inputs->emplace(it2, v);
    cout << "==end==";

    if (found) {
      return true;
    } else {
      results->pop_back();
    }
  }
  return false;
}

void TestSumK(int k) {
  list<int> inputs = {1, 2, 3, 5, 8, 10, 12, 16, 18};
  PRINT(inputs);

  vector<int> values = {11, 20, 15, 18, 34, 33};
  for (const int value : values) {
    vector<int> results;
    if (SumK(&inputs, value, k, &results)) {
      cout << "find " << value << ": ";
      PRINT(results);
    } else {
      cout << "fail to find " << value << "\n";
    }
  }
}

int main() {
  //  TestSum2();
  //  TestSumK(3);
  TestSumK(4);
}
