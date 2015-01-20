// How many choices for Android lock pattern?

#include <iostream>
#include <vector>
#include <map>
using namespace std;

static const int kMinValidDigits = 4;

class Solution {
public:
  Solution() {
    // Given panel like:
    //
    // 0 1 2
    // 3 4 5
    // 6 7 8
    //
    // 0-2 becomes valid if and only if 1 has been visited.
    int arr[] = {(1 << 0) | (1 << 2), 1,
		 (1 << 3) | (1 << 5), 4,
		 (1 << 6) | (1 << 8), 7,
		 (1 << 0) | (1 << 6), 3,
		 (1 << 1) | (1 << 7), 4,
		 (1 << 2) | (1 << 8), 5,
		 (1 << 0) | (1 << 8), 4,
		 (1 << 2) | (1 << 6), 4};
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i+=2) {
      skip_points_[arr[i]] = arr[i+1];
    }
  }

  // the basic idea is to try points of 0, 1, 4 as start points with
  // backtrace approach, use saved map to save the previous result to
  // avoid computing again:
  //
  // 0 1 X
  // X 4 X
  // X X X
  int Compute() {
    map<int, int> saved;
    return (Pattern(0, 1, 1, &saved) * 4 +
	    Pattern(1, 1 << 1, 1, &saved) * 4 +
	    Pattern(4, 1 << 4, 1, &saved));
  }

private:
  // point belongs to [0, 8]
  bool IsVisited(int point, int visited_points) {
    return (1 << point) & visited_points;
  }

  // param visited represents the bool visit[9] of points.
  int Pattern(int point, int visited_points, int visited_num,
	      map<int, int>* saved) {
    if (saved->count(visited_points) > 0) {
      // computed previously.
      return (*saved)[visited_points];
    }
    int count = 0;
    if (visited_num >= kMinValidDigits) {
      count += 1;
    }
    vector<int> neighbours = GetNeighbours(point, visited_points);
    for (int v : neighbours) {
      if (IsVisited(v, visited_points)) {
	continue;
      }
      count += Pattern(v, visited_points | (1 << v), visited_num + 1, saved);
    }
    (*saved)[visited_points] = count;
    return count;
  }

  vector<int> GetNeighbours(int point, int visited_points) {
    vector<int> ret;
    for (int i = 0; i < 9; i++) {
      if (i == point) {
	continue;
      }
      if (IsVisited(i, visited_points)) {
	continue;
      }
      // e.g. from 0 to 2, but 1 is not visited yet.
      if (!CanSkip(point, i, visited_points)) {
	continue;
      }
      ret.push_back(i);
    }
    return ret;
  }

  bool CanSkip(int p1, int p2, int visited_points) {
    int s = min(p1, p2);
    int l = max(p1, p2);
    int m = Between(s, l);
    if (m < 0) {
      // no worry about any point to skip, that's safe.
      return true;
    }
    return IsVisited(m, visited_points);
  }

  // any point between small and large in the panel?
  int Between(int small, int large) {
    int key = (1 << small) | (1 << large);
    if (skip_points_.count(key) == 0) {
      return -1;
    }
    return skip_points_[key];
  }

  map<int, int> skip_points_;
};

int main() {
  int v = 1;
  for (int i = 0; i < kMinValidDigits; i++) {
    v *= 10;
  }
  cout << kMinValidDigits << " passwords: " << v << "\n";
  Solution s;
  cout << "Android pattern with at lease " << kMinValidDigits << " digits: "
       << s.Compute() << endl;
}
