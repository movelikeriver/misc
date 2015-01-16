// Compute and return the square root of double X.

#include <cmath>
#include <iostream>
using namespace std;

const double kEpsilon = 0.00001;

bool Equal(double a1, double a2, double epsilon) {
  if (abs(a1 - a2) < epsilon) {
    return true;
  }
  return false;
}

double BinSearch(double input, double high, double low, double epsilon) {
  // binary search
  while (true) {
    double mid = (high + low) / 2;
    double v = mid * mid;
    if (Equal(v, input, epsilon)) {
      return mid;
    }
    if (v > input) {
      high = mid;
    } else {
      low = mid;
    }
  }
}

double Sqrt(double input) {
  if (input < 0 ||
      Equal(input, 0.0, kEpsilon) ||
      Equal(input, 1.0, kEpsilon)) {
    return input;
  }
  if (input > 1) {
    return BinSearch(input, input / 2, 1, kEpsilon);
  } else {
    return BinSearch(input, 1, input / 2, kEpsilon);
  }
}

int main() {
  double arr[] = {0.04, 0, 1, 16, 3600};
  for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
    double a = arr[i];
    cout << Sqrt(a) << ": " << a << "\n";
  }
}
