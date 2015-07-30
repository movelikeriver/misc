#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <utility>
using namespace std;

void Print(const vector<string>& vec) {
  for (const string& s : vec) {
    cout << s << "\n";
  }
  cout << endl;
}

void Print(const vector<pair<string, int> >& vec) {
  for (const auto& p : vec) {
    cout << "pair<string, int>(\"" << p.first << "\", " << p.second << "), \n";
  }
  cout << endl;
}

bool Repeated(const string& raw, const string& query) {
  int idx = raw.find(query);
  if (idx == string::npos) {
    return false;
  }
  return raw.find(query, idx + query.size()) != string::npos;
}

int CommonPrefix(const string& input1, const string& input2) {
  int i = 0;
  for (; i < min(input1.size(), input2.size()); ++i) {
    // It may reach the entire string and still match.
    if (input1[i] != input2[i]) {
      return i;
    }
  }
  return i;
}

int main() {
  string input = "aaabbbaaabbbaaacccdddcccddd";

  // Build suffix tree.
  vector<string> vec;
  for (int i = 0; i < input.length(); ++i) {
    vec.emplace_back(input.substr(i, input.length()-i));
  }
  sort(vec.begin(), vec.end());

  // Find all common prefix and repeatable in original input string.
  vector<pair<string, int>> vec2;
  unordered_set<string> processed;
  for (int i = 1; i < vec.size(); i++) {
    int k = CommonPrefix(vec[i-1], vec[i]);
    if (k == 0) {
      continue;
    }
    int delta = vec[i-1].size() - vec[i].size();
    if (delta < 0) delta = -delta;
    if (delta < k) {
      // overlap
      continue;
    }
    const string s = vec[i].substr(0, k);
    if (processed.count(s) > 0) {
      continue;
    }
    processed.insert(s);
    // It seems to be not necessary to check Repeated() again since the delta is done.
    if (Repeated(input, s)) {
      vec2.emplace_back(pair<string, int>(s, s.size()));
    }
  }

  Print(vec2);

  std::sort(vec2.begin(), vec2.end(),
            [](const pair<string, int>& p1, const pair<string, int>& p2) {
              cout << p1.first << "," << p1.second << " vs "
                   << p2.first << "," << p2.second << endl;
              if (p1.second > p2.second) {
                return true;
              }
              if (p1.first < p2.first) {
                return true;
              }
              return false;
            });

  Print(vec2);
}
