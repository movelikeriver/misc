// From http://www.careercup.com/question?id=6361609643491328
//
// Store a set of sudden-death tournament results in a compact format
// (eg. a bit array) and a set of predicted match results (also in a
// bit array). Score the predictions, giving one point per correctly
// guessed match, without unpacking the bit array into a more
// convenient format (ie. you have to traverse the tree in-place).
//
//
// For example:
/*
 If the prediction is:
        A
    A   -    F
  A - C    F - G
 A-B C-D  E-F G-H

 Represented as 1111101 (from top to bottom)

 But the final result is:
        A
    A   -    H
  A - D    E - H
 A-B C-D  E-F G-H

 Represented as 1101010 (from top to bottom)

 The correctly guessed matches (in other words, the winners) are:  A-F, A-C, A-B
*/

#include <iostream>
#include <vector>
using namespace std;

int Guess(const vector<bool>& result,
	  vector<bool>& prediction) {
  int cnt = 0;
  for (int i = result.size()-1; i >= 0; --i) {
    if (result[i] == prediction[i]) {
      if (i >= result.size()/2) {
	cnt++;
	continue;
      }

      int left = i*2 + 1;
      int right = i*2 + 2;
      if ((result[i] && (result[left] == prediction[left])) ||
	  (!result[i] && (result[right] == prediction[right]))) {
	// the correct winner in previous round match
	cnt++;
      } else {
	// mark it as wrong result, then next round can't be true.
	prediction[i] = !prediction[i];
      }
    }
  }
  return cnt;
}

int main() {
  bool a[] = {1,1,1,1,1,0,1};
  bool b[] = {1,1,0,1,0,1,0};
  vector<bool> prediction(a, a + sizeof(a)/sizeof(a[0]));
  vector<bool> result(b, b + sizeof(b)/sizeof(b[0]));
  cout << Guess(result, prediction) << endl;
}
