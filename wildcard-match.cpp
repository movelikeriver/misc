#include <assert.h>

#include <iostream>
using namespace std;


bool wildcard(const string& input, const int s1,
	      const string& pattern, const int s2) {
  if (input.size() == s1 && pattern.size() == s2) {
    // to the end
    return true;
  }
  if (input[s1] == pattern[s2]) {
    // input++ and pattern++
    return wildcard(input, s1+1, pattern, s2+1);
  }

  if (pattern[s2] == '*') {
    if (pattern.size() == (s2+1)) {
      // to the end
      return true;
    }
    if (pattern[s2+1] != input[s1]) {
      // input++
      return wildcard(input, s1+1, pattern, s2);
    }

    // For "abcdedc" vs "a*dc", we need to check both "edc" vs "dc"
    // and "edc" vs "*dc".
    if (wildcard(input, s1+1, pattern, s2+2)) {
      return true;
    }

    if (wildcard(input, s1+1, pattern, s2)) {
      return true;
    }
  }

  return false;
}


int main() {
  assert(wildcard("abcdedc", 0, "a*dc", 0));
  cout << "PASS!" << endl;
}
